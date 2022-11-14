#include <QCoreApplication>

#include "chatserver.h"

#include "pipeclass.h"

HANDLE MutexSocket, MutexPipe, MutexSendMessage;

//Сокет має бути в одному потоці, а пайпа, може бути окремо де завгодно.


//Глобальна змінна, яка буде давати сигнал від пайпи
//Сокету, що можна писати дані в сокет.
bool IsWritten = false;

//Глобальний вказівник на сокетсервер, для того, щоб пайпа могла передати
//повідомлення
ChatServer * SocketServer;

DWORD WINAPI PipeCommunication(LPVOID lpParameter)
{
  PipeClass * PipeServer = (PipeClass *)lpParameter;
  PipeServer->CreatePipe();
  // Мютекс який створюється в клієнті і він дає сигнал,
  // Коли можна читати повідомлення на сервері.
  MutexSendMessage = OpenMutexW(MUTEX_ALL_ACCESS, 0, TEXT("Mutex_Send"));
      while(true)
        {
          WaitForSingleObject(MutexSendMessage, INFINITE);
          PipeServer->ReadPipe();
          IsWritten = true;
          ReleaseMutex(MutexSendMessage);
        }
  delete PipeServer;
}


// Серверний сокет може писати і клієнт може легко читати.
// Якщо навпаки треба юзати waitforReadyRead() хоча б на одну мс
// треба тоді придумати синхронізацію і відправку повідомлень
DWORD WINAPI SocketCommunication(LPVOID lpParameter)
{
  // Мютекс для сокета, який дає сигнал клієнту, що написано повідомлення.
  // Клієнт відкриває мютекс в потоці, який вічно очікує повідомлення.
  // При отриманні сигналу зчитує повідомлення, захоплює мютекс
  // і після зчитування звільняє мютекс. І сервер знов захоплює мютекс.
  // Аналогічно для мютекса для пайпи
  MutexSocket = CreateMutexW(NULL, 1, TEXT("Mutex_Socket"));
  MutexPipe = CreateMutexW(NULL, 1, TEXT("Mutex_Pipe"));
  PipeClass * PipeServer = (PipeClass *)lpParameter;
  ChatServer * SocketServer = new ChatServer;
  SocketServer->StartServer();
  SocketServer->waitForNewConnection(INFINITY);
  while(true)
    {
      while(!SocketServer->SocketRead())
        {
          if(IsWritten)
            {
              SocketServer->SetListOfMessages(PipeServer->GetListOfMessages());
              SocketServer->SocketWrite();
              IsWritten = false;
              ReleaseMutex(MutexSocket);
              WaitForSingleObject(MutexSocket, INFINITE);
            }
        }
      PipeServer->SetListOfMessages(SocketServer->GetListOfMessages());
      PipeServer->WritePipe();
      ReleaseMutex(MutexPipe);
      WaitForSingleObject(MutexPipe, INFINITE);
    }
  delete SocketServer;
}

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  QThread * SocketThread;
  QThread * PipeThread;
  PipeClass * PipeServer = new PipeClass;
  SocketThread = QThread::create(SocketCommunication, PipeServer);
  SocketThread->start();
  PipeThread = QThread::create(PipeCommunication, PipeServer);
  PipeThread->start();
  return a.exec();
}



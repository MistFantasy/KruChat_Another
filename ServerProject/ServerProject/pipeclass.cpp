#include "pipeclass.h"

PipeClass::PipeClass()
{
  strcpy(szBuffer, "\0");
}

void PipeClass::SetListOfMessages(QVector<MessageStruct> ListOfMessages)
{
  m_ListOfMessages = ListOfMessages;
}

QVector<MessageStruct> PipeClass::GetListOfMessages() const
{
  return m_ListOfMessages;
}

void PipeClass::WritePipe()
{
  DWORD dwNoBytesWrite;
  // Очищення буфера
  BOOL bFlushFileBuffer;
  // Запис у Pipe
  strcpy(szBuffer, m_ListOfMessages.last().to_cString().data());
   WriteFile(
   Pipe,
   szBuffer,
   sizeof(szBuffer),
   &dwNoBytesWrite,
   NULL
  );
  // Почистити буфер
  //bFlushFileBuffer = FlushFileBuffers(Pipe);
  qDebug() << "Message from Socket: " <<
              m_ListOfMessages.last().to_cString().data() << " sended to Pipe";
  strcpy(szBuffer, "\0");
}

bool PipeClass::ReadPipe()
{
  DWORD dwNoBytesRead;
  bool PipeIsReaded = true;
  strcpy(szBuffer, "\0");
  // Читання з Pipe
   ReadFile(
   Pipe,
   szBuffer,
   sizeof (szBuffer),
   &dwNoBytesRead,
   NULL
  );
  if(szBuffer[0] == '\0')
    PipeIsReaded = false;
  if(PipeIsReaded)
    {
      qDebug() << "DATA READING FROM Pipe -> " << szBuffer;
      m_ListOfMessages.append(fromString(szBuffer));
    }
  return PipeIsReaded;
}

void PipeClass::PipeDisconnect()
{
  // Відключаємо Pipe
  DisconnectNamedPipe(Pipe);

  // Закриваємо хендл
  CloseHandle(Pipe);
}

void PipeClass::CreatePipe()
{
   qDebug() << "NAMED PIPE SERVER\n*****************";
   DWORD dwNoBytesWrite;
   // Булева змінна для позначення чи Pipe законектився
   BOOL bConnectNamedPipe = false;
   HANDLE MutexCreationPipe = nullptr;
   // Створення Pipe
   Pipe = CreateNamedPipe
   (
    L"\\\\.\\pipe\\MYNAMEDPIPE",
    PIPE_ACCESS_DUPLEX,
    PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_NOWAIT,
    PIPE_UNLIMITED_INSTANCES,
    sizeof (szBuffer),
    sizeof (szBuffer),
    0,
    NULL
   );
   if (Pipe == INVALID_HANDLE_VALUE)
   {
    qDebug() << "NamedPipe creation failed with error number: " << GetLastError();
   }
   else
     qDebug() << "NamedPipe creation is successful";

   // Підключення Pipe
   //bConnectNamedPipe = ConnectNamedPipe(Pipe, NULL);
   while(!MutexCreationPipe)
     {
       MutexCreationPipe = OpenMutexW(MUTEX_ALL_ACCESS, 0, TEXT("Mutex_Creation"));
     }
   CloseHandle(MutexCreationPipe);
   bConnectNamedPipe = ConnectNamedPipe(Pipe, NULL);
   qDebug() << "ConnectNamedPipe connection is successful: " << GetLastError();
}

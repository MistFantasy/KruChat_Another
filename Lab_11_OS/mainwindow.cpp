#include "mainwindow.h"
#include "ui_mainwindow.h"

HANDLE MutexSocketClient;

DWORD WINAPI WaitForMessages(LPVOID lpParameter)
{
  MutexSocketClient = OpenMutexW(MUTEX_ALL_ACCESS, 0, TEXT("Mutex_Socket"));
  Socket * ChatReceiver = (Socket *)lpParameter;
  while(true)
    {
      WaitForSingleObject(MutexSocketClient, INFINITE);
      qDebug() << ChatReceiver->getData().to_cString().data();
      ReleaseMutex(MutexSocketClient);
      Sleep(100);
    }
}

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  srand(time(NULL));
//
//     if(rand() % 2)
//       {
//         Chat = new Socket();
//         User = "Denys";
//       }
//     else
//       {
//         Chat = new Pipe();
//         User = "Nastya";
//       }
  Chat = new Socket();
  User = "Denys";
  HANDLE WaitForMessageThread;
  DWORD WaitForMessageThreadID;
  WaitForMessageThread = CreateThread(NULL, 0, WaitForMessages,
                                      Chat, 0, &WaitForMessageThreadID);
}

MainWindow::~MainWindow()
{
  delete ui;
  //delete Chat;
}

void MainWindow::on_pushButton_clicked()
{
    MessageStruct message(User, ui->lineEdit->text(), QTime().currentTime());
    Chat->sendData(message);
}

//void MainWindow::sockDisc()
//{
//    socket->deleteLater();
//}




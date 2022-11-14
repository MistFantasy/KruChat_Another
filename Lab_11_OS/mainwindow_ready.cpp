#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
HANDLE MutexClient;
Dialog user_info;
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{

  ui->setupUi(this);
  ui->tableWidget->setRowCount(0);
  ui->tableWidget->setColumnCount(1);
  user_info.setModal(true);
  user_info.exec();
  srand(time(NULL));
//        connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
//        connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
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
  MutexClient = OpenMutexA(NULL, 0, "Mutex_Client");
  Chat = new Pipe();
  User = "Nastya";
}

MainWindow::~MainWindow()
{
  delete ui;
  //delete Chat;
}

DWORD WINAPI WaitForMessages(LPVOID lpParameter)
{
  ChatAPI * ChatReceiver = (ChatAPI *)lpParameter;
//  while(true)
//    {
      if(ChatReceiver->getData().to_cString().data())
      //WaitForSingleObject(MutexClient, INFINITE);
        qDebug() << ChatReceiver->getData().to_cString().data();
      //ReleaseMutex(MutexClient);
      //Sleep(5000);
//    }
}

void MainWindow::on_pushButton_clicked()
{
    HANDLE WaitForMessageThread;
    DWORD WaitForMessageThreadID;
    QTime time;
    MessageStruct message(user_info.getUser(), ui->lineEdit->text(), QTime().currentTime());
    //std::string str = message.to_cString();
    int row=0;

    Chat->sendData(message);
    WaitForMessageThread = CreateThread(NULL, 0, WaitForMessages,
                                        Chat, 0, &WaitForMessageThreadID);
    //MessageStruct test = fromString(str.data());
    //DualPipe->sendData(test);
    //char * line2 = pipe->getData().to_cString();
    //ui->lineEdit->setText(line2);
}




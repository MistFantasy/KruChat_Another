#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
HANDLE MutexPipeClient, // Мютекс для взаємодії пайпи з сервером
MutexSendMessage,       // Мютекс-сигнал, що повідомлення від пайпи надіслано
MutexCreationPipe,      // Мютекс для з'єднання пайпи з сервером
MutexSocketClient;      // Мютекс для взаємодії сокета з сервером
int SyncMethod = 0;     // Змінна яка вертається з діалогу, яка
                        // містить номер вибраної міжпроцесну взаємодію
int row = 0;
QTableWidget * TableWidget;
QStatusBar * StatusBar;

DWORD WINAPI WaitForMessages(LPVOID lpParameter)
{
  MutexSocketClient = OpenMutexW(MUTEX_ALL_ACCESS, 0, TEXT("Mutex_Socket"));
  MutexPipeClient = OpenMutexW(MUTEX_ALL_ACCESS, 0, TEXT("Mutex_Pipe"));
  ChatAPI * ChatReceiver = (ChatAPI *)lpParameter;
  MessageStruct message;
  while(true)
    {
      switch(SyncMethod)
        {
          case 0:
          {
            WaitForSingleObject(MutexPipeClient, INFINITE);
            message = ChatReceiver->getData();
            ReleaseMutex(MutexPipeClient);
            break;
          }
          case 1:
          {
            WaitForSingleObject(MutexSocketClient, INFINITE);
            message = ChatReceiver->getData();
            ReleaseMutex(MutexSocketClient);
            break;
          }
        }
      if(message.m_sendTime.hour() == -1 ||
         message.m_sendTime.minute() == -1)
        {
          StatusBar->showMessage("Ви відключились від сервера.");
        }
      else
        {
          StatusBar->showMessage("");
          TableWidget->insertRow(TableWidget->rowCount());
          QTableWidgetItem *item = new QTableWidgetItem(
                "\n" + message.m_userName
            + "\n"+message.m_message+"\n"
            + QString::number(message.m_sendTime.hour())
            +":" + QString::number(message.m_sendTime.minute()));
          item->setTextAlignment(Qt::AlignLeft);
          TableWidget->setItem(row++, 0, item);
          TableWidget->resizeRowsToContents();
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  TableWidget = ui->tableWidget;
  StatusBar = ui->statusBar;
  QHeaderView* header = ui->tableWidget->horizontalHeader();
  header->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableWidget->setRowCount(0);
  ui->tableWidget->setColumnCount(1);
  Dialog user_info(&User, &SyncMethod, this);
  user_info.setModal(true);
  user_info.exec();
  this->setWindowTitle("KruChat / " + User);
  switch(SyncMethod)
    {
      case 0:
      {
        Chat = new Pipe();
        MutexSendMessage = CreateMutexW(NULL, 1, TEXT("Mutex_Send"));
        MutexCreationPipe = CreateMutexW(NULL, 0, TEXT("Mutex_Creation"));
        break;
      }
      case 1:
      {
        Chat = new Socket();
        break;
      }
    }
  row = 0;
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
  ui->tableWidget->insertRow(ui->tableWidget->rowCount());
  MessageStruct message(User, ui->lineEdit->text(), QTime().currentTime());
  QTableWidgetItem *item = new QTableWidgetItem(
    message.m_message+"\n"
    + QString::number(message.m_sendTime.hour())
    +":" + QString::number(message.m_sendTime.minute()));
  item->setTextAlignment(Qt::AlignRight);
  ui->tableWidget->setItem(row++, 0, item);
  ui->lineEdit->setText("");
  ui->tableWidget->resizeRowsToContents();
  Chat->sendData(message);
  switch(SyncMethod)
  {
    case 0:
      {
        ReleaseMutex(MutexSendMessage);
        WaitForSingleObject(MutexSendMessage, INFINITE);
        break;
      }
  }
}





#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "socket.h"
#include "Pipe.h"
#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <windows.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public slots:
  void sockReady();
  void sockDisc();

private slots:
  void on_pushButton_clicked();

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QTcpSocket* socket;
  QByteArray Data;
  HANDLE hCreateNamedPipe;
  char szInputBuffer[1023];
  char szOutputBuffer[1023];
  DWORD dwszInputBuffer = sizeof(szInputBuffer);
  DWORD dwszOutputBuffer = sizeof(szOutputBuffer);
//  void CreateServerSocket();
//  void CreateSocket();
  //  void WaitForSocket();
  void PipeMessage();
private:
  Ui::MainWindow *ui;
//  WSADATA WSA;
//  SOCKET Master, New_Socket, ClientSocket, S;
//  struct sockaddr_in Server, Address;
//  int Activity, Addrlen, i, valread;
//  fd_set Readfds;

};
#endif // MAINWINDOW_H

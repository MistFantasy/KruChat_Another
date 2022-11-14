#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "socket.h"
#include "Pipe.h"
#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <windows.h>
#include <memoryapi.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

private slots:
  void on_pushButton_clicked();

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  char szInputBuffer[SIZEOFBUFFER];
  char szOutputBuffer[SIZEOFBUFFER];
  void PipeMessage();
  void WaitForMessage();
private:
  Ui::MainWindow *ui;
  ChatAPI * Chat;
  QString User;
};
#endif // MAINWINDOW_H

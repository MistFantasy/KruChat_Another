#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "socket.h"
//#include "Pipe.h" Підключити коли збирати в один проект
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

public slots:
  //void sockReady();
  //void sockDisc();

private slots:
  void on_pushButton_clicked();

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
private:
  Ui::MainWindow *ui;
  Socket * Chat;
  QTcpSocket * socket;
  QString User;
};
#endif // MAINWINDOW_H

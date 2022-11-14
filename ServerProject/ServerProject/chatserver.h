#ifndef CHATSERVER_H
#define CHATSERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <windows.h>
#include "MessageStruct.h"
#include "pipeclass.h"
#include <QThread>
class ChatServer : public QTcpServer
{
  Q_OBJECT
public:
  ChatServer();
  ~ChatServer();
  QTcpSocket * GetSocket();
  void SocketWrite();
  void SetListOfMessages(QVector<MessageStruct> ListOfMessages);
  QVector<MessageStruct> GetListOfMessages() const;
public slots:
  bool SocketRead();
  void StartServer();
  void incomingConnection(qintptr SocketDescriptor);
  void SocketDisconnection();
private:
  QTcpSocket * Socket;  //QVector<QTcpSocket *>
  QVector<MessageStruct> m_ListOfMessages;
};

#endif // CHATSERVER_H

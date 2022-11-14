#include "chatserver.h"
#include "chatserver.h"

//QAbstractSocket::flush() необхідний для того, щоб точно передати дані
//бо в інакшому випадку вони є забуферизовані і не передаються

ChatServer::ChatServer() : Socket(nullptr)
{
}

ChatServer::~ChatServer()
{
}

void ChatServer::StartServer()
{
  //Socket->bind(0.0.0.0, 5555);
  if(this->listen(QHostAddress::Any, 5555)) //QHostAdress localHost
    qDebug() << "Server Listening\n";
  else
    qDebug() << "Server not Listening\n";
}

void ChatServer::incomingConnection(qintptr SocketDesriptor)
{
  Socket = new QTcpSocket(this);
  Socket->setSocketDescriptor(SocketDesriptor);
    connect(Socket, SIGNAL(disconnected()), this, SLOT(SocketDisconnection()));
  qDebug() << SocketDesriptor << " Client connected;\n";
}

bool ChatServer::SocketRead()
{
  bool SocketIsReaded = false;
  if(Socket)
    {
      SocketIsReaded = true;
      QByteArray IncomingData;
      Socket->waitForReadyRead(1);
      IncomingData = Socket->readAll();
      if(IncomingData.size() == 0)
        SocketIsReaded = false;
      if(SocketIsReaded)
        {
          qDebug() << "Message from Socket: " << IncomingData;
          m_ListOfMessages.append(fromString(IncomingData.data()));
        }
    }
  return SocketIsReaded;
}

void ChatServer::SocketWrite()
{
  Socket->write(m_ListOfMessages.last().to_cString().data());
  Socket->flush();
  qDebug() << "Message from Pipe: " <<
              m_ListOfMessages.last().to_cString().data()
           << " sended to Socket";
}

void ChatServer::SetListOfMessages(QVector<MessageStruct> ListOfMessages)
{
  m_ListOfMessages = ListOfMessages;
}

QVector<MessageStruct> ChatServer::GetListOfMessages() const
{
  return m_ListOfMessages;
}

void ChatServer::SocketDisconnection()
{
  qDebug() << "Disconnect";
  Socket->deleteLater();
}

QTcpSocket * ChatServer::GetSocket()
{
  return Socket;
}



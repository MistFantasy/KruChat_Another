#include "socket.h"

Socket::Socket()
{
    m_socket = new QTcpSocket();
    if(m_socket)
      {
        m_socket->connectToHost(QHostAddress::LocalHost, 5555);
        qDebug() << "Socket connected: " << m_socket->waitForConnected(INFINITY);
      }
}

bool Socket::sendData(MessageStruct message)
{
    QByteArray SendDataBuffer = message.to_cString().data();
    m_socket->write(SendDataBuffer);
    m_socket->flush();
}

MessageStruct Socket::getData()
{
    QByteArray GetDataBuffer;
    GetDataBuffer = m_socket->readAll();
    return fromString(GetDataBuffer.data());
}

QTcpSocket *Socket::GetSocket() const
{
  return m_socket;
}

Socket::~Socket()
{

}

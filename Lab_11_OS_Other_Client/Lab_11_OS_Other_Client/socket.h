#include "ChataAPI.h"
#include "MessageStruct.h"
#include <QTcpServer>
#include <QTcpSocket>
#ifndef SOCKET_H
#define SOCKET_H


class Socket : public ChatAPI
{
private:
    QTcpSocket* m_socket;
public slots:
    //void sockDisc();
public:
    Socket();
    bool sendData(MessageStruct message);
    MessageStruct getData();
    QTcpSocket * GetSocket() const;
    ~Socket();
};

#endif // SOCKET_H

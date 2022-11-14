#include <QString>
#include <QTime>
#ifndef MESSAGESTRUCT_H
#define MESSAGESTRUCT_H
#define SIZEOFBUFFER 1024
#define NAMEUSER 20
#define TIME 10
struct MessageStruct
{
    MessageStruct();
    MessageStruct(QString userName, QString message, QTime sendTime);
    QString m_userName;
    QString m_message;
    QTime m_sendTime;
    friend MessageStruct fromString(char * str);
    std::string to_cString();
};

MessageStruct fromString(char * str);
#endif // MESSAGESTRUCT_H

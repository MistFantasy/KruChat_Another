#include "MessageStruct.h"
#include <string.h>
MessageStruct::MessageStruct()
{

}

MessageStruct::MessageStruct(QString userName, QString message, QTime sendTime)
    :m_userName(userName), m_message(message), m_sendTime(sendTime)
{

}

std::string MessageStruct::to_cString()
{
   //Структура повідомлення "user|message|time"
    QString str;
    str.append(m_userName);
    str.append("|");
    str.append(m_message);
    str.append("|");
    str.append(m_sendTime.toString("hh:mm"));
    str.append('\0');
    return str.toStdString();
}

MessageStruct fromString(char *str)
{
    MessageStruct message;
    char *line;
    line = strtok(str, "|");
    message.m_userName = line;
    line = strtok(NULL, "|");
    message.m_message = line;
    line = strtok(NULL, "\0");
    QString TempTime;
    TempTime.append(line);
    message.m_sendTime = QTime::fromString(TempTime, "hh:mm");
    return message;
}

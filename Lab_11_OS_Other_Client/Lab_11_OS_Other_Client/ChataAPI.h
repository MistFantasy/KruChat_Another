#include "MessageStruct.h"

#ifndef CHATAAPI_H
#define CHATAAPI_H

class ChatAPI
{
public:
    virtual bool sendData(MessageStruct message) = 0;
    virtual MessageStruct getData() = 0;
    //virtual ~ChatAPI() = 0;
};

#endif // CHATAAPI_H

#include "ChataAPI.h"
#ifndef PIPE_H
#define PIPE_H
#include <windows.h>
#include "MessageStruct.h"
class Pipe: public ChatAPI
{
public:
    Pipe();
    HANDLE hCreateFile;
    BOOL bReadFile;
    DWORD dwNoBytesRead;
    char szReadFileBuffer[SIZEOFBUFFER];
    DWORD dwReadFileBufferSize = sizeof(szReadFileBuffer);
    BOOL bWriteFile;
    DWORD dwNoBytesWrite;
    char szWriteFileBuffer[SIZEOFBUFFER];
    DWORD dwWriteFileBufferSize = sizeof(szWriteFileBuffer);

//    void ReadData();
//    void WriteData();


    bool sendData(MessageStruct message) override;
    MessageStruct getData() override;
};
#endif // PIPE_H

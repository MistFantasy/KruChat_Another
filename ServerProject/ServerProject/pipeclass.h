#ifndef PIPECLASS_H
#define PIPECLASS_H
#include <windows.h>
#include "MessageStruct.h"
class PipeClass
{
public:
  PipeClass();
  void PipeDisconnect();
  bool ReadPipe();
  void CreatePipe();
  void WritePipe();
  char szBuffer[SIZEOFBUFFER];
  void SetListOfMessages(QVector<MessageStruct> ListOfMessages);
  QVector<MessageStruct> GetListOfMessages() const;
private:
  HANDLE Pipe; // QVector<HANDLE>
  QVector<MessageStruct> m_ListOfMessages;
};

#endif // PIPECLASS_H

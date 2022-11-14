#include "Pipe.h"
#include <QDebug>


Pipe::Pipe()
{
        hCreateFile = CreateFile(
         L"\\\\.\\pipe\\MYNAMEDPIPE",
         GENERIC_READ | GENERIC_WRITE,
         0,
         NULL,
         OPEN_EXISTING,
         FILE_ATTRIBUTE_NORMAL,
         NULL
        );
        if (INVALID_HANDLE_VALUE == hCreateFile)
        {
        qDebug()<< "NamedPipeCreateFile.txt file creation has failed with error number: " << GetLastError();
        }
        qDebug()<< "NamedPipeCreateFile.txt file creation is successful\n";
};

MessageStruct Pipe::getData()
{
  MessageStruct Structure;
  bReadFile = ReadFile(
    hCreateFile,
    szReadFileBuffer,
    dwReadFileBufferSize,
    &dwNoBytesRead,
    NULL
    );
  if (bReadFile == FALSE)
    {
      qDebug() << "ReadFile has failed with error number: " << GetLastError();
    }
  qDebug()<< "ReadFile is successful\n";
  Structure = fromString(szReadFileBuffer);
  qDebug()<< "DATA READING FROM SERVER -> " +
             QString::fromStdString(Structure.to_cString().data());
  return Structure;
}

bool Pipe::sendData(MessageStruct message)
{
  bWriteFile = WriteFile(
     hCreateFile,
     message.to_cString().data(),
     dwWriteFileBufferSize,
     &dwNoBytesWrite,
     NULL
    );
    if (bWriteFile == FALSE) {
     qDebug() << "WriteFile has failed with error number: " << GetLastError();
    }
    qDebug() << "WriteFile is successful\n";
    return bWriteFile;
}


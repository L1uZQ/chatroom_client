#ifndef DATAPARSER_H
#define DATAPARSER_H
#include"config.h"

class dataparser
{
    //数据头部——协议号(1B)-账号(2B)-数据类型(1B)-数据长度(4B)-数据
private:
    char *bp;
    unsigned int protocolId;
    unsigned int account;
    unsigned int dataType;
    unsigned int dataLength;

    unsigned int parseInt(int len);

public:
    dataparser(char * buffer);

    bool baseParse();

    unsigned int getProtocolId();
    unsigned int getAccount();
    unsigned int getDataType();
    unsigned int getDataLength();

    ~dataparser();

};

#endif // DATAPARSER_H

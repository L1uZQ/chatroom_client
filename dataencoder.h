#pragma once
#ifndef DATAENCODER_H
#define DATAENCODER_H
#include"config.h"
#include<QString>

using namespace std;

class dataencoder
{
private:
    char head[BASE_BUFFER_SIZE];
    char * hp;
    void encodeElement(unsigned int data, unsigned int len);


public:
    dataencoder();
    string encode(unsigned int protocolid,unsigned int account, unsigned int datatype, unsigned int datalength);
};

#endif // DATAENCODER_H

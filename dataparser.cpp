#include "dataparser.h"

dataparser::dataparser(char * buffer)
{
    bp = buffer;
}

bool dataparser::baseParse()
{
    this->protocolId = parseInt(PROTOCOL_ID_SIZE);
    this->account = parseInt(ACCOUNT_SIZE);
    this->dataType = parseInt(DATA_TYPE_SIZE);
    this->dataLength = parseInt(DATA_SIZE);
}

unsigned int dataparser::parseInt(int len)
{
    unsigned int sum = 0;
    unsigned int i=0;
    for(char *end = bp+len-1; bp<=end; end--)
    {
        sum = sum + (((unsigned int)((unsigned char)(*end))) << i);
        i += 8;
    }
    bp = bp+len;
    return sum;
}

unsigned int dataparser::getProtocolId() {
    return this->protocolId;
}
unsigned int dataparser::getAccount() {
    return this->account;
}
unsigned int dataparser::getDataType() {
    return this->dataType;
}
unsigned int dataparser::getDataLength() {
    return this->dataLength;
}

dataparser::~dataparser() {

}

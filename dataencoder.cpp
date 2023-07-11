#include "dataencoder.h"
#include<QDebug>
dataencoder::dataencoder()
{

}

string dataencoder::encode(unsigned int protocolid, unsigned int account, unsigned int datatype, unsigned int datalength)
{
    hp = head;
    encodeElement(protocolid, PROTOCOL_ID_SIZE);
    encodeElement(account, ACCOUNT_SIZE);
    encodeElement(datatype, DATA_TYPE_SIZE);
    encodeElement(datalength, DATA_SIZE);
    return string(head,sizeof(head));
}

void dataencoder::encodeElement(unsigned int data, unsigned int len)
{
    char* c = hp + len - 1;
    for (int i = len; i > 0; i--) {
        *c = (char)(data & 0xff);
        c--;
        data >>= 8;
    }
    hp = hp + len;
}

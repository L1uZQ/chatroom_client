#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include<QTcpSocket>
#include<QDebug>
#include<QJsonObject>
#include<QJsonDocument>

#include"dataencoder.h"
#include"dataparser.h"
#include"config.h"

#define TCP_BUFFER_SIZE 8192

class client
{
public:

    QString hostName;
    quint16 port;
    QTcpSocket tcpClient;
    char buffer[TCP_BUFFER_SIZE];
    unsigned int protocolId;
    unsigned int account;
    unsigned int datatype;
    unsigned int datalength;
    const string ACK_PACKET = dataencoder().encode(ACK,0,0,0);
    
public:
    client();
    void recvHeadData(); //从服务器接收的数据头
    
    QJsonObject recvServerMsg(); //接收服务器数据
    
    //向服务器发送文本
    void sendText(unsigned int account, string text, unsigned int protocolId = SEND);
    
    void closeTcpSocket(); //关闭连接
    
    QTcpSocket * getTcpClient();
    
    ~client();

};

#endif // CLIENT_H

#include "client.h"

client::client()
{

}

//接收服务器的数据
QJsonObject client::recvServerMsg()
{
    recvHeadData();
    tcpClient.read(buffer, datalength);
    QString serverMsg = QString::fromStdString(string(buffer,datalength));
    QJsonObject serverInfoObj = QJsonDocument::fromJson(serverMsg.toUtf8()).object();
    return serverInfoObj;
}

void client::recvHeadData()
{
    int size = tcpClient.read(buffer, BASE_BUFFER_SIZE);
    //对服务器编码的数据头进行解码
    dataparser parser(buffer);
    parser.baseParse();
    protocolId = parser.getProtocolId();
    account = parser.getAccount();
    datatype = parser.getDataType();
    datalength = parser.getDataLength();
}

void client::sendText(unsigned int account, string text, unsigned int protocolId)
{
    dataencoder encoder;
    qDebug()<<"输入的字节数"<<text.length();
    string headstr = encoder.encode(protocolId,account,TEXT,text.length());
    tcpClient.write(headstr.data(), headstr.length());
    qDebug()<<"头部大小"<<headstr.length();
    if(text.length()!=0)
    {
        tcpClient.write(text.data(),text.length());
        qDebug()<<"发送成功，数据总大小"<<text.length();
    }
}

QTcpSocket * client::getTcpClient()
{
    return &tcpClient;
}

void client::closeTcpSocket()
{
    tcpClient.disconnectFromHost();
    tcpClient.close();
}


client::~client()
{

}





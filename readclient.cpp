#include "readclient.h"



readclient::readclient()
{

}

readclient * readclient::r_client=nullptr;

readclient * readclient::getTcpSocketClient()
{
    if(r_client==nullptr){
        r_client = new readclient;
        r_client->hostName = QString::fromStdString("43.136.177.64");
        r_client->port = stoi("9007");
        qDebug() << "------------正在连接服务器--------------";
        r_client->tcpClient.connectToHost(r_client->hostName, r_client->port);
        qDebug() << "------------连接服务器成功--------------";
    }
    return r_client;
}

bool readclient::readData()
{
    recvHeadData();

    tcpClient.write(ACK_PACKET.data(), ACK_PACKET.length());
    content = "";
    qDebug() << "----------数据长度-----------" << datalength;
    if(datatype == TEXT){
        readTextContent();
        return true;
    }
    else if(datatype ==IMAGE){

    }
    return false;
}


void readclient::readTextContent()
{
    while(tcpClient.waitForReadyRead(-1))
    {
        unsigned int size = 0;
        qDebug() << "-------readTextContent需要读取的字节数---------" << datalength;
        unsigned int splitDataLength = tcpClient.bytesAvailable();
        unsigned int bufsize = TCP_BUFFER_SIZE;

        while(datalength != 0 && tcpClient.bytesAvailable()){
            qDebug() << "-----------------可读数据------------" << tcpClient.bytesAvailable();
            size = tcpClient.read(buffer, min(bufsize, datalength));
            datalength -= size;
            qDebug() << "-------readTextContent剩余读取的字节数---------" << datalength;
            content = content + string(buffer, size);
        }

        string SPLIT_ACK_PACKET = dataencoder().encode(ACK,account,TEXT,splitDataLength);
        tcpClient.write(SPLIT_ACK_PACKET.data(), SPLIT_ACK_PACKET.length());
        if(datalength == 0){
            switch(protocolId){
                case SEND: emit textDisplayAble();break;
            case NOTICE:notice = content; emit noticeDisplayAble();break;
            case ONLINELIST: emit onlineDisplayAble();break;
            }
            break;
        }
        qDebug() << "-----------readTextContent剩余读取的字节数------" << datalength;
    }
    qDebug() << "读取完毕.......";
}




string readclient::getTextContent(){
    return content;
}

string readclient::getNoticeContent(){
    return notice;
}

string readclient::getImagePath(){
    return imagePath;
}

readclient::~readclient(){
    delete r_client;
    r_client = nullptr;
}





#include "writeclient.h"

writeclient::writeclient()
{

}

writeclient* writeclient::w_client = nullptr;

writeclient * writeclient::getTcpsocketClient()
{
    if(w_client == nullptr)
    {
        w_client = new writeclient;
    }
    w_client->hostName = QString::fromStdString("43.136.177.64");
    w_client->port = stoi("9007");

    qDebug() << "------------正在连接服务器--------------" << w_client->hostName;

    time_t start;
    time(&start);

    w_client->tcpClient.connectToHost(w_client->hostName,w_client->port);
    bool connResult = w_client->tcpClient.waitForConnected(100000);

    time_t end;
    time(&end);
    qDebug()<<"连接时长"<<(end-start);

    if(end-start<8){
        qDebug()<<"连接成功";
    }else{
        w_client  =nullptr;
    }
    return w_client;
}

void writeclient::writeImage(unsigned int account, string imagePath)
{

}


writeclient::~writeclient()
{
    delete w_client;
    w_client = nullptr;
}

#include "readthread.h"
#include "readclient.h"
#include<QTcpSocket>
ReadThread::ReadThread()
{

}

void ReadThread::run(){
//    Client * client = Client::getTcpSocketClient();
//    QTcpSocket * tcpSocket = client->getTcpClient();
    readclient * r_client = readclient::getTcpSocketClient();
    QTcpSocket * tcpSocket = r_client->getTcpClient();
    while(true){
        if(tcpSocket->waitForReadyRead(-1)){
               r_client->readData();
        }
    }
}

#ifndef READCLIENT_H
#define READCLIENT_H

#include <QObject>
#include<QTcpSocket>
#include<cstring>
#include<QJsonDocument>
#include<QJsonObject>
#include<QDebug>

#include"client.h"
#include"dataparser.h"
#include"dataencoder.h"
using namespace std;

class readclient : public QObject, public client
{
    Q_OBJECT
public:
    readclient();
    static readclient * r_client;
    string imagePath;
    string content= "";
    string notice = "";
public:
    static readclient * getTcpSocketClient();

    bool readData();
    void readTextContent();
    void readImageContent();

    string getTextContent();
    string getNoticeContent();
    string getImagePath();

    ~readclient();

signals:
    void textDisplayAble();
    void imageDisplayAble();
    void noticeDisplayAble();
    void onlineDisplayAble();
public slots:

};

#endif // READCLIENT_H

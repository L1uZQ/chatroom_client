#ifndef WRITECLIENT_H
#define WRITECLIENT_H

#include <QObject>
#include<QTcpSocket>
#include<cstring>
#include<QDebug>
#include<QJsonDocument>
#include<QJsonObject>

#include"dataencoder.h"
#include"dataparser.h"
#include "client.h"

class writeclient : public QObject, public client
{
    Q_OBJECT
public:
    writeclient();
    static writeclient * w_client;
public:
    static writeclient * getTcpsocketClient();

    void writeImage(unsigned int account, string imagePath);

    ~writeclient();
signals:

public slots:
};

#endif // WRITECLIENT_H

#ifndef LOGININ_H
#define LOGININ_H

#include <QWidget>
#include<QTcpSocket>
#include<QMessageBox>

#include"dataencoder.h"
#include"readclient.h"
#include"writeclient.h"
#include"user.h"

namespace Ui {
class LoginIn;
}

class LoginIn : public QWidget
{
    Q_OBJECT

public:
    explicit LoginIn(QWidget *parent = nullptr);
    ~LoginIn();
    void connectServer();

private:
    Ui::LoginIn *ui;
    writeclient * w_client = nullptr;
    readclient * r_client = nullptr;
    user * rm_user = nullptr;
    void closeEvent(QCloseEvent * e);
    void sleep(int msec);
};

#endif // LOGININ_H

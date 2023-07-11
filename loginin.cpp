#include "loginin.h"
#include "ui_loginin.h"
#include"registerform.h"
#include<QDebug>
#include"readclient.h"
#include"writeclient.h"
#include"widget.h"
#include <QTimer>

LoginIn::LoginIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginIn)
{
    ui->setupUi(this);

    //登录连接服务器
    connect(ui->LoginInButton,&QPushButton::clicked,this, &LoginIn::connectServer);

    //注册账号
    connect(ui->registerButton,&QPushButton::clicked,this,[=](){
        //连接服务，看不懂这里为什么要连接，先暂时不管
//        w_client = writeclient::getTcpsocketClient();
//        if(w_client==nullptr){
//            qDebug() << "连接服务器超时";
//            QMessageBox::information(this, "登录提示", "连接服务器超时");
//            return;
//        }
        //有bug，这里切换到注册页面之后还要回到登录页面，需要保存一下
        RegisterForm * rf = new RegisterForm;
        rf->loginform = this;
        rf->show();
        this->hide();
    });
}

LoginIn::~LoginIn()
{
    delete ui;
}


//连接服务器，验证账号密码
void LoginIn::connectServer()
{
    qDebug() << "-------------开始连接服务器----------------";
    w_client = writeclient::getTcpsocketClient();
    if(w_client == nullptr){
        qDebug() << "连接服务器超时";
        QMessageBox::information(this, "登录提示", "连接服务器超时");
        return;
    }
    QString account = ui->userid_lineEdit->text();
    qDebug() << "账号:" << account;
    QString password = ui->password_lineEdit->text();
    qDebug() << "密码:" << password;

    QJsonObject information;
    information.insert("account", account);
    information.insert("password", password);
    QJsonDocument doc;
    doc.setObject(information);
    string loginMsg =doc.toJson(QJsonDocument::Compact).toStdString();
    w_client->sendText(account.toUtf8().toInt(), loginMsg, LOGIN);
    w_client->getTcpClient()->waitForReadyRead(-1);

    qDebug() << "收到后台确认信息---------------------";
    QJsonObject serverInfoObj = w_client->recvServerMsg();
    qDebug() << serverInfoObj["status"];
    int status = serverInfoObj["status"].toInt();
    qDebug() << "status:" << status;

    if(status == LOGIN_SUCCESS){
        r_client = readclient::getTcpSocketClient();
        qDebug() << "登陆成功, 开始read端---------";
        //readClient->writeText(account, "", READ);
        Widget * widgetform = new Widget;
        widgetform->loginform = this;
        rm_user = new user(account.toUtf8().toInt(), serverInfoObj["username"].toString());
        widgetform->rm_user = rm_user;
        qDebug() << "account:" << account << "->" << "username:" << serverInfoObj["username"].toString();
        widgetform->disPlayUserInfo();
        widgetform->show(); //切换页面
        r_client->sendText(account.toUtf8().toInt(), "", READ);
        this->hide();
    }
    else if(status == LOGIN_FAIL){
        QMessageBox::information(this, "登录提示", "账号或密码错误,请重试");
    }
    else if(status == LOGIN_EXIST){
        QMessageBox::information(this, "登录提示", "该账号已登录，不可重复登录");
    }
}

void LoginIn::closeEvent ( QCloseEvent * e )
{
    qDebug() << "loginform关闭了";
    int userId = rm_user != nullptr? rm_user->getUserId():0;

    if(r_client != nullptr){
        qDebug() << "readClient关闭了";
        w_client->sendText(userId, "", LOGOUT);
        //确保登出信息能够及时发到服务端
        sleep(300);
        w_client->getTcpClient()->disconnectFromHost();
        sleep(100);
        r_client->getTcpClient()->disconnectFromHost();
        sleep(100);
    }
    else if(w_client != nullptr){
        qDebug() << "writeClient关闭了";
        //确保关闭信息能够及时发到服务端
        w_client->sendText(userId, "", CLOSE);
        sleep(300);
        w_client->getTcpClient()->disconnectFromHost();
        sleep(100);
    }
}


void LoginIn::sleep(int msec){
    QEventLoop eventloop;
    QTimer::singleShot(msec, &eventloop, SLOT(quit()));
    eventloop.exec();
}






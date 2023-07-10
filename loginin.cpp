#include "loginin.h"
#include "ui_loginin.h"
#include"registerform.h"
#include<QDebug>

LoginIn::LoginIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginIn)
{
    ui->setupUi(this);

    //登录连接服务器
    connect(ui->LoginInButton,&QPushButton::clicked,this, &LoginIn::connectServer);

    //注册账号
    connect(ui->registerButton,&QPushButton::clicked,this,[=](){
        //连接服务
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

}

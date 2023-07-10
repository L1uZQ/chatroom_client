#include "registerform.h"
#include "ui_registerform.h"
#include<QMessageBox>
#include<QJsonObject>
#include<QDebug>
#include<QJsonDocument>

RegisterForm::RegisterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterForm)
{
    ui->setupUi(this); // 初始化ui

    //根据正则表达式过滤字符串
    ui->account_lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]{3,6}$")));
    ui->name_lineEdit->setValidator(new QRegExpValidator(QRegExp("[\u4e00-\u9fa5a-zA-Z]{1,9}$")));
    ui->password_lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9a-zA-Z]{6,16}$")));

    connect(ui->submit_pushButton,&QPushButton::clicked,this,[=](){
        QString account = ui->account_lineEdit->text();
        if(account.length()<3){
            QMessageBox::information(this,"提示","账号长度应为3-6位");
            return ;
        }
        if(account.toInt() > 65535){
            QMessageBox::information(this,"注册提示","账号数字不能超过65535");
            return;
        }
        QString username = ui->name_lineEdit->text();
        if(username.length() < 3){
            QMessageBox::information(this,"注册提示","昵称长度应为3-9位");
            return;
        }
        QString password = ui->password_lineEdit->text();
        if(password.length() < 6){
            QMessageBox::information(this,"注册提示","密码长度应为6-16位");
            return;
        }

        QJsonObject information;
        information.insert("account", account);
        information.insert("username", username);
        information.insert("password", password);

        QJsonDocument doc;
        doc.setObject(information);
        QString s = doc.toJson(QJsonDocument::Compact);
        qDebug()<<"测试数据"<<s;


    });

}

RegisterForm::~RegisterForm()
{
    delete ui;
}

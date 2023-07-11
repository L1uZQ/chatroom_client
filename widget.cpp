#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //获取客户端连接
    w_client = writeclient::getTcpsocketClient();
    qDebug() << "开始read端1---------";
    r_client = readclient::getTcpSocketClient();

    //文本数据
    connect(ui->sendTextButton, &QPushButton::clicked, this, [=](){
        QString text = ui->inputTextEdit->toPlainText();
        if(text.trimmed().length()==0)
        {
            QMessageBox::information(this,"发送提示","不能发送空的内容");
            return ;
        }
        w_client->sendText(rm_user->getUserId(), text.toStdString());
        ui->inputTextEdit->clear();
    });

    thread = new ReadThread;
    thread->start();

    connect(r_client,&readclient::textDisplayAble, this, [=](){
        ui->contentListWidget->addItem(QString::fromStdString(r_client->getTextContent()));
    });

    ui->contentListWidget->setIconSize(QSize(200,200));

    connect(ui->exitButton,&QPushButton::clicked,this,[=](){
        thread->exit();
        this->close();
        this->loginform->close();
    });


    connect(r_client,&readclient::noticeDisplayAble,this,[=](){
        ui->noticeListWidget->addItem(QString::fromStdString(r_client->getNoticeContent()));
    });

    connect(r_client, &readclient::onlineDisplayAble, this, [=](){
        ui->onlineListWidget->clear();
        QVariantList onlineList = QJsonDocument::fromJson(QString::fromStdString(r_client->getTextContent()).toUtf8()).toVariant().toList();
        for(auto & user: onlineList){
            QVariantMap map = user.toMap();
            QString element = map["account"].toString() + "\t" + map["username"].toString() + "\t" + map["loginTime"].toString();
            ui->onlineListWidget->addItem(element);
        }
        ui->onlineLabel->setText("当前在线人数(" + QString::number(onlineList.size()) + "人)");
    });


}

Widget::~Widget()
{
    delete ui;
    delete rm_user;
}

void Widget::disPlayUserInfo()
{

}

void Widget::closeEvent(QCloseEvent *e)
{
    thread->exit();
    this->loginform->close();
}


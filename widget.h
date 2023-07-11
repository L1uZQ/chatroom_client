#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"writeclient.h"
#include"loginin.h"
#include"readclient.h"
#include"user.h"
#include"readthread.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void disPlayUserInfo();
    LoginIn * loginform;
    user * rm_user = nullptr;
private:
    Ui::Widget *ui;
    writeclient * w_client = nullptr;
    readclient * r_client = nullptr;
    void closeEvent(QCloseEvent * e);
    ReadThread *thread;
};

#endif // WIDGET_H

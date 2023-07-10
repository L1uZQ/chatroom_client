#ifndef LOGININ_H
#define LOGININ_H

#include <QWidget>
#include<QTcpSocket>


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
//    WriteClient * writeClient = nullptr;
//    ReadClient * readClient = nullptr;
//    User * user = nullptr;
//    void closeEvent(QCloseEvent * e);
    void sleep(int msec);
};

#endif // LOGININ_H

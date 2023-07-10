#include "widget.h"
#include <QApplication>
#include"loginin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginIn l;
    l.show();
//    Widget w;
//    w.show();

    return a.exec();
}

#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QWidget>
#include <loginin.h>

namespace Ui {
class RegisterForm;
}

class RegisterForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterForm(QWidget *parent = 0);
    ~RegisterForm();
    LoginIn * loginform;

private:
    Ui::RegisterForm *ui;
};

#endif // REGISTERFORM_H

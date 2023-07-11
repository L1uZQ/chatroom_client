#ifndef USER_H
#define USER_H
#include<QString>
#include<string>

class user
{
public:
    user(unsigned int userId, QString username);
    QString getUsername();
    unsigned int getUserId();

private:
    QString username;
    unsigned int userId;

};

#endif // USER_H

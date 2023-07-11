#include "user.h"

user::user(unsigned int userId, QString username)
{
    this->userId = userId;
    this->username = username;
}

QString user::getUsername()
{
    return username;
}

unsigned int user::getUserId()
{
    return userId;
}

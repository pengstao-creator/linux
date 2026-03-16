#include "../headers/Person.h"


User::User(/* args */)
{
}

User::User(string username, int userAge)
{
    this->username = username;
    this->userAge = userAge;
}

void User::displayUser()
{
    cout << this->username <<"   " << this->userAge << endl;
}

User::~User()
{
}
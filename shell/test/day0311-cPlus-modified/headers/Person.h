#include <iostream>
using namespace std;

class User
{
private:
    string username;
    int userAge;
public:
    User(/* args */);
    User(string username,int userAge);
    void displayUser();
    ~User();
};
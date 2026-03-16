#include <iostream>
using namespace std;

class Person
{
private:
    string name;
    int age;
public:
    Person(/* args */);
    Person(string name,int age);
    void printPerson();
    ~Person();
};

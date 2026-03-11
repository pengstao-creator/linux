#include "Person.h"


Person::Person(/* args */)
{
}

Person::Person(string name, int age)
{
    this->name = name;
    this->age = age;
}

void Person::printPerson()
{
    cout << this->name <<"   " << this->age << endl;
}

Person::~Person()
{
}

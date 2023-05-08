#pragma once

#include "ClassRegister.h"
#include <iostream>
#include <string>

class ClassA : public Object
{
public:
    ClassA() {};
    ~ClassA() {};

    void show()
    {
        std::cout << age << std::endl;
    }

    void set_name_and_age(std::string& name, int _sex, int _age) 
    {
        age = _age;
        std::cout << "name: " << name << " _sex: " << _sex << std::endl;
        //return age;
    }

    void f1()
    {
        std::cout << "f1" << std::endl;
    }

public:
    int age;
    std::string name;
};

REFLECT_REGISTER_CLASS(ClassA);
REFLECT_REGISTER_FIELD(ClassA, age, int); //age必须是public
REFLECT_REGISTER_FIELD(ClassA, name, std::string); //age必须是public
REFLECT_REGISTER_METHOD_VOID(ClassA, f1);
REFLECT_REGISTER_METHOD_VOID(ClassA, show);
REFLECT_REGISTER_METHOD(ClassA, set_name_and_age);


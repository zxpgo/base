#include <iostream>
#include "ClassFactory.h"
#include "Sigleton.h"
#include "ClassA.h"

int main()
{
    ClassFactory* factory = Sigleton<ClassFactory>::get_instance();
    Object* a = factory->create_class("ClassA");

    int age = 0;
    a->set_field_value("age", 100);
    a->get_field_value("age", age);
    std::cout << age << std::endl; 

    std::string name;
    std::string old = "hello";
    a->set_field_value("name", old);
    a->get_field_value("name", name);
    std::cout << name << std::endl; 
    
    std::string func = "f1";
    a->call(func);
    old = "hello world";
    a->call<void, std::string, int, int>("set_name_and_age", "china", 1, 130);
    //std::cout << "ret: " << ret << std::endl;

    a->get_field_value("name", name);
    std::cout << "name: " << name << std::endl; 

    func= "show";
    a->call(func);

    return 0;
}
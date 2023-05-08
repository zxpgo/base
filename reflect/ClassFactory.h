#pragma once

#include <map>
#include <string>
#include <vector>
#include "Sigleton.h"
#include "ClassField.h"
#include "ClassObject.h"
#include "ClassMethod.h"
#include <iostream>

class ClassFactory;
class ClassField;

class ClassFactory
{
public:
    void register_class(const std::string& class_name, create_object method);
    Object* create_class(const std::string& class_name);

    void register_class_field(const std::string& class_name, const std::string& field_name, const std::string& type, int offset);
    ClassField* get_class_field(const std::string& class_name, const std::string& field_name);

    void register_class_method(const std::string& class_name, const std::string& method_name, uintptr_t method);
    ClassMethod* get_class_method(const std::string& class_name, const std::string& method_name);

private:
    std::map<std::string, create_object> m_class_map;
    std::map<std::string, std::vector<ClassField*> > m_class_fields;
    std::map<std::string, std::vector<ClassMethod*> > m_class_methods;
};


#define OFFSET(class_name, field_name)  \
           { class_name class_name##filed_name; \
           ((size_t)(&class_name##filed_name.field_name - &class_name##field_name)) }
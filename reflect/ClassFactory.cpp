#include "ClassFactory.h"

void ClassFactory::register_class(const std::string& class_name, create_object method)
{
    m_class_map[class_name]  = method;
}

Object* ClassFactory::create_class(const std::string& class_name)
{
    return m_class_map[class_name]();
}

void ClassFactory::register_class_field(const std::string& class_name, const std::string& field_name, const std::string& type, int offset)
{
    m_class_fields[class_name].push_back(new ClassField(field_name, type, offset));
}

ClassField* ClassFactory::get_class_field(const std::string& class_name, const std::string& field_name)
{
    if (m_class_fields.find(class_name) == m_class_fields.end())
    {
        std::cout << "not found: " << class_name << std::endl;
        return NULL;
    }

    for (int i = 0; i < m_class_fields[class_name].size(); ++i)
    {
        if (field_name == m_class_fields[class_name][i]->name())
        {
            return m_class_fields[class_name][i];
        }
    }

    return NULL;
}

void ClassFactory::register_class_method(const std::string& class_name, const std::string& method_name, uintptr_t method)
{
    m_class_methods[class_name].push_back(new ClassMethod(method_name, method));
}

ClassMethod* ClassFactory::get_class_method(const std::string& class_name, const std::string& method_name)
{
    if (m_class_methods.find(class_name) == m_class_methods.end())
    {
        std::cout << "not found: " << class_name << std::endl;
        return NULL;
    }

    for (int i = 0; i < m_class_methods[class_name].size(); ++i)
    {
        if (method_name == m_class_methods[class_name][i]->name())
        {
            return m_class_methods[class_name][i];
        }
    }

    return NULL;
}

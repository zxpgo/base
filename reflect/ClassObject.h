#pragma once

#include <string>
#include <assert.h>
#include <functional>
#include "Sigleton.h"

class ClassFactory;
class ClassField;
class ClassMethod;

class Object
{
public:
    Object() {};
    virtual ~Object() {};
    
    void call(const std::string& method_name);

    void set_class_name(const std::string& class_name) 
    {
        m_class_name = class_name;
    }

    const std::string& get_class_name()
    {
        return m_class_name;
    }

template<typename T, typename... Args>
T call(const char* method_name, Args... args)
{
    ClassFactory* factory = Sigleton<ClassFactory>::get_instance();
    ClassMethod* method = factory->get_class_method(get_class_name(), method_name);
    assert(method != NULL);

    auto func = method->method();
    typedef std::function<T(decltype(this),  Args...)> class_method;

    return (*((class_method*)func))(this, args...);
}

    template<class T>
    void get_field_value(const std::string& field_name, T& value)
    {
        ClassFactory* factory = Sigleton<ClassFactory>::get_instance();
        ClassField* field = factory->get_class_field(get_class_name(), field_name);
        assert(field != NULL);

        value = *(T*)((unsigned char*)(this) + (size_t)field->offset());
    }

    template<class T>
    void set_field_value(const std::string& field_name, const T& value)
    {
        ClassFactory* factory = Sigleton<ClassFactory>::get_instance();
        ClassField* field = factory->get_class_field(get_class_name(), field_name);
        assert(field != NULL);

        *(T*)((unsigned char*)(this) + (size_t)field->offset()) = value;
    }

private:
    std::string m_class_name;
};

typedef Object* (*create_object)(void);
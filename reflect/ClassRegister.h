#pragma once

#include "Sigleton.h"
#include "ClassFactory.h"
#include <string>
#include <iostream>
#include <functional>

class RegisterClass
{
public:
    RegisterClass(const std::string& class_name, create_object method)
    {
        ClassFactory* factory = Sigleton<ClassFactory>::get_instance();
        factory->register_class(class_name, method);
    }

    RegisterClass(const std::string& class_name, const std::string& field_name, const std::string& type, int offset)
    {
        std::cout << class_name << " " << field_name << " " << type << " " << offset << std::endl;
        ClassFactory* factory = Sigleton<ClassFactory>::get_instance();
        factory->register_class_field(class_name, field_name, type, offset);
    }

    RegisterClass(const std::string& class_name, const std::string& method_name, uintptr_t method)
    {
        std::cout << class_name << " " << method_name << " " << method << std::endl;
        ClassFactory* factory = Sigleton<ClassFactory>::get_instance();
        factory->register_class_method(class_name, method_name, method); 
    }
};

#define REFLECT_REGISTER_CLASS(class_name)        \
            Object* createObject##class_name()    \
            {                                     \
                Object* obj = new class_name();   \
                obj->set_class_name(#class_name); \
                return obj;                       \
            }                                     \
            RegisterClass register_class##class_name(#class_name, createObject##class_name);

#define REFLECT_REGISTER_FIELD(class_name, field_name, type) \
    class_name class_name##field_name;               \
    RegisterClass register_class##class_name##field_name(#class_name, #field_name, #type, \
    ((size_t)(&class_name##field_name.field_name) - (size_t)(&class_name##field_name)));

#define REFLECT_REGISTER_METHOD_VOID(class_name, method_name) \
            std::function<void(class_name*)> class_name##method_name = &class_name::method_name; \
            RegisterClass class_register##class_name##method_name(#class_name, #method_name, (uintptr_t)&class_name##method_name);

template<typename... Args>
using Function = std::function<void(Args...)>;

template<typename... Args>
using MemberFunction = std::function<void(void*, Args...)>;

template<typename T, typename RetType, typename... Args>
MemberFunction<Args...> make_member_function(RetType (T::*func)(Args...)) {
    return [func](void* obj, Args... args) -> RetType {
        return (static_cast<T*>(obj)->*func)(args...);
    };
}

template<typename Func,  typename RetType, typename... Args>
RetType call(Func func, Args... args) {
    return func(args...);
}

template<typename Func, typename RetType, typename... Args>
RetType call(Func func, void* obj, Args... args) {
    return func(obj, args...);
}

#define REFLECT_REGISTER_METHOD(class_name, method_name) \
            auto class_name##method_name = make_member_function(&class_name::method_name); \
            RegisterClass class_register##class_name##method_name(#class_name, #method_name, (uintptr_t) &class_name##method_name);


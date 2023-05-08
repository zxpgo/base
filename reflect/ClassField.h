#pragma once

#include <string>

class ClassField
{
public:
    ClassField(const std::string& _field_name, const std::string& _type, int _offset):
        m_field_name(_field_name),
        m_type_name(_type),
        m_offset(_offset) { }

    std::string& name() { return m_field_name; }
    std::string& type() { return m_type_name; }
    int offset() { return m_offset; }
private:
    std::string m_field_name;
    std::string m_type_name;
    int m_offset;
};
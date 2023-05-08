#ifndef __INI_FILE_H__
#define __INI_FILE_H__

#include <map>
#include <string>
#include "value.h"

class Section
{
public:

    Value& get(const std::string& key)
    {
        return m_section[key];
    }

    void set(const std::string& key, const Value& value)
    {
        m_section[key] = value;
    }

    Value& operator [](const std::string& key)
    {
        return m_section[key];
    }

    std::string print();

private:
    std::map<std::string, Value> m_section;
};

class IniFile
{
public:
    void load(const std::string& file_name);
    void save();

    Value& get(const std::string section_name, const std::string& key);
    void set(const std::string section_name, const std::string& key, Value& value);

    std::string str();
    void print();

    std::string trim(const std::string& str);

public:
    std::string file_name;
    std::map<std::string, Section> m_data;
};
#endif //__INI_FILE_H__
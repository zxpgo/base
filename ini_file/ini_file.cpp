#include "ini_file.h"
#include <fstream>
#include <iostream>
#include <sstream>

void IniFile::load(const std::string& _file_name)
{
    file_name = _file_name;
    std::ifstream stream(file_name);
    if (stream)
    {
        std::string line;
        std::string section_name;
        while(std::getline(stream, line))
        {
            line = trim(line);
            if (line[0] == '[')
            {
                section_name = line.substr(1, line.find_last_not_of("]"));
                m_data[section_name] = Section();
            } else 
            {
                std::size_t pos = line.find("=");
                assert(pos != std::string::npos);

                std::string key = line.substr(0, pos);
                key = trim(key);
                std::string value = line.substr(pos + 1);
                value = trim(value);
                m_data[section_name][key] = value;
            }
        }
    }

    stream.close();
}

void IniFile::save()
{
    std::ofstream stream(file_name);
    if (stream)
    {
        stream << str();
    }

    stream.close();
}

Value& IniFile::get(const std::string section_name, const std::string& key)
{
    return m_data[section_name][key];
}

void IniFile::set(const std::string section_name, const std::string& key, Value& value)
{
    m_data[section_name][key] = value;
}

std::string IniFile::str()
{
    std::ostringstream ss;
    for (auto iter = m_data.begin(); iter != m_data.end(); ++iter)
    {
        ss << "[" << iter->first << "]" << std::endl;
        ss << iter->second.print();
    }

    return ss.str();
}

void IniFile::print()
{
    std::cout << str() << std::endl;
}

std::string IniFile::trim(const std::string& str)
{
    std::string temp_str = str;
    temp_str.erase(0, temp_str.find_first_not_of(" /n/r"));
    temp_str.erase(temp_str.find_last_not_of(" /n/r")+1);

    return temp_str;
}

std::string Section::print()
{
    std::ostringstream ss;
    for (auto iter = m_section.begin(); iter != m_section.end(); ++iter)
    {
        std::string value = iter->second;
        ss << iter->first << "=" << value << std::endl;
    }

    return ss.str();
}

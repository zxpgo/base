#ifndef __VALUE_H__
#define __VALUE_H__

#include <string>
#include <assert.h>

class Value
{
public:
	Value(){};
	Value(bool flag) 
	{
		m_value = flag ? "true" : "false";
	}

	template<class T>
	Value(T num)
	{
		m_value = std::to_string(num);
	}

	Value(const std::string& str)
	{
		m_value = str;
	}

	Value(const char* str)
	{
		m_value = str;
	}
	
	Value& operator=(const bool& flag)
	{
		m_value = flag ? "true" : "false";
		return *this;
	}

	template<class T>
	Value& operator=(const T& value)
	{
		m_value = std::to_string(value);
		return *this;
	}

	Value& operator=(const std::string& value)
	{
		m_value = value;
		return *this;
	}

	Value& operator=(const char*& value)
	{
		m_value = value;
		return *this;
	}

	operator bool()
	{
		return m_value == "true";
	}

	operator int()
	{
		return std::stoi(m_value);
	}

	operator double()
	{
		return std::stod(m_value);
	}

	operator float()
	{
		return std::stof(m_value);
	}

	operator std::string()
	{
		return m_value;
	}

private:
	std::string m_value;
};


#endif //__VALUE_H__

#pragma once

template <class T>
class Sigleton
{
public:
    static T* get_instance()
    {
        if (m_instance == NULL)
        {
            m_instance = new T();
        }

        return m_instance;
    }

private:
    Sigleton(){};
    ~Sigleton(){};
    Sigleton(const Sigleton<T>&);
    Sigleton<T>& operator=(const Sigleton<T>&);

private:
    static T* m_instance;
};

template<class T>
T* Sigleton<T>::m_instance = NULL;
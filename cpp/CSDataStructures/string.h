#ifndef STRING_H
#define STRING_H
#include <iostream>
#include <cstring>
#include <string>

class String
{
    private:
    char * arr = nullptr;
    size_t length;

    public:
    String(const char * str);
    ~String()
    {
        delete[]arr;
    }
    size_t size() const;
    bool is_empty() const;
    String& append(char * str);
    String& operator=(const char * str);
    String& operator=(const char& ch);
    String& operator=(const String& str);
    String& operator+=(const char * str);
    String& operator+=(const char &ch);
    String& operator+=(const String& str);
    
    
    


    char &operator[](const size_t index) const
    {
        return arr[index];
    }
    friend std::ostream& operator<<(std::ostream & os,const  String&str)
    {
        
        for (size_t i = 0; i < str.length; i++)
        {
            os << str[i];
        }

        return os;
    }

};

String::String(const char * str)
{
    size_t len = strlen(str);
    arr = new char[len];

    for (size_t i = 0; i < len; i++)
    {
        arr[i] = static_cast<char>(str[i]);
    }
    length = len;
}

size_t String::size() const
{
    return length;
}

String& String::operator=(const char * str)
{
    delete[] arr;
    size_t len = strlen(str);
    length = len;
    arr = new char[length];
    for (size_t i = 0; i < length; i++)
    {
        arr[i] = str[i];
    }

    return *this;
}

String& String::operator=(const char &ch)
{
    delete[] arr;
    arr = new char[1];
    length = 1;
    arr[length - 1] = ch;

    return *this; 
}

String& String::operator=(const String& str)
{
    if (this == &str)
    {
        return *this;
    }
    delete[] arr;
    arr = new char[str.size()];
    length = str.size();
    for (size_t i = 0; i < length; i++)
    {
        this->arr[i] = str[i];
    }

    return *this;
}

String& String::operator+=(const char * str)
{
    auto pos = length;
    char * temp = new char[this->length];
    strcpy(temp, arr);
    
    delete[] arr;

    length = strlen(str) + this->length;

    arr = new char[length];

    strcpy(arr, temp);

    delete[] temp;
    size_t start = 0;
    for (auto i = pos; i < length; i++)
    {
        arr[i] = str[start++];
    }

    return *this;
}

String& String::operator+=(const char &ch)
{
    char * tmp = new char[length];
    strcpy(tmp, arr);
    delete[] arr;
    length++;
    arr = new char[length];
    strcpy(arr, tmp);
    delete[]tmp;
    arr[length-1] = ch;
    return *this;
}

String& String::operator+=(const String& str)
{
    size_t old_size = this->length;
    size_t str_size = str.size();
    auto position = length;
    char * temp2 = new char[length];

    strcpy(temp2, arr);

    delete[] arr;

    this->length = old_size + str_size;

    arr = new char[this->length];

    strcpy(arr, temp2);

    delete[] temp2;

    auto start = 0;
    for (auto i = position; i < length; i++)
    {
        arr[i] = str[start++];
    }

    return *this;

}



#endif
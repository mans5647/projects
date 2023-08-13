#ifndef TEST_H
#define TEST_H
#include "./include/sha1.hpp"
#include "./include/common.hpp"

struct Dt
{
    std::string name;
    std::string surname;
    std::string password;
    std::string salt;
    int role;
    
    friend std::ostream &operator<<(std::ostream & os, Dt&dat)
    {
        os << dat.name;
        os << dat.surname;
        os << dat.password;
        os << dat.salt;
        return os;
    }
    friend std::istream& operator>>(std::istream & is, Dt & dat)
    {
        std::getline(is, dat.name, ':');
        std::getline(is, dat.surname, ':');
        std::getline(is, dat.password, ':');
        std::getline(is, dat.salt, ';');
        return is;
    }

    template <typename type>
    friend type * ReadFromFile(std::ifstream & file);
    template <typename type>
    friend void WriteToFile(type & dat);
};


template <typename type, class f = type>
std::shared_ptr<f> ReadFromFile(std::ifstream & file)
{
    std::shared_ptr<f> dat(new f);
    file >> *dat;
    return dat;
}

template <typename type>
void WriteToFile(type & dat)
{
    std::ofstream file("credits.txt", std::ios::app);
    if (file.is_open())
    {
        file << dat;
    }
    else
    {
        std::cerr<<"Unable to open file";
    }
    file.close();
}

std::string get_alphabet();

std::string gensalt()
{
    std::srand(std::time(0));
    std::string result_str;
    std::string alph = get_alphabet();
    for (std::size_t i = 0; i < 15; i++)
    {
        result_str += alph[std::rand() % (alph.size() - 1)];
    }
    return result_str;
}

std::string get_alphabet()
{
    char alphabet[61];
    char let = 'A';
    for (int i = 0; i < 51; i++)
    {
        alphabet[i] = let;
        if (let == 90)
        {
            while (let < 97)
            {
                ++let;
            }
            alphabet[i] = let;

        }
        ++let;
    }

    char number = 48;
    for (int i = 51; i < 61; i++)
    {
        alphabet[i] = number++;
    }
    std::string fn = alphabet;
    return fn;
}

template <class ValueType, class Collection>
long b_search(Collection & col, long left, long right, ValueType & value)
{
    while (left <= right)
    {
        long middle = left + (right - left) / 2;
        if (col[middle]->name == value)
        {
            return middle;
        }
        if (col[middle]->name < value)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }
    return -1;
}

#endif
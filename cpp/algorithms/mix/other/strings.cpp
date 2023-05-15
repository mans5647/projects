#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>

uint16_t getCount(std::wstring& str)
{

    uint16_t counter(0);
    size_t start = 0;
    size_t where = str.find_first_of(L", \t\n");
    while (str[start] != '\0')
    {
        if (str[start] == str[where])
        {
            std::wcout << L'\n';
            counter++;
        }

        std::wcout << str[start];

        start++;
    }
    counter++;
    return counter;
}

std::wstring getPhone(const std::wstring& str)
{
    size_t i = 0;
    std::wstring New_str;
    while (str[i] != '\0')
    {

        if (str[i] == '+')
        {
            New_str += '+';
        }
        if (isdigit(str[i]) != 0)
        {
            New_str += str[i];
        }
        if (isspace(str[i]) && isdigit(str[i + 1]))
        {
            break;
        }
        i++;
    }
    return New_str;
}



int main()
{


    std::setlocale(LC_ALL, "ru");
    std::system("chcp 1251");
    std::wstring* arr = new std::wstring[7];
    const wchar_t** hints = new const wchar_t* [4];

    hints[0] = L"(подсчет слов)";
    hints[1] = L"(вывод номера телефона)";
    hints[2] = L"(сравнение строк)";
    hints[3] = L"(замена)";

    for (size_t i = 0; i < 7; i++)
    {
        std::wcout << L"Введите " << i + 1 << L" строку: ";
        std::getline(std::wcin, arr[i]);
    }
    std::wstring mes{};
    bool res = (std::equal(arr[2].begin(), arr[2].end(), arr[3].begin())) ? true : false;


    if (res) mes = L"Строки одинаковые"; else { mes = L"Строки разные"; }

    uint16_t count = getCount(arr[0]);
    std::cout << '\n';
    std::wcout << hints[0] << L" (?) количество слов: " << count << '\n';
    std::wcout << hints[1] << L" (?) номер телефона из строки: " << getPhone(arr[1]) << '\n';
    std::wcout << hints[2] << L" (?) сравнение строк: " << mes << '\n';


    std::wcout << hints[3] << L" (?) Замена подстроки: Изначальная 5-я строка: " << arr[4] << '\n';

    size_t i = 0;
    while (arr[4][i] != '\0')
    {
        i = arr[4].find(arr[5], i);
        if (i == std::string::npos) break;
        arr[4].replace(i, arr[6].size(), arr[6]);
        i++;
    }
    std::wcout << hints[3] << L" (?) Замена подстроки: 5-я строка после замены: " << arr[4] << '\n';
    delete[]arr;
    delete[]hints;
    return 0;
}
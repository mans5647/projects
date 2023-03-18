#include <string>
#include <iostream>
#include <locale>

int main()
{
    std::setlocale(LC_ALL, "ru");
    std::wstring str(L"Привет брок");
    str[0] = L'Р';
    std::wcout<<str<<std::endl;
}
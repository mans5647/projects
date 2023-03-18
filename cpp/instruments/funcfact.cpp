#include <iostream>
#include <cstdint>


int64_t factorial(int64_t & number)
{
    if (number == 0 | number == 1)
    {
        return 1;
    }
    else
    {
        return number * factorial(--number);
    }
}



int main(void)
{
    int64_t number, result;
    number = result = 0;
    std::system("chcp 1251");
    std::setlocale(LC_ALL, "ru");
    while (true)
    {
        std::cout<<"������� �����: ";
        std::cin>>number;
        if (number < 0)
        {
            std::cout<<"������������� ����� �� ���������\n";
            break;
        }
        if ((result = factorial(number)) == 1)
        {
            std::cout<<"��������� 1 ��� 0 ����� 1 \n";
        }
        std::cout<<"���������: "<<result<<'\n';
    }
}
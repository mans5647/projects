#include <iostream> 
#include <string>
#include <clocale>
#include <string.h>
typedef long long ll_t; // ���������� ���� ������

int main()
{
    system("chcp 1251"); // ��� ����� ���������
    setlocale(LC_ALL, "ru"); // ��������� ������
    char numb[1000]; // ��� ���������
    ll_t sum = 0; // ��������� ����� ����� 0
    ll_t delim = 2; // ��������
    while (1) // ����������� ����
    {
        ll_t fact_counter = 1; // ���������
        ll_t fact_result = 1; // ��������� ����������
        std::cout<<"������� ����� "; 
        std::cin >> numb; // ����...
        
        if (!strcmp(numb, "end")) // �������� �� ����� 'end'
        {
            std::cout<<"����� ���� ������� �����: "<<sum<<'\n';
            std::cout<<"�����!\n";
            break;
        }

        ll_t number = std::atoi(numb); // ������� ������ � �����


        if (number < 0) 
        {
            std::cout<<"����� �������������!\n";
            std::cout<<"-----------------------\n";
        }
        else if (number == 0)
        {
            std::cout<<"��������� ����� 0 ����� 1\n\n";
            std::cout<<"-----------------------\n";
        }
        else if (number == 1)
        {
            std::cout<<"��������� ����� 1 ����� 1\n\n";
            std::cout<<"-----------------------\n";
        }
        
        else if (number > 0 && number != 0 && number != 1) 
        {
            ll_t tmpVar = number; // ���������� ��� ���������� ������� ������ � ���� �������� �����
            while (fact_counter <= number) // ���� ����������
            {
                fact_result*= fact_counter;
                --tmpVar;
                fact_counter++;
            }
            std::cout<<"��������� "<<number<<" ����� "<<fact_result<<"\n"; // ����� ����������...
        }


        while (number > 0) // �������� �� �������� �����
        {
            if (number == 1) // 1 - �� �������
            {
                std::cout<<"1 �� �������� ������� ������!\n";
                break;
            }
            else if (number % delim == 0) // ���� ������� �� ������� �� 2 ����� 0 �� ��������� ���� 
            {
                break;
            }
            else
            {
                std::cout<<"����� "<<number<<" �������!\n"; // ������� ���������
                std::cout<<"-----------------------\n"; 
                sum+=number; // ���������� ������� �����
                break;
            }
            --number; // ���������� �����
        }
        
        

    }
    
return 0;
}
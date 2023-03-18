#include <iostream> 
#include <string>
#include <clocale>
#include <string.h>
typedef long long ll_t; // назначение типа данных

int main()
{
    system("chcp 1251"); // дл€ смены раскладки
    setlocale(LC_ALL, "ru"); // установка локали
    char numb[1000]; // дл€ сообщени€
    ll_t sum = 0; // начальна€ сумма равна 0
    ll_t delim = 2; // делитель
    while (1) // бесконечный цикл
    {
        ll_t fact_counter = 1; // множитель
        ll_t fact_result = 1; // результат факториала
        std::cout<<"¬ведите число "; 
        std::cin >> numb; // ввод...
        
        if (!strcmp(numb, "end")) // проверка на слово 'end'
        {
            std::cout<<"—умма всех простых чисел: "<<sum<<'\n';
            std::cout<<"¬ыход!\n";
            break;
        }

        ll_t number = std::atoi(numb); // перевод строки в число


        if (number < 0) 
        {
            std::cout<<"„исло отрицательное!\n";
            std::cout<<"-----------------------\n";
        }
        else if (number == 0)
        {
            std::cout<<"‘акториал числа 0 равен 1\n\n";
            std::cout<<"-----------------------\n";
        }
        else if (number == 1)
        {
            std::cout<<"‘акториал числа 1 равен 1\n\n";
            std::cout<<"-----------------------\n";
        }
        
        else if (number > 0 && number != 0 && number != 1) 
        {
            ll_t tmpVar = number; // переменна€ дл€ вычислени€ которое хранит в себе значение числа
            while (fact_counter <= number) // счет факториала
            {
                fact_result*= fact_counter;
                --tmpVar;
                fact_counter++;
            }
            std::cout<<"‘акториал "<<number<<" равен "<<fact_result<<"\n"; // вывод результата...
        }


        while (number > 0) // проверка на простоту числа
        {
            if (number == 1) // 1 - не простое
            {
                std::cout<<"1 не €вл€етс€ простым числом!\n";
                break;
            }
            else if (number % delim == 0) // если остаток от делени€ на 2 равен 0 то завершаем счет 
            {
                break;
            }
            else
            {
                std::cout<<"„исло "<<number<<" простое!\n"; // выводим результат
                std::cout<<"-----------------------\n"; 
                sum+=number; // складываем простые числа
                break;
            }
            --number; // уменьшение числа
        }
        
        

    }
    
return 0;
}
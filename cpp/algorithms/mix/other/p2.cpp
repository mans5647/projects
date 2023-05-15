#include <iostream>
#include <vector>
#include <ctime>
#include <memory>
#include <clocale>


void sort_by_asc(std::vector<int> & it) // функция для сортировки по возрастанию
{
    int temp; // временное место
    for (auto i = 0; i < it.size(); i++)
    {
        for (auto j = 0; j < it.size() - i - 1; j++)
        {
            if (it[j] > it[j + 1])
            {
                temp = it[j];
                it[j] = it[j + 1];
                it[j + 1] = temp;
            }
        }
    }
}

void sort_by_desc(std::vector<int> & it) // функция для сортировки по убыванию
{
    int temp; // временное место
    for (auto i = 0; i < it.size(); i++)
    {
        for (auto j = 0; j < it.size() - i - 1; j++)
        {
            if (it[j] < it[j + 1])
            {
                temp = it[j];
                it[j] = it[j + 1];
                it[j + 1] = temp;
            }
        }
    }
}

void Display(void (*ptr)(std::vector<int> & it),void (*ptr1)(std::vector<int> & it), std::vector<int> & it) // функция для отображения результатов 
{
    std::srand((unsigned int)time(0));
    for (auto &a : it)
    {
        a = std::rand() % 199; // заполнение случайными числами от 0 до 199
    }


    std::cout<<"До сортировки: ";
    for (auto & i : it)
    {   
        std::cout<<i<<' ';
    }

    std::cout<<"\n\n";

    std::cout<<"После сортировки: \n\n";
    ptr(it); // вызов по указетелю
    std::cout<<"По возрастанию: ";
    for (auto & i : it)
    {   
        std::cout<<i<<' ';
    }

    std::cout<<"\n";
    ptr1(it); // вызов по указателю
    std::cout<<"По убыванию: ";
    

    for (auto & i : it)
    {   
        std::cout<<i<<' ';
    }
}

int main()
{   
    std::system("chcp 65001");
    setlocale(LC_ALL, "ru"); // локализация
    auto N = 0; // переменная отвечающая за количество элементов
    std::cout<<"Количество элементов: ";
    std::cin >> N; 
    std::vector<int> a(N, 0);
    Display(sort_by_asc, sort_by_desc, a); // вызов функция для отображения результатов
    
}
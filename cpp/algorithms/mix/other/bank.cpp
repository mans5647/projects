#ifndef STD_CPP
#define STD_CPP
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <utility>
#include <clocale>
#endif


class BankAccount final // bank account - класс аккаунта
{
    public:
    explicit BankAccount(const uint32_t & acc_number, const double & initial_money) : number(std::move(acc_number)), balance(std::move(initial_money)), 
    rate(0) {} // явный конструктор для установки значений аккаунта
    BankAccount() = default; // по умолчанию (необязателен)
    
    void Deposit(double ** money); //  фн для начисления средств
    
    void WithDraw(double ** howmuch); // фн для списывания средств
    
    double GetBalance() const; // фн для получения баланса
    
    double GetRate() const; // фн для получения процентной ставки

    double SetRate(double *rate); // фн для установки процентой ставки

    double GetPercents(); // фн для подсчета процентов

    uint32_t GetAccountNumber() const; // фн для получения номера аккаунта

    friend bool Transfer(BankAccount& acc1, BankAccount& acc2, double * how_much) // др фн для передачи средств
    {
        bool IsSuccess = false; // изначально false 
        if (*how_much <= 0) throw std::invalid_argument("Количество средств для передачи не может быть меньше или равно нулю"); // бросаем исключение если средств для передачи меньше или равно нулю
        IsSuccess = (acc1.balance < *how_much) ? false : true, acc1.WithDraw(&how_much), acc2.Deposit(&how_much); // тернарная операция для начисления средств
        return IsSuccess; // возвращение значения
    }

    private:

    uint32_t number; // номер аккаунта
    double balance; // баланс
    double rate; // процентная ставка

};

void BankAccount::Deposit(double ** money)
{
    balance += **money; // увеличиваем баланс
}

void BankAccount::WithDraw(double ** howmuch)
{
    if (**howmuch > balance) throw std::invalid_argument("Средств для снятия больше чем ваш баланс"); // бросаем исключение если средств для снятия мегьше чем баланс
    balance -= **howmuch; // вычитаем баланс
}

double BankAccount::GetBalance() const
{
    return balance; // возвращяем баланс
}

double BankAccount::GetRate() const
{
    return rate; // возвращяем процентную ставку
}

double BankAccount::SetRate(double *rate)
{
    this->rate = *rate; // присваиваем процентную ставку
}

double BankAccount::GetPercents()
{
    return static_cast<double>(((balance / 100) * rate) / 12); // возвращаем проценты
}

uint32_t BankAccount::GetAccountNumber() const
{
    return number; // возвращем номер аккаунта
}


int main(void)
{
    std::setlocale(LC_ALL, "ru");
    std::system("chcp 1251");

    uint32_t number = 0;
    double init_sum = 0;
    double amount = 0;
    double Prc = 0;
    


    std::cout<<"Данные для аккаунта \n"; // вводим данные для акканута
    std::cout<<"Номер счета (аккаунта): ";
    std::cin >> number;
    std::cout<<"Начальные средства: ";
    std::cin>> init_sum;
    BankAccount acc1(number, init_sum); // создаем объект
    std::cout<<"Процентная ставка для аккаунта номер: "<<acc1.GetAccountNumber()<<": ";
    std::cin >> Prc;
    if (Prc > 20) 
    {
        std::cerr<<"Процентная ставка не может быть больше 20%";
        return -1;
    }
    acc1.SetRate(&Prc); // уст. ставку

    std::cout<<"Данные для аккаунта \n"; // вводим данные для акканута
    std::cout<<"Номер счета (аккаунта): ";
    std::cin >> number;
    std::cout<<"Начальные средства ";
    std::cin>> init_sum;

    BankAccount acc2(number, init_sum); // создаем объект
    std::cout<<"Процентная ставка для аккаунта номер: "<<acc2.GetAccountNumber()<<": ";
    std::cin >> Prc;
    if (Prc > 20) 
    {
        std::cerr<<"Процентная ставка не может быть больше 20%"; 
        return -1;
    }
    acc2.SetRate(&Prc);  // уст. ставку

    std::cout<<"Введите передаваемую сумму: ";

    std::cin>>amount; // вводим количество средств для перевода

    bool success = Transfer(acc1, acc2, &amount); // вызываем функцию и иниц. переменную
    if (!success) // в случае false
    {
        std::cerr<<"На аккаунте "<<'('<<acc1.GetAccountNumber()<<')'<<"недостаточно денег\n"; // недостаточно денег
        return 0; // возвращяем значение main()
    }

    std::cout<<"Аккаунт номер: "<<acc1.GetAccountNumber()<<" | "<<acc1.GetBalance()<<"руб.   Ставка: "<<acc1.GetRate()<<"% Проценты: "<<acc1.GetPercents()<<" руб.\n"; // выводим результаты
    std::cout<<"Аккаунт номер: "<<acc2.GetAccountNumber()<<"  | "<<acc2.GetBalance()<<"руб.  Ставка: "<<acc2.GetRate()<<"% Проценты: "<<acc2.GetPercents()<<" руб.\n"; // выводим результаты
}
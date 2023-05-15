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


class BankAccount final // bank account - ����� ��������
{
    public:
    explicit BankAccount(const uint32_t & acc_number, const double & initial_money) : number(std::move(acc_number)), balance(std::move(initial_money)), 
    rate(0) {} // ����� ����������� ��� ��������� �������� ��������
    BankAccount() = default; // �� ��������� (������������)
    
    void Deposit(double ** money); //  �� ��� ���������� �������
    
    void WithDraw(double ** howmuch); // �� ��� ���������� �������
    
    double GetBalance() const; // �� ��� ��������� �������
    
    double GetRate() const; // �� ��� ��������� ���������� ������

    double SetRate(double *rate); // �� ��� ��������� ��������� ������

    double GetPercents(); // �� ��� �������� ���������

    uint32_t GetAccountNumber() const; // �� ��� ��������� ������ ��������

    friend bool Transfer(BankAccount& acc1, BankAccount& acc2, double * how_much) // �� �� ��� �������� �������
    {
        bool IsSuccess = false; // ���������� false 
        if (*how_much <= 0) throw std::invalid_argument("���������� ������� ��� �������� �� ����� ���� ������ ��� ����� ����"); // ������� ���������� ���� ������� ��� �������� ������ ��� ����� ����
        IsSuccess = (acc1.balance < *how_much) ? false : true, acc1.WithDraw(&how_much), acc2.Deposit(&how_much); // ��������� �������� ��� ���������� �������
        return IsSuccess; // ����������� ��������
    }

    private:

    uint32_t number; // ����� ��������
    double balance; // ������
    double rate; // ���������� ������

};

void BankAccount::Deposit(double ** money)
{
    balance += **money; // ����������� ������
}

void BankAccount::WithDraw(double ** howmuch)
{
    if (**howmuch > balance) throw std::invalid_argument("������� ��� ������ ������ ��� ��� ������"); // ������� ���������� ���� ������� ��� ������ ������ ��� ������
    balance -= **howmuch; // �������� ������
}

double BankAccount::GetBalance() const
{
    return balance; // ���������� ������
}

double BankAccount::GetRate() const
{
    return rate; // ���������� ���������� ������
}

double BankAccount::SetRate(double *rate)
{
    this->rate = *rate; // ����������� ���������� ������
}

double BankAccount::GetPercents()
{
    return static_cast<double>(((balance / 100) * rate) / 12); // ���������� ��������
}

uint32_t BankAccount::GetAccountNumber() const
{
    return number; // ��������� ����� ��������
}


int main(void)
{
    std::setlocale(LC_ALL, "ru");
    std::system("chcp 1251");

    uint32_t number = 0;
    double init_sum = 0;
    double amount = 0;
    double Prc = 0;
    


    std::cout<<"������ ��� �������� \n"; // ������ ������ ��� ��������
    std::cout<<"����� ����� (��������): ";
    std::cin >> number;
    std::cout<<"��������� ��������: ";
    std::cin>> init_sum;
    BankAccount acc1(number, init_sum); // ������� ������
    std::cout<<"���������� ������ ��� �������� �����: "<<acc1.GetAccountNumber()<<": ";
    std::cin >> Prc;
    if (Prc > 20) 
    {
        std::cerr<<"���������� ������ �� ����� ���� ������ 20%";
        return -1;
    }
    acc1.SetRate(&Prc); // ���. ������

    std::cout<<"������ ��� �������� \n"; // ������ ������ ��� ��������
    std::cout<<"����� ����� (��������): ";
    std::cin >> number;
    std::cout<<"��������� �������� ";
    std::cin>> init_sum;

    BankAccount acc2(number, init_sum); // ������� ������
    std::cout<<"���������� ������ ��� �������� �����: "<<acc2.GetAccountNumber()<<": ";
    std::cin >> Prc;
    if (Prc > 20) 
    {
        std::cerr<<"���������� ������ �� ����� ���� ������ 20%"; 
        return -1;
    }
    acc2.SetRate(&Prc);  // ���. ������

    std::cout<<"������� ������������ �����: ";

    std::cin>>amount; // ������ ���������� ������� ��� ��������

    bool success = Transfer(acc1, acc2, &amount); // �������� ������� � ����. ����������
    if (!success) // � ������ false
    {
        std::cerr<<"�� �������� "<<'('<<acc1.GetAccountNumber()<<')'<<"������������ �����\n"; // ������������ �����
        return 0; // ���������� �������� main()
    }

    std::cout<<"������� �����: "<<acc1.GetAccountNumber()<<" | "<<acc1.GetBalance()<<"���.   ������: "<<acc1.GetRate()<<"% ��������: "<<acc1.GetPercents()<<" ���.\n"; // ������� ����������
    std::cout<<"������� �����: "<<acc2.GetAccountNumber()<<"  | "<<acc2.GetBalance()<<"���.  ������: "<<acc2.GetRate()<<"% ��������: "<<acc2.GetPercents()<<" ���.\n"; // ������� ����������
}
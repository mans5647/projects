#include "template.h"
#include "sum.h"
#include <iostream>

int main()
{
    auto ia = 0, ib = 0;
    auto da = 0.0, db = 0.0;
    std::string sa, sb;

    std::cout<<"Enter ints: \n";
    std::cin >> ia;
    std::cin >> ib;
    auto res1 = return_sum(ia, ib);

    std::cout<<"Enter doubles: \n";
    std::cin >> da;
    std::cin >> db;

    auto res2 = return_sum(da, db);

    std::cin.ignore(10, '\n');
    std::cout<<"Enter strings: \n";
    std::getline(std::cin, sa);

    std::getline(std::cin, sb);

    std::string res3 = return_sum(sa, sb);
    std::cout<<"Res1: "<<res1<<'\n';
    std::cout<<"Res2: "<<res2<<'\n';
    std::cout<<"Res3: "<<res3<<'\n';
}
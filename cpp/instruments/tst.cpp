#include <iostream>

int main()
{
    unsigned short var = 34;
    unsigned short & ref = var;

    std::cout<<"The address of our variable is "<<&var<<'\n';
    std::cout<<"The address of our reference is "<<&ref<<'\n';
    std::cout<<"Value under us variable is "<<var<<'\n';
    std::cout<<"Value under us reference is "<<ref<<'\n';
}
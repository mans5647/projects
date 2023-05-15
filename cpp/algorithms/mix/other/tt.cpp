#include <iostream>
#include <ctime>


int main()
{
    std::srand(time(NULL));
    auto i = 48;
    auto g = std::rand() % 100;
    if (49 <= i && i <= 60)
    {
        std::cout<<"OK";
    }
    else
    {
        std::cout<<"Not ok!";
    }
}
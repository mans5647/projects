#include <iostream>

int main()
{
    size_t number;
    std::cout<<"Enter a number: ";
    std::cin>>number;
    if (number < 100 || number > 500000)
    {
        std::cerr<<"Number should be less and more\n";
        main();
    }
    else
    {
        while (number != 0)
        {
            if (number % 2 == 0)
            {
                std::cout<<"Clojnoe\n";
                break;
            }
            else
            {
                std::cout<<"Prostoe\n";
                break;
            }
            number--;
        }
    }
    return 0;
}
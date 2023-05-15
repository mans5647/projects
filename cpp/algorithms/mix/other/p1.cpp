#include <iostream>


void average(int * ptr, size_t n)
{
    double * ptr_average = nullptr;
    double final_average = 0;
    ptr_average = &final_average;

    for (auto i = 0; i < n; i++)
    {
        final_average += ptr[i];
    }
    final_average /= n;
    std::cout<<"Average value of array is: "<<*ptr_average<<'\n';
    return;
}


int main()
{
    size_t n(0);
    std::cout<<"Enter N: ";
    std::cin >> n; 
    int * arr = new int[n];

    for (auto i = 0; i < n; ++i)
    {
        std::cout<<"Enter element of "<<i + 1<<": ";
        std::cin >> arr[i];
    }

    average(arr, n);

    return 0;
}
#include <iostream>

template <typename type>
void insertion_sort(type * arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = i; j > 0 && )
    }
}


template <typename T>
void printArray(T * arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        std::cout<<arr[i]<<' ';
    }
}

int main()
{
    float arr[] = {56.0,3.056,3.34,78.243,23.453,89.423,123.1234};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    insertion_sort(arr, size);
    printArray(arr, size);
    return 0;
}
#include <iostream>
#include <vector>
#include <ctime>

void set_vals(std::vector<std::vector<int>> &vector_ptr);
void print_vector(std::vector<std::vector<int>> &vector_ptr);

void get_Values(std::vector<std::vector<int>> &vector_ptr);

void find_average(std::vector<std::vector<int>> &vector_ptr);

int main(void)
{
    size_t rows, cols;
    std::cout<<"Enter rows amount : ";
    std::cin >> rows;
    std::cout<<"Enter columns amount : ";
    std::cin >> cols;
    system("cls");
    std::vector<int> columns_(cols, 0);
    std::vector<std::vector<int>> sample(rows, columns_);
    std::cout<<"\n\n\n";
    set_vals(sample);
    std::cout<<"\n";
    print_vector(sample);
    std::cout<<"\n";
    get_Values(sample);
    std::cout<<"\n";
    find_average(sample);
    std::cout<<"\n";
    return 0;
}

void set_vals(std::vector<std::vector<int>> &vector_ptr)
{
    srand((unsigned int) time(NULL));
    for (size_t i = 0; i < vector_ptr.size(); i++)
    {
        
        for (size_t j = 0; j < vector_ptr[i].size(); j++)
        {
            vector_ptr[i][j] = rand() % 199;
        }
    }
    return;
}

void print_vector(std::vector<std::vector<int>> & vector_ptr)
{
    for (size_t i = 0; i < vector_ptr.size(); i++)
    {
        for (size_t j = 0; j < vector_ptr[i].size(); j++)
        {
            std::cout<<"Value of "<<i<<" and "<<j<<" is "<<vector_ptr[i][j]<<'\n';
        }
    }
}

void get_Values(std::vector<std::vector<int>> &vector_ptr)
{
    int max = vector_ptr[0][0];
    int min = vector_ptr[0][0];
    for (size_t i = 0; i < vector_ptr.size(); i++)
    {
        for (size_t j = 0; j < vector_ptr.size(); j++)
        {
            if (vector_ptr[i][j] < min)
            {
                min = vector_ptr[i][j];
            }
            if (vector_ptr[i][j] > max)
            {
                max = vector_ptr[i][j];
            }
        }
    }
    std::cout<<"Max element: "<<max<<'\n';
    std::cout<<"Min element: "<<min<<'\n';
    return;
}

void find_average(std::vector<std::vector<int>> &vector_ptr)
{
    long double sum = 0;
    int length = 0;
    for (size_t i = 0; i < vector_ptr.size(); i++)
    {
        
        for (size_t j = 0; j < vector_ptr[i].size(); j++)
        {
            sum+=vector_ptr[i][j];
            length++;
        }
    }
    std::cout<<"Average value of vector is : "<<sum / length<<'\n';
}
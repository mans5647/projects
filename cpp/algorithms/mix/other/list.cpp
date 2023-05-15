#include <iostream>
#include <string>


template <typename T > class my_list
{
    public:
        my_list(size_t Size);
        ~my_list()
        {
            delete[] dynamic_array;
        }
        void push_back(T element);
        void pop_back(void);
        void get_capacity();
        size_t size();
        T get(size_t At_index);
        T& operator[](size_t index);
        friend ostream& operator<<(std::ostream & os, const &my_list list);
        void PrintAll()
        {
            for (size_t i = 0; i < current_size; i++)
            {
                std::cout<<dynamic_array[i];
            }
        }
    private:
        T * dynamic_array;
        int current_size;
        int capacity;
        
};

template <typename T> my_list<T>::my_list(size_t Size)
{
    this->dynamic_array = new T[Size];
    this->capacity = Size;
    this->current_size = 0;
}

template <typename T>
void my_list<T>::push_back(T element)
{
    if (this->current_size == capacity)
    {
        T * new_arr = new T[capacity * 2];
        for (unsigned int iter = 0; iter < capacity * 2; ++iter)
        {
            new_arr[iter] = this->dynamic_array[iter];
        }
        delete[]dynamic_array;
        capacity*=2;
        dynamic_array = new_arr;
    }
    dynamic_array[current_size] = element;
    current_size++;
}

template <typename T > T& my_list<T>::operator[](size_t index)
{
    return dynamic_array[index];
}

template <typename T> friend ostream& my_list<T>::operator<<(std::ostream & os, const &my_list list)
{
    os << list[0];
    return os;
}

template<class T > void my_list<T>::pop_back(void)
{
    signed i;
    dynamic_array[current_size - 1] = i;
    current_size--;
}


template <typename T> T my_list<T>::get(size_t At_index)
{
    if (At_index > dynamic_array[current_size - 1] | At_index < 0)
    {
        throw("no such index");
    }
    return dynamic_array[At_index];
}
template <class T> size_t my_list<T>::size()
{
    return current_size;
}
class instance
{
    public:
    std::string name;
    std::string surname;
    size_t age;
    instance(std::string *t_name, std::string *t_surname, size_t * t_age)
    {
        name = *t_name;
        surname = *t_surname;
        age = *t_age;
    }
};




int main()
{
    std::string nm = "mansur";
    std::string j = "galimov";
    size_t age = 56;
    instance inst = instance(&nm, &j, &age);
    my_list<float> l(25);
    l.push_back(3);
    l.push_back(3);
    l.push_back(3);
    l[0] = 34.5485986;
    l[12] = 34;
    
    my_list<instance> h(3);
    h[0].name = "Mansur";
    std::cout<<h[0].name<<' ';
    
    return 0;
}
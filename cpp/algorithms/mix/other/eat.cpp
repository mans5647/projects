#include <iostream>
#include <utility>
#include <cstdint>
#include <string>

class Pet;
class Dog;
class Cat;

class Animal
{
    public:
    Animal(std::string & name);
    Animal() = default;
    protected:
    std::string name;
};

class Pet
{
    public:
    virtual void Feed() = 0;
};

class Dog : Animal, Pet
{
    public:
    Dog(std::string & name, auto & random, std::uint32_t amount)
    {
        this->name = std::move(name);
        this->random = std::move(random);
        this->amount = std::move(amount);
        
    }
    void Feed() override;
    private:
    std::uint32_t random;
    std::uint32_t amount;
};

void Dog::Feed()
{
    std::cout<<"Dog eating...\n";
    if (random >= (amount - 10) && random <= amount)
    {
        std::cout<<"The dog "<<'`'<<name<<'\''<<" deliciusly ate! Great!"<<'\n';
        
    }
    else
    {
        std::cout<<"Dog "<<'`'<<name<<'\''<<" died!"<<'\n';
        
    }
    return;
}

class Cat : Animal, Pet
{
    public:
    Cat(std::string & name, auto & random, std::uint32_t amount)
    {
        this->name = std::move(name);
        this->random = std::move(random);
        this->amount = std::move(amount);
    }
    void Feed() override;
    private:
    std::uint32_t random;
    std::uint32_t amount;
};

void Cat::Feed()
{
    std::cout<<"Cat eating...\n";
    if ( random >= (amount - 10) && random <= amount)
    {   
        std::cout<<"The cat "<<'`'<<name<<'\''<<" deliciusly ate! Great!"<<'\n';
    }
    else
    {
        std::cout<<"Cat "<<'`'<<name<<'\''<<" died!"<<'\n';
    }
    return;
}


int main()
{
    std::uint32_t amount = 0; // our feed
    std::string name;
    auto i1 = std::rand() % 100; // random value for dog
    auto i2 = std::rand() % 100; // random value for cat
    std::cout<<"You have Dog and Cat! Feed them. \n";
    std::cout<<"Enter amount for dog: ";
    std::cin >> amount;
    std::cin.ignore(10, '\n');
    std::cout<<"Enter dog name: ";
    std::getline(std::cin, name);
    Dog d1(name, i1, amount);
    std::cout<<"Enter amount for cat: ";
    std::cin >> amount;
    std::cin.ignore(10, '\n');
    std::cout<<"Enter cat name: ";
    std::getline(std::cin, name);
    Cat c1(name, i2, amount);
    d1.Feed();
    c1.Feed();
}


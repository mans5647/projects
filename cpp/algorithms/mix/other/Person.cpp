#ifndef CPP_STD
#include <iostream>
#include <vector>
#include <string>
#endif
typedef uint32_t u32;

struct Person
{
    std::string name;
    u32 age;    
    virtual void DisplayInfo() const;
};

void Person::DisplayInfo() const
{
    std::cout<<"Имя: "<<name<<'\n';
    std::cout<<"Возраст: "<<age<<'\n';
}


class Person_Entity : public Person
{
    public:
    static u32 person_count;
    Person_Entity() = default;
    protected:
    void DisplayInfo() const
    {
        std::cout<<"Имя "<<name<<'\n';
        std::cout<<"Возраст: "<<age<<'\n';
    }
    public:
    void Display_Count()
    {
        std::cout<<"Сейчас в компании: "<<person_count<<" сотрудников\n";
    }
    void Display()
    {
        for (auto i = 0; i < persons.size(); i++)
        {
            persons[i].DisplayInfo();
            std::cout<<'\n';
        }
    }
    void Add_Person(Person *prs)
    {
        persons.emplace_back(*prs);
        std::cout<<prs->name<<" добавлен в список сотрудников..."<<'\n';
        person_count++;
    }
    private:
    static std::vector<Person> persons;

    public:
    ~Person_Entity()
    {
        std::cout<<"Завершение работы...";
    }

};


u32 Person_Entity::person_count = 0;
std::vector<Person>Person_Entity::persons;

int main()
{
    std::setlocale(LC_ALL, "ru");
    std::system("chcp 1251");
    Person prs1;
    Person prs2;
    Person prs3;
    Person prs4;

    std::cout<<"Сейчас в компании: "<<Person_Entity::person_count<<" сотрудников\n";
    prs1.name = "John Miller";
    prs1.age = 34;

    prs2.name = "Andrei J.";
    prs2.age = 27;
    

    prs3.name = "Kenny Timmler";
    prs3.age = 44;

    prs4.name = "Karina Slender";
    prs4.age = 45;

    
    Person_Entity persons;

    persons.Add_Person(&prs1);
    persons.Add_Person(&prs2);
    persons.Add_Person(&prs3);
    persons.Add_Person(&prs4);

    persons.Display_Count();
    

    std::cout<<"Информация о сотрудниках \n";
    persons.Display();
   

}


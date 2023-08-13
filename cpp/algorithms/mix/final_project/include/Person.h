#ifndef PERSON_H
#define PERSON_H
#include "./Types.h"
#include "./common.hpp"
#include "./defines.hpp"
#include "./sha1.hpp"
#include "../test.hpp"
#include "./menu.h"
#include <conio.h>
#include <windows.h>
#include <typeinfo>
#define FILE_NAME "products.txt"
#define W_FILE "whouse.txt"
#define FILE_LOGINS "credits.txt"
#define FILE_MENU "menu.txt"
#define LOG_FILE "logs.txt"
#define REQUEST_FILE "requests.txt"
#define REST_MONEY_FILE "restaurant_money.txt"
#define WHOUSE_FILE "warehouse.txt"
#define CLEAR() std::system("cls");
#define PRESS "Press any key to return to menu... ";
#define NOT_FOUND "There is no such object...";
#define VALID_NAME_LENGTH 8
#define VALID_PASSWORD_LENGTH 10
#define EMPTY "---"

#define PASSWORD_RULES "\t\t--- Password length might be at least 10 characters\n\\
\t\t--- Password should contain numbers\n\\
\t\t--- Password should contain special characters like @,$ % and etc.\n\\
\t\t--- Password should contain at least 1 Upper Letter!\n";


namespace project
{



    const std::map<unsigned int, const char*> roles = {
    {1, ADMIN},
    {2, WAITER},
    {3, COOK},
    {4, ACCOUNT},
    {5, W_HOUSE},
    {6, PROVIDER}
    };

    void WriteLog(std::string && line) // функция для записи логов
    {
        std::ofstream log_file(LOG_FILE, std::ios::app);
        log_file << line <<'\n';
        log_file.close();
    }

    std::string GetTime() // функция для получения текущего времени
    {
        const auto now = std::chrono::system_clock::now();
        const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
        return ctime(&t_c);
    }

    struct LoginData // структура для представления логина
    {
        std::string name;
        std::string surname;
        std::string patron;
        std::string password;
        std::string salt;
        int role;
        LoginData() = default;
        LoginData(const LoginData & another)
        {
            name = std::move(another.name);
            surname = std::move(another.surname);
            password = std::move(another.password);
            salt = std::move(another.salt);
            patron = std::move(another.patron);
            role = std::move(another.role);
        }

        LoginData & operator=(const LoginData & Data)
        {
            name = std::move(Data.name);
            surname = std::move(Data.surname);
            password = std::move(Data.password);
            salt = std::move(Data.salt);
            patron = std::move(Data.patron);
            role = std::move(Data.role);
            return *this;
        }

    friend std::ostream & operator<< (std::ostream& os, LoginData & dt)
    {
        os << dt.name <<","<<dt.surname<<","<<dt.patron<<","<<dt.password<<","<<dt.salt<<","<<dt.role<<";\n";
        return os; // оператор для ввода в поток
    }
    friend std::istream & operator >> (std::istream & is, LoginData & dt)
    {
        std::getline(is, dt.name, ',');
        std::getline(is, dt.surname, ',');
        std::getline(is, dt.patron, ',');
        std::getline(is, dt.password, ',');
        std::getline(is, dt.salt, ',');
        std::string role;
        std::getline(is, role, ';');
        is.ignore(100, '\n');
        dt.role = std::stoi(role);
        return is; // оператор для извлечения из потока
    }


    };


    struct SortNames // структура для сортировки имен
    {
        bool operator()(std::shared_ptr<LoginData> & first,std::shared_ptr<LoginData> & second)
        {
            return first->name < second->name;
        }
    };

    class PrintMenus // структура для вывода меню
    {
        public:
        void operator()(const std::shared_ptr<MenuItem> &item)
        {
            std::cout<<item->name<<'\t'<<item->description<<'\t'<<item->gram<<'\t'<<item->price<<'\t'
            << item->time<<'\n';
            std::cout<<"Products are:\n";
            for (auto i : item->Products)
            {
                std::cout<<"\t\t--- Id: "<<i->id<<'\n';
                std::cout<<"\t\t--- Name: "<<i->name<<'\n';
                std::cout<<"\t\t--- Price: "<<i->price<<'\n';
            }
            std::cout<<" ----- Menu item end ----- \n";
        }
    };

    template <typename Collection, typename ValueType = Collection>

    long b_src(Collection & col, std::size_t first, std::size_t second, ValueType & value);
    // бинарный поиск (различные специализации)
    template <>
    long b_src(std::vector<std::shared_ptr<LoginData>> &logins,
    std::size_t first, std::size_t second, std::string & login)
    {
        SortNames srt;
        std::sort(logins.begin(), logins.end(), srt);

        while (first <= second)
        {
            long mid = first + (second - first) / 2;
            if (logins[mid]->name == login)
            {
                return mid;
            }
            if (logins[mid]->name < login)
            {
                first = mid + 1;
            }
            else
            {
                second = mid - 1;
            }
        }
        return -1;
    }

    template <>
    long b_src(std::vector<std::shared_ptr<MenuItem>> & menus,
    std::size_t first, std::size_t second, std::string & dish_name)
    {
        std::sort(menus.begin(), menus.end(),
        [](std::shared_ptr<MenuItem> & first,std::shared_ptr<MenuItem> & second)
        { return first->name < second->name; });
        while (first <= second)
        {
            long mid = first + (second - first) / 2;
            if (menus[mid]->name == dish_name)
            {
                return mid;
            }
            if (menus[mid]->name < dish_name)
            {
                first = mid + 1;
            }
            else
            {
                second = mid - 1;
            }
        }
        return -1;
    }



    using namespace Types;

    struct Find_Id // для нахождения айди
        {
            Find_Id(uint Id) : Id(Id) {}
            bool operator()(std::shared_ptr<Product> & pr)
            {
                return pr->id == Id;
            }
            uint Id;
        };
    class SysAdmin // класс системного администратора
    {

        public:
        explicit SysAdmin(LoginData & log_data, std::vector<std::shared_ptr<LoginData>> & logins);
        // конструктор
        bool CorrectCommand(std::string & com); // для вызова команды
        void Session(); // сессия пользователя


        bool update_item(uint & Id); // обновления продукта
        bool delete_item(uint & Id); // удаления продукта
        bool AddItem(); // добавления продукта
        bool read_item(uint & Id);  // чтение продукта


        bool AddUser(); // добалвения пользователя
        bool ReadUser(std::string & name); // чтения пользователя
        bool UpdateUser(std::string & name); // обновления пользователя
        bool DeleteUser(std::string & name); // удаления пользователя


        bool AddMenu(); // добавления пункта меню
        bool UpdateMenu(std::string & dish_name); // обновление пункта меню
        bool DeleteMenu(std::string & dish_name);// удаление пункта меню
        bool ReadMenu(std::string & dish_name);// чтение пункта меню

        bool GetAllMenu(); // получение всего меню
        void WriteAllMenu(); // запись всего меню
        bool GetData_from_file();  // получение продуктов
        bool GetUsersFromFile(); // получение пользователей
        void WriteData_to_file();  // запись продуктов
        void PrettyPrintUsers(); // вывод в приличном виде пользователей
        std::shared_ptr<Product> GetProduct(std::ifstream & file); // чтение из потока продукта
        void WriteItem(std::shared_ptr<Product>& pr, std::ostream & Out); // запись продукта
        void WriteUser(std::shared_ptr<LoginData> & log, std::ostream & Out); // запись пользователя
        void WriteAllUsers(); // запись всех пользователей
        void PrettyPrintSelfData(); // вывод в приличном виде персональной информации
        bool PrettyPrintProducts(); // вывод в приличном виде продуктов
        bool PrettyPrintMenus(); // вывод в приличном виде всего меню
        void LoadLogs(); // загрузка логов
        friend bool Password_validity(std::string & password); // проверка валидности пароля 
        private:
        std::vector<std::shared_ptr<LoginData>> logins; // массив логинов
        std::vector<std::shared_ptr<Product>> Products; // массив продуктов
        std::vector<std::shared_ptr<MenuItem>> Menus; // массив меню
        std::vector<std::string> Logs; // массив логов
        LoginData logdata; // персональная информация
        const std::vector<const char *> CommandList =
        {
            NULL,
            "getusers", // 1 list all users :: ok
            "getproducts", // 2 list all products :: ok
            "changeitem", // 3 update item :: ok
            "changeuser", // 4 update user :: ok
            "additem", // 5 insert item :: ok
            "delete", // 6 delete item :: ok
            "getjournal", // 7 list actions :: not
            "list", // 8 list commands :: ok
            "info", // 9 getpersonalinfo :: ok
            "adduser", // 10 Adds user to logins :: ok
            "deluser", // 11 Removes user by name :: ok
            "getuser", // 12 Get personal user info :: ok
            "addmenu", // 13 - Adds new menu object to list of menu's :: ok
            "delmenu", // 14 - Removes menu item by name or id :: ok
            "chmenu", // 15 - Changes menu item by property :: ok
            "rdmenu", // 16 - Get menu item by id ok
            "getmenu" // 17 ok
        };


        std::vector<unsigned int> Keys; // массив ключей 
        std::string GetRole(unsigned int Key) // получение роли
        {
            return (*roles.find(Key)).second;
        }
    };

    SysAdmin::SysAdmin(LoginData & log_data, std::vector<std::shared_ptr<LoginData>> & logins)
    {
        logdata = log_data;
        this->logins = std::move(logins);
    }


    bool Password_validity(std::string & password)
    {
        if (password.length() < VALID_PASSWORD_LENGTH)
        {
            return false;
        }
        if (std::none_of(password.cbegin(), password.cend(),
        [](char x)
        {return (x >= 0x21 && x <= 0x2F)
        || x == 0x40
        || (x >= 0x5B && x <= 0x60);}))
        {
            return false;
        }
        if (std::none_of(password.cbegin(), password.cend(), [](char x)
        {return x >= 0x30 && x <= 0x39;}))
        {
            return false;
        }

        if (std::none_of(password.cbegin(), password.cend(), [](char x)
        {return x >= 65 && x <= 90; }))
        {
            return false;
        }
        return true;
    }




    void SysAdmin::Session()
    {
        std::string command;
        std::cout<<"Welcome to admin panel, "<<logdata.name<<":\n";
        std::cout<<"Any below command are permitted: \n";
        for (auto i = CommandList.cbegin() + 1;i != CommandList.cend(); i++)
        {
            std::cout<<*i<<"\n";
        }

        while (command != "exit")
        {

            std::cout<<"\n: ";
            std::getline(std::cin, command);
            bool is = CorrectCommand(command);
            if (!is)
            {
                std::cerr<<"\nFailed to perform command...\n";
            }
            else
            std::cout<<"\nCommand executed successfully...\n";
        }
        std::cout<<"\n\n";
        std::cin.ignore(10, '\n');
    }

    void SysAdmin::WriteAllUsers()
    {
        std::ofstream fl(FILE_LOGINS, std::ios::out);
        if (fl.is_open())
        {
            for (auto i : logins)
            {
                WriteUser(i, fl);
            }
        }
    }


    bool SysAdmin::CorrectCommand(std::string & com)
    {
        bool Success = false, st = false;
        if (com == CommandList[1])
        {
            PrettyPrintUsers();
            Success = true;
        }
        else if (com == CommandList[2])
        {
            PrettyPrintProducts();
            Success = true;
        }

        else if (com == CommandList[3])
        {
            uint id;
            std::cout<<"Enter product id: ";
            std::cin >> id;
            st = update_item(id);
            if (st) Success = true;
        }
        else if (com == CommandList[4])
        {
            std::string Name;
            std::cout<<"Enter name of user which will be changed: ";
            std::getline(std::cin, Name);
            Success = (UpdateUser(Name)) ? true : false;
        }
        else if (com == CommandList[5] )
        {
            st = AddItem();
            if (st) Success = true;
        }
        else if (com == CommandList[6])
        {
            uint id;
            std::cout<<"Enter product id: ";
            std::cin >> id;
            st = delete_item(id);
            if (st) Success = true;
        }
        else if (com == CommandList[7])
        {
            LoadLogs();
            Success = true;
        }
        else if (com == CommandList[8])
        {
            for (auto i = CommandList.cbegin() + 1; i != CommandList.cend(); i++)
            {
                std::cout<<*i<<"\n";
            }
            Success = true;
        }
        else if (com == CommandList[9])
        {
            PrettyPrintSelfData();
            Success = true;
        }
        else if (com == CommandList[10])
        {
            Success = (AddUser()) ? true : false;
        }
        else if (com == CommandList[11])
        {
            std::string name;
            std::cout<<"Enter name: ";
            std::getline(std::cin, name);
            Success = (DeleteUser(name)) ? true : false;
        }
        else if (com == CommandList[12])
        {
            std::string name;
            std::cout<<"Enter name: ";
            std::getline(std::cin, name);
            Success = (ReadUser(name)) ? true : false;
        }
        else if (com == CommandList[13])
        {
            Success = (AddMenu()) ? true : false;
        }
        else if (com == CommandList[14])
        {
            std::string dish_name;
            std::cout<<"Enter dish name to delete it: ";
            std::getline(std::cin, dish_name);
            Success = (DeleteMenu(dish_name)) ? true : false;
        }
        else if (com == CommandList[15])
        {
            std::string dish_name;
            std::cout<<"Enter dish name to change: ";
            std::getline(std::cin, dish_name);
            Success = (UpdateMenu(dish_name)) ? true : false;
        }
        else if (com == CommandList[16])
        {
            std::string dish_name;
            std::cout<<"Enter dish name to read: ";
            std::getline(std::cin, dish_name);
            Success = (ReadMenu(dish_name)) ? true : false;
        }
        else if (com == CommandList[17])
        {
            Success = (PrettyPrintMenus()) ? true : false;
        }
        else
        {
            Success = false;
        }

        return Success;
    }






    std::shared_ptr<Product> SysAdmin::GetProduct(std::ifstream & file)
    {
        std::shared_ptr<Product> NewProduct(new Product);
        file >> *NewProduct;
        return NewProduct;
    }

    void SysAdmin::WriteItem(std::shared_ptr<Product> & pr, std::ostream & Out)
    {
        Out << * pr;
    }




    std::shared_ptr<LoginData> ReadItem(std::ifstream & file)
    {
        std::shared_ptr<LoginData> l(new LoginData);
        file >> *l;
        return l;
    }

    void SysAdmin::WriteUser(std::shared_ptr<LoginData> & log, std::ostream & Out)
    {
        Out << * log;
    }

    bool SysAdmin::GetUsersFromFile()
    {
        if (!logins.empty())
        {
            logins.clear();
        }
        bool Success = false;
        std::ifstream File(FILE_LOGINS, std::ios::in);
        if (File.is_open())
        {
            if (File.peek() == EOF)
            {
                return Success;
            }
            while (File.peek() != '\n')
            {
                if (File.eof())
                {
                    Success = true;
                    break;
                }
                logins.push_back(ReadItem(File));
            }
        }
        return Success;
    }
    bool SysAdmin::GetData_from_file()
    {
        bool Success = false;
        std::ifstream File(FILE_NAME, std::ios::in);
        if (File.is_open())
        {
            if (File.peek() == EOF)
            {
                return Success;
            }
            while (File.peek() != '\n')
            {
                if (File.eof())
                {
                    Success = true;
                    break;
                }
                Products.push_back(GetProduct(File));
            }
        }
        return Success;
    }

    void SysAdmin::WriteData_to_file()
    {
        std::ofstream file;
        file.open(FILE_NAME, std::ios::out);
        if (file.is_open())
        {
            for (auto i = Products.begin(); i != Products.end(); i++)
            {
                WriteItem(*i, file);
            }
        }
    }

    void SysAdmin::PrettyPrintUsers()
    {
        CLEAR();
        logins.clear();
        bool is = GetUsersFromFile();
        if (!is)
        {
            std::cerr<<"Could't retrieve users from file...";
            auto ExitChar = getch();
            return;
        }
        std::string role;
        std::cout<<"Name\t\tSurname\t\tPatronymic\t\tRole\n\n";
        for (auto i = logins.cbegin(); i != logins.cend(); i++)
        {
            role = GetRole((*i)->role);
            std::cout<<(*i)->name<<"\t\t"<<(*i)->surname<<"\t\t"<<(*i)->patron<<"\t\t"<<role<<"\n";
        }
        std::cout<<PRESS;
        auto ExitChar = getch();
        return;
    }

    void SysAdmin::PrettyPrintSelfData()
    {
        CLEAR();
        std::cout<<"Your Credentials: \n";
        std::cout<<"Name: "<<logdata.name<<"\n";
        std::cout<<"Surname: "<<logdata.surname<<"\n";
        std::cout<<"Patronymic: "<<logdata.patron<<"\n";
        std::cout<<"Role: "<<logdata.role<<"\n";
        std::cout<<PRESS;
        auto ecode = getch();
        return;
    }

    bool SysAdmin::PrettyPrintProducts()
    {
        CLEAR();
        bool OK = true;
        if (Products.empty())
        {
            OK = (GetData_from_file()) ? true : false;
        }

        std::cout<<"ID\t\tNAME\t\tPRICE\n\n";
        for (auto it = Products.cbegin(); it != Products.cend(); it++)
        {

            std::cout<<(*it)->id<<"\t\t"<<(*it)->name<<"\t\t"<<(*it)->price<<'\n';
        }
        std::cout<<PRESS;
        auto ex = getch();
        return OK;
    }
    bool SysAdmin::AddItem()
    {
        CLEAR();
        Products.clear();
        bool is = GetData_from_file();
        uint Id, price;
        std::string name;
        std::cout<<"Enter new product name: ";
        std::getline(std::cin, name);
        std::cout<<"Enter product id: ";
        std::cin >> Id;
        std::cout<<"Enter product price: ";
        std::cin >> price;
        if (name.empty())
        {
            std::cerr<<"Name should not be null\n";
            return false;
        }
        std::shared_ptr<Product> New_Product(new Product);
        New_Product->name = name;
        New_Product->id = Id;
        New_Product->price = price;
        Products.push_back(New_Product);
        std::ofstream File("products.txt", std::ios::out);
        if (File.is_open())
        {
            for (auto i = Products.begin(); i != Products.end(); i++)
            {
                WriteItem(*i, File);
            }
        }
        std::cout<<"Item added!\n";
        std::cout<<PRESS;
        std::cin.ignore(100, '\n');
        auto ex = getch();
        return true;
    }
    bool SysAdmin::read_item(uint & Id)
    {
        CLEAR();
        bool Ok = false;

        Products.clear();
        bool GetOk = GetData_from_file();
        if (GetOk)
        {
            auto iter = std::find_if(Products.begin(), Products.end(), Find_Id(Id));
            if (iter != Products.end())
            {
                std::cout<<"Product ID: "<<(*iter)->id<<"\n";
                std::cout<<"Product name: "<<(*iter)->name<<"\n";
                std::cout<<"Product price: "<<(*iter)->price<<"\n";
                std::cout<<"--------------------------------\n";
                Ok = true;
            }
            else
            {
                std::cerr<<"There is no such product with this id...\n";
                Ok = false;
            }
        }
        std::cout<<PRESS;
        auto i = getch();
        return Ok;
    }

    bool SysAdmin::update_item(uint & Id)
    {
        CLEAR();
        Products.clear();
        bool st = GetData_from_file();
        if (!st) return false;
        auto iter = std::find_if(Products.begin(), Products.end(), Find_Id(Id));
        if (iter != Products.end())
        {
            std::cout<<"What you need to change?:\n";
            std::cout<<"1. Name 2. Price 3. Id\n";
            std::cout<<": ";
            int action = 0;
            std::cin>> action;
            switch (action)
            {
                case 1:
                {
                    std::cin.ignore(100, '\n');
                    std::string New_name;
                    std::cout<<"Enter new name: ";
                    std::getline(std::cin, New_name);
                    if (!New_name.empty())
                    {
                        (*iter)->name = New_name;
                        std::ofstream fl("products.txt", std::ios::out);
                        if (fl.is_open())
                        {
                            for (uint i = 0; i < Products.size(); i++)
                            {
                                WriteItem(Products[i], fl);
                            }
                        }

                    }
                    break;
                }
                case 2:
                {
                    uint price;
                    std::cout<<"Enter new price: ";
                    std::cin >> price;
                    (*iter)->price = price;
                    break;
                }
                case 3:
                {
                    uint id;
                    std::cout<<"Enter new Id: ";
                    std::cin >> id;
                    (*iter)->id = id;
                    break;
                }
                default:
                {
                    std::cerr<<"Wrong product property...\n";
                    return false;
                }
            }
            WriteData_to_file();
            return true;
        }
        else
        {
            return false;
        }
        return false;
    }

    bool SysAdmin::delete_item(uint & Id)
    {
        CLEAR();
        Products.clear();
        bool default_result = false;
        bool ok = GetData_from_file();
        if (ok)
        {
            auto iter = std::find_if(Products.begin(), Products.end(), Find_Id(Id));
            if (iter != Products.end())
            {
                Products.erase(iter);
                default_result = true;
                std::cout<<"Success remove...\n";
                WriteData_to_file();
            }
            else
            {
                std::cerr<<NOT_FOUND"\n";
            }
        }
        std::cout<<PRESS;
        auto ex = getch();
        return default_result;
    }

    bool SysAdmin::AddUser()
    {
        CLEAR()
        std::string name, surname, patron, password,conf_password;
        int role;
        std::cout<<"----- User adding -----\n\n";
        std::cout<<"Enter username: ";
        std::getline(std::cin, name);
        if (name.length() < VALID_NAME_LENGTH)
        {
            std::cerr<<"Name should be at least 8 chars\n";
            return false;
        }
        std::cout<<"Enter surname: ";
        std::getline(std::cin, surname);
        if (surname.empty())
        {
            std::cerr<<"Surname length might be at least 8 chars\n";
            return false;
        }
        std::cout<<"Enter patronymic (optional): ";
        std::getline(std::cin, patron);
        if (patron.empty())
        {
            patron = EMPTY;
        }
        std::cout<<"Enter password: ";
        std::getline(std::cin, password);

        if (!Password_validity(password))
        {
            std::cerr<<PASSWORD_RULES;
            return false;
        }

        std::cout<<"Confirm password: ";
        std::getline(std::cin, conf_password);
        if (conf_password != password)
        {
            std::cerr<<"Passwords does not match";
            return false;
        }

        std::cout<<"Enter role: ";
        std::cin >> role;

        logins.clear();
        if (GetUsersFromFile())
        {
            if (b_src(logins, 0, logins.size() - 1, name) == -1)
            {
                std::string salt = gensalt();
                std::string final_password = password + salt;
                SHA1 sh;
                sh.update(final_password);
                LoginData NewUser;
                NewUser.name = name;
                NewUser.surname = surname;
                NewUser.patron = patron;
                NewUser.password = sh.final();
                NewUser.salt = salt;
                NewUser.role = role;
                WriteToFile(NewUser);
                std::wcout<<"Success registration\n";
                return true;
            }
            else
            {
                std::wcout<<"Such user already in system";
                return false;
            }
        }
        else
        {
            std::wcout<<"Failed";
            return false;
        }




    }

    bool SysAdmin::UpdateUser(std::string & name)
    {
        CLEAR()
        logins.clear();
        bool ok = false;
        std::string criteria;

        if (GetUsersFromFile())
        {
            long index = b_src(logins, 0, logins.size() - 1, name);
            if (index != -1)
            {
                int act;
                std::cout<<"What do you want to change?\n \\
                            1 - name, 2 - surname 3 - patronymic\n \\
                            4 - password 5 - role\n";
                std::cout<<": ";
                std::cin >> act;
                std::cin.ignore(1000, '\n');
                switch (act)
                {
                    case 1:
                    {
                        std::cout<<"Enter new name: ";
                        std::getline(std::cin, criteria);
                        if (criteria.empty())
                        {
                            std::cerr<<"Name should not be empty.\n";
                            return false;
                        }
                        if (criteria.length() < 8)
                        {
                            std::cerr<<"Name must be at least 8 chars\n";
                            return false;
                        }

                        logins[index]->name = criteria;
                        WriteAllUsers();
                        std::cout<<"Name changed successfully... ";
                        ok = true;
                        break;
                    }
                    case 2:
                    {
                        std::cout<<"Enter new surname: ";
                        std::getline(std::cin, criteria);
                        if (criteria.empty())
                        {
                            std::cerr<<"Surname should not be empty...\n";
                            return false;
                        }
                        logins[index]->surname = criteria;
                        WriteAllUsers();
                        std::cout<<"Surname changed successfully... ";
                    }
                    case 3:
                    {
                        std::cout<<"Enter new patronymic: ";
                        std::getline(std::cin, criteria);
                        if (criteria.empty())
                        {
                            criteria = EMPTY;
                        }
                        logins[index]->patron = criteria;
                        WriteAllUsers();
                        std::cout<<"Patronymic changed successfully... ";
                        ok = true;
                        break;
                    }
                    case 4:
                    {
                        std::cout<<"Enter new password: ";
                        std::getline(std::cin, criteria);
                        if (!Password_validity(criteria))
                        {
                            std::cerr<<PASSWORD_RULES;
                            ok = false;
                        }
                        else
                        {
                            std::string Confirmation;
                            std::cout<<"Confirm password: ";
                            std::getline(std::cin, Confirmation);
                            if (Confirmation != criteria)
                            {
                                std::cerr<<"Passwords does not match!";
                                ok = false;
                            }
                            else
                            {
                                std::string salt = gensalt();
                                std::string final_password = criteria + salt;
                                SHA1 sh;
                                sh.update(final_password);
                                logins[index]->password = final_password;
                                logins[index]->salt = salt;
                                ok = true;
                            }
                        }
                        break;
                    }
                    case 5:
                    {
                        std::cout<<"Enter new role: ";
                        std::getline(std::cin, criteria);
                        if (criteria.empty())
                        {
                            return false;
                        }
                        if (std::any_of(criteria.cbegin(), criteria.cend()
                        , [](char x) { return x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z';}))
                        {
                            return false;
                        }

                        int new_role = std::stoi(criteria);
                        if (new_role <= 0 || new_role > 6)
                        {
                            return false;
                        }
                        logins[index]->role = new_role;
                        WriteAllUsers();
                        std::cout<<"Role changed successfully... \n";
                        ok = true;
                        break;
                    }
                    default:
                    {
                        std::cout<<"Wrong property selected...\n";
                        ok = false;
                    }
                }

            }
            else
            {
                std::cerr<<"User not found... ";
                ok = false;
            }
        }
        else
        {
            std::cerr<<"Error reading file... ";
            ok = false;
        }
        std::cout<<PRESS;
        auto i = getch();
        return ok;
    }

    bool SysAdmin::ReadUser(std::string & name)
    {
        CLEAR()
        bool ok = false;
        if (logins.empty())
        {
            GetUsersFromFile();
        }
        long pos = b_src(logins, 0, logins.size() - 1, name);
        if (pos != -1)
        {
            std::cout<<"Name: "<<logins[pos]->name<<'\n';
            std::cout<<"Surname: "<<logins[pos]->surname<<'\n';
            std::cout<<"Patronymic: "<<logins[pos]->patron<<'\n';
            std::cout<<"Role: "<<logins[pos]->role<<'\n';
            ok = true;
        }
        else
        {
            std::cerr<<"User not found...\n";
        }
        std::cout<<PRESS;
        auto exit = getch();
        return ok;
    }

    bool SysAdmin::DeleteUser(std::string & name)
    {
        bool ok = false;
        if (logins.empty())
        {
            GetUsersFromFile();
        }
        long pos = b_src(logins, 0, logins.size() - 1, name);
        if (pos != -1)
        {
            logins.erase(logins.begin() + pos);
            std::cout<<"User deleted...\n";
            WriteAllUsers();
            ok = true;
        }
        else
        {
            std::cerr<<"User not found...\n";
        }
        std::cout<<PRESS;
        auto exit = getch();
        return ok;
    }

    bool SysAdmin::GetAllMenu()
    {
        bool result = false;
        std::ifstream file(FILE_MENU, std::ios::in);
        if (file.is_open())
        {
            while (file.peek() != '\n')
            {
                if (file.eof())
                {
                    result = true;
                    break;
                }
                Menus.push_back(GetMenuItem(file));
            }
        }
        else
        {
            std::cerr<<"There no menu item. Add new menu item to read this file.\n";
            result = false;
        }

        return result;

    }

    void SysAdmin::WriteAllMenu()
    {
        std::ofstream file(FILE_MENU, std::ios::out);
        if (file.is_open())
        {
            for (auto i : Menus)
            {
                WriteMenuItem(file, *i);
            }
        }
    }

    bool SysAdmin::AddMenu()
    {
        CLEAR();
        if (Menus.empty()) GetAllMenu();
        if (Products.empty()) GetData_from_file();
        std::string name, desc;
        float gram,price,time;
        std::cout<<"--- Adding menu item ---\n";
        std::cout<<"Enter new menu item name: ";
        std::getline(std::cin, name);
        if (name.empty()) return false;
        std::cout<<"Enter new description: ";
        std::getline(std::cin, desc);
        if (desc.empty()) return false;
        std::shared_ptr<MenuItem> item(new MenuItem);
        std::string End;
        std::cout<<"Enter products: \n";
        std::cout<<"Available products: \n";
        for (auto i : Products)
        {
            std::cout<<i->id<<" -- "<<i->name<<'\n';
        }
        while (true)
        {
            std::cout<<"Enter product for "<<name<<": ";
            std::getline(std::cin, End);
            if (End == "stop")
            {
                break;
            }
            if (std::any_of(End.cbegin(), End.cend(),
            [](char x){return x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z' || x >= 32 && x <= 47; }))
            {
                std::cerr<<"Enter valid id!\n";
            }
            else
            {
                uint32_t id = 0;
                try
                {
                    id = std::stoi(End);
                }
                catch (std::invalid_argument & arg)
                {
                    std::clog<<"Id may be empty. Writing products back. Reverting operation.";
                    std::ofstream rebuild("products.txt", std::ios::out);
                    for (auto i : Products)
                    {
                        rebuild << *i;
                    }
                    return false;
                }
                auto iter = std::find_if(Products.begin(), Products.end(), Find_Id(id));
                if (iter != Products.end())
                {
                    item->Products.push_back(*iter);
                }
                else
                {
                    std::cerr<<"No such id...\n";
                }
            }
        }


        std::cout<<"Enter new gram (gr): ";
        std::cin >> gram;
        std::cout<<"Enter new price: ";
        std::cin >> price;
        std::cout <<"Enter new time of cooking: ";
        std::cin >> time;
        item->name = name;
        item->description = desc;
        item->gram = gram;
        item->price = price;
        item->time = time;
        Menus.push_back(item);
        WriteAllMenu();
        std::cout<<"Menu item added!\n";
        std::cout<<PRESS;
        auto exit = getch();
        return true;
    }

    bool SysAdmin::PrettyPrintMenus()
    {
        CLEAR();
        PrintMenus pr;
        if (Menus.empty()) GetAllMenu();
        std::for_each(Menus.cbegin(), Menus.cend(), pr);
        return true;
    }

    bool SysAdmin::UpdateMenu(std::string & dish_name)
    {
        CLEAR();
        bool res = false;
        if (Menus.empty()) GetAllMenu();
        long pos = b_src(Menus, 0, Menus.size() - 1, dish_name);
        if (pos != -1)
        {
            std::string name,description;
            float gram, price,time;
            int action;
            std::cout<<"Changing `"<<Menus[pos]->name<<"`\n";
            std::cout<<"\\
            \t\t1 - name\n\\
            \t\t2 - description\n\\
            \t\t3 - grammovka\n\\
            \t\t4 - price\n\\
            \t\t5 - time\n\\
            \tAction: ";
            std::cin >> action;
            std::cin.ignore(1, '\n');
            switch (action)
            {
                case 1:
                {
                    std::cout<<"Enter new product name: ";
                    std::getline(std::cin, name);
                    Menus[pos]->name = name;
                    break;
                }
                case 2:
                {
                    std::cout<<"Enter new description: ";
                    std::getline(std::cin, description);
                    Menus[pos]->description = description;
                    break;
                }
                case 3:
                {
                    std::cout<<"Enter new grammovka: ";
                    std::cin >> gram;
                    Menus[pos]->gram = gram;
                    break;
                }
                case 4:
                {
                    std::cout<<"Enter new price: ";
                    std::cin >> price;
                    Menus[pos]->price = price;
                    break;
                }
                case 5:
                {
                    std::cout<<"Enter new time of cooking: ";
                    std::cin >> time;
                    Menus[pos]->time = time;
                    break;
                }
                default:
                {
                    std::cerr<<"Wrong action...\n";
                    return false;
                }
            }
            std::cout<<"Changes saved...\n";
            WriteAllMenu();
            res = true;
        }
        else
        {
            std::cerr<<"Not found!\n";
        }
        std::cout<<PRESS;
        auto exit = getch();
        return res;
    }

    bool SysAdmin::DeleteMenu(std::string & dish_name)
    {
        CLEAR();
        bool res = false;
        if (Menus.empty()) GetAllMenu();
        long pos = b_src(Menus, 0, Menus.size() - 1, dish_name);
        if (pos != -1)
        {
            Menus.erase(Menus.begin() + pos);
            std::cout<<"Deleted menu item `"<<dish_name<<"`...\n";
            res = true;
            WriteAllMenu();
        }
        else
        {
            std::cerr<<"Not found!\n";
        }
        std::cout<<PRESS;
        auto exit = getch();
        return res;
    }

    bool SysAdmin::ReadMenu(std::string & dish_name)
    {
        CLEAR();
        bool res = false;
        if (Menus.empty()) GetAllMenu();
        long pos = b_src(Menus, 0, Menus.size() - 1, dish_name);
        if (pos != -1)
        {
            std::cout<<"Expanded information about `"<<dish_name<<":\n";
            std::cout<<"Name: "<<Menus[pos]->name<<'\n';
            std::cout<<"Desription: "<<Menus[pos]->description<<'\n';
            std::cout<<"Grammovka: "<<Menus[pos]->gram<<'\n';
            std::cout<<"Price: "<<Menus[pos]->price<<'\n';
            std::cout<<"Time of cooking: "<<Menus[pos]->time<<'\n';
            res = true;
        }
        else
        {
            std::cerr<<"Not found!\n";
        }
        std::cout<<PRESS;
        auto exit = getch();
        return res;
    }

    void SysAdmin::LoadLogs()
    {
        std::ifstream logger(LOG_FILE, std::ios::in);
        if (logger.is_open())
        {
            if (logger.peek() == -1)
            {
                std::cout<<"Log file is empty. Sometime it will be filled...\n";
            }
            else
            {
                std::string tmp;
                while (std::getline(logger, tmp))
                {
                    std::clog << tmp;
                }
            }
        }
        else
        {
            std::cout<<"There are no actions performed by employees...\n";
        }
        std::cout<<"\n";
        std::cout<<PRESS;
        auto exit = getch();
    }

    class Warehouser // класс складского
    {
        public:
        Warehouser() = default; // конструктор по умолчанию
        Warehouser(const LoginData & login); // констуктор копирования
        void Session(); // сессия пользователя
        void make_request(); // создание запроса
        void AllProducts(); // получение продуктов
        std::set<std::shared_ptr<Product>> types; // типы продуктов

        private:
        std::shared_ptr<Product> GetSingle(std::ifstream & file); // получение продукта
        bool get_products(); // получение всех продуктов
        std::vector<std::shared_ptr<Product>> products_available; // доступные продукты
        std::vector<std::shared_ptr<Request>> all_products; // все продукты
        std::vector<std::shared_ptr<Request>> requests; // запросы
        std::vector<const char *> list = { // лист команд
            NULL,
            "makequery", // 1 - creates request and sends if possible
            "whouse", // 2 - sees all products
            "logout" // 3 - exits
        };
        LoginData info;


        protected:
        void get_requests() // получение всех запросов
        {
            std::ifstream file("requests.txt", std::ios::in);
            if (file.is_open())
            {
                if (file.peek() == -1)
                {
                    std::clog<<"Seems you didn't made any request...\n";
                }
                while (file.peek() != '\n')
                {
                    if (file.eof()) break;
                    requests.push_back(getter::ReadItem<Request, Request>(file));
                }
            }
            else
            {
                std::clog<<"Error!\n";
            }
            file.close();
        }

        bool get_all_products() // получение всех продуктов
        {
            std::ifstream file(W_FILE, std::ios::in);
            bool ok = false;
            if (file.is_open())
            {
                if (file.peek() == -1)
                {
                    std::clog<<"Your warehouse is empty!\n";
                }
                else
                {
                    while (file.peek() != '\n')
                    {
                        if (file.eof()) 
                        {
                            ok = true;
                            break;
                        }
                        all_products.push_back(getter::ReadItem<Request, Request>(file));
                    }
                }
            }
            else
            {
                std::clog<<"File not created. Create file.\n";
            }
            file.close();
            return ok;
        }


    };

    Warehouser::Warehouser(const LoginData & logins)
    {
        info = logins;
    }

    void Warehouser::Session()
    {
        std::cout<<"Hello `"<<info.name<<"`\n";
        std::cout<<"Commands are following: \n";
        for (auto i = list.cbegin() + 1; i != list.cend(); i++)
        {
            std::cout<<*i<<"\n";
        }
        std::string command;
        while (true)
        {
            std::cout<<"\n: ";
            std::getline(std::cin, command);
            if (command.empty())
            {
                continue;
            }
            else if (command == "exit")
            {
                break;
            }
            else if (command == list[1])
            {
                make_request();
            }
            else if (command == list[2])
            {
                AllProducts();
            }
            else if (command == list[3])
            {
                break;
            }
            else 
            {
                continue;
            }
        }
    }

    void Warehouser::AllProducts()
    {
        CLEAR();
        bool cont = false;
        if (all_products.empty())
        {
            cont = get_all_products();
        }
        if (cont)
        {
            std::cout<<"QUANTITY\t\tID\tNAME\tPRICE\n";
            std::cout<<"--------\t\t--\t----\t-----\n";
            for (auto i : all_products)
            {
                for (auto j : i->items)
                {
                    std::cout<<j.first<<"\t\t"<<j.second->id<<"\t"<<j.second->name<<"\t"<<j.second->price<<'\n';
                }
            }
        }
        else
        {
            std::clog<<"Make new requests!!!!\n";   
        }
        all_products.clear();
        std::cout<<PRESS;
        auto ex = getch();

    }

    void Warehouser::make_request()
    {
        CLEAR();
        std::cout<<"--- Request creation ---\n";
        if (products_available.empty())
        {
            auto is = get_products();
        }
        if (requests.empty())
        {
            get_requests();
        }


        std::cout<<"Products available: \n";
        std::cout<<"ID\tNAME\tPRICE\n";
        std::cout<<"--\t----\t-----\n";
        for (auto i : products_available)
        {
            std::cout<<i->id<<"\t"<<i->name<<"\t"<<i->price<<"\n";
        }
        std::shared_ptr<Request> new_request(new Request);
        std::cout<<"Enter id to add to request: \n";
        std::string id_;
        while (true)
        {
            std::cout<<"Id (-1 to exit the loop): ";
            std::getline(std::cin, id_);
            int id = 0;
            try 
            {
                id = std::stoi(id_);
            }
            catch (std::invalid_argument & arg)
            {
                std::clog<<"Id contains restricted characters. Aborting request.\n";
                return;
            }
            if (id < 0) break;
            auto it = std::find_if(products_available.begin(), products_available.end(), Find_Id(id));
            if (it != products_available.end())
            {
                std::vector<int> request_numbers;
                if (requests.empty())
                {
                    new_request->request_number = 1;
                }
                else
                {
                    for (auto i = requests.begin(); i != requests.end(); i++)
                    {
                        request_numbers.push_back((*i)->request_number);
                    }
                    auto max_request = std::max_element(request_numbers.begin(), request_numbers.end());
                    new_request->request_number = (*max_request) + 1;
                }
                
                std::cout<<"How much do you want to get? Enter quantity: ";
                int quan;
                bool exit = true;
                while (exit)
                {
                    std::cout<<": ";
                    std::cin >> quan;
                    if (quan <= 0)
                    {
                        std::cout<<"Enter valid quantity!\n";
                    }
                    else
                    {
                        exit = false;
                    }
                }
                std::cin.ignore(100, '\n');
                new_request->items.insert({quan, *it});
            }
            else
            {
                std::clog<<"Product not found in available!\n";
            }
        }
        if (new_request->items.empty())
        {
            std::clog<<"Request is empty. You cannot send it.\n";
        }
        else
        {
            int sum_of_request = 0;
            for (auto i : new_request->items)
            {
                sum_of_request += i.second->price;
            }
            std::ifstream get_rest_sum(REST_MONEY_FILE, std::ios::in);
            std::string amount;
            get_rest_sum >> amount;
            int amnt;
            try
            {
                amnt = std::stoi(amount);
            }
            catch (std::invalid_argument)
            {
                std::clog<<"Restaurant has no money!\n";
                return;
            }
            std::string action;
            if (amnt < sum_of_request)
            {
                action = '[' + GetTime() + ']' + info.name + " tried to send request, but failed.";
                std::clog<<"Warning: The restaurant has not enough funds to get pruducts by this request\n";
            }
            else
            {
                std::ofstream write_money(REST_MONEY_FILE, std::ios::out);
                write_money << amnt;
                requests.push_back(new_request);
                std::ofstream file(REQUEST_FILE, std::ios::out);
                for (auto i : requests)
                {
                    file << *i;
                }
                action = '[' + GetTime() + ']' + info.name + " performed request.";
                std::cout<<"Request are leaved successfully\n";
            }
            WriteLog(std::move(action));
        }
        std::cout<<PRESS;
        auto x = getch();
    }

    bool Warehouser::get_products()
    {
        bool Success = false;
        std::ifstream File(FILE_NAME, std::ios::in);
        if (File.is_open())
        {
            if (File.peek() == EOF)
            {
                return Success;
            }
            while (File.peek() != '\n')
            {
                if (File.eof())
                {
                    Success = true;
                    break;
                }
                products_available.push_back(GetSingle(File));
            }
        }
        return Success;
    }

    std::shared_ptr<Product> Warehouser::GetSingle(std::ifstream & file)
    {
        std::shared_ptr<Product> NewProduct(new Product);
        file >> * NewProduct;
        return NewProduct;
    }



    class Provider // класс провайдера
    {
        public:
        explicit Provider(LoginData & log_data);
        void Session(); // сессия
        void SeeRequests(); // вывод всех запросов от складского
        bool ApproveRequest(); // подтверждение запроса
        private:
        LoginData info; // персональная информация
        std::vector<std::shared_ptr<Request>> requests; // массив запросов

        const std::vector<const char*> list = { // массив команд
            NULL,
            "see",
            "approve",
            "logout"
        };

        bool get_requests() // получение запросов
        {
            bool is = false;
            std::ifstream file(REQUEST_FILE, std::ios::in);
            if (file.is_open())
            {
                if (file.peek() == -1)
                {
                    std::clog<<"There are no requests...\n";
                }
                else
                {
                    while (file.peek() != '\n')
                    {
                        if (file.eof())
                        {
                            is = true;
                            break;
                        }
                        requests.push_back(getter::ReadItem<Request,Request>(file));
                    }
                }
            }
            else
            {
                std::cout<<"File is not exists or broken. \n";
            }
            return is;
        }
    };

    Provider::Provider(LoginData & log_data)
    {
        info = log_data;
    }

    void Provider::Session()
    {
        std::string com;
        std::cout<<"Hello `"<<info.name<<"`\n";
        std::cout<<"The following commands are permitted: \n";
        for (auto i = list.cbegin() + 1; i != list.cend(); i++)
        {
            std::cout<<*i<<"\n";
        }
        while (true)
        {
            std::cout<<"\n: ";
            std::getline(std::cin, com);
            if (com.empty())
            {
                continue;
            }
            else if (com == list[1])
            {
                SeeRequests();
            }
            else if (com == list[2])
            {
                ApproveRequest();
            }
            else if (com == list[3])
            {
                break;
            }
        }
    }

    void Provider::SeeRequests()
    {
        CLEAR();
        bool cont = false;
        requests.clear();
        cont = get_requests();
        if (cont)
        {
            std::cout<<"QUANTITY\tID\tNAME\tPRICE\n";
            std::cout<<"--------\t\t--\t----\t-----\n";
            for (auto i : requests)
            {
                for (auto j : i->items)
                {
                    std::cout<<j.first<<"\t\t"<<j.second->id<<"\t"<<j.second->name<<"\t"<<j.second->price<<"\n";
                }
                std::cout<<"---- REQUEST NUMBER: "<<i->request_number<<" ----\n";
            }
        }
        else
        {
            std::cout<<"No requests there...\n";
        }
        std::cout<<PRESS;
        auto x = getch();
    }

    struct find_by_number // структура для нахождения номера запроса
    {
        find_by_number(int number) : number(number) {}
        bool operator()(std::shared_ptr<Request> & req)
        {
            return number == req->request_number;
        }
        int number;
    };
    bool Provider::ApproveRequest()
    {
        CLEAR();
        requests.clear();
        std::ifstream file(REST_MONEY_FILE, std::ios::in);
        std::string amount;
        file >> amount;
        int rest_money = std::stoi(amount);
        bool cont = false;
        if (requests.empty())
        {
            cont = get_requests();
        }
        if (cont)
        {
            std::vector<int> can_be_approved;
            for (auto i : requests)
            {
                can_be_approved.push_back(i->request_number);
            }
            std::string num;
            while (!can_be_approved.empty())
            {
                std::cout<<"The following requests can be approved (or exit)\n";
                for (auto i : can_be_approved)
                {
                    std::cout<<i<<',';
                }
                std::cout<<"Enter number of request to give it: ";
                std::getline(std::cin, num);
                if (num == "exit")
                {
                    break;
                }
                auto num_ = std::atoi(num.c_str());
                auto iter = std::find_if(requests.begin(), requests.end(), find_by_number(num_));
                if (iter != requests.end())
                {
                    std::ofstream write_whouse(W_FILE, std::ios::app);
                    auto tmp = *iter;
                    write_whouse << *tmp;
                    int sum_of_transfer = 0;
                    for (auto i : (*iter)->items)
                    {
                        sum_of_transfer += (i.second->price * i.first);
                    }
                    rest_money -= sum_of_transfer;
                    requests.erase(iter);
                    auto tmp_iter = std::find_if(can_be_approved.begin(), can_be_approved.end(), [num_](int x) {return num_ == x; });
                    can_be_approved.erase(tmp_iter);
                    std::string action = "[ " + GetTime() + "] " + info.name + " sended products to restaurant";
                    WriteLog(std::move(action));
                }
                else 
                {
                    std::clog<<"Wrong number of request...\n";
                }
            }

            std::ofstream new_money(REST_MONEY_FILE, std::ios::out);
            new_money << rest_money;
            std::ofstream rewrite_requests(REQUEST_FILE, std::ios::out);
            for (auto i : requests)
            {
                rewrite_requests << *i;
            }
        }
        else
        {
            std::cout<<"No requests...\n";
        }
        std::cout<<PRESS;
        auto x = getch();
        return cont;
    }


    class Guest // гость
    {
        public:
        void Session(); // сессия
        

        private:
        std::vector<std::shared_ptr<Order>> Orders; // заказа
        std::vector<std::shared_ptr<MenuItem>> Menus; // меню
        void WriteOrders(); // запись всего меню
        virtual void GetOrders(); // получение меню
        void ChooseMenuItems(); // выбор меню
        LoginData log; // персональная информация
        const std::vector<const char *> list = {
            NULL,
            "getorders",
            "choose",
            "logout"
        };

        protected:
        std::shared_ptr<MenuItem> GetMenuItem(std::ifstream & file)
        {
            std::shared_ptr<MenuItem> mi(new MenuItem);
            file >> * mi;
            return mi;
        }
        private:
        const int balance = INT32_MAX;


        struct find_order_id // структра для нахождения id
        {
            find_order_id(int id) : id(id) {}
            bool operator()(Order & order)
            {
                return id == order.order_id;
            }
            int id;
        };
    };

    void Guest::Session()
    {
        CLEAR();
        std::cin.ignore(1, '\n');
        std::cout<<"Hello guest:\n";
        std::cout<<"The following commands are permitted: \n";
        for (auto i = list.cbegin() + 1; i != list.cend(); i++)
        {
            std::cout<<*i<<"\n";
        }
        std::string command;
        while (true)
        {
            std::cout<<"\nCurrent balance ($): "<<balance<<"\n";
            std::cout<<": ";
            std::getline(std::cin, command);
            if (command == list[1])
            {
                GetOrders();
            }
            else if (command == list[2])
            {
                ChooseMenuItems();
            }
            else if (command == list[3])
            {
                break;
            }
            else if (command.empty())
            {
                continue;
            }
        }
    }

    void Guest::ChooseMenuItems()
    {
        CLEAR();
        Menus.clear();
        std::ifstream file(FILE_MENU, std::ios::in);
        if (file.is_open())
        {
            while (file.peek() != '\n')
            {
                if (file.eof())
                {
                    break;
                }
                Menus.push_back(GetMenuItem(file));
            }
        }
        else
        {
            std::cerr<<"There no menu item. Add new menu item to read this file.\n";
        }

        std::cout<<"The menu is following: \n";
        std::string dish;
        Order new_order;
        int sum_of_tranfer = 0;
        while (true)
        {
            std::cout<<"NAME\tDESCRIPTION\tPRICE\tTIME OF COOKING\n";
            for (auto i : Menus)
            {
                std::cout<<i->name<<"\t"<<i->description<<"\t"<<i->price<<"\t"<<i->time<<"\n";
            }
            std::cout<<"Enter name of dish to add it to order or 'exit': ";
            std::getline(std::cin, dish);
            if (dish.empty())
            {
                continue;
            }
            if (dish == "exit")
            {
                break;
            }
            else
            {
                long pos = b_src(Menus, 0, Menus.size() - 1, dish);
                if (pos != -1)
                {
                    new_order.Dishes.push_back(Menus[pos]->name);
                    sum_of_tranfer += Menus[pos]->price;
                }
                else
                {
                    std::cout<<"Dish not found. Enter valid dish name\n";
                }
            }
        }
        if (new_order.Dishes.empty())
        {
            std::cout<<"We cannot create new order for you because it is empty\n";
            return;
        }
        std::srand(time(NULL));
        int next_order_id = std::rand() % 1000;
        new_order.order_id = next_order_id;
        new_order.order_status = 1;
        std::ofstream fl("orders.txt", std::ios::app);
        fl << new_order;
        std::cout<<"You spent "<<sum_of_tranfer<<" ($)\n";
        std::ifstream get_rest_balance(REST_MONEY_FILE, std::ios::in);
        std::string rest_balance;
        get_rest_balance >> rest_balance;
        get_rest_balance.close();
        int r_balance = std::stoi(rest_balance);
        r_balance += sum_of_tranfer;
        std::ofstream put_rest_balance(REST_MONEY_FILE, std::ios::in);
        put_rest_balance << r_balance;
        std::ofstream sold_items("sold.txt", std::ios::app);
        sold_items << new_order;
        std::cout<<"Order created!\n";
        std::cout<<PRESS;
        auto x = getch();
    }

    void Guest::GetOrders()
    {
        CLEAR();
        std::ifstream file("orders.txt", std::ios::in);
        if (file.is_open())
        {
            while (file.peek() != '\n')
            {
                if (file.eof()) break;
                Orders.push_back(getter::ReadItem<Order, Order>(file));
            }
            for (auto i : Orders)
            {
                std::cout<<"ORDER #: "<<i->order_id<<"\n";
                std::cout<<"DISHES: ";
                for (auto j : i->Dishes)
                {
                    std::cout<<j<<",";
                }
                std::cout<<"\n";
                auto it = i->Order_states.find(i->order_status);
                std::cout<<"STATUS: "<<(*it).second<<"\n";
                std::cout<<"------ END ------\n";
            }
        }

        else
        {
            std::clog<<"You didn't make any order\n";
        }
        Orders.clear();
        std::cout<<PRESS;
        auto x = getch();
    }


    class Account // бухгалтер
    {
        public:
        Account() = default;
        explicit Account(LoginData & login);
        void Session(); // сессия
        private: 
        void ShowInfo(); // показ всей информацией
        bool GetAllRequests(); // получение всех запросов
        int GetSendedRequests(); // получение всех отправленных запросов
        int GetRestaturantMoney(); // получение всех денег ресторана
        void PrettyPrintEachOther(); // вывод данных
        int GetSold(); // получение суммы
        void print_sold(); // вывод всех проданных блюд
        int GetAllMenu() // получение всего меню
        {
            int status = local::OK;
            std::ifstream file(FILE_MENU, std::ios::in);
            if (file.is_open())
            {
                if (file.peek() == -1)
                {
                    status = local::FILE_EMPTY;
                }
                else
                {
                    while (file.peek() != '\n')
                    {
                        if (file.eof())
                        {
                            break;
                        }
                    Menus.push_back(GetMenuItem(file));
                    }
                }
            }
            else
            {
                status = local::FILE_NOT_CREATED;
            }
            return status;
        }
        protected:
        enum local {OK = 0, FILE_NOT_CREATED, FILE_EMPTY};
        private:
        std::vector<std::shared_ptr<Request>> requests;
        std::vector<std::shared_ptr<Request>> temp;
        std::vector<std::shared_ptr<Order>> orders;
        std::vector<std::shared_ptr<MenuItem>> Menus;
        LoginData log;

        const std::vector<const char *> list = {
            NULL,
            "getinfo",
            "logout"
        };

    };

    Account::Account(LoginData & log)
    {
        this->log = log;
    }

    void Account::Session()
    {
        CLEAR();
        std::cout<<"Hello `"<<log.name<<"`\n";
        std::cout<<"The following commands are permitted: \n";
        for (auto i = list.cbegin() + 1; i != list.cend(); i++)
        {
            std::cout<<*i<<'\n';
        }

        std::string command;
        while (true)
        {
            std::cout<<"\n: ";
            std::getline(std::cin, command);
            if (command.empty())
            {
                continue;
            }
            else if (command == list[1])
            {
                PrettyPrintEachOther();   
            }
            else if (command == list[2])
            {
                break;
            }
            else
            {
                continue;
            }
        }

    }
    
    void Account::print_sold()
    {
        std::cout<<"Information of sold menus is following: \n";
        int all_sum = 0;
        for (auto menu_item : Menus)
        {
            std::cout<<"Sum of sold dish "<<menu_item->name<<" is ";
            int sum_of = 0, count_of = 0;
            for (auto order : orders)
            {
                for (auto dish_name : order->Dishes)
                {
                    if (menu_item->name == dish_name)
                    {
                        ++count_of;
                    }
                }
            }
            sum_of = menu_item->price * count_of;
            all_sum += sum_of;
            std::cout<<sum_of<<" ($) and individual price is "<<menu_item->price<<"\n";
            std::cout<<"Count is: "<<count_of<<"\n";

        }
        std::cout<<"Amount of all sold dishes is "<<all_sum<<" ($)\n";
    }

    int Account::GetSold()
    {
        int st = local::OK;
        if (!orders.empty())
        {
            orders.clear();
        }
        std::ifstream file("sold.txt", std::ios::in);
        if (file.is_open())
        {
            if (file.peek() == -1)
            {
                st = local::FILE_EMPTY;
            }
            else
            {
                while (file.peek() != '\n')
                {
                    if (file.eof()) break;
                    orders.push_back(getter::ReadItem<Order, Order>(file));
                }
            }
        }
        else
        {
            st = local::FILE_NOT_CREATED;
        }
        return st;
    }
    bool Account::GetAllRequests()
    {
        bool is = false;
        std::ifstream file(W_FILE, std::ios::in);
        if (file.is_open())
        {
            if (file.peek() == -1)
            {
                std::clog<<"Nothing in warehouse.\n";
            }
            else
            {
                while (file.peek() != '\n')
                {
                    if (file.eof())
                    {
                        is = true;
                        break;
                    }
                    requests.push_back(getter::ReadItem<Request, Request>(file));
                }
            }
        }
        else
        {
            std::cout<<"File not has not been created...\n";
        }
        return is;
    }

    int Account::GetSendedRequests()
    {
        int count = -1;
        std::ifstream file(REQUEST_FILE, std::ios::in);
        if (file.is_open())
        {
            if (file.peek() == -1)
            {
                file.close();
                return count;
            }
            else
            {
                while (file.peek() != '\n')
                {
                    if (file.eof())
                    {
                        break;
                    }
                    temp.push_back(getter::ReadItem<Request, Request>(file));
                }
                count = temp.size();
            }
        }
        else
        {
            return -1;
        }
        return count; 
    }


    int Account::GetRestaturantMoney()
    {
        std::ifstream file(REST_MONEY_FILE, std::ios::in);
        std::string amount;
        file >> amount;
        file.close();
        return std::stoi(amount);
    }


    void Account::PrettyPrintEachOther()
    {
        CLEAR();
        bool cont = false;
        if (requests.empty())
        {
            cont = GetAllRequests();
        }
        if (cont)
        {
            int tmp = GetRestaturantMoney();
            std::cout<<"Restaurant money: "<<tmp<<" ($)\n";
            std::cout<<"The each and overall item amount is: \n";
            std::set<std::string> names;
            for (auto i : requests)
            {
                for (auto j : i->items)
                {
                    names.insert(j.second->name);
                }
            }
            int all_sum = 0;
            for (auto it = names.begin(); it != names.end(); it++)
            {
                std::cout<<" -- The sum of "<<*it<<" is ";
                uint sum_of = 0, quantity = 0, price = 0;
                for (auto i : requests)
                {
                    for (auto j : i->items)
                    {
                        if (j.second->name == *it)
                        {
                            price = j.second->price;
                            quantity += j.first;
                        }
                    }
                }
                sum_of = quantity * price;
                all_sum += sum_of;
                std::cout<<sum_of<<" and price is "<<price<<" ($) | Kept in stock (pcs.): "<<quantity<<"\n";
            }
            std::cout<<"Amount of all products is: "<<all_sum<<" ($)\n";
            std::cout<<"----------------------------------------\n";
            std::cout<<"---------- REQUESTS ----------\n";
            std::cout<<"Information about awaiting requests: \n";
            int count = GetSendedRequests();
            if (count == 0)
            {
                std::cout<<"You have no requests ...\n";
            }
            else if (count == -1)
            {
                std::cout<<"Database is closed ...\n";
            }
            else
            {
                std::set<int> Keys;
                int all_sum2 = 0;
                for (auto i : temp)
                {
                    for (auto j : i->items)
                    {
                        Keys.insert(j.second->id);
                    }
                }
                for (auto it = Keys.begin(); it != Keys.end(); it++)
                {
                    uint sum_of = 0, quantity = 0, price = 0;
                    std::string name;
                    for (auto i : requests)
                    {
                        for (auto j : i->items)
                        {
                            if (j.second->id == *it)
                            {
                                name = std::move(j.second->name);
                                price = j.second->price;
                                quantity += j.first;
                            }
                        }
                    }
                    sum_of = quantity * price;
                    all_sum2 += sum_of;
                    std::cout<<"Request item's "<<name<<" sum is "<<sum_of<<" and price is "<<price<<"| Awaiting to get "<<quantity<<"\n";
                }
                std::cout<<"Amount of all products is: "<<all_sum2<<" ($)\n";

            }
            int menu_getter_status = GetAllMenu();
            if (menu_getter_status == local::OK)
            {
                int status = GetSold();
                std::cout<<"\n\n---------- SOLD DISHES ----------\n";
                switch (status)
                {
                    case local::OK:
                    {
                        print_sold();
                        break;
                    }
                    case local::FILE_NOT_CREATED:
                    {
                        std::clog<<"File of sold items does not exists\n";
                        break;
                    }
                    case local::FILE_EMPTY:
                    {
                        std::cout<<"You sold nothing...\n";
                        break;
                    }
                }
            }
            else if (menu_getter_status == local::FILE_EMPTY)
            {
                std::clog<<"Menu is empty\n";
            }
            else
            {
                std::clog<<"Menu file does not exists\n";
            }
        }   
        else
        {
            std::clog<<"No items in warehouse...\n";
        }
        requests.clear();
        Menus.clear();
        orders.clear();
        std::cout<<PRESS;
        auto x = getch();
    }

    class Cook : protected Guest, public Account // класс повара
    {
        public:
        Cook(LoginData & log)
        {
            this->log = log;
        }
        Cook() = default;
        Cook(const Cook & cook);
        void Session(); // сессия
        private:
        
        std::vector<std::shared_ptr<Order>> Orders; // все заказы
        std::vector<std::shared_ptr<MenuItem>> Menus; // все меню
        LoginData log;
        virtual int LoadOrders(); // загрузка заказов
        int LoadMenu(); // загрузка меню
        void start_cook(); // начало приготоления
        void process(); // процесс приготовления 
        void GetOrders() override; // получение всех заказов
        const std::vector<const char *> list = { 
            NULL,
            "see",
            "begin",
            "logout",
        };
    };


    void Cook::Session()
    {
        CLEAR();
        std::cout<<"Hello `"<<log.name<<"`\n";
        std::cout<<"The following commands are permitted: \n";
        for (auto i = list.cbegin() + 1; i != list.cend(); i++)
        {
            std::cout<<*i<<"\n";
        }
        std::string command;
        while (true)
        {
            std::cout<<"\n: ";
            std::getline(std::cin, command);
            if (command == list[1])
            {
                GetOrders();
            }
            else if (command == list[2])
            {
                start_cook();
            }
            else if (command == list[3])
            {
                break;
            }
        }
    }
    int Cook::LoadMenu()
    {
        int st = local::OK;
        std::ifstream file(FILE_MENU, std::ios::in);
        if (file.is_open())
        {
            if (file.peek() == -1)
            {
                st = local::FILE_EMPTY;
            }
            else
            {    
                while (file.peek() != '\n')
                {
                    if (file.eof())
                    {
                        break;
                    }
                    Menus.push_back(GetMenuItem(file));
                }
            }
        }
        else
        {
            st = local::FILE_NOT_CREATED;
        }
        return st;
    }
    int Cook::LoadOrders()
    {
        int st = local::OK;
        std::ifstream file("orders.txt", std::ios::in);
        if (file.is_open())
        {
            if (file.peek() == -1)
            {
                st = local::FILE_EMPTY;
            }
            else
            {
                while (file.peek() != '\n')
                {
                    if (file.eof()) break;
                    Orders.push_back(getter::ReadItem<Order, Order>(file));
                }
            }
        }
        else
        {
            st = local::FILE_NOT_CREATED;
        }
        return st;
    }
    void Cook::GetOrders()
    {
        CLEAR();
        Orders.clear();
        int res = LoadOrders();
        if (res == local::OK)
        {
            for (auto i : Orders)
            {
                std::cout<<"ORDER #: "<<i->order_id<<"\n";
                std::cout<<"DISHES: ";
                for (auto j : i->Dishes)
                {
                    std::cout<<j<<",";
                }
                std::cout<<"\n";
                auto it = i->Order_states.find(i->order_status);
                std::cout<<"STATUS: "<<(*it).second<<"\n";
                std::cout<<"------ END ------\n";
            }
        }
        else if (res == local::FILE_EMPTY)
        {
            std::clog<<"No orders...\n";
        }
        else
        {
            std::clog<<"Database is closed...\n";
        }
        std::cout<<PRESS;
        auto x = getch();
    }


    void Cook::process()
    {
        int res = LoadMenu();
        if (res == local::OK)
        {
            if (std::none_of(Orders.begin(), Orders.end(), [](std::shared_ptr<Order> ord){ return ord->order_status == 1;}))
            {
                std::cout<<"There are no ongoing orders to cook...\n";
                return;
            }
            std::cout<<"You can cooking the following orders: \n";
            for (auto order : Orders)
            {
                if (order->order_status == 1)
                {
                    std::cout<<"["<<order->order_id<<"] :: Dishes: ";
                    for (auto dish_name : order->Dishes)
                    {
                        std::cout<<dish_name<<", ";
                    }
                }
            }
            std::cout<<"\n";
            std::cout<<"Enter the number of order to start cooking it: ";
            std::string order_number;
            std::getline(std::cin, order_number);
            int order_num = 0;
            try
            {
                order_num = std::stoi(order_number);
            }
            catch (std::invalid_argument & arg)
            {
                std::clog<<"Number contains ambiguous chars. Canceled order cooking. \n";
                return;
            }
            auto iter = std::find_if(Orders.begin(), Orders.end(), 
            [order_num](std::shared_ptr<Order> pr){return order_num == pr->order_id;});
            if (iter != Orders.end())
            {
                {
                    (*iter)->order_status = 2;
                    std::ofstream fl("orders.txt", std::ios::out);
                    for (auto i : Orders)
                    {
                        fl << *i;
                    }
                }
                std::vector<uint> ids;
                for (auto i : (*iter)->Dishes)
                {
                    for (auto j : Menus)
                    {
                        if (i == j->name)
                        {
                            for (auto it : j->Products)
                            {
                                ids.push_back(it->id);
                            }
                        }
                    }
                }
                
                std::cout<<"Ids for this order is: ";
                std::sort(ids.begin(), ids.end());
                ids.erase(std::unique( ids.begin(), ids.end() ), ids.end() );
                for (auto i : ids)
                {
                    std::cout<<i<<",";
                }
                std::cout<<"\n";
                std::string id;
                uint id_;
                while (!ids.empty())
                {
                    std::cout<<"Leaved: ";
                    for (auto i : ids)
                    {
                        std::cout<<i<<',';
                    }
                    std::cout<<"Enter ids to cook it: ";
                    std::getline(std::cin, id);
                    try
                    {
                        id_ = std::stoi(id);
                    }
                    catch(std::invalid_argument)
                    {
                        std::clog<<"Id cannot contain letters!\n";
                    }
                    auto it = std::find(ids.begin(), ids.end(), id_);
                    if (it != ids.end())
                    {
                        ids.erase(it);
                    }
                    else
                    {
                        std::cout<<"Enter only valid ids!\n";
                    }
                }

                (*iter)->order_status = 3;
                std::ofstream fl("orders.txt", std::ios::out);
                for (auto i : Orders)
                {
                    fl << *i;
                }
                std::cout<<"Waiter taken order!\n";
            }
            else
            {
                std::cout<<"Wrong order number\n";
            }
        }
        else if (res == local::FILE_EMPTY)
        {
            std::clog<<"Menu is empty\n";
        }
        else
        {
            std::clog<<"Database closed...\n";
        }
        Menus.clear();

    }



    void Cook::start_cook()
    {
        CLEAR();
        if (!Orders.empty())
        {
            Orders.clear();
        }
        int st = LoadOrders();
        switch (st)
        {
            case local::OK:
            {
                process();
                break;
            }
            case local::FILE_EMPTY:
            {
                break;
            }
            case local::FILE_NOT_CREATED:
            {
                break;
            }
        }

        std::cout<<PRESS;
        auto x = getch();
    }

    class Waiter : protected Cook // класс официанта
    {
        public:
        Waiter(LoginData & log);
        Waiter(const Waiter & log);
        void Session(); // сессия
        private:
        void ChangeStatus(); // смена статуса заказа
        int LoadOrders() override; // загрузка всех заказов
        LoginData log;
        std::vector<std::shared_ptr<Order>> Orders; // всех заказы
        const std::vector<const char*> list = {
            NULL,
            "change",
            "logout"
        };
    };

    Waiter::Waiter(LoginData & log)
    {
        this->log = log;
    }

    int Waiter::LoadOrders()
    {
        int st = local::OK;
        std::ifstream file("orders.txt", std::ios::in);
        if (file.is_open())
        {
            if (file.peek() == -1)
            {
                st = local::FILE_EMPTY;
            }
            else
            {
                while (file.peek() != '\n')
                {
                    if (file.eof()) break;
                    Orders.push_back(getter::ReadItem<Order, Order>(file));
                }
            }
        }
        else
        {
            st = local::FILE_NOT_CREATED;
        }
        return st;
    }

    void Waiter::ChangeStatus()
    {
        CLEAR();
        int st = LoadOrders();
        if (st == local::OK)
        {
            if (std::none_of(Orders.begin(), Orders.end(), [](std::shared_ptr<Order> & ord){return ord->order_status == 3;}))
            {
                std::clog<<"No orders to complete...\n";    
            }
            else
            {
                std::cout<<"You can finish the following orders: \n";
                for (auto i : Orders)
                {
                    if (i->order_status == 3)
                    {
                        std::cout<<"Order num: "<<i->order_id<<" Dishes: ";
                        for (auto j : i->Dishes)
                        {
                            std::cout<<j<<',';
                        }
                        std::cout<<"\n\n------ ORDER END ------\n";
                    }
                }
                std::string order_number;
                int id;
                std::cout<<"Enter number of order, to complete it: ";
                std::getline(std::cin, order_number);
                try
                {
                    id = std::stoi(order_number);
                }
                catch (std::invalid_argument)
                {
                    std::clog<<"Invalid id entered. Revert changes\n";
                    return;
                }
                auto order_iter = std::find_if(Orders.begin(), Orders.end(),
                [id](std::shared_ptr<Order> & ord){return ord->order_id == id;});
                if (order_iter != Orders.end())
                {
                    (*order_iter)->order_status = 4;
                    std::ofstream file("orders.txt", std::ios::out);
                    for (auto i : Orders)
                    {
                        file << *i;
                    }
                    std::cout<<"Order completed!\n";
                }
                else
                {
                    std::cout<<"Wrong order id!\n";
                }
            }
        }
        else if (st == local::FILE_EMPTY)
        {
            std::clog<<"No any order!\n";
        }
        else
        {
            std::clog<<"Database is closed...\n";
        }
        Orders.clear();
        std::cout<<PRESS;
        auto x = getch();
        return;
    }

    void Waiter::Session()
    {
        CLEAR();
        std::cout<<"Hello `"<<log.name<<"`\n";
        std::cout<<"The following commands are permitted: \n";
        for (auto i = list.cbegin() + 1; i != list.cend(); i++)
        {
            std::cout<<*i<<'\n';
        }
        std::string command;
        while (true)
        {
            std::cout<<"\n: ";
            std::getline(std::cin, command);
            if (command == list[1])
            {
                ChangeStatus();
            }
            else if (command == list[2])
            {
                break;
            }
            else if (command.empty())
            {
                continue;
            }
        }
    }

    

}

#endif
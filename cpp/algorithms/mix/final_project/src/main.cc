#include "../include/Person.h"
#include "../include/sha1.hpp"
#include "../test.hpp"
#include <algorithm>


struct password_validity_check // проверка для символов
{
    bool operator()(char Sym)
    {
        return (Sym >= 0x21 && Sym <= 0x2F) || Sym == 0x40
        || (Sym >= 0x5B && Sym <= 0x60);
    }
};


struct password_validity_any_numbers // проверка для цифр
{
    bool operator()(char Number)
    {
        return Number >= 0x30 && Number <= 0x39;
    }
};

struct is_upperletter // проверка для символов верхнего регистра
{
    bool operator()(char letter)
    {
        return letter >= 65 && letter <= 90;
    }
};



class Invalid_name_length : public std::exception // класс исключения для невалидной длины имени пользователя
{
    public:
    Invalid_name_length(const char * expl)
    {
        msg = expl;
    }
    const char * what() const noexcept
    {
        return msg.c_str();
    }
    private:
    std::string msg;
};

void Register() // функция для регистрации
{
    std::cin.ignore(1000, '\n');
    std::string name, surname,patron; 
    std::string password;
    int role;
    std::cout<<"Register new user\n";
    try
    {
        std::cout<<"Enter name (more or eq to 8): ";
        std::getline(std::cin, name);
        if (name.length() < VALID_NAME_LENGTH)
        {
            throw Invalid_name_length("Name length should be more or less 8 letters. Re-sign\n");
        }
        std::cout<<"Your surname (any length, but not empty): ";
        std::getline(std::cin, surname);
        if (surname.empty()) 
        {
            throw std::length_error("You should enter your surname as any letter, but not emptiness!");
        }
        std::cout<<"Patronimyc (optional): ";
        std::getline(std::cin, patron);
        if (patron.empty())
        {
            patron = EMPTY; // если отчетство не введено то то присваиваем пустоту
        }
        std::cout<<"Password (at least 8 letters): ";
        std::getline(std::cin, password);
        if (password.length() < VALID_PASSWORD_LENGTH)
        {
            throw std::length_error("Length of password is invalid. Minimum 8 characters\n");
        } // кидаем исключение
        password_validity_check ps;
        password_validity_any_numbers ps1;
        is_upperletter upper_letter;
        if (!std::any_of(password.begin(), password.end(), ps))
        {
            std::cerr<<"Password should contain any of special characters\n";
            return;
        } // если хотя бы одного специсимвола нет то выводим информируещее сообщение
        if (!std::any_of(password.begin(), password.end(), ps1))
        {
            std::cerr<<"Password should contain at least 1 number\n";
            return;
        } // если хотя бы одной цифры нет то выводим информируещее сообщение

        if (!std::any_of(password.begin(), password.end(), upper_letter))
        {
            std::cerr<<"Password should contain at least 1 upper letter\n";
            return;
        } // если хотя бы одной верхней буквы нет то выводим информируещее сообщение


        std::cout<<"Enter your role (1 - admin, 2 - waiter, 3 - cook, 4 - accountary, 5 - warehouser, 6 - provider): ";
        std::cin >> role;
        switch (role) // в зависимости от цифры присваеиваем значение роли
        {
            case 1:
            role = 1;
            break;
            case 2:
            role = 2;
            break;
            case 3:
            role = 3;
            break;
            case 4:
            role = 4;
            break;
            case 5:
            role = 5;
            break;
            case 6:
            role = 6;
            break;
            default:
            std::cerr<<"Role you entered is invalid. Roles listed below: \n";
            for (auto i : project::roles)
            {
                std::cout<<i.first<<". "<<i.second<<"\n";
            }
            return;
        }

        std::vector<std::shared_ptr<project::LoginData>> Tmp; // вектор для хранения логинов
        std::ifstream Read("credits.txt", std::ios::in); // открытие потока для получения логинов

        if (Read.is_open())
        {
            if (Read.peek() == EOF) // если файл пустой то записываем первого пользователя
            {
                std::string UserSalt = gensalt();
                std::string UserFinalPassword = password + UserSalt;
                SHA1 hash;
                hash.update(UserFinalPassword);
                project::LoginData RegisteredUser;
                RegisteredUser.name = name;
                RegisteredUser.surname = surname;
                RegisteredUser.patron = patron;
                RegisteredUser.role = role;
                RegisteredUser.password = hash.final();
                RegisteredUser.salt = UserSalt;
                WriteToFile(RegisteredUser);
                std::cout<<"Register success";
                return;
            }
            else
            {
                while (Read.peek() != -1)
                {
                    if (Read.eof()) break;
                    Tmp.push_back(ReadFromFile<project::LoginData, project::LoginData>(Read));
                }
            }
        }


        long found = b_search(Tmp, 0, Tmp.size() - 1, name); // бинарный поиск для нахождения имени
        
        if (found != -1) // если пользователь с таким именем уже существует то отменяем регистрацию
        {
            std::cout<<"This user already registered in system\n";
            return;
        }
        else // в ином случае регистрация нового пользователя
        {
            std::string UserSalt = gensalt(); // генерация соли
            std::string UserFinalPassword = password + UserSalt;
            SHA1 hash; // хэш функция
            hash.update(UserFinalPassword);
            project::LoginData RegisteredUser;
            RegisteredUser.name = name; // имя
            RegisteredUser.surname = surname; // фамилия
            RegisteredUser.patron = patron; // отчество
            RegisteredUser.role = role; // роль
            RegisteredUser.password = hash.final(); // пароль в захешир. виде
            RegisteredUser.salt = UserSalt; // соль
            WriteToFile(RegisteredUser); // записываем в файл
            std::cout<<"Register success\n"; 
        }
        

    }
    catch (Invalid_name_length arg) // ловим исключение
    {
        std::cout<<arg.what();
    }

    catch (std::length_error arg) // ловим исключение
    {
        std::cout<<arg.what();
    }
    return;
}

void Login()
{
    std::cin.ignore(1000, '\n');
    std::string login;
    std::string password;
    std::cout<<"Enter your login: "; // вводим логин
    std::getline(std::cin, login);
    std::cout<<"Enter your password: ";
    std::getline(std::cin, password); // вводим пароль

    std::vector<std::shared_ptr<project::LoginData>> logins; // для логинов
    
    std::ifstream file;
    file.open("credits.txt", std::ios::in); // считываем все логины

    if (file.is_open())
    {
        if (file.peek() == EOF) // если пусто то возрращаемя обратно
        {
            return;
        }
        while (file.peek() != -1) // чтение файла
        {
            if (file.eof()) break;
            logins.push_back(ReadFromFile<project::LoginData, project::LoginData>(file));
        }
    }
    if (logins.empty()) // если пусто то информруем пользователя
    {
        std::cout<<"No logins found in the file. Register first\n";
        return;
    }
    
    
    long found = project::b_src(logins, 0, logins.size() - 1, login); // ищем пользователя в векторе

    if (found != -1) // если найден, то получаем индекс
    {
        std::cout<<"Your name: "<<logins[found]->name<<", checking password...\n";
        SHA1 sh;
        std::string check_pass = password + logins[found]->salt;
        sh.update(check_pass);
        if (sh.final() == logins[found]->password) // если хеш пароля введенного совпадает с хешем который в файле
        {
            project::LoginData LoggedUser(*logins[found]);
            switch (LoggedUser.role)
            {
                case 1:
                {
                    project::SysAdmin Admin(LoggedUser, logins); // создаем админа, начинаем сессию
                    Admin.Session();
                    break;
                }
                break;
                case 2:
                {
                    project::Waiter wt(LoggedUser); // создаем официанта, начинаем сессию
                    wt.Session();
                    break;
                }
                case 3:
                {
                    project::Cook cook(LoggedUser); // создаем повара, начинаем сессию
                    cook.Session();
                    break;
                }
                case 4:
                {
                    project::Account acc(LoggedUser); // создаем бухгалтера, начинаем сессию
                    acc.Session();
                    break;
                }
                case 5:
                {
                    project::Warehouser house(LoggedUser); // создаем складского, начинаем сессию
                    house.Session();
                    break;
                }
                case 6:
                {
                    project::Provider prov(LoggedUser); // создаем провайдера, начинаем сессию
                    prov.Session();
                    break;
                }
                break;
            }
        }
        else
        {
            std::cout<<"Incorrect password.\n"; // информируем 
        }
    }
    else
    {
        std::cout<<"Login not found.\n"; // логин не найден
    }

}

bool menu() // меню
{
    CLEAR();
    int action;
    std::cout<<"1. Register"<<"\n";
    std::cout<<"2. Login\n";
    std::cout<<"3. Guest login\n";
    std::cout<<"4. Exit\n";
    std::cout<<": ";
    std::cin >> action;
    if (action == 1)
    {
        Register(); // регистрация
    }
    else if (action == 2)
    {
        Login(); // логин
    }
    else if (action == 3)
    {
        project::Guest guest;
        guest.Session(); // сессия гостя
    }
    else
    {
        return true;
    }
    return false;
}

int main()
{
    std::ifstream file(REST_MONEY_FILE, std::ios::in);
    if (!file.is_open())
    {
        file.close();
        std::ofstream fl(REST_MONEY_FILE, std::ios::out);
        fl << "100000";
    }
    bool ExitApproved = false;
    while (ExitApproved != true)
    {
        ExitApproved = menu();
    }
    
    return 0;
}
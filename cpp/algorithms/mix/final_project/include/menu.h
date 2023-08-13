#ifndef MENU_H
#define MENU_H
#include "./Product.h"
#include "./common.hpp"

using namespace project;
struct MenuItem // структура меню
{
    MenuItem() = default; 
    MenuItem(const MenuItem & it);
    std::string name; // имя блюда
    std::string description; // описание блюда
    float gram; // граммовка
    float price; // цена
    float time; // время приготовления
    std::vector<std::shared_ptr<Product>> Products; // продукты
    friend std::ostream & operator << (std::ostream & os, MenuItem & it); // операторы
    friend std::istream & operator >> (std::istream & is, MenuItem & it);

};

std::ostream & operator << (std::ostream & os, MenuItem & it)
{
    os << it.name << ':'<<it.description<<':'<<it.gram<<':'<<it.price<<':';
    os << it.time <<'<';
    for (auto i : it.Products)
    {
        os << i->id <<',' << i->name << ',' << i->price <<'|';
    }
    os << '>';
    os << '\n';
    return os;
}

std::istream & operator >> (std::istream & is, MenuItem & it)
{
    std::string gram, price, time, product_space;
    std::getline(is, it.name, ':');
    std::getline(is, it.description, ':');
    std::getline(is, gram, ':');
    std::getline(is, price, ':');
    std::getline(is, time, '<');
    it.gram = std::atof(gram.c_str());
    it.price = std::atof(price.c_str());
    it.time = std::atof(time.c_str());
    
    std::getline(is, product_space);

    std::istringstream reader(product_space);
    while (reader.peek() != '>')
    {
        if (reader.eof()) break;
        std::string id, name, price;
        std::getline(reader, id, ',');
        std::getline(reader, name, ',');
        std::getline(reader, price, '|');
        std::shared_ptr<Product> product(new Product);
        product->id = std::atoi(id.c_str());
        product->name = name;
        product->price = std::atoi(price.c_str());
        it.Products.push_back(product);
    }
    return is;
}

void WriteMenuItem(std::ofstream & file, MenuItem & value)
{
    file << value;
} // функция для записи пункта меню

std::shared_ptr<MenuItem> GetMenuItem(std::ifstream & file)
{
    std::shared_ptr<MenuItem> mi(new MenuItem);
    file >> * mi;
    return mi;
} // фнукция для получения пункта меню



struct Request // структура запроса
{
    int request_number; // номер запроса
    std::map<int, std::shared_ptr<Product>> items;
    // хеш таблица (количество продукта, продукт)
    // операторы для записи и извлечения 
    friend std::ostream & operator << (std::ostream & os, Request & request);
    friend std::istream & operator >> (std::istream & is, Request & request);
};

std::ostream & operator << (std::ostream & os, Request & request)
{
    os << request.request_number << '<';
    for (auto i : request.items)
    {
        os << i.first << ":" << i.second->id << ":" << i.second->name << ":" << i.second->price << '|';
    }
    os << '>';
    os << '\n';
    return os;
}

std::istream & operator >> (std::istream & is, Request & request)
{
    std::string Number,count, id, name, price, product_space;
    std::getline(is, Number, '<');
    std::getline(is, product_space);
    std::istringstream reader(product_space);
    while (reader.peek() != '>')
    {
        if (reader.eof()) break;
        std::getline(reader, count, ':');
        std::getline(reader, id, ':');
        std::getline(reader, name, ':');
        std::getline(reader, price, '|');
        std::shared_ptr<Product> it(new Product);
        int count_ = std::atoi(count.c_str());
        it->id = std::atoi(id.c_str());
        it->name = name;
        it->price = std::atoi(price.c_str());
        request.items.insert({count_, it});
    }
    request.request_number = std::atoi(Number.c_str());
    return is;
}
// шаблонная функция для записи
template <typename t>
void Write(std::ofstream & file_stream, t & type)
{
    file_stream << *type;
}

namespace getter
{
    // шаблонная функция для чтения объекта
    template <typename value_type, class getter_type = value_type>
    std::shared_ptr<getter_type> ReadItem(std::ifstream & file)
    {
        std::shared_ptr<getter_type> NewItem(new getter_type);
        file >> *NewItem;
        return NewItem;
    }
};


struct Order // структура заказа
{
    int order_id; // номер заказа
    std::vector<std::string> Dishes; // блюда
    int order_status; // статус заказа
    // операторы для записи и извлечения из потока
    friend std::ostream & operator << (std::ostream & os, Order & ord);
    friend std::istream & operator >> (std::istream & is, Order & ord);

    const std::map<int, std::string> Order_states =
    {
        {1, "PAID and given to kitchen"},
        {2, "In the process of cooking"},
        {3, "Transfered to waiter"},
        {4, "Made"}
    };
    // статусы заказов
};

std::ostream & operator << (std::ostream & os, Order & ord)
{
    os << ord.order_id << ':' << ord.order_status;
    os << '<';
    for (auto i : ord.Dishes)
    {
        os << i <<'|';
    }
    os << '>';
    os << '\n';
    return os;
}

std::istream & operator >> (std::istream & is, Order & ord)
{
    std::string number, status;
    std::getline(is, number, ':');
    std::getline(is, status, '<');
    std::string blank;
    std::getline(is, blank);
    std::istringstream str(blank);
    while (str.peek() != '>')
    {
        if (str.eof()) break;
        std::string dish;
        std::getline(str, dish, '|');
        ord.Dishes.push_back(dish);
    }
    ord.order_id = std::atoi(number.c_str());
    ord.order_status = std::atoi(status.c_str());
    return is;

}



#endif
#ifndef PRODUCT_H
#define PRODUCT_H
#include "./Types.h"

namespace project
{
    using namespace Types;
    struct Product // структура продукта
    {
        uint id; // номер продукта
        Str name; // имя продукта
        uint price; // цена
        Product() = default;
        Product(const uint & id, Str & name, const uint price)
        {
            this->id = id;
            this->name = name;
            this->price = price;
        } // конструктор
        friend std::ostream & operator<<(std::ostream& stream, Product & product)
        {
            stream << product.id <<','<<product.name<<','<<product.price<<';';
            return stream;
        } 
        friend std::istream & operator>>(std::istream& stream, Product & product)
        {
            std::string Id, Price;
            std::getline(stream, Id, ',');
            std::getline(stream, product.name, ',');
            std::getline(stream, Price, ';');
            product.id = std::stoi(Id);
            product.price = std::stoi(Price);
            return stream;
        }
    };
}

#endif
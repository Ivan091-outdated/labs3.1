#include <iostream>
#include <cstring>
#include "product.h"

Product::Product(const char *name, int count, long price) {
    auto len  = strlen(name) + 1;
    this->name = new char[len];
    this->name = strcpy(this->name, name);
    this->count = count;
    this->price = price;
    std::cout << name << " created." << std::endl;
}

Product::Product(const Product &other) : Product::Product(other.name, other.count, other.price) {
}

Product::Product() : Product::Product("< blank >", -1, -1) {
}

Product::~Product() {
    std::cout << name << " deleted." << std::endl;
    delete name;
}

const char *Product::getName() const {
    return name;
}

Product Product::setName(const char *newName) {
    delete[] name;
    auto len = strlen(newName) + 1;
    name = new char[len];
    strcpy(name, newName);
    return *this;
}

Product Product::setName(char *newName) {
    delete[] name;
    name = newName;
    return *this;
}

int Product::getCount() const {
    return count;
}

Product Product::setCount(int newCount) {
    count = newCount;
    return *this;
}

long Product::getPrice() const {
    return price;
}

Product Product::setPrice(long newPrice) {
    price = newPrice;
    return *this;
}

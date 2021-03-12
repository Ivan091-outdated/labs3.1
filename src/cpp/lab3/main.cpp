#include <iostream>
#include "product.h"

int main() {
    auto a = new Product("Apple", 1000, 2000);
    Product b;
    Product c("Balls", 2, 1);

    // Указатель на функцию.
    auto pgetName = &Product::getName;
    auto name = (*a.*pgetName)();

    a->setName("Milk").setCount(10000).setPrice(450);

    delete a;
}

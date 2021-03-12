//
// Created by ivan on 12/3/21.
//

#ifndef LAB3_PRODUCT_H
#define LAB3_PRODUCT_H


class Product {
public:
    Product(const char *name, int count, long price);

    Product(const Product &other);

    Product();

    ~Product();

    const char *getName() const;

    Product *setName(const char *newName);

    Product *setName(char *newName);

    int getCount() const;

    Product *setCount(int newCount);

    long getPrice() const;

    Product *setPrice(long newPrice);

private:
    char *name;
    int count;
    long price;
};


#endif //LAB3_PRODUCT_H

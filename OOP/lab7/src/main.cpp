#include <iostream>
#include "ArrayList.h"

int main() {
    ArrayList<int> list(10);
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);
    list.add(6);
    list.add(7);
    list.add(8);
    std::cout << list << std::endl;
    list.insert(3, 100);
    std::cout << list << std::endl;
    list.erase(4);
    std::cout << list << std::endl;
}

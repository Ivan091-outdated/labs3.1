#include <iostream>

class Parent : public std::exception {
public:
    Parent() = default;
};

class Child : public Parent {
public:
    Child() = default;
};

void task1(){
    try {
        std::cout << "\ntask1\n\n";
        throw Child();
    }
    catch (Parent &parent) {
        std::cerr << "caught Parent\n";
    }
    catch (Child &child) {
        std::cerr << "caught Child\n";
    }
}

void task2() {
    try {
        std::cout << "\ntask2\n\n";
        throw Child();
    }
    catch (Child &child) {
        std::cerr << "caught Child\n";
        try {
            throw Parent();

        }
        catch (Parent &parent) {
            std::cerr << "caught inner Parent\n";
        }
    }
    catch (Parent &parent) {
        std::cerr << "caught Parent\n";
    }
}


int main() {
    task1();
    task2();
}

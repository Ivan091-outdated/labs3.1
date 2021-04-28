#include <iostream>
#include "Person.h"
#include "Student.h"
#include <sstream>

int main() {
    Student a("name", 20, 5.6);
    Student b("name", 19, 7.8);
    Student c("name", 18, 9.0);
    Student d("name", 31, 5.1);
    for (auto q : Person::getList()){
        std::cout << q->toString();
    }
}

//
// Created by ivan on 17/3/21.
//

#include "Person.h"

#include <utility>

Person::Person(std::string name, int age) : name(std::move(name)), age(age) {}

const std::string &Person::getName() const {
    return name;
}

void Person::setName(const std::string &name) {
    Person::name = name;
}

int Person::getAge() const {
    return age;
}

void Person::setAge(int age) {
    Person::age = age;
}

std::ostream &operator<<(std::ostream &os, const Person &person) {
    os << "name: " << person.name << " age: " << person.age;
    return os;
}

Person::Person(const Person &other) : Person(other.name, other.age) {}

Person::~Person() = default;

//
// Created by ivan on 28/4/21.
//

#include "Person.h"

#include <utility>

std::vector<Person*> Person::list= std::vector<Person*>();

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

std::vector<Person *> Person::getList() {
    return Person::list;
}

Person::Person(std::string name, int age) : name(std::move(name)), age(age) {
    Person::list.push_back(this);
}

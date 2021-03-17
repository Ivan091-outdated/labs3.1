//
// Created by ivan on 17/3/21.
//

#include "Teacher.h"

Teacher::~Teacher() = default;

Teacher::Teacher(const std::string &name, int age, long salary) : Person(name, age), salary(salary) {}

long Teacher::getSalary() const {
    return salary;
}

void Teacher::setSalary(long salary) {
    Teacher::salary = salary;
}

std::ostream &operator<<(std::ostream &os, const Teacher &teacher) {
    os << static_cast<const Person &>(teacher) << " salary: " << teacher.salary;
    return os;
}

Teacher::Teacher(const Teacher &other) : Person(other), salary(other.salary) {}

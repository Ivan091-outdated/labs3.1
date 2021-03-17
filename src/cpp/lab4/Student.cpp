//
// Created by ivan on 17/3/21.
//

#include "Student.h"

Student::Student(const std::string &name, int age, double averageGrade) : Person(name, age),
                                                                          averageGrade(averageGrade) {}

std::ostream &operator<<(std::ostream &os, const Student &student) {
    os << static_cast<const Person &>(student) << " averageGrade: " << student.averageGrade;
    return os;
}

Student::Student(const Student &other) : Person(other), averageGrade(other.averageGrade) {}

Student::~Student() = default;

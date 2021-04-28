//
// Created by ivan on 28/4/21.
//

#include <sstream>
#include "Student.h"

double Student::getGrade() const {
    return grade;
}

void Student::setGrade(double grade) {
    Student::grade = grade;
}

std::string Student::toString() {
    std::stringstream ss;
    ss << "Student name: " << this->name << " age: " << this->age << " grade: " << this->grade << std::endl;
    return ss.str();
}

Student::Student(const std::string &name, int age, double grade) : Person(name, age), grade(grade) {}

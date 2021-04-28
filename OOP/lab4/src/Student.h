//
// Created by ivan on 28/4/21.
//

#ifndef SRC_STUDENT_H
#define SRC_STUDENT_H


#include <ostream>
#include "Person.h"

class Student : Person{
private:
    double grade;
public:
    Student(const std::string &name, int age, double grade);

    double getGrade() const;

    void setGrade(double grade);

    std::string toString() override;
};


#endif //SRC_STUDENT_H

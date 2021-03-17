//
// Created by ivan on 17/3/21.
//

#ifndef LAB4_STUDENT_H
#define LAB4_STUDENT_H


#include <ostream>
#include "Person.h"

class Student : public Person {

public:
    Student(const std::string &name, int age, double averageGrade);

    Student(const Student &other);

    ~Student() override;

    friend std::ostream &operator<<(std::ostream &os, const Student &student);

private:
    double averageGrade
};


#endif //LAB4_STUDENT_H

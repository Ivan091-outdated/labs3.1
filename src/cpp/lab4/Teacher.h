//
// Created by ivan on 17/3/21.
//

#ifndef LAB4_TEACHER_H
#define LAB4_TEACHER_H


#include <ostream>
#include "Person.h"

class Teacher : public Person {
public:
    Teacher(const std::string &name, int age, long salary);

    Teacher(const Teacher &other);

    ~Teacher() override;

    long getSalary() const;

    void setSalary(long salary);

    friend std::ostream &operator<<(std::ostream &os, const Teacher &teacher);

protected:
    long salary;
};


#endif //LAB4_TEACHER_H

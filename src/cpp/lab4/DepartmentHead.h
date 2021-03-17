//
// Created by ivan on 17/3/21.
//

#ifndef LAB4_DEPARTMENTHEAD_H
#define LAB4_DEPARTMENTHEAD_H


#include "Teacher.h"

class DepartmentHead : public Teacher {
public:
    DepartmentHead(const std::string &name, int age, long salary, int peopleCount);

    DepartmentHead(const DepartmentHead& other);

private:

    int peopleCount;
};


#endif //LAB4_DEPARTMENTHEAD_H

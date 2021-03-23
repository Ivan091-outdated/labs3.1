//
// Created by ivan on 17/3/21.
//

#include "DepartmentHead.h"

DepartmentHead::DepartmentHead(const std::string &name, int age, long salary, int peopleCount) :
Teacher(name, age, salary), peopleCount(peopleCount) {}

DepartmentHead::DepartmentHead(const DepartmentHead &other) : Teacher(other), peopleCount(other.peopleCount) {}

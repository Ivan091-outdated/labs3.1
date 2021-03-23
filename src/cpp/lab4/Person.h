//
// Created by ivan on 17/3/21.
//

#ifndef LAB4_PERSON_H
#define LAB4_PERSON_H


#include <string>
#include <ostream>

class Person {
public:
    Person(std::string name, int age);

    Person(const Person &other);

    virtual ~Person();

    const std::string &getName() const;

    void setName(const std::string &name);

    int getAge() const;

    void setAge(int age);

    friend std::ostream &operator<<(std::ostream &os, const Person &person);

protected:
    std::string name;
    int age;
};


#endif //LAB4_PERSON_H

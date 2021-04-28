//
// Created by ivan on 28/4/21.
//

#ifndef SRC_PERSON_H
#define SRC_PERSON_H


#include <string>
#include <vector>
#include <ostream>

class Person {
private:
    static std::vector<Person*> list;
protected:
    std::string name;
    int age = 0;
public:
    Person(std::string name, int age);

    const std::string &getName() const;

    void setName(const std::string &name);

    int getAge() const;

    void setAge(int age);

    virtual std::string toString() = 0;

    static std::vector<Person*> getList();
};

#endif //SRC_PERSON_H

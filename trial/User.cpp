#include <iostream>
#include "User.h"

using namespace std;

User::User(int id, string name) {

    this->id = id;
    this->name = name;
}

int User::getId() const {

    return id;
}

string User::getName() const {

    return name;
}

void User::show() const {

    cout
        << "ID: "
        << id
        << " Name: "
        << name
        << endl;
}
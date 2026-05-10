#include "User.h"
#include <stdio.h>

User::User(int id, string name) {
    this->id = id;
    this->name = name;
}

int User::getId() const { return id; }
string User::getName() const { return name; }

void User::show() const {
    printf("User | ID: %d | Name: %s\n", id, name.c_str());
}
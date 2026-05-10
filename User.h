#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
private:
    int id;
    string name;

public:
    User(int id = 0, string name = "");

    int getId() const;
    string getName() const;

    void show() const;
};

#endif
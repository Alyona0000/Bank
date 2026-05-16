#include <iostream>
#include "Security.h"

using namespace std;

Security::Security(
    string name,
    string type,
    double price,
    int quantity,
    double yearlyGrowth
) {

    this->name = name;
    this->type = type;

    this->price = price;

    this->quantity = quantity;

    this->yearlyGrowth = yearlyGrowth;
}

string Security::getName() const {

    return name;
}

string Security::getType() const {

    return type;
}

double Security::getPrice() const {

    return price;
}

int Security::getQuantity() const {

    return quantity;
}

void Security::updatePrice() {

    double growth = yearlyGrowth / 365.0;

    price = price + price * growth;
}

double Security::buy(int count) {

    quantity += count;

    return price * count;
}

double Security::sell(int count) {

    if (count > quantity) {

        count = quantity;
    }

    quantity -= count;

    return price * count;
}

double Security::totalValue() const {

    return price * quantity;
}

void Security::show() const {

    cout
        << name
        << " "
        << type
        << " price: "
        << price
        << " quantity: "
        << quantity
        << endl;
}
#include "Security.h"
#include <stdio.h>
#include <stdlib.h>

Security::Security(string name, string type, double price,
                   int quantity, double yearlyGrowth) {
    this->name = name;
    this->type = type;
    this->price = price;
    this->quantity = quantity;
    this->yearlyGrowth = yearlyGrowth;
}

string Security::getName() const { return name; }
string Security::getType() const { return type; }
double Security::getPrice() const { return price; }
int Security::getQuantity() const { return quantity; }

void Security::updatePrice() {
    double randomChange = (rand() % 21 - 10) / 100.0;
    double dailyGrowth = yearlyGrowth / 365.0;

    price = price * (1 + dailyGrowth + randomChange / 20.0);

    if (price < 1) {
        price = 1;
    }
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
    printf("Security | %s | Type: %s | Price: %.2f | Quantity: %d | Value: %.2f\n",
           name.c_str(), type.c_str(), price, quantity, totalValue());
}
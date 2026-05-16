#ifndef SECURITY_H
#define SECURITY_H

#include <string>

using namespace std;

class Security {

private:

    string name;
    string type;

    double price;

    int quantity;

    double yearlyGrowth;

public:

    Security(
        string name = "",
        string type = "",
        double price = 0,
        int quantity = 0,
        double yearlyGrowth = 0
    );

    string getName() const;

    string getType() const;

    double getPrice() const;

    int getQuantity() const;

    void updatePrice();

    double buy(int count);

    double sell(int count);

    double totalValue() const;

    void show() const;
};

#endif
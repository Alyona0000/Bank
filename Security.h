#ifndef SECURITY_H
#define SECURITY_H

#include <string>

class Security {
private:
    std::string name;
    std::string type;
    double price;
    int quantity;
    double yearlyGrowth;

public:
    Security(const std::string& name = "",
             const std::string& type = "",
             double price = 0,
             int quantity = 0,
             double yearlyGrowth = 0);

    std::string getName() const;
    std::string getType() const;

    double getPrice() const;
    int getQuantity() const;

    void updatePrice();

    double buy(int count);
    double sell(int count);

    double totalValue() const;

    void show() const;
};

#endif
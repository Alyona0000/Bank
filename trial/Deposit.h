#ifndef DEPOSIT_H
#define DEPOSIT_H

class Deposit {

private:

    int userId;

    int startDay;
    int endDay;

    double amount;
    double interest;

public:

    Deposit(
        int userId = 0,
        int startDay = 0,
        int endDay = 0,
        double amount = 0,
        double interest = 0
    );

    int getUserId() const;

    int getStartDay() const;

    int getEndDay() const;

    double getAmount() const;

    double getInterest() const;

    double dailyCost() const;

    void show() const;
};

#endif

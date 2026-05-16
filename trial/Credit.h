#ifndef CREDIT_H
#define CREDIT_H

class Credit {

private:

    int userId;

    int startDay;
    int endDay;

    double amount;
    double interest;

public:

    Credit(
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

    double dailyProfit() const;

    void show() const;
};

#endif
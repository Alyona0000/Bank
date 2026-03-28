#include <stdio.h>

class Deposit {
private:
    int date_issue;
    int return_date;
    double amount;
    double interest;

public:
    Deposit(int di = 0, int rd = 0, double a = 0, double i = 0) {
        date_issue = di;
        return_date = rd;
        amount = a;
        interest = i;
    }

    double income() const {
        return amount * interest;
    }

    double getAmount() const {
        return amount;
    }
};

class Credit {
private:
    int date_issue;
    int return_date;
    double amount;
    double interest;

public:
    Credit(int di = 0, int rd = 0, double a = 0, double i = 0) {
        date_issue = di;
        return_date = rd;
        amount = a;
        interest = i;
    }

    double income() const {
        return amount * interest;
    }

    double getAmount() const {
        return amount;
    }
};

class Bank {
private:
    double starting_capital;
    Deposit deposit;
    Credit credit;

public:
    Bank(double capital, Deposit d, Credit c) {
        starting_capital = capital;
        deposit = d;
        credit = c;
    }

    double working_day_formula() {
        double D = deposit.getAmount();
        double K = credit.getAmount();
        double KP = credit.income();
        double DP = deposit.income();

        starting_capital = starting_capital + D - K + KP - DP;

        return starting_capital;
    }

    void show() {
        printf("Capital: %.2f\n", starting_capital);
    }
};
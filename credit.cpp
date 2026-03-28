#include <stdio.h>

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

    void show() const {
        printf("Credit: %.2f, interest = %.2f\n", amount, interest);
    }
};
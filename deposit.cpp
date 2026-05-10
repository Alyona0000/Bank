#include "Deposit.h"
#include <stdio.h>

Deposit::Deposit(int userId, int startDay, int endDay,
                 double amount, double interest) {
    this->userId = userId;
    this->startDay = startDay;
    this->endDay = endDay;
    this->amount = amount;
    this->interest = interest;
}

int Deposit::getUserId() const { return userId; }
int Deposit::getStartDay() const { return startDay; }
int Deposit::getEndDay() const { return endDay; }
double Deposit::getAmount() const { return amount; }
double Deposit::getInterest() const { return interest; }

double Deposit::dailyCost() const {
    return amount * interest / 365.0;
}

void Deposit::show() const {
    printf("Deposit | User: %d | Amount: %.2f | Interest: %.2f | Days: %d-%d\n",
           userId, amount, interest, startDay, endDay);
}
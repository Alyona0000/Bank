#include <iostream>
#include "Credit.h"

using namespace std;

Credit::Credit(
    int userId,
    int startDay,
    int endDay,
    double amount,
    double interest
) {

    this->userId = userId;

    this->startDay = startDay;
    this->endDay = endDay;

    this->amount = amount;
    this->interest = interest;
}

int Credit::getUserId() const {

    return userId;
}

int Credit::getStartDay() const {

    return startDay;
}

int Credit::getEndDay() const {

    return endDay;
}

double Credit::getAmount() const {

    return amount;
}

double Credit::getInterest() const {

    return interest;
}

double Credit::dailyProfit() const {

    return amount * interest / 365.0;
}

void Credit::show() const {

    cout
        << "Credit | User: "
        << userId
        << " Amount: "
        << amount
        << endl;
}
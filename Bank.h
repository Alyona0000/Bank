#ifndef BANK_H
#define BANK_H

#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

#include "Deposit.h"
#include "Credit.h"
#include "Security.h"
#include "User.h"

using namespace std;

template <typename T>
class Bank {
private:
    T capital;
    T startCapital;

    vector<User> users;
    vector<Deposit> deposits;
    vector<Credit> credits;
    vector<Security> securities;

    T totalDeposits;
    T totalCredits;
    T creditProfit;
    T depositCosts;
    T securityProfit;

    int currentDay;

public:
    Bank(T capital = 0) {
        this->capital = capital;
        this->startCapital = capital;

        totalDeposits = 0;
        totalCredits = 0;
        creditProfit = 0;
        depositCosts = 0;
        securityProfit = 0;

        currentDay = 1;
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void addDeposit(const Deposit& deposit) {
        deposits.push_back(deposit);
        capital += deposit.getAmount();
        totalDeposits += deposit.getAmount();
    }

    void addCredit(const Credit& credit) {
        if (capital >= credit.getAmount()) {
            credits.push_back(credit);
            capital -= credit.getAmount();
            totalCredits += credit.getAmount();
        }
    }

    void addSecurity(const Security& security) {
        securities.push_back(security);
    }

    void addManualDeposit(T amount) {
        if (amount <= 0) return;

        deposits.push_back(Deposit(1, currentDay, currentDay + 365, amount, 0.08));

        capital += amount;
        totalDeposits += amount;
    }

    void giveManualCredit(T amount) {
        if (amount <= 0) return;

        if (capital >= amount) {
            credits.push_back(Credit(1, currentDay, currentDay + 365, amount, 0.18));

            capital -= amount;
            totalCredits += amount;
        }
    }

    void buyRandomSecurity() {
        if (securities.empty()) return;

        int index = rand() % securities.size();
        int count = rand() % 5 + 1;

        T cost = securities[index].getPrice() * count;

        if (capital >= cost) {
            securities[index].buy(count);
            capital -= cost;
        }
    }

    void sellRandomSecurity() {
        if (securities.empty()) return;

        int index = rand() % securities.size();
        int count = rand() % 3 + 1;

        T income = securities[index].sell(count);

        capital += income;
        securityProfit += income;
    }

    void simulateNextDay() {
        currentDay++;

        T KP = 0;
        T DP = 0;

        for (size_t i = 0; i < deposits.size(); i++) {
            if (currentDay >= deposits[i].getStartDay() &&
                currentDay <= deposits[i].getEndDay()) {
                DP += deposits[i].dailyCost();
            }
        }

        for (size_t i = 0; i < credits.size(); i++) {
            if (currentDay >= credits[i].getStartDay() &&
                currentDay <= credits[i].getEndDay()) {
                KP += credits[i].dailyProfit();
            }
        }

        for (size_t i = 0; i < securities.size(); i++) {
            securities[i].updatePrice();
        }

        capital = capital + KP - DP;

        creditProfit += KP;
        depositCosts += DP;
    }

    T profit() const {
        return capital - startCapital;
    }

    string toJson() const {
        stringstream ss;

        ss << "{";
        ss << "\"capital\":" << capital << ",";
        ss << "\"totalDeposits\":" << totalDeposits << ",";
        ss << "\"totalCredits\":" << totalCredits << ",";
        ss << "\"creditProfit\":" << creditProfit << ",";
        ss << "\"depositCosts\":" << depositCosts << ",";
        ss << "\"securityProfit\":" << securityProfit << ",";
        ss << "\"profit\":" << profit() << ",";
        ss << "\"day\":" << currentDay;
        ss << "}";

        return ss.str();
    }
};

#endif
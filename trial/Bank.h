#ifndef BANK_H
#define BANK_H

#include <vector>
#include <iostream>

#include "User.h"
#include "Deposit.h"
#include "Credit.h"
#include "Security.h"

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

public:

    Bank(T capital = 0) {

        this->capital = capital;
        this->startCapital = capital;

        totalDeposits = 0;
        totalCredits = 0;

        creditProfit = 0;
        depositCosts = 0;
        securityProfit = 0;
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void addDeposit(const Deposit& deposit) {
        deposits.push_back(deposit);
    }

    void addCredit(const Credit& credit) {
        credits.push_back(credit);
    }

    void addSecurity(const Security& security) {
        securities.push_back(security);
    }

    void simulateDay(int day) {

        T depositsMoney = 0;
        T creditsMoney = 0;

        T creditsProfit = 0;
        T depositsCost = 0;

        T securitiesIncome = 0;

        for (size_t i = 0; i < deposits.size(); i++) {

            if (deposits[i].getStartDay() == day) {

                depositsMoney += deposits[i].getAmount();
            }

            if (day >= deposits[i].getStartDay()
                && day <= deposits[i].getEndDay()) {

                depositsCost += deposits[i].dailyCost();
            }
        }

        for (size_t i = 0; i < credits.size(); i++) {

            if (credits[i].getStartDay() == day) {

                creditsMoney += credits[i].getAmount();
            }

            if (day >= credits[i].getStartDay()
                && day <= credits[i].getEndDay()) {

                creditsProfit += credits[i].dailyProfit();
            }
        }

        for (size_t i = 0; i < securities.size(); i++) {

            securities[i].updatePrice();

            int action = rand() % 3;

            if (action == 0) {

                int count = rand() % 3 + 1;

                double cost = securities[i].buy(count);

                if (capital >= cost) {

                    capital -= cost;
                }
            }

            else if (action == 1) {

                int count = rand() % 3 + 1;

                double income = securities[i].sell(count);

                capital += income;

                securitiesIncome += income;
            }
        }

        capital =
            capital
            + depositsMoney
            - creditsMoney
            + creditsProfit
            - depositsCost;

        totalDeposits += depositsMoney;
        totalCredits += creditsMoney;

        creditProfit += creditsProfit;
        depositCosts += depositsCost;
        securityProfit += securitiesIncome;
    }

    T profit() const {

        return capital - startCapital;
    }

    void showState() const {

        cout << "Capital: " << capital << endl;

        cout << "Deposits: " << totalDeposits << endl;

        cout << "Credits: " << totalCredits << endl;

        cout << "Credit profit: " << creditProfit << endl;

        cout << "Deposit costs: " << depositCosts << endl;

        cout << "Security income: " << securityProfit << endl;

        cout << "Current profit: " << profit() << endl;
    }

    void showAllData() const {

        cout << "\n=== USERS ===\n" << endl;

        for (size_t i = 0; i < users.size(); i++) {

            users[i].show();
        }

        cout << "\n=== DEPOSITS ===\n" << endl;

        for (size_t i = 0; i < deposits.size(); i++) {

            deposits[i].show();
        }

        cout << "\n=== CREDITS ===\n" << endl;

        for (size_t i = 0; i < credits.size(); i++) {

            credits[i].show();
        }

        cout << "\n=== SECURITIES ===\n" << endl;

        for (size_t i = 0; i < securities.size(); i++) {

            securities[i].show();
        }
    }
};

#endif
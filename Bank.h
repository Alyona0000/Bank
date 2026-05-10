#ifndef BANK_H
#define BANK_H

#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
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
        T D = 0;
        T K = 0;
        T KP = 0;
        T DP = 0;
        T SP = 0;

        for (size_t i = 0; i < deposits.size(); i++) {
            if (deposits[i].getStartDay() == day) {
                D += deposits[i].getAmount();
            }

            if (day >= deposits[i].getStartDay() &&
                day <= deposits[i].getEndDay()) {
                DP += deposits[i].dailyCost();
            }
        }

        for (size_t i = 0; i < credits.size(); i++) {
            if (credits[i].getStartDay() == day) {
                K += credits[i].getAmount();
            }

            if (day >= credits[i].getStartDay() &&
                day <= credits[i].getEndDay()) {
                KP += credits[i].dailyProfit();
            }
        }

        for (size_t i = 0; i < securities.size(); i++) {
            securities[i].updatePrice();

            int action = rand() % 3;

            if (action == 0) {
                int count = rand() % 3 + 1;
                T cost = securities[i].buy(count);

                if (capital >= cost) {
                    capital -= cost;
                }
            } else if (action == 1) {
                int count = rand() % 3 + 1;
                T income = securities[i].sell(count);
                capital += income;
                SP += income;
            }
        }

        capital = capital + D - K + KP - DP;

        totalDeposits += D;
        totalCredits += K;
        creditProfit += KP;
        depositCosts += DP;
        securityProfit += SP;
    }

    void simulatePeriod(int days) {
        ofstream file("bank_result.csv");

        file << "day,capital,total_deposits,total_credits,credit_profit,deposit_costs,security_profit\n";

        for (int day = 1; day <= days; day++) {
            simulateDay(day);

            file << day << ","
                 << capital << ","
                 << totalDeposits << ","
                 << totalCredits << ","
                 << creditProfit << ","
                 << depositCosts << ","
                 << securityProfit << "\n";

            if (day % 30 == 0) {
                printf("\n--- Day %d ---\n", day);
                showState();
            }
        }

        file.close();
    }

    T profit() const {
        return capital - startCapital;
    }

    void showState() const {
        printf("Bank capital: %.2f\n", (double)capital);
        printf("Total deposits received: %.2f\n", (double)totalDeposits);
        printf("Total credits issued: %.2f\n", (double)totalCredits);
        printf("Credit profit: %.2f\n", (double)creditProfit);
        printf("Deposit costs: %.2f\n", (double)depositCosts);
        printf("Security operations income: %.2f\n", (double)securityProfit);
        printf("Current profit: %.2f\n", (double)profit());

        printf("\nSecurities:\n");
        for (size_t i = 0; i < securities.size(); i++) {
            securities[i].show();
        }
    }

    void showAllData() const {
        printf("\n===== USERS =====\n");
        for (size_t i = 0; i < users.size(); i++) {
            users[i].show();
        }

        printf("\n===== DEPOSITS =====\n");
        for (size_t i = 0; i < deposits.size(); i++) {
            deposits[i].show();
        }

        printf("\n===== CREDITS =====\n");
        for (size_t i = 0; i < credits.size(); i++) {
            credits[i].show();
        }

        printf("\n===== SECURITIES =====\n");
        for (size_t i = 0; i < securities.size(); i++) {
            securities[i].show();
        }
    }
};

#endif
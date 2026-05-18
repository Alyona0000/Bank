#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Bank.h"
#include "User.h"
#include "Deposit.h"
#include "Credit.h"
#include "Security.h"

using namespace std;

int main() {
    cout << "PROGRAM STARTED" << endl;
    // system("pause");

    srand(time(NULL));

    Bank<double> bank(100000);

    ifstream file("data.csv");

    if (!file.is_open()) {
        cout << "Cannot open CSV file!" << endl;
        return 1;
    }

    string line;

    getline(file, line);
    while (getline(file, line)) {

        stringstream ss(line);

        string type;
        string userId, name;
        string startDay, endDay;
        string amount, interest;

        string securityName;
        string securityType;
        string price;
        string quantity;
        string growth;

        getline(ss, type, ',');
        getline(ss, userId, ',');
        getline(ss, name, ',');

        getline(ss, startDay, ',');
        getline(ss, endDay, ',');

        getline(ss, amount, ',');
        getline(ss, interest, ',');

        getline(ss, securityName, ',');
        getline(ss, securityType, ',');

        getline(ss, price, ',');
        getline(ss, quantity, ',');
        getline(ss, growth, ',');

        if (type == "user") {

            bank.addUser(
                User(
                    stoi(userId),
                    name
                )
            );
        }

        else if (type == "deposit") {

            bank.addDeposit(
                Deposit(
                    stoi(userId),
                    stoi(startDay),
                    stoi(endDay),
                    stod(amount),
                    stod(interest)
                )
            );
        }

        else if (type == "credit") {

            bank.addCredit(
                Credit(
                    stoi(userId),
                    stoi(startDay),
                    stoi(endDay),
                    stod(amount),
                    stod(interest)
                )
            );
        }

        else if (type == "security") {

            bank.addSecurity(
                Security(
                    securityName,
                    securityType,
                    stod(price),
                    stoi(quantity),
                    stod(growth)
                )
            );
        }
    }

    file.close();

    cout << "\n===== DATA =====\n" << endl;

    bank.showAllData();

    cout << "\n===== SIMULATION =====\n" << endl;

    for (int day = 1; day <= 30; day++) {

        cout << "\n----- DAY " << day << " -----\n" << endl;

        bank.simulateDay(day);

        bank.showState();
    }

/*
 */
    cout << "Press ENTER to exit..." << endl;
    cin.get();

    return 0;
}
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// -------------------- Deposit --------------------
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

    int getDateIssue() const {
        return date_issue;
    }

    int getReturnDate() const {
        return return_date;
    }

    double getAmount() const {
        return amount;
    }

    double getInterest() const {
        return interest;
    }

    // скільки банк платить по депозиту за рік
    double income_year() const {
        return amount * interest;
    }

    // скільки банк платить за 1 день
    double income_per_day() const {
        return (amount * interest) / 365.0;
    }

    void show() const {
        printf("Deposit: date_issue=%d, return_date=%d, amount=%.2f, interest=%.2f\n",
               date_issue, return_date, amount, interest);
    }
};

// -------------------- Credit --------------------
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

    int getDateIssue() const {
        return date_issue;
    }

    int getReturnDate() const {
        return return_date;
    }

    double getAmount() const {
        return amount;
    }

    double getInterest() const {
        return interest;
    }

    // скільки банк заробляє по кредиту за рік
    double income_year() const {
        return amount * interest;
    }

    // скільки банк заробляє за 1 день
    double income_per_day() const {
        return (amount * interest) / 365.0;
    }

    void show() const {
        printf("Credit: date_issue=%d, return_date=%d, amount=%.2f, interest=%.2f\n",
               date_issue, return_date, amount, interest);
    }
};

// -------------------- Bank --------------------
class Bank {
private:
    double starting_capital;
    vector<Deposit> deposits;
    vector<Credit> credits;

public:
    Bank(double capital = 0) {
        starting_capital = capital;
    }

    void add_deposit(const Deposit& d) {
        deposits.push_back(d);
    }

    void add_credit(const Credit& c) {
        credits.push_back(c);
    }

    void show_lists() const {
        printf("Starting capital: %.2f\n", starting_capital);

        printf("\nDeposits:\n");
        for (size_t i = 0; i < deposits.size(); i++) {
            deposits[i].show();
        }

        printf("\nCredits:\n");
        for (size_t i = 0; i < credits.size(); i++) {
            credits[i].show();
        }
    }

    // читання CSV
    void read_csv(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            printf("Error: cannot open file %s\n", filename.c_str());
            return;
        }

        string line;
        getline(file, line); // пропускаємо заголовок

        while (getline(file, line)) {
            stringstream ss(line);
            string type, date_issue_str, return_date_str, amount_str, interest_str;

            getline(ss, type, ',');
            getline(ss, date_issue_str, ',');
            getline(ss, return_date_str, ',');
            getline(ss, amount_str, ',');
            getline(ss, interest_str, ',');

            int date_issue = stoi(date_issue_str);
            int return_date = stoi(return_date_str);
            double amount = stod(amount_str);
            double interest = stod(interest_str);

            if (type == "deposit") {
                Deposit d(date_issue, return_date, amount, interest);
                add_deposit(d);
            }
            else if (type == "credit") {
                Credit c(date_issue, return_date, amount, interest);
                add_credit(c);
            }
        }

        file.close();
    }

    // розрахунок на 1 день
    double calculate_one_day(int day) {
        double D = 0;   // нові депозити в цей день
        double K = 0;   // нові кредити в цей день
        double KP = 0;  // прибуток по кредитах за день
        double DP = 0;  // витрати по депозитах за день

        for (size_t i = 0; i < deposits.size(); i++) {
            if (deposits[i].getDateIssue() == day) {
                D += deposits[i].getAmount();
            }

            if (day >= deposits[i].getDateIssue() && day <= deposits[i].getReturnDate()) {
                DP += deposits[i].income_per_day();
            }
        }

        for (size_t i = 0; i < credits.size(); i++) {
            if (credits[i].getDateIssue() == day) {
                K += credits[i].getAmount();
            }

            if (day >= credits[i].getDateIssue() && day <= credits[i].getReturnDate()) {
                KP += credits[i].income_per_day();
            }
        }

        // формула робочого дня:
        // A = A + D - K + KP - DP
        starting_capital = starting_capital + D - K + KP - DP;

        return starting_capital;
    }

    // розрахунок на рік вперед
    void calculate_year() {
        printf("\n----- Calculation for 1 year -----\n");

        for (int day = 1; day <= 365; day++) {
            double capital_today = calculate_one_day(day);

            // щоб не виводити 365 рядків без потреби,
            // показуємо тільки кожен 30-й день і останній
            if (day % 30 == 0 || day == 365) {
                printf("Day %d -> capital = %.2f\n", day, capital_today);
            }
        }

        printf("\nCapital after 1 year: %.2f\n", starting_capital);
    }
};

// -------------------- main --------------------
int main() {
    Bank bank(2000); // початковий капітал

    bank.read_csv("data.csv");
    bank.show_lists();
    bank.calculate_year();

    return 0;
}
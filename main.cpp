#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Bank.h"
#include "User.h"
#include "Deposit.h"
#include "Credit.h"
#include "Security.h"

int main() {
    srand(time(NULL));

    Bank<double> bank(100000);

    bank.addUser(User(1, "Anna"));
    bank.addUser(User(2, "Oleh"));
    bank.addUser(User(3, "Maria"));
    bank.addUser(User(4, "Ivan"));

    bank.addDeposit(Deposit(1, 1, 365, 10000, 0.08));
    bank.addDeposit(Deposit(2, 20, 300, 7000, 0.07));
    bank.addDeposit(Deposit(3, 50, 250, 12000, 0.09));

    bank.addCredit(Credit(1, 5, 365, 15000, 0.18));
    bank.addCredit(Credit(2, 40, 320, 8000, 0.16));
    bank.addCredit(Credit(4, 70, 360, 20000, 0.20));

    bank.addSecurity(Security("Apple", "stock", 180, 10, 0.12));
    bank.addSecurity(Security("Tesla", "stock", 220, 8, 0.15));
    bank.addSecurity(Security("Government Bond", "bond", 100, 20, 0.05));

    printf("===== START BANK DATA =====\n");
    bank.showAllData();

    printf("\n===== SIMULATION START =====\n");
    bank.simulatePeriod(365);

    printf("\n===== FINAL BANK STATE =====\n");
    bank.showState();

    printf("\nResults saved to bank_result.csv\n");

    return 0;
}
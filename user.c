#include <stdio.h>
#include "deposit.c"
#include "credit.c"
#include "bank.c"

int main() {

    Bank bank;
    bank.starting_capital = 10000;
    bank.dep_count = 0;
    bank.cred_count = 0;

    Deposit d1 = {1, 10, 5000, 0.05};
    Credit c1 = {1, 10, 3000, 0.1};

    add_deposit(&bank, d1);
    add_credit(&bank, c1);

    double result = calculate_day(&bank);

    printf("Capital after day: %.2f\n", result);

    return 0;
}
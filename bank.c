#include <stdio.h>

#define MAX 100

typedef struct {
    double starting_capital;

    Deposit deposits[MAX];
    int dep_count;

    Credit credits[MAX];
    int cred_count;

} Bank;


//  депозит
void add_deposit(Bank *b, Deposit d) {
    b->deposits[b->dep_count++] = d;
}

//  кредит
void add_credit(Bank *b, Credit c) {
    b->credits[b->cred_count++] = c;
}


// ФОРМУЛА РОБОЧОГО ДНЯ !!!!!!!!!!!!!!!!
double calculate_day(Bank *b) {

    double D = 0;   // видані депозити
    double K = 0;   // видані кредити
    double KP = 0;  // проценти по кредитах
    double DP = 0;  // проценти по депозитах

    for(int i = 0; i < b->dep_count; i++) {
        D += b->deposits[i].amount;
        DP += b->deposits[i].amount * b->deposits[i].interest;
    }

    for(int i = 0; i < b->cred_count; i++) {
        K += b->credits[i].amount;
        KP += b->credits[i].amount * b->credits[i].interest;
    }

    // формула:
    // О = A + D + K + KP - DP

    b->starting_capital =
        b->starting_capital
        + D        // отримали від депозитів
        + K        // видали кредити (оборот)
        + KP       // заробили %
        - DP;      // виплатили %

    return b->starting_capital;
}
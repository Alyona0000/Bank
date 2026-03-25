#include <stdio.h>

typedef struct {
    int date_issue;
    int return_date;
    double amount;
    double interest;
} Deposit;

// дохід з депозиту(відсоток)
double deposit_income(Deposit d) {
    return d.amount * d.interest;
}
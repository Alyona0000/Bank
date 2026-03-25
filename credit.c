#include <stdio.h>

typedef struct {
    int date_issue;
    int return_date;
    double amount;
    double interest;
} Credit;

// дохід з кредиту(відсоток)
double credit_income(Credit c) {
    return c.amount * c.interest;
}
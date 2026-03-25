#include <stdio.h>

typedef struct {
    int date_issue;
    int return_date;
    double amount;
    double interest;
} Credit;


double credit_income(Credit c) {
    return c.amount * c.interest;
}
#include <iostream>
#include "Account.h"
#include "Savings_Account.h"
#include "Money_Market_Account.h"
using namespace std;

int main() {
    Money_Market_Account mma = Money_Market_Account(0.05, 6);
    Money_Market_Account mma2 = mma;
    Savings_Account acct = Savings_Account(0.05);
    Savings_Account acct2 = acct;
    Account Keith_Account {};
    Keith_Account.deposit(2000);
    Keith_Account.withdraw(500);
    Savings_Account* Keith_Savings_Account {nullptr};
    Keith_Savings_Account = new Savings_Account {0.035};
    Keith_Savings_Account->deposit(15000);
    Keith_Savings_Account->withdraw(4000);
    Keith_Savings_Account->show_interest_rate();
    Money_Market_Account* Keith_MMA {nullptr};
    double interest_rate {0.05};
    int withdraws_per_month {6};
    Keith_MMA = new Money_Market_Account {interest_rate, withdraws_per_month};
    Keith_MMA->deposit(30000);
    Keith_MMA->show_interest_rate();
    Keith_MMA->show_withdraws_per_month();
    Money_Market_Account* Keith_Test {nullptr};
    Keith_Test = new Money_Market_Account(*Keith_MMA); // am I supposed to be able to do this???
    Keith_Test->show_account_breakdown();
    Keith_Test->deposit(1000);
    Keith_Test->set_interest_rate(0.07);
    Keith_Test->set_withdraws_per_month(10);
    Keith_Test->show_account_breakdown();
    Keith_MMA->show_account_breakdown();
    Money_Market_Account Another_Test = Money_Market_Account(0.03, 6);
    Keith_Test->withdraw(1000);
    //Money_Market_Account mma = Money_Market_Account(0.05, 6);
    //Money_Market_Account mma2 = mma;
}

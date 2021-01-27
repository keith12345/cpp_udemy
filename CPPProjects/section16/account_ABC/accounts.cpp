#include <iostream>
#include "Account.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include "utils.cpp"
#include <string>
#include <vector>

int main() {
    Checking_Account acc = Checking_Account();

    Checking_Account acc1 = Checking_Account("Account 1", 1000);
    acc1.deposit(-4000);
    acc1.withdraw(4000);
    acc1.update_interest_rate(0.02);
    acc1.deposit(2000);

    std::string account_name = "Account 2";
    double account_balance = 2000.0;
    double interest_rate = 0.05;
    Checking_Account acc2 = Checking_Account(account_name, account_balance, interest_rate);
    int additional_deposit = 1200;
    double updated_interest_rate = 0.075;
    acc2.deposit(additional_deposit);
    acc2.update_interest_rate(updated_interest_rate);

    //Savings_Account sav_acc = Savings_Account("Keith's Savings Account", 2000);
    //sav_acc.withdraw(35);
    //sav_acc.withdraw(200);

    std::vector<Account> accounts = std::vector<Account>();
    accounts.push_back(acc);
    //accounts.push_back(acc1);
    //accounts.push_back(acc2);
    //accounts.push_back(sav_acc);
//
    //display_accounts(accounts);
}

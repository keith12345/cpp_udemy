#include <iostream>
#include "CheckingAccount.h"
#include "utils.cpp"
#include <string>

int main() {
    Checking_Account acc = Checking_Account();
    std::cout << acc << std::endl;

    Checking_Account acc1 = Checking_Account("Account 1", 1000, 0.01);
    std::cout << acc1 << std::endl;
    acc1.deposit(-4000);
    acc1.withdraw(4000);
    acc1.update_interest_rate(0.02);
    acc1.deposit(2000);
    std::cout << acc1 << std::endl;

    std::string account_name = "Account 2";
    double account_balance = 2000.0;
    double interest_rate = 0.05;
    Checking_Account acc2 = Checking_Account(account_name, account_balance, interest_rate);
    std::cout << acc2 << std::endl;
    int additional_deposit = 1200;
    double updated_interest_rate = 0.075;
    acc2.deposit(additional_deposit);
    acc2.update_interest_rate(updated_interest_rate);
    std::cout << acc2 << std::endl;
}

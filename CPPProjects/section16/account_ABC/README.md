# Expected output from running `accounts.cpp`

```c++
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
    std::cout << std::endl;

    std::string account_name = "Account 2";
    double account_balance = 2000.0;
    double interest_rate = 0.05;
    Checking_Account acc2 = Checking_Account(account_name, account_balance, interest_rate);
    int additional_deposit = 1200;
    double updated_interest_rate = 0.075;
    acc2.deposit(additional_deposit);
    acc2.update_interest_rate(updated_interest_rate);
    std::cout << std::endl;

    Savings_Account sav_acc = Savings_Account("Keith's Savings Account", 2000);
    sav_acc.withdraw(35);
    sav_acc.withdraw(200);
    sav_acc.deposit(1500);
    std::cout << sav_acc << std::endl;
    std::cout << std::endl;

    std::vector<Account*> accounts;
    accounts.push_back(&acc);
    accounts.push_back(&acc1);
    accounts.push_back(&acc2);
    accounts.push_back(&sav_acc);

    display_accounts(accounts);
}

```

Expected output:
```
Calling Checking Account Constructor for: Unnamed
Calling Checking Account Constructor for: Account 1
[ERROR] - Invalid value: -4000 is negative
You have 1000 in your account. You are withdrawing: 4000
You are now carrying a negative balance: -3000
Updating interest rate from:0 to: 0.02
Balance increased by: 2000. Your new balance is: -1000
You are still carrying a negative balance: -1000

Calling Checking Account Constructor for: Account 2
Balance increased by: 1200. Your new balance is: 3200
Updating interest rate from:0.05 to: 0.075

Calling Checking Account Constructor for: Keith's Savings Account
Calling Savings Account Constructor for: Keith's Savings Account
You have made 0 withdrawals this month.
You have 1 remaining withdrawals this month.
You have 2000 in your account. You are withdrawing: 35
You have no remaining withdrawals
Balance increased by: 1500. Your new balance is: 3465
Displaying Account: Keith's Savings Account
	Balance: 3465
	Interest Rate: 0.2
	You have performed 1 withdrawals this month
	You have 0 remaining withdrawals this month.


Displaying Accounts:

Displaying Account: Unnamed
	Balance: 0
	Interest Rate: 0

Displaying Account: Account 1
	Balance: -1000
	Interest Rate: 0.02

Displaying Account: Account 2
	Balance: 3200
	Interest Rate: 0.075

Displaying Account: Keith's Savings Account
	Balance: 3465
	Interest Rate: 0.2
	You have performed 1 withdrawals this month
	You have 0 remaining withdrawals this month.

Calling Savings Account Destructor for: Keith's Savings Account
Calling Checking Account Destructor for: Keith's Savings Account
Calling ABC Account Destructor
Calling Checking Account Destructor for: Account 2
Calling ABC Account Destructor
Calling Checking Account Destructor for: Account 1
Calling ABC Account Destructor
Calling Checking Account Destructor for: Unnamed
Calling ABC Account Destructor
```

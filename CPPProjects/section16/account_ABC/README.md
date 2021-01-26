# Expected output from running `accounts.cpp`

```c++
#include <iostream>
#include "CheckingAccount.h"
#include "utils.cpp"
#include <string>

int main() {
    Checking_Account acc = Checking_Account();
    std::cout << acc << std::endl;

    Checking_Account acc1 = Checking_Account("Account 1", 1000);
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

```

```
Calling Constructor for: Unnamed
Account Name: Unnamed
Balance: 0
Interest Rate: 0

Calling Constructor for: Account 1
Account Name: Account 1
Balance: 1000
Interest Rate: 0

[ERROR] - Invalid value: -4000 is negative
You have 1000 in your account and are withdrawing 4000
You are now carrying a negative balance: -3000
Updating interest rate from: 0 to 0.02
Balance increased by: 2000. Your new balance is: -1000
You are still carrying a negative balance: -1000
Account Name: Account 1
Balance: -1000
Interest Rate: 0.02

Calling Constructor for: Account 2
Account Name: Account 2
Balance: 2000
Interest Rate: 0.05

Balance increased by: 1200. Your new balance is: 3200
Updating interest rate from: 0.05 to 0.075
Account Name: Account 2
Balance: 3200
Interest Rate: 0.075

Calling destructor for: Account 2
Calling destructor for: Account 1
Calling destructor for: Unnamed
```

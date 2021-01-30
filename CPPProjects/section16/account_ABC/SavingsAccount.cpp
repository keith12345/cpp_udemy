#include <iostream>
#include <string>
#include "SavingsAccount.h"

Savings_Account::Savings_Account(const std::string& account_name, const double& balance, const double& interest_rate, const int& withdrawals_per_month)
    : Checking_Account(account_name, balance, interest_rate), withdrawals_per_month {nullptr}, withdrawals_this_month {nullptr} {
        std::cout << "Calling Savings Account Constructor for: " << account_name << std::endl;
        this->withdrawals_per_month = new int;
        *this->withdrawals_per_month = withdrawals_per_month;
        this->withdrawals_this_month = new int;
        *this->withdrawals_this_month = 0;
    }

bool Savings_Account::withdraw(const double& amount) {
    if (*this->withdrawals_this_month < *this->withdrawals_per_month) {
        std::cout << "You have made " << *this->withdrawals_this_month << " withdrawals this month." << std::endl;
        std::cout << "You have " << (*this->withdrawals_per_month - *this->withdrawals_this_month) << " remaining withdrawals this month." << std::endl;
        *this->withdrawals_this_month += 1;
        return Checking_Account::withdraw(amount);
    } else {
        std::cout << "You have no remaining withdrawals" << std::endl;
        return false;
    }
}

void Savings_Account::print(std::ostream& os) const {
    Checking_Account::print(os);
    os << "\tYou have performed " << *this->withdrawals_this_month << " withdrawals this month" << std::endl;
    os << "\tYou have " << (*this->withdrawals_per_month - *this->withdrawals_this_month) << " remaining withdrawals this month." << std::endl;
}

Savings_Account::~Savings_Account() {
    std::cout << "Calling Savings Account Destructor for: " << this->account_name << std::endl;
    delete this->withdrawals_per_month;
    delete this->withdrawals_this_month;
}

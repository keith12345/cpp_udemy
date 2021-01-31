#include <iostream>
#include <string>
#include "CheckingAccount.h"
#include "utils.cpp"

Checking_Account::Checking_Account(const std::string& account_name, const double& balance, const double& interest_rate)
    : account_name {account_name}, balance {nullptr}, interest_rate {nullptr} {
        std::cout << "Calling Checking Account Constructor for: " << account_name << std::endl;
        this->balance = new double {balance};
        this->interest_rate = new double {interest_rate};
    }


Checking_Account::~Checking_Account() {
    std::cout << "Calling Checking Account Destructor for: " << this->account_name << std::endl;
    delete balance;
    delete interest_rate;
}

bool Checking_Account::withdraw(const double& amount) {
    if (amount > 0) {
        std::cout << "You have " << *balance << " in your account. You are withdrawing: " << amount << std::endl;
        *balance -= amount;
        if (*balance < 0) {
            std::cout << "You are now carrying a negative balance: " << *balance << std::endl;
        }
        return true;
    } else {
        std::cout << "[ERROR] Invalid value: " << amount << " is negative" << std::endl;
        return false;
    }
}

bool Checking_Account::deposit(const double& amount) {
    if (amount > 0) {
        *balance += amount;
        std::cout << "Balance increased by: " << amount << ". Your new balance is: " << *balance << std::endl;
        if (*balance < 0) {
            std::cout << "You are still carrying a negative balance: " << *balance << std::endl;
        }
        return true;
    } else {
        std::cout << "[ERROR] - Invalid value: " << amount << " is negative" << std::endl;
        return false;
    }
}

void Checking_Account::print(std::ostream& os) const {
    os << "Displaying Account: " << this->account_name << std::endl;
    os << "\tBalance: " << *this->balance << std::endl;
    os << "\tInterest Rate: " << *this->interest_rate << std::endl;
}

bool Checking_Account::update_interest_rate(const double& updated_interest_rate) {
    if (updated_interest_rate > 0) {
        std::cout << "Updating interest rate from: " << *this->interest_rate << " to: " << updated_interest_rate << std::endl;
        *this->interest_rate = updated_interest_rate;
        return true;
    } else {
        std::cout << "[ERROR] Invalid value: " << updated_interest_rate << " is negative" << std::endl;
        return false;
    }
}

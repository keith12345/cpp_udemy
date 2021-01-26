#include <iostream>
#include <ostream>
#include <string>
#include "CheckingAccount.h"

Checking_Account::Checking_Account(const std::string& account_name, const double& balance, const double& interest_rate) {
    Checking_Account(std::move(account_name), std::move(balance), std::move(interest_rate));
    }

Checking_Account::Checking_Account(std::string&& account_name, double&& balance, double&& interest_rate)
    : account_name {account_name}, balance {nullptr}, interest_rate {nullptr} {
        this->balance = new double;
        *this->balance = balance;
        this->interest_rate = new double;
        *this->interest_rate = interest_rate;
    }

Checking_Account::~Checking_Account() {
    delete balance;
    delete interest_rate;
}

bool Checking_Account::withdraw(double&& amount) {
    if (amount > 0) {
        *balance -= amount;
        if (*balance < 0) {
            std::cout << "You are now carrying a negative balance: " << *balance << std::endl;
        }
        return true;
    } else {
        std::cout << "[ERROR] Invalid value - " << amount << " is negative" << std::endl;
        return false;
    }
}

bool Checking_Account::withdraw(double& amount) {
    return Checking_Account::withdraw(std::move(amount));
}

bool Checking_Account::deposit(double&& amount) {
    if (amount > 0) {
        *balance += amount;
        if (*balance < 0) {
            std::cout << "You are still carrying a negative balance: " << *balance << std::endl;
        }
        return true;
    } else {
        std::cout << "[ERROR] - Invalid value: " << amount << " is negative" << std::endl;
        return false;
    }
}

bool Checking_Account::deposit(double& amount) {
    return Checking_Account::deposit(std::move(amount));
}

void Checking_Account::print(std::ostream& os) const {
    os << "Account Name: " << this->account_name << std::endl;
    os << "Balance: " << this->balance << std::endl;
    os << "Interest Rate: " << this->interest_rate << std::endl;
}

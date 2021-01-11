#include <iostream>
#include "Account.h"
using namespace std;


Account::Account()
    :balance {nullptr} {
        balance = new double;
        *balance = 0;
}

Account::~Account() {
    std::cout << "Deconstructing Account" << std::endl;
    delete balance;
}

Account::Account(const Account& source)
    :balance {nullptr} {
        std::cout << "Account copy constructor called" << std::endl;
        balance = new double;
        *this->balance = *source.balance;
}

Account::Account(Account&& source)
    :balance {nullptr} {
        std::cout << "Account move constructor called" << std::endl;
        this->balance = new double;
        this->balance = source.balance;
        source.balance = {nullptr};
}

Account& Account::operator=(const Account& source) {
    std::cout << "Copy assignment operator called for Account" << std::endl;
    if (this == &source) {
        return *this;
    }
    delete this->balance;
    *this->balance = *source.balance;
    return *this;
}

Account& Account::operator=(Account&& source) {
    std::cout << "Move assignment operator called for Account" << std::endl;
    if (this == &source) {
        return *this;
    }
    delete this->balance;
    this->balance = source.balance;
    source.balance = nullptr;
    return *this;
}


void Account::deposit(double& amount) {
    std::cout << "You have " << this->get_balance() << " and are depositing " << amount << std::endl;
    *this->balance += amount;
    std::cout << "Your new balance is " << *this->balance << std::endl;
}

void Account::deposit(double&& amount) {
    std::cout << "You have " << this->get_balance() << " and are depositing " << amount << std::endl;
    *this->balance += amount;
    std::cout << "Your new balance is " << *this->balance << std::endl;
}

void Account::withdraw(double& amount) {
    std::cout << "You have " << this->get_balance() << " and are withdrawing " << amount << std::endl;
    *this->balance -= amount;
    if (*this->balance < 0) {
        std::cout << "WARNING: Negative Balance" << std::endl;
    } else {
        std::cout << "Your new balance is " << *this->balance << std::endl;
    }
}

void Account::withdraw(double&& amount) {
    std::cout << "You have " << this->get_balance() << " and are withdrawing " << amount << std::endl;
    *this->balance -= amount;
    if (*this->balance < 0) {
        std::cout << "WARNING: Negative Balance" << std::endl;
    } else {
        std::cout << "Your new balance is " << *this->balance << std::endl;
    }
}

double Account::get_balance() {
    return *this->balance;
}

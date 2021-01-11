#include <iostream>
#include "Savings_Account.h"
using namespace std;

Savings_Account::Savings_Account()
    : interest_rate {nullptr} {
        interest_rate = new double;
        *this->interest_rate = 0;
    }

Savings_Account::Savings_Account(double& ir)
    : interest_rate {nullptr} {
        interest_rate = new double;
        *this->interest_rate = ir;
}

Savings_Account::Savings_Account(double&& ir)
    : interest_rate {nullptr} {
        interest_rate = new double;
        *this->interest_rate = ir;
}

Savings_Account::Savings_Account(const Savings_Account& source)
    : Account(source), interest_rate {nullptr} {
        std::cout << "copy constructor called for saings account" << std::endl;
        this->interest_rate = new double;
        *this->interest_rate = *source.interest_rate;
}

Savings_Account::Savings_Account(Savings_Account&& source)
    : Account(source), interest_rate {nullptr} {
        std::cout << "Move constructor called for saings account" << std::endl;
        this->interest_rate = new double;
        this->interest_rate = source.interest_rate;
        source.interest_rate = nullptr;
    }

Savings_Account& Savings_Account::operator=(const Savings_Account& source) {
    std::cout << "Copy assignment operator called for Savings_Account" << std::endl;
    if (this == &source) {
        return *this;
    }
    Account::operator=(source);
    *this->interest_rate = *source.interest_rate;
    return *this;
}

Savings_Account& Savings_Account::operator=(Savings_Account&& source) {
    std::cout << "Move assignment constructor called for Savings_Account" << std::endl;
    if (this == &source) {
        return *this;
    }
    Account::operator=(source);
    delete this->interest_rate;
    this->interest_rate = source.interest_rate;
    source.interest_rate = nullptr;
    return *this;
}

double Savings_Account::get_interest_rate() {
    return *this->interest_rate;
}

void Savings_Account::set_interest_rate(const double&& new_interest_rate) {
    std::cout << "Updating interest rate from: " << *this->interest_rate
        << " to: " << new_interest_rate << std::endl;
    *this->interest_rate = new_interest_rate;
}

void Savings_Account::show_interest_rate() {
    std::cout << "The interest rate on your account is " << get_interest_rate() << "%" << std::endl;
}

Savings_Account::~Savings_Account() {
    std::cout << "Deconstructing Savings Account" << std::endl;
    delete this->interest_rate;
}

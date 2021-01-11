#include <iostream>
#include "Money_Market_Account.h"
using namespace std;

Money_Market_Account::Money_Market_Account(double& ir, int& wpm)
    : Savings_Account(ir), withdraws_per_month {nullptr}, withdraws_this_month {nullptr} {
        std::cout << "l-value reference initializer called" << std::endl;
        withdraws_this_month = new int;
        withdraws_per_month = new int;
        *this->withdraws_per_month = wpm;
        *this->withdraws_this_month = 0;
}

Money_Market_Account::Money_Market_Account(double&& ir, int&& wpm)
    : Savings_Account(ir), withdraws_per_month {nullptr}, withdraws_this_month {nullptr} {
        std::cout << "r-value reference initializer called" << std::endl;
        withdraws_per_month = new int;
        *this->withdraws_per_month = wpm;
        withdraws_this_month = new int;
        *this->withdraws_this_month = 0;
}

Money_Market_Account::Money_Market_Account(const Money_Market_Account& source)
    : Savings_Account(source), withdraws_per_month {nullptr}, withdraws_this_month {nullptr} {
        std::cout << "Copy constructor called for Money Market Account" << std::endl;
        this->withdraws_per_month = new int;
        *this->withdraws_per_month = *source.withdraws_per_month;
        this->withdraws_this_month = new int;
        *this->withdraws_this_month = *source.withdraws_this_month;
    }

Money_Market_Account::Money_Market_Account(Money_Market_Account&& source)
    : Savings_Account(source), withdraws_per_month {nullptr}, withdraws_this_month {nullptr} {
        std::cout << "Move constructor used for Money Market Account" << std::endl;
        this->withdraws_per_month = new int;
        this->withdraws_per_month = source.withdraws_per_month;
        source.withdraws_per_month = nullptr;
        this->withdraws_this_month = new int;
        this->withdraws_this_month = source.withdraws_this_month;
        source.withdraws_this_month = nullptr;
    }

Money_Market_Account& Money_Market_Account::operator=(const Money_Market_Account& source) {
    std::cout << "Copy assignment operator called for Money_Market_Account" << std::endl;
    if (this == &source) {
        return *this;
    }
    Account::operator=(source);
    *this->withdraws_per_month = *source.withdraws_per_month;
    return *this;
}

Money_Market_Account& Money_Market_Account::operator=(Money_Market_Account&& source) {
    std::cout << "Move assignment operator called for Money_Market_Account" << std::endl;
    if (this == &source) {
        return *this;
    }
    Account::operator=(source);
    this->withdraws_per_month = source.withdraws_per_month;
    source.withdraws_per_month = nullptr;
    return *this;
}


void Money_Market_Account::set_withdraws_per_month(const int&& withdraws_per_month) {
    std::cout << "Updating withdraws per month from: " << *this->withdraws_per_month
        << " to: " << withdraws_per_month << std::endl;
    *this->withdraws_per_month = withdraws_per_month;
}

void Money_Market_Account::show_withdraws_per_month() {
    std::cout << "Withdraws allowed per month: " << *withdraws_per_month << std::endl;
}

Money_Market_Account::~Money_Market_Account() {
    std::cout << "Deconstructing Money Market Account" << std::endl;
    delete withdraws_this_month;
    delete withdraws_per_month;
}

void Money_Market_Account::show_account_breakdown() {
    std::cout << "Displaying account info summary: " << std::endl;
    std::cout << "\tYour balance: " << this->get_balance() << std::endl;
    std::cout << "\tYour interest rate: " << this->get_interest_rate() << std::endl;
    std::cout << "\tYou withdraws per month: " << *this->withdraws_per_month << std::endl;
}


//Money_Market_Account::Money_Market_Account(double&& ir)
    //: interest_rate {nullptr} {
        //interest_rate = new double;
        //*this->interest_rate = ir;
//}

//void Money_Market_Account::show_interest_rate() {
    //std::cout << "The interest rate on your account is " << get_interest_rate() << "%" << std::endl;
//}

//Money_Market_Account::~Money_Market_Account() {
    //delete this->interest_rate;
//}

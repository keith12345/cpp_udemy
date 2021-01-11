#pragma once
#include "Account.h"


class Savings_Account: public Account {
    private:
        double* interest_rate;
    protected:
        double get_interest_rate();
    public:
        Savings_Account();
        Savings_Account(double& interest_rate);
        Savings_Account(double&& interest_rate);
        Savings_Account(const Savings_Account& source);
        Savings_Account(Savings_Account&& source);
        Savings_Account& operator=(const Savings_Account& source);
        Savings_Account& operator=(Savings_Account&& source);
        void set_interest_rate(const double&& new_interest_rate);
        ~Savings_Account();
        void show_interest_rate();
};

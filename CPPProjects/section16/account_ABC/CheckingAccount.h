#pragma once
#include "Account.h"
#include <string>

class Checking_Account: public Account {
    private:
        std::string account_name;
        double* balance;
        double* interest_rate;
    public:
        //Checking_Account(std::string&& account_name, double&& balance, double&& interest_rate);
        Checking_Account(const std::string& account_name = "Unnamed", const double& balance = 0.0, const double& interest_rate = 0.0);
        virtual ~Checking_Account();
        virtual void print(std::ostream& os) const override;
        virtual bool withdraw(const double& amount) override;
        virtual bool deposit(const double& amount) override;
        bool update_interest_rate(const double& updated_interest_rate);
};

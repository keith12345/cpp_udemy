#pragma once
#include <iostream>
#include <string>

class Account {
        friend std::ostream& operator<<(std::ostream &os, const Account& acc);
    public:
        virtual ~Account() = 0;
        virtual void print(std::ostream& os) const = 0;
        virtual bool deposit(double& amount) = 0;
        virtual bool deposit(double&& amount) = 0;
        virtual bool withdraw(double& amount) = 0;
        virtual bool withdraw(double&& amount) = 0;
};

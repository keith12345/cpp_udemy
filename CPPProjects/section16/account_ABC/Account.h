#pragma once
#include <ostream>
#include <string>

class Account {
        friend inline std::ostream& operator<<(std::ostream &os, const Account& acc);
    public:
        virtual ~Account() {};
        virtual void print(std::ostream& os) const = 0;
        virtual bool deposit(const double& amount) = 0;
        virtual bool withdraw(const double& amount) = 0;
};

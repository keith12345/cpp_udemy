#pragma once
#include <iostream>
#include <ostream>
#include <string>

class Account {
        friend inline std::ostream& operator<<(std::ostream &os, const Account& acc);
    public:
        virtual ~Account() {
            std::cout << "Calling ABC Account Destructor" << std::endl;
        };
        //virtual ~Account() = default; // Same as above
        virtual void print(std::ostream& os) const = 0;
        virtual bool deposit(const double& amount) = 0;
        virtual bool withdraw(const double& amount) = 0;
};

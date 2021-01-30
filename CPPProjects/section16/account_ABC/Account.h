#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include "I_Printable.h"

class Account: public I_Printable {
    public:
        virtual ~Account() {
            std::cout << "Calling ABC Account Destructor" << std::endl;
        };
        //virtual ~Account() = default; // Same as above
        virtual bool deposit(const double& amount) = 0;
        virtual bool withdraw(const double& amount) = 0;
};

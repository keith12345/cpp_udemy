#include <iostream>

class I_Printable {
        friend std::ostream& operator<<(std::ostream &os, const I_Printable& obj);
    public:
        virtual void print(std::ostream& os) const = 0;
};

std::ostream& operator<<(std::ostream& os, const I_Printable& obj) {
    obj.print(os);
    return os;
}

class Account: public I_Printable {
    public:
        virtual void withdraw(double amount) {
            std::cout << "In Account::withdraw" << std::endl;
        }
        virtual void print(std::ostream& os) const override {
            os << "Account dipslay" << std::endl;
        }
        virtual ~Account() {};
};

class Checking_Account: public Account {
    public:
        virtual void withdraw(double amount) override {
            std::cout << "In Checking_Account::withdraw" << std::endl;
        }
        virtual void print(std::ostream& os) const override {
            os << "Checking_Account dipslay" << std::endl;
        }
        virtual ~Checking_Account() {};
};

int main() {
    Account* acc = new Account();
    std::cout << *acc << std::endl;
    Account* acc2 = new Checking_Account();
    std::cout << *acc2 << std::endl;
    I_Printable* acc3 = new Checking_Account();
    std::cout << *acc3 << std::endl;
    //acc3->withdraw(100.0); // Will not work
    acc2->withdraw(100.0);
}

#pragma once


class Account {
    private:
        double* balance;
    public:
        double get_balance();
        void deposit(double& amount);
        void deposit(double&& amount);
        void withdraw(double& amount);
        void withdraw(double&& amount);
        Account& operator=(const Account& source);
        Account& operator=(Account&& source);
        Account();
        Account(const Account& source);
        Account(Account&& source);
        ~Account();
};

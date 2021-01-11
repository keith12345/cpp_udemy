#pragma once
#include "Savings_Account.h"


class Money_Market_Account: public Savings_Account {
    private:
        int* withdraws_per_month;
        int* withdraws_this_month;
    public:
        Money_Market_Account(double& interest_rate, int& withdraws_per_month);
        Money_Market_Account(double&& interest_rate, int&& withdraws_per_month);
        Money_Market_Account(const Money_Market_Account& source);
        Money_Market_Account(Money_Market_Account&& source);
        Money_Market_Account& operator=(const Money_Market_Account& source);
        Money_Market_Account& operator=(Money_Market_Account&& source);
        ~Money_Market_Account();
        void set_withdraws_per_month(const int&& withdraws_per_month);
        void show_withdraws_this_month();
        void show_withdraws_per_month();
        void show_account_breakdown();
};

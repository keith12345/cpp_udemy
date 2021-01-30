#include <ostream>
#include <string>
#include "CheckingAccount.h"

class Savings_Account: public Checking_Account {
        friend inline std::ostream& operator<<(std::ostream &os, const Account& acc);
    public:
        int* withdrawals_per_month;
        int* withdrawals_this_month;
        Savings_Account(const std::string& account_name = "Unnamed",
                const double& balance = 0,
                const double& interest_rate = 0.2,
                const int& withdrawals_per_month = 1);
        virtual ~Savings_Account() override;
        virtual void print(std::ostream& os) const override;
        virtual bool withdraw(const double& amount) override;
};

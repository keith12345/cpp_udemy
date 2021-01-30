#include <iostream>
#include <vector>
#include "Account.h"

std::ostream& operator<<(std::ostream& os, const I_Printable& printable) {
    printable.print(os);
    return os;
}

inline void display_accounts(const std::vector<Account*>& accs) {
    std::cout << "Displaying Accounts:\n" << std::endl;
    for (const Account* acc: accs) {
        std::cout << *acc << std::endl;
    }
}

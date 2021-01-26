#include <iostream>
#include "Account.h"

std::ostream& operator<<(std::ostream& os, const Account& acc) {
    acc.print(os);
    return os;
}

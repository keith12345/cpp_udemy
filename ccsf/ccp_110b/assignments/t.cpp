#include <iostream>
#include <string>
#include <limits>


enum Person { BILL, JOHN, CLAIRE, BOB };


int main() {
    Person p;
    p = BOB;
    //p++;
    BILL > BOB;
    p = static_cast<Person>(0);
    p = static_cast<Person>(12);
    int x = {BILL};
    Person pp = static_cast<Person>(40000000000);
    std::cout << (40000000000 - 1345294336) << std::endl;
    std::cout << pp << std::endl;
}

#include <ios>
#include <iostream>
#include <limits>
#include <cstring>
#include <iomanip>


//enum Person { BILL, JOHN, CLAIRE, BOB };
int test;
struct T {
    struct tt;
};


int main() {
    std::cout << std::boolalpha << std::endl;
    std::cout << std::isalpha('a') << std::endl;
    char c = '%';
    bool b = std::isalpha(c);
    std::cout << b << std::endl;
    c = std::toupper('a');
    std::cout << c << std::endl;
    char s[] = "ooo test ooo";
    char s2[] = "test";
    bool bb = std::strcmp(s, s2);
    std::cout << bb << std::endl;
}

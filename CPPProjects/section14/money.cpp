#include <iostream>
#include "Money.h"

using namespace std;

int main() {
    Money m1 {125};
    Money m2 {12, 17};
    std::cout << (m1.get_dollars()*100 + m1.get_cents()) << std::endl;
    Money sum = m1 + m2;
    std::cout << (sum.get_dollars()*100 + sum.get_cents()) << std::endl;
    std::cout << sum.get_dollars() << std::endl;
    std::cout << sum.get_cents() << std::endl;
    std::cout << m2.get_cents() << std::endl;
    ++m2;
    std::cout << m2.get_cents() << std::endl;
    m2++;
    std::cout << m2.get_cents() << std::endl;
    std::cout << m2 << std::endl;
    m2 *= 6;
    std::cout << m2 << std::endl;
}

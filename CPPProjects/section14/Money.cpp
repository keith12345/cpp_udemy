#include "Money.h"

Money::Money(int dollars, int cents) : dollars{dollars}, cents{cents} {}

Money::Money(int total) : dollars {total/100}, cents{total%100}  {}

Money operator+(const Money& m1, const Money& m2) {
    return Money(m1.dollars+m2.dollars, m1.cents+m2.cents);
}

std::ostream& operator<<(std::ostream& os, const Money& m) {
    os << "dollars: " << m.dollars << " cents: " << m.cents;
    return os;
}

Money& Money::operator++() {
    this->cents += 1;
    return *this;
}

Money Money::operator++(int) {
    Money temp (*this);
    operator++();
    return temp;
}

Money& Money::operator*=(int& n) {
    int* temp_cents = new int;
    *temp_cents = this->cents * n;
    this->cents = *temp_cents % 100;
    this->dollars *= n;
    this->dollars += *temp_cents / 100;
    std::cout << *this << std::endl;
    delete temp_cents;
    return *this;
}


Money& Money::operator*=(int&& n) {
    int* temp_cents = new int;
    *temp_cents = this->cents * n;
    this->cents = *temp_cents % 100;
    this->dollars *= n;
    this->dollars += *temp_cents / 100;
    std::cout << *this << std::endl;
    delete temp_cents;
    return *this;
}

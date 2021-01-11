#ifndef _MONEY_MONEY_H
#define _MONEY_MONEY_H

#include <iostream>
#include <ostream>

class Money {
    int dollars;
    int cents;
public:
    Money(int dollars, int cents);
    Money(int total);
    int get_dollars() const {return dollars;}
    int get_cents() const {return cents; }


    Money& operator++();
    Money operator++(int);
    Money& operator*=(int& n);
    Money& operator*=(int&& n);
    friend Money operator+(const Money& m1, const Money& m2);
    friend std::ostream& operator<<(std::ostream& os, const Money& m);
};


#endif //_MONEY_MONEY_H

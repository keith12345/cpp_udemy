/*

Invariants:
int denominator must be greater than 0

void Fraction::simplify();

pre: Called within the constructor of a Fraction object.
Denominator must be greater than 0.
post: Modifies numerator and denominator in place, converts to lowest terms.

int reduce(int& a, int& b);

pre: Finds the great common divisor of two numbers.
post: Returns the greatest common divisor of two numbers.
Allows for early termination for numbers where the greatest common divisor
is one of the two numbers.

 */


#include <iostream>
#include <cassert>
#include "Fraction.h"


// Helper func prototypes


void reduce(int& a, int& b);
void reducePowersOfTwo(int& numerator, int& denominator);
void reduceOtherPowers(int& numerator, int& denominator);


// Member methods


Fraction::Fraction() : Fraction(0, 1) {}






Fraction::Fraction(const int& numerator, const int& denominator) {
    assert(denominator != 0);
    this->numerator = numerator;
    this->denominator = denominator;
    simplify();
}






void Fraction::print() const {
    std::cout << this->numerator
              << "/"
              << this->denominator;
}






Fraction Fraction::multipliedBy(const Fraction& f) const {
    return Fraction(
        this->numerator * f.numerator,
        this->denominator * f.denominator
    );
}






Fraction Fraction::dividedBy(const Fraction& f) const {
    return Fraction(
        this->numerator * f.denominator,
        this->denominator * f.numerator
    );
}






Fraction Fraction::addedTo(const Fraction& f) const {
    return Fraction(
        this->numerator * f.denominator + this->denominator * f.numerator,
        this->denominator * f.denominator
    );
}






Fraction Fraction::subtract(const Fraction& f) const {
    return Fraction(
        this->numerator * f.denominator - this->denominator * f.numerator,
        this->denominator * f.denominator
    );
}






bool Fraction::isEqualTo(const Fraction& f) const {
    return (this->numerator * f.denominator == this->denominator * f.numerator);
}






/*
 * pre: Called within the constructor of a Fraction object.
 * Denominator must be greater than 0.
 * post: Modifies numerator and denominator in place, converts to lowest terms.
 */
void Fraction::simplify() {
    reducePowersOfTwo(numerator, denominator);
    reduceOtherPowers(numerator, denominator);
}






// Helper funcs


void reducePowersOfTwo(int& numerator, int& denominator) {
    while ((numerator % 2 == 0) && (denominator % 2 == 0)) {
        numerator >>= 1;
        denominator >>= 1;
    }
}


void reduceOtherPowers(int& numerator, int& denominator) {
    for (int i = 3; i <= std::min(numerator, denominator); i++) {
        while (numerator % i == 0 && denominator % i == 0) {
            numerator /= i;
            denominator /= i;
        }
    }
}

/*

Invariants:
int denominator must be greater than 0

void Fraction::simplify();

pre: Called within the constructor of a Fraction object.
Denominator must be greater than 0.
post: Modifies numerator and denominator in place, converts to lowest terms.

int getGreatestCommonDivisor(const int& a, const int& b);

pre: Finds the great common divisor of two numbers.
post: Returns the greatest common divisor of two numbers.
Allows for early termination for numbers where the greatest common divisor
is one of the two numbers.

 */


#include <iostream>
#include <cassert>
#include "Fraction.h"


// Helper func prototypes


int getGreatestCommonDivisor(const int& a, const int& b);


// Member methods


Fraction::Fraction() : Fraction(0, 1) {}






Fraction::Fraction(const int& numerator, const int& denominator) {
    this->numerator = numerator;
    assert(denominator != 0);
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
    int greatestCommonDivisor = 1;
    if (numerator >= 2 && denominator >= 2) {
        greatestCommonDivisor = getGreatestCommonDivisor(numerator, denominator);
    }
    this->numerator /= greatestCommonDivisor;
    assert(denominator != 0);
    this->denominator /= greatestCommonDivisor;
}






// Helper funcs


/*
 * Given two numbers, finds the greatest common divisor.
 * Allows for early termination for numbers where the greatest common divisor
 * is one of the two numbers.
 */
int getGreatestCommonDivisor(const int& a, const int& b) {
    int minNumber = std::min(a, b);
    int maxNumber = std::max(a, b);
    int greatestCommonDivisor = 1;

    if (maxNumber % minNumber == 0) {
        greatestCommonDivisor = minNumber;
    } else {
        int divisorThreshold = minNumber / 2;
        for (int i = 1; i <= divisorThreshold; i++) {
            if (a % i == 0  && b % i == 0) {
                greatestCommonDivisor = i;
            }
        }
    }
    return greatestCommonDivisor;
}
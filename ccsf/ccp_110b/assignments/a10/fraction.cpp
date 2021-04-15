/*

Invariants:
int denominator must not be equal to zero.
Default values:
    int numerator = 0
    int denominator = 1

void Fraction::simplify();

pre: Called within the constructor of a Fraction object.
Denominator must be greater than 0.
post: Modifies numerator and denominator in place, converts to lowest terms.
Automatically sets numerator to negative if either number is negative.
Automatically sets denominator to 1 if numerator is 0, otherwise reduces to lowest terms.

void reducePowersOfTwo(int& numerator, int& denominator);

pre: Called within the simplify function which is called within the constructor of a
the Fraction object.
post: Uses bit shifting for quick division for multiples of 2 (I just wanted an excuse
to use bitshift). Divides by 2 until either number is not divisible by 2. Modifies the
numbers in place.

void reduceOtherPowers(int& numerator, int& denominator);

pre: Called within the simplify function which is called within the constructor of a
the Fraction object.
post: Divides both numbers by incrementing number n (n >= 3) while both numbers are divisible
by n. n increments until it is equal to the smaller of the two numbers. Modifies the numbers
in place.

 */


#include <iostream>
#include <cassert>
#include "fraction.h"
using namespace std;

namespace cs_fraction {






// Helper func prototypes


void reducePowersOfTwo(int& numerator, int& denominator);
void reduceOtherPowers(int& numerator, int& denominator);


// Member methods





Fraction::Fraction(const int& numerator, const int& denominator) {
    assert(denominator != 0);
    this->numerator = numerator;
    this->denominator = denominator;
    simplify();
}






int Fraction::getNumerator() const {
    return this->numerator;
}






int Fraction::getDenominator() const {
    return this->denominator;
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






// Operation methods

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






// Overloaded mathetical operators

Fraction operator*(const Fraction& leftObj, const Fraction& rightObj) {
    return leftObj.multipliedBy(rightObj);
}






Fraction operator/(const Fraction& leftObj, const Fraction& rightObj) {
    return leftObj.dividedBy(rightObj);
}






Fraction operator+(const Fraction& leftObj, const Fraction& rightObj) {
    return leftObj.addedTo(rightObj);
}






Fraction operator-(const Fraction& leftObj, const Fraction& rightObj) {
    return leftObj.subtract(rightObj);
}






// Overloaded compound operators

Fraction& Fraction::operator*=(const Fraction& f) {
    *this = *this * f;
    return *this;
}






Fraction& Fraction::operator/=(const Fraction& f) {
    *this = *this / f;
    return *this;
}






Fraction& Fraction::operator+=(const Fraction& f) {
    *this = *this + f;
    return *this;
}






Fraction& Fraction::operator-=(const Fraction& f) {
    *this = *this - f;
    return *this;
}






// Overloaded comparison operators

bool operator>(const Fraction& leftObj, const Fraction& rightObj) {
    return (
        leftObj.numerator * rightObj.denominator
        > rightObj.numerator * leftObj.denominator
    );
}






bool operator<(const Fraction& leftObj, const Fraction& rightObj) {
    return (
        leftObj.numerator * rightObj.denominator
        < rightObj.numerator * leftObj.denominator
    );
}






bool operator>=(const Fraction& leftObj, const Fraction& rightObj) {
    return (
        leftObj.numerator * rightObj.denominator
        >= rightObj.numerator * leftObj.denominator
    );
}






bool operator<=(const Fraction& leftObj, const Fraction& rightObj) {
    return (
        leftObj.numerator * rightObj.denominator
        <= rightObj.numerator * leftObj.denominator
    );
}






bool operator==(const Fraction& leftObj, const Fraction& rightObj) {
    return rightObj.isEqualTo(leftObj);
}






bool operator!=(const Fraction& leftObj, const Fraction& rightObj) {
    return !rightObj.isEqualTo(leftObj);
}






// Incrementers/Decrementers

Fraction& Fraction::operator++() {
    this->numerator += this->denominator;
    return *this;
}






Fraction Fraction::operator++(int) {
    Fraction temp = Fraction(*this);
    this->numerator += this->denominator;
    return temp;
}






Fraction& Fraction::operator--() {
    this->numerator -= this->denominator;
    return *this;
}






Fraction Fraction::operator--(int) {
    Fraction temp = Fraction(*this);
    this->numerator -= this->denominator;
    return temp;
}






// Overloaded insertion and extraction operators

std::ostream& operator<<(std::ostream& os, const Fraction& obj) {
    if (obj.numerator % obj.denominator == 0) {
        os << (obj.numerator / obj.denominator);
    } else {
        int absNum = std::abs(obj.numerator);
        int absDen = std::abs(obj.denominator);
        if (std::min(obj.numerator, obj.denominator) < 0) {
            os << "-";
        }
        if (absNum > absDen) {
            os << absNum / absDen
               << "+";
        }
        os << absNum % absDen
           << "/"
           << absDen;
    }
    return os;
}






std::istream& operator>>(std::istream& is, Fraction& obj) {
    int numerator;
    is >> numerator;

    int wholeNumber = 0;
    int denominator;
    if (is.peek() == '+') {
        wholeNumber = numerator;
        is >> numerator;
    }

    if (is.peek() == '/') {
        is.ignore();
        is >> denominator;
    } else {
        denominator = 1;
    }

    if (wholeNumber < 0) {
        numerator = (wholeNumber * denominator - numerator);
    } else {
        numerator = (wholeNumber * denominator + numerator);
    }

    obj.numerator = numerator;
    obj.denominator = denominator;
    obj.simplify();
    return is;
}






// utils

/*
 * pre: Called within the constructor of a Fraction object.
 * Denominator must not be equal to 0.
 * post: Modifies numerator and denominator in place, converts to lowest terms.
 */
void Fraction::simplify() {
    if (denominator < 0) {
        numerator *= -1;
        denominator *= -1;
    }
    if (numerator == 0) {
        denominator = 1;
    } else {
        reducePowersOfTwo(numerator, denominator);
        reduceOtherPowers(numerator, denominator);
    }
}






// Helper funcs

void reducePowersOfTwo(int& numerator, int& denominator) {
    while ((numerator % 2 == 0) && (denominator % 2 == 0)) {
        numerator >>= 1;
        denominator >>= 1;
    }
}






void reduceOtherPowers(int& numerator, int& denominator) {
    for (int i = 3; i <= std::abs(std::min(numerator, denominator)); i++) {
        while (numerator % i == 0 && denominator % i == 0) {
            numerator /= i;
            denominator /= i;
        }
    }
}






}

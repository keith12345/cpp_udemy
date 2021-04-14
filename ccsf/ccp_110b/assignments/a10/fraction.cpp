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
#include "fraction.h"
using namespace std;
using namespace cs_fraction;


// Helper func prototypes


void reduce(int& a, int& b);
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






Fraction Fraction::dividedBy(const Fraction& f) const {
    return Fraction(
        f.numerator * this->denominator,
        f.denominator * this->numerator
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
        f.numerator * this->denominator - f.denominator * this->numerator,
        f.denominator * this->denominator
    );
}






bool Fraction::isEqualTo(const Fraction& f) const {
    return (this->numerator * f.denominator == this->denominator * f.numerator);
}


namespace cs_fraction {

// Overloaded mathetical operators

Fraction operator*(const Fraction& leftObj, const Fraction& rightObj) {
    return rightObj.multipliedBy(leftObj);
}

Fraction operator/(const Fraction& leftObj, const Fraction& rightObj) {
    return rightObj.dividedBy(leftObj);
}

Fraction operator+(const Fraction& leftObj, const Fraction& rightObj) {
    return rightObj.addedTo(leftObj);
}

Fraction operator-(const Fraction& leftObj, const Fraction& rightObj) {
    return rightObj.subtract(leftObj);
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
        static_cast<double>(leftObj.numerator)/leftObj.denominator
        > static_cast<double>(rightObj.numerator)/rightObj.denominator
    );
}

bool operator<(const Fraction& leftObj, const Fraction& rightObj) {
    return (
        static_cast<double>(leftObj.numerator)/leftObj.denominator
        < static_cast<double>(rightObj.numerator)/rightObj.denominator
    );
}

bool operator>=(const Fraction& leftObj, const Fraction& rightObj) {
    return (
        static_cast<double>(leftObj.numerator)/leftObj.denominator
        >= static_cast<double>(rightObj.numerator)/rightObj.denominator
    );
}

bool operator<=(const Fraction& leftObj, const Fraction& rightObj) {
    return (
        static_cast<double>(leftObj.numerator)/leftObj.denominator
        <= static_cast<double>(rightObj.numerator)/rightObj.denominator
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
    bool isNegative = false;
    if (is.peek() == '-') {
        isNegative = true;
        is.ignore();
    }
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

    numerator = (wholeNumber * denominator + numerator);
    if (isNegative)
        numerator = -numerator;
    obj.numerator = numerator;
    obj.denominator = denominator;
    obj.simplify();
    return is;
}

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
    for (int i = 3; i <= std::abs(std::min(numerator, denominator)); i++) {
        while (numerator % i == 0 && denominator % i == 0) {
            numerator /= i;
            denominator /= i;
        }
    }
}

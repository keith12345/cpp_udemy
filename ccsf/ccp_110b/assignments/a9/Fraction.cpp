#include <iostream>
#include <cassert>
#include "Fraction.h"






// Helper func prototypes


int getGreatestCommonDivisor(const int& a, const int& b);






// Member methods


/*
 * No-args constructor calls the 2-args constructor with arguments numerator=0
 * and denominator=1.
 * Denominator set to 1 to avoid division by zero.
 */
Fraction::Fraction() : Fraction(0, 1) {}






/*
 * 2-args constructor that automatically reduces all Fraction objects upon creation
 * but calling the simplify() method which divides both numbers by the greatest common divisor
 */
Fraction::Fraction(const int& numerator, const int& denominator) {
    this->numerator = numerator;
    assert(denominator != 0);
    this->denominator = denominator;
    simplify();
}






/*
 * Prints a representation of the fraction
 */
void Fraction::print() const {
    std::cout << this->numerator
              << "/"
              << this->denominator;
}






/*
 * Multiplies the Fraction object by a passed Fraction object.
 * Returns a new reduced fraction.
 */
Fraction Fraction::multipliedBy(const Fraction& f) const {
    return Fraction(
        this->numerator * f.numerator,
        this->denominator * f.denominator
    );
}






/*
 * Divides the Fraction object by a passed Fraction object.
 * Returns a new reduced fraction.
 */
Fraction Fraction::dividedBy(const Fraction& f) const {
    return Fraction(
        this->numerator * f.denominator,
        this->denominator * f.numerator
    );
}






/*
 * Adds the Fraction object to a passed Fraction object.
 * Returns a new reduced fraction.
 */
Fraction Fraction::addedTo(const Fraction& f) const {
    return Fraction(
        this->numerator * f.denominator + this->denominator * f.numerator,
        this->denominator * f.denominator
    );
}






/*
 * Subtracts the Fraction object from a passed Fraction object.
 * Returns a new reduced fraction.
 */
Fraction Fraction::subtract(const Fraction& f) const {
    return Fraction(
        this->numerator * f.denominator - this->denominator * f.numerator,
        this->denominator * f.denominator
    );
}






/*
 * Checks whether two fractions are equal.
 * Fractions to not need to be reduced to determine equality.
 */
bool Fraction::isEqualTo(const Fraction& f) const {
    return (this->numerator * f.denominator == this->denominator * f.numerator);
}






/*
 * Simplifies a fraction in-place by dividing both the numerator and the denominator
 * by the greatest common divisor.
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

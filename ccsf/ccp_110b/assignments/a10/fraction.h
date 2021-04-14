/*
object storing a Fraction as a numerator and denominator.
All Fraction objects are automatically stored in lowest terms.
Standard mathetical operations are available as methods to be called off of one Fraction
object and passing another Fraction object.

Public attributes:
int numerator - the number above the line in a common fraction showing how many of the
parts indicated by the denominator are taken, for example, 2 in 2/3.
int denominator - the number below the line in a common fraction; a divisor, for example, 3 in 2/3.

Public Members:

void print() const;

pre: Fraction is comprised of two integers, a numerator and a denominator
post: Renders the fraction in the format <numerator>/<denominator>.

Fraction multipliedBy(const Fraction& f) const;

pre: Method called off of one fraction object, takes another fraction object as its argument.
Multiplies the Fraction object by a passed Fraction object.
post: Returns a new reduced fraction in lowest terms.

Fraction dividedBy(const Fraction& f) const;

pre: Method called off of one fraction object, takes another fraction object as its argument.
Divides the Fraction object by a passed Fraction object.
post: Returns a new Fraction object in lowest terms.

Fraction addedTo(const Fraction& f) const;

pre: Method called off of one fraction object, takes another fraction object as its argument.
Adds the Fraction object to a passed Fraction object.
post: Returns a new Fraction object in lowest terms.

Fraction subtract(const Fraction& f) const;

pre: Method called off of one fraction object, takes another fraction object as its argument.
Subtracts the Fraction object from a passed Fraction object.
post: Returns a new Fraction object in lowest terms.

bool isEqualTo(const Fraction& f) const;

pre: Method called off of one fraction object, takes another fraction object as its argument.
Checks whether two fractions are equal. Fraction do not need to be reduced to determine equality.
post: Returns a boolean indicating whether the two Fraction objects are equal in value.

Fraction();

pre: No-args constructor calls the 2-args constructor with arguments numerator=0 and denominator=1
Denominator set to 1 to avoid division by zero.
post: Creates new Fraction object with numerator of 0 and denominator of 1.

Fraction(const int& numerator, const int& denominator);

pre: 2-args constructor that automatically reduces all Fraction objects upon creation but calling
the simplify() method which divides both numbers by the greatest common divisor
post: Creates new Fraction object in a lowest terms of the specified numerator and denominator.

*/

#include <ostream>
#include <istream>



#ifndef FRACTION_H
#define FRACTION_H




namespace cs_fraction {



/*
 * Declaration of Fraction object
 */
class Fraction {
    private:
        int numerator;
        int denominator;
        void simplify();

    public:
        Fraction(const int& numerator = 0, const int& denominator = 1);

        void print() const;
        int getNumerator() const;
        int getDenominator() const;

        // Mathemtical expression methods
        Fraction multipliedBy(const Fraction& f) const;
        Fraction dividedBy(const Fraction& f) const;
        Fraction addedTo(const Fraction& f) const;
        Fraction subtract(const Fraction& f) const;
        bool isEqualTo(const Fraction& f) const;

        // Operators

        // Mathemtical expression operators
        friend Fraction operator*(const Fraction& leftObj, const Fraction& rightObj);
        friend Fraction operator/(const Fraction& leftObj, const Fraction& rightObj);
        friend Fraction operator+(const Fraction& leftObj, const Fraction& rightObj);
        friend Fraction operator-(const Fraction& leftObj, const Fraction& rightObj);

        // Compound mathematical operators
        Fraction& operator*=(const Fraction& f);
        Fraction& operator/=(const Fraction& f);
        Fraction& operator+=(const Fraction& f);
        Fraction& operator-=(const Fraction& f);

        // Comparison operators
        friend bool operator>(const Fraction& leftObj, const Fraction& rightObj);
        friend bool operator<(const Fraction& leftObj, const Fraction& rightObj);
        friend bool operator<=(const Fraction& leftObj, const Fraction& rightObj);
        friend bool operator>=(const Fraction& leftObj, const Fraction& rightObj);
        friend bool operator==(const Fraction& leftObj, const Fraction& rightOb);
        friend bool operator!=(const Fraction& leftObj, const Fraction& rightOb);

        //
        Fraction& operator++();
        Fraction operator++(int);
        Fraction& operator--();
        Fraction operator--(int);

        friend std::ostream& operator<<(std::ostream& os, const Fraction& obj);
        friend std::istream& operator>>(std::istream& is, Fraction& obj);
};

}

#endif

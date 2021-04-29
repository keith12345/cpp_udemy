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

Fraction(const int& numerator = 0, const int& denominator = 1);

pre: 2-args constructor that automatically reduces all Fraction objects upon creation but calling
the simplify() method which divides both numbers by the greatest common divisor.
Contains default parameters for numerator (0) and denominator (1).
Handles single integers which are set to the numerator. In such cases, the denominator is
set to 0.
post: Creates new Fraction object in a lowest terms of the specified numerator and denominator.

void print() const;

pre: Fraction is comprised of two integers, a numerator and a denominator
post: Renders the fraction in the format <numerator>/<denominator>.

int getNumerator() const;

pre: Called off of instantiated Fraction object.
post: Returns private member `numerator` from Fraction object.

int getDenominator() const;

pre: Called off of instantiated Fraction object.
post: Returns private member `denominator` from Fraction object.

//// Mathemtical expression methods ////

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

//// Logical Comparison Methods ////

bool isEqualTo(const Fraction& f) const;

pre: Method called off of one fraction object, takes another fraction object as its argument.
Checks whether two fractions are equal. Fraction do not need to be reduced to determine equality.
post: Returns a boolean indicating whether the two Fraction objects are equal in value.

//////// Operators ////////

//// Mathemetical expression operators ////

// Mathemtical expression operators

friend Fraction operator*(const Fraction& leftObj, const Fraction& rightObj);

pre: Friend method for multiplication. Automatically promotes left/right int to Fraction object.
post: Returns a new Fraction obejct in lowest terms.

friend Fraction operator/(const Fraction& leftObj, const Fraction& rightObj);

pre: Friend method for division. Automatically promotes left/right int to Fraction object.
post: Returns a new Fraction obejct in lowest terms.

friend Fraction operator+(const Fraction& leftObj, const Fraction& rightObj);

pre: Friend method for addition. Automatically promotes left/right int to Fraction object.
post: Returns a new Fraction obejct in lowest terms.

friend Fraction operator-(const Fraction& leftObj, const Fraction& rightObj);

pre: Friend method for subtraction. Automatically promotes left/right int to Fraction object.
post: Returns a new Fraction obejct in lowest terms.

// Compound mathematical operators

Fraction& operator*=(const Fraction& f);

pre: Requires left operand to be a Fraction Object. Will automatically promote left operand
to fraction object if int.
Uses * operator which is an alias for the multipliedBy method.
post: Modifies left operand in place returning a Fraction object.

Fraction& operator/=(const Fraction& f);

pre: Requires left operand to be a Fraction Object. Will automatically promote left operand
to fraction object if int.
Uses / operator which is an alias for the dividedBy method.
post: Modifies left operand in place returning a Fraction object.

Fraction& operator+=(const Fraction& f);

pre: Requires left operand to be a Fraction Object. Will automatically promote left operand
to fraction object if int.
Uses + operator which is an alias for the addedTo method.
post: Modifies left operand in place returning a Fraction object.

Fraction& operator-=(const Fraction& f);

pre: Requires left operand to be a Fraction Object. Will automatically promote left operand
to fraction object if int.
Uses - operator which is an alias for the subtract method.
post: Modifies left operand in place returning a Fraction object.


// Comparison operators

friend bool operator>(const Fraction& leftObj, const Fraction& rightObj);

pre: Friend method for greater than comparision.
Automatically promotes left/right int to Fraction object.
post: Returns bool indicating whether left operand is greater than right operand.

friend bool operator<(const Fraction& leftObj, const Fraction& rightObj);

pre: Friend method for less than comparision.
Automatically promotes left/right int to Fraction object.
post: Returns bool indicating whether left operand is less than right operand.

friend bool operator<=(const Fraction& leftObj, const Fraction& rightObj);

pre: Friend method for less than or equal to comparision.
Automatically promotes left/right int to Fraction object.
post: Returns bool indicating whether left operand is less than or equal to right operand.

friend bool operator>=(const Fraction& leftObj, const Fraction& rightObj);

pre: Friend method for greater than or equal to comparision.
Automatically promotes left/right int to Fraction object.
post: Returns bool indicating whether left operand is greater than or equal to right operand.

friend bool operator==(const Fraction& leftObj, const Fraction& rightOb);

pre: Friend method for equal to comparision.
Automatically promotes left/right int to Fraction object.
post: Returns bool indicating whether left operand is equal to right operand.

friend bool operator!=(const Fraction& leftObj, const Fraction& rightOb);

pre: Friend method for equal to comparision.
Automatically promotes left/right int to Fraction object.
post: Returns bool indicating whether left operand is NOT equal to right operand.

// Increment and Decrement Operators

Fraction& operator++();

pre: Called off of instantiated Fraction object.
post: Increments the Fraction object (not just the numerator) by 1. Modifies in-place.

Fraction operator++(int);

pre: Called off of instantiated Fraction object.
post: Increments the Fraction object (not just the numerator) by 1.
Modifies the Fraction object in-place but returns the pre-incremented value.

Fraction& operator--();

pre: Called off of instantiated Fraction object.
post: Decrements the Fraction object (not just the numerator) by 1. Modifies in-place.

Fraction operator--(int);

pre: Called off of instantiated Fraction object.
post: Decrements the Fraction object (not just the numerator) by 1.
Modifies the Fraction object in-place but returns the pre-decremented value.

//// Insertion and Extraction Operators ////

friend std::ostream& operator<<(std::ostream& os, const Fraction& obj);

pre: Friend method for printing Fraction object contents using insertion operator.
Left operand must be ostream and right operand must be instantiated Fraction object.
post: Overloads ostream object and returns ostream reference displaying the Fraction
object contents.
Renders the fraction in the format <numerator>/<denominator>.

friend std::istream& operator>>(std::istream& is, Fraction& obj);

pre: Friend method of extracting Fraction objects from user inputs or files
using istream.
Left operand must be an istream and right operand must be a declared fraction object.
Does not perform any type checking.
post: Modifies Fraction object in place and converts to lowest terms.

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

        // Logical expression methods
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

        // Increment and Decrement Operators
        Fraction& operator++();
        Fraction operator++(int);
        Fraction& operator--();
        Fraction operator--(int);

        // Insertion and Extraction Operators
        friend std::ostream& operator<<(std::ostream& os, const Fraction& obj);
        friend std::istream& operator>>(std::istream& is, Fraction& obj);
};

}

#endif


/*

----- Testing basic Fraction creation & printing
(Fractions should be in reduced form, and as mixed numbers.)
Fraction [0] = 1/2
Fraction [1] = -5/7
Fraction [2] = 10
Fraction [3] = -4
Fraction [4] = 0
Fraction [5] = 4+2/3
Fraction [6] = 0

----- Now reading Fractions from file
Read Fraction = 1/3
Read Fraction = 1/2
Read Fraction = 3/4
Read Fraction = -4/5
Read Fraction = 6
Read Fraction = 5
Read Fraction = -8
Read Fraction = 1+2/5
Read Fraction = -16+2/3
Read Fraction = 1+1/4
Read Fraction = 2
Read Fraction = -4+1/4
Read Fraction = -10+5/6

----- Testing relational operators between Fractions
Comparing 1/2 to -1/2
	Is left < right? false
	Is left <= right? false
	Is left > right? true
	Is left >= right? true
	Does left == right? false
	Does left != right ? true
Comparing -1/2 to 1/2
	Is left < right? true
	Is left <= right? true
	Is left > right? false
	Is left >= right? false
	Does left == right? false
	Does left != right ? true
Comparing 1/2 to 1/10
	Is left < right? false
	Is left <= right? false
	Is left > right? true
	Is left >= right? true
	Does left == right? false
	Does left != right ? true
Comparing 1/10 to 0
	Is left < right? false
	Is left <= right? false
	Is left > right? true
	Is left >= right? true
	Does left == right? false
	Does left != right ? true
Comparing 0 to 0
	Is left < right? false
	Is left <= right? true
	Is left > right? false
	Is left >= right? true
	Does left == right? true
	Does left != right ? false

----- Testing relations between Fractions and integers
Comparing -1/2 to 2
	Is left < right? true
	Is left <= right? true
	Is left > right? false
	Is left >= right? false
	Does left == right? false
	Does left != right ? true
Comparing -3 to 1/4
	Is left < right? true
	Is left <= right? true
	Is left > right? false
	Is left >= right? false
	Does left == right? false
	Does left != right ? true

----- Testing binary arithmetic between Fractions
1/6 + 1/3 = 1/2
1/6 - 1/3 = -1/6
1/6 * 1/3 = 1/18
1/6 / 1/3 = 1/2
1/3 + -2/3 = -1/3
1/3 - -2/3 = 1
1/3 * -2/3 = -2/9
1/3 / -2/3 = -1/2
-2/3 + 5 = 4+1/3
-2/3 - 5 = -5+2/3
-2/3 * 5 = -3+1/3
-2/3 / 5 = -2/15
5 + -1+1/3 = 3+2/3
5 - -1+1/3 = 6+1/3
5 * -1+1/3 = -6+2/3
5 / -1+1/3 = -3+3/4

----- Testing arithmetic between Fractions and integers
-1/2 + 4 = 3+1/2
-1/2 - 4 = -4+1/2
-1/2 * 4 = -2
-1/2 / 4 = -1/8
3 + -1/2 = 2+1/2
3 - -1/2 = 3+1/2
3 * -1/2 = -1+1/2
3 / -1/2 = -6

----- Testing shorthand arithmetic assignment on Fractions
1/6 += 4 = 4+1/6
4+1/6 -= 4 = 1/6
1/6 *= 4 = 2/3
2/3 /= 4 = 1/6
4 += -1/2 = 3+1/2
3+1/2 -= -1/2 = 4
4 *= -1/2 = -2
-2 /= -1/2 = 4
-1/2 += 5 = 4+1/2
4+1/2 -= 5 = -1/2
-1/2 *= 5 = -2+1/2
-2+1/2 /= 5 = -1/2

----- Testing shorthand arithmetic assignment using integers
-1/3 += 3 = 2+2/3
2+2/3 -= 3 = -1/3
-1/3 *= 3 = -1
-1 /= 3 = -1/3

----- Testing increment/decrement prefix and postfix
Now g = -1/3
g++ = -1/3
Now g = 2/3
++g = 1+2/3
Now g = 1+2/3
g-- = 1+2/3
Now g = 2/3
--g = -1/3
Now g = -1/3

 */

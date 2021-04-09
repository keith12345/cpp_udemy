#ifndef FRACTION_H
#define FRACTION_H







/*
 * Declaration of Fraction object
 */
class Fraction {
    public:
        void print() const;
        Fraction multipliedBy(const Fraction& f) const;
        Fraction dividedBy(const Fraction& f) const;
        Fraction addedTo(const Fraction& f) const;
        Fraction subtract(const Fraction& f) const;
        bool isEqualTo(const Fraction& f) const;

        Fraction();
        Fraction(const int& numerator, const int& denominator);
    private:
        int numerator;
        int denominator;
        void simplify();
};


#endif

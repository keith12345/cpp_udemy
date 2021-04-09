#include <iostream>
using namespace std;






class Fraction {
    public:
        void print();
        void set(int numerator, int denominator);
        Fraction multipliedBy(Fraction f);
        Fraction dividedBy(Fraction f);
        Fraction addedTo(Fraction f);
        Fraction subtract(Fraction f);
        bool isEqualTo(Fraction f);
    private:
        int numerator;
        int denominator;
};






int main()
{
    Fraction f1;
    Fraction f2;
    Fraction result;

    f1.set(9, 8);
    f2.set(2, 3);

    cout << "The product of ";
    f1.print();
    cout << " and ";
    f2.print();
    cout << " is ";
    result = f1.multipliedBy(f2);
    result.print();
    cout << endl;

    cout << "The quotient of ";
    f1.print();
    cout << " and ";
    f2.print();
    cout << " is ";
    result = f1.dividedBy(f2);
    result.print();
    cout << endl;

    cout << "The sum of ";
    f1.print();
    cout << " and ";
    f2.print();
    cout << " is ";
    result = f1.addedTo(f2);
    result.print();
    cout << endl;

    cout << "The difference of ";
    f1.print();
    cout << " and ";
    f2.print();
    cout << " is ";
    result = f1.subtract(f2);
    result.print();
    cout << endl;

    if (f1.isEqualTo(f2)){
        cout << "The two Fractions are equal." << endl;
    } else {
        cout << "The two Fractions are not equal." << endl;
    }
}






void Fraction::set(int numerator, int denominator) {
    this->numerator = numerator;
    this->denominator = denominator;
}






void Fraction::print() {
    std::cout << this->numerator
              << "/"
              << this->denominator;
}






Fraction Fraction::multipliedBy(Fraction f) {
    Fraction out;
    out.set(
        this->numerator * f.numerator,
        this->denominator * f.denominator
    );
    return out;
}






Fraction Fraction::dividedBy(Fraction f) {
    Fraction out;
    out.set(
        this->numerator * f.denominator,
        this->denominator * f.numerator
    );
    return out;
}






Fraction Fraction::addedTo(Fraction f) {
    Fraction out;
    out.set(
        this->numerator * f.denominator + this->denominator * f.numerator,
        this->denominator * f.denominator
    );
    return out;
}






Fraction Fraction::subtract(Fraction f) {
    Fraction out;
    out.set(
        this->numerator * f.denominator - this->denominator * f.numerator,
        this->denominator * f.denominator
    );
    return out;
}






bool Fraction::isEqualTo(Fraction f) {
    return (this->numerator * f.denominator == this->denominator * f.numerator);
}






/*
 * The product of 9/8 and 2/3 is 18/24
 * The quotient of 9/8 and 2/3 is 27/16
 * The sum of 9/8 and 2/3 is 43/24
 * The difference of 9/8 and 2/3 is 11/24
 * The two Fractions are not equal.
 */

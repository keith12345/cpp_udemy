#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int* p;
    cout << "Value stored at *p is " << *p << endl;
    cout << "The address of *p is " << &p << endl;
    cout << "The address that *p is pointing to is " << p << endl;
    cout << "The size of *p is " << sizeof(p) << endl;
    p = {nullptr};
    cout << "Setting p to a nullptr." << endl;
    cout << "The address that *p is pointing to is " << p << endl;

    int n {10};
    cout << "Declaring and initializing a new variable, n" << endl;
    cout << "The value of n " << n << endl;
    cout << "The memory address of n " << &n << endl;
    p = &n;
    cout << "Setting p - &n" << endl;
    cout << "The value of p " << p << endl;
    cout << boolalpha;
    cout << "p == &n " << (p == &n) << " and *p == n " << (*p == n) << endl;

    cout << "address of a pointer: " << &p << endl;
    int* q {nullptr};
    q = p;
    cout << "p and q: " << p << " " << q << endl;
    int** r {nullptr};
    r = &p;
    cout << "r " << r << endl;
    cout << "de-reference *r " << *r << endl;
    cout << "Double de-reference **r " << **r << endl;

}

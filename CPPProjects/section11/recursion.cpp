#include <iostream>
using namespace std;

unsigned long long factorial(unsigned n) {
    unsigned long long out {};
    if (n < 2) {
        out = n;
    } else {
        out = n * factorial(n-1);
    }
    return out;
}

int main() {
    unsigned n {50};
    unsigned long long f {};
    f = factorial(n);
    cout << f << endl;
}

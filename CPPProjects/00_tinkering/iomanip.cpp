#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    float a {12.999};
    cout << fixed << setprecision(2);
    cout << a << endl;
    float b {10.125};
    cout << b << endl;
    float c {10.1250001};
    cout << c << endl;
    float d {10.125001};
    cout << d << endl;
}

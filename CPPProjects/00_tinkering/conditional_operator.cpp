#include <iostream>
using namespace std;


int main() {
    int num {};

    cout << "enter an integer: " << endl;
    cin >> num;

    cout << num << " is " << ( (num % 2 == 0) ? "even" : "odd" ) << endl;
}

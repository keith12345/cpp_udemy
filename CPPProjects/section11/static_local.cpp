#include <iostream>
using namespace std;

void print() {
    static int n {100};
    cout << n << endl;
    n += 1;
    cout << n << endl;
}

int main() {
    cout << "Round 1" << endl;
    print();
    cout << "Round 2" << endl;
    print();
}

#include <iostream>
using namespace std;

int main() {
    int* p {nullptr};
    p = new int;
    *p = 10;
    cout << *p << endl;
    delete p;
}

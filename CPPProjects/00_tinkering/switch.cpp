#include <iostream>
using namespace std;

int main() {
    int a {2};

    switch (a) {
        case 1:
            cout << "1 was selected" << endl;
        case 2:
            cout << "2 was selected" << endl;
        case 3:
            cout << "3 was selected" << endl;
        case 4:
            cout << "4 was selected" << endl;
            break;
        default:
            cout << "None of 1, 2, 3, 4 were selected" << endl;
    }
}

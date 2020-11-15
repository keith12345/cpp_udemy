#include <iostream>
using namespace std;

int main() {
    enum Color {
        red, green, blue
    };

    Color screen_color {green};

    switch (screen_color) {
        case red: cout << "red" << endl; break;
        case green: cout << "green" << endl; break;
        case blue: cout << "blue" << endl; break;
        default: cout << "How'd we get here" << endl;
    }
}

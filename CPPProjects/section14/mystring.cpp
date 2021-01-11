#include "Mystring.h"
#include <iostream>

using namespace std;


int main() {
    Mystring a {"Hello"};
    Mystring b;
    b = a;
    std::cout << (b == a) << std::endl;
    b.display();
    b = "This is a test";
    b.display();
    b = Mystring {"Another test"};
    b.display();
    Mystring c {b};
    c.display();
    c = -b;
    c.display();
    c = a + move(" I am a robot");
    c.display();
    std::cin >> c;
    std::cout << c << std::endl;
};

#include <iostream>

void showMessage(int);

int main() {
    showMessage(5);
}


void showMessage(int n) {
    if (n > 0) {
        std::cout << "Good day!" << std::endl;
        showMessage(n-1);
    }
}

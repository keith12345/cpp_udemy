#include <iostream>

int main() {
    int j;
    int k;
    int i = 1;
    j = i++;
    k = ++i;

    std::cout << "i = " << i << std::endl;
    std::cout << "j = " << j << std::endl;
    std::cout << "k = " << k << std::endl;
}

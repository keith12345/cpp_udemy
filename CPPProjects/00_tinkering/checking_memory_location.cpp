#include <iostream>

int main() {
    int test;
    std::cout << "Unitialized test: " << test << std::endl;
    std::cout << "Test mem location: " << &test << std::endl;
    int* test_pointer= &test;
    std::cout << "Printing what is at that location in memory: " << *test_pointer << std::endl;
    test = 10;
    std::cout << "Assigned test to 10: " << test << std::endl;
    std::cout << "Checking to see if same mem location: " << &test << std::endl;
    std::cout << "Checking value at that location: " << *test_pointer << std::endl;
}

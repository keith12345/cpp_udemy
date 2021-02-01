#include <iostream>
#include <memory>

void my_deleter(int* ptr) {
    std::cout << "Calling custom deleter" << std::endl;
    delete ptr;
}

int main() {
    std::shared_ptr<int> n { new int {10}, my_deleter };

    std::shared_ptr<int> n1 ( new int {20}, [] (int* ptr) {
            std::cout << "Using lambda deleter" << std::endl;
            delete ptr;
        }
    );
}

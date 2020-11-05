#include <iostream>

int main() {
    std::cout << "Hello world, bru" << std::endl;
    return 0;
}

// setting compile settings
// g++ - gnu c++ compiler
// -Wall - Show all warnings
// -std - Standard (course uses c++14
// then specify the file in-line
// g++ -Wall -std=c++14 main.cpp
//
// This will create a new file in that directory called "a.out"
// to run that file, simply type ./a.out
// if you want to name the file you can use the -o flag
// (which stands for "output")
// so if we run g++ -Wall -std=c++14 main.cpp -o main
// then we'll create a main file that we can run with ./main

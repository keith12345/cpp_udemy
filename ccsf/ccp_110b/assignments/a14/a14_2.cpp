#include <ios>
#include <iostream>
#include <iomanip>
#include "mystring.h"
using namespace cs_mystring;
using namespace std;






void isPalindrome(MyString str, int lowerBound, int upperBound);






int main() {
    MyString input;
    std::cout << std::boolalpha;
    std::cout << "Enter a string: ";
    input.read(std::cin, '\n');
    do {
        isPalindrome(input, 0, input.length() - 1);
        std::cout << "Enter a string: ";
        input.read(std::cin, '\n');
    } while (input != "quit");
}






/*
 * takes a MyString object as an argument as well as a lowerBound and
 * upperBound.
 * Prints whether or not the passed MyString is a palindrome.
 */
void isPalindrome(MyString str, int lowerBound, int upperBound) {
    while (ispunct(str[lowerBound]) || isspace(str[lowerBound]))
        ++lowerBound;
    while (ispunct(str[upperBound]) || isspace(str[upperBound]))
        --upperBound;
    if (lowerBound < upperBound) {
        if (tolower(str[lowerBound]) != tolower(str[upperBound])) {
            std::cout << str
                      << " is not a palindrome."
                      << std::endl;
        } else {
            isPalindrome(str, ++lowerBound, --upperBound);
        }
    } else {
        std::cout << str
                  << " is a palindrome."
                  << std::endl;
    }
}






/*
   Enter a string: test
   test is not a palindrome.
   Enter a string: Able was I, ere I saw Elba
   Able was I, ere I saw Elba is a palindrome.
   Enter a string: peanut butter
   peanut butter is not a palindrome.
   Enter a string: quit
 */

#include <cstring>
#include <iostream>


void reverseWithinBounds(char* str, int, int);
void reverseCstring(char* str);






int main() {
    char str[] = "some string";
    std::cout << "The original string:\n\t" << str << std::endl;
    reverseWithinBounds(str, 5, 10);
    std::cout << "Reversing part of the string:\n\t" << str << std::endl;
    reverseWithinBounds(str, 5, 10);
    std::cout << "Changing it back:\n\t" << str << std::endl;
    reverseCstring(str);
    std::cout << "Reversing the whole string:\n\t" << str << std::endl;
    reverseCstring(str);
    std::cout << "Switching the whole string back:\n\t" << str << std::endl;
}






/*
 * Takes a c-string as an argument, as well as a lower and upper bound
 * Reverse the order of characters within the specified bounds.
 * Operations are performed in place.
 */
void reverseWithinBounds(char* str, int lowerBound, int upperBound) {
    if (lowerBound < upperBound) {
        char tmp = std::move(str[lowerBound]);
        str[lowerBound] = std::move(str[upperBound]);
        str[upperBound] = std::move(tmp);
        reverseWithinBounds(str, ++lowerBound, --upperBound);
    }
}






/*
 * Takes a c-string as an argument
 * Reverses the order of characters in the string.
 * Operations are performed in place.
 */
void reverseCstring(char* str) {
    reverseWithinBounds(str, 0, std::strlen(str) - 1);
}






/*
The original string:
	some string
Reversing part of the string:
	some gnirts
Changing it back:
	some string
Reversing the whole string:
	gnirts emos
Switching the whole string back:
	some string
 */

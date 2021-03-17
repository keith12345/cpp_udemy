/*
Name: Keith Kirkpatrick
Class: CS 110B Programming Fundamentals: C++
Date: March 12th, 2021
Instructor: Dave Harden
File: a6_1.cpp
Usage:
    Requires no user input.
    Tests the following c-string manipulation functions:
        int lastIndexOf(const char* inString, char target);
        void reverse(char* inString);
        int replace(char* inString, char target, char replacementChar);
        bool isPalindrome(const char* inString);
        void toupper(char* inString);
        int numLetters(const char* inString);
 */

#include <iostream>
#include <cstring>
#include <iomanip>






// Helper funcs
int lastIndexOf(const char* inString, char target);
void reverse(char* inString);
int replace(char* inString, char target, char replacementChar);
bool isPalindrome(const char* inString);
void toupper(char* inString);
int numLetters(const char* inString);






int main() {
    char s[] = "This is my test string";
    int lastIndex = lastIndexOf(s, 't');
    std::cout << "Getting the last index of the letter 't' in: " << s << std::endl;
    std::cout << "Last index is " << lastIndex << std::endl;
    std::cout << "Printing char at last-index-of: " << s[lastIndex] << std::endl;
    std::cout << std::endl;

    std::cout << "Reversing test string: " << s << std::endl;
    reverse(s);
    std::cout << "which results in: " << s << std::endl;
    reverse(s);
    std::cout << "Reversing again should bring things back to normal: " << s << std::endl;
    std::cout << std::endl;

    std::cout << "Replacing all 't's with 'x's in test string: " << s << std::endl;
    int nReplacements = replace(s, 't', 'x');
    std::cout << "There were " << nReplacements << " replacements resulting in: " << s << std::endl;
    std::cout << "We can use lastIndexOf() to check whether any 't's still remain.\n"
              << "If there are 0 't's it should return -1: " << lastIndexOf(s, 't') << std::endl;
    nReplacements = replace(s, 'x', 't');
    std::cout << "Replacing all 'x's with 't's to bring things back to normal: " << s << std::endl;
    std::cout << "There should be the same number of replacments as there were before: "
              << nReplacements << std::endl;
    std::cout << std::endl;

    std::cout << std::boolalpha;
    std::cout << "Testing test string which is NOT a palindrome. Should return false: "
              << isPalindrome(s) << std::endl;
    std::cout << "Testing 'aba' which is a palindrome. Should return true: "
              << isPalindrome("aba") << std::endl;
    std::cout << "Testing 'a' which is a palindrome. Should return true: "
              << isPalindrome("a") << std::endl;
    std::cout << "Testing 'ab' which is NOT a palindrome. Should return false: "
              << isPalindrome("ab") << std::endl;
    std::cout << "Testing 'aa' which is a palindrome. Should return true: "
              << isPalindrome("aa") << std::endl;
    std::cout << std::endl;

    std::cout << "Converting test string to upper case: " << s << std::endl;
    toupper(s);
    std::cout << "Which gives us: " << s << std::endl;
    std::cout << std::endl;

    std::cout << "Finding in number of lettings in test string: " << numLetters(s) << std::endl;
    std::cout << std::endl;

    std::cout << "Testing all functions on empty c-strings for sanity check:" << std::endl;

    char emptyString[] = "";
    std::cout << "LastIndexOf(): " << lastIndexOf(emptyString, 't') << std::endl;
    reverse(emptyString);
    std::cout << "No output to show for reverse() for empty string: " << emptyString << std::endl;
    std::cout << "replace(): " << replace(emptyString, ' ', 't') << std::endl;
    std::cout << "isPalindrome(): " << isPalindrome(emptyString) << std::endl;
    std::cout << "\tEmpty strings are palindromes because they read the same forwards and backwarsds." << std::endl;
    toupper(s);
    std::cout << "No output to show for toupper()" << std::endl;
    std::cout << "numLetters(): " << numLetters(emptyString) << std::endl;
}






/*
   Takes a pointer to the first character of c-string char array, and a target char
   as arguments.
   This function finds the last index where the target char can be found in the string.
   it returns -1 if the target char does not appear in the string. The function should
   be case sensitive (so 'b' is not a match for 'B').
 */
int lastIndexOf(const char* inString, char target) {
    int targetIndex = -1;
    int indexer = 0;
    while (inString[indexer] != '\0') {
        if (inString[indexer] == target) {
            targetIndex = indexer;
        }
        indexer++;
    }
    return targetIndex;
}






/*
   Takes a pointer to the first character of c-string char array as an argument.
   This function alters any string that is passed in. It should reverse the string. If
   "flower" gets passed in it should be reversed in place to "rewolf". For efficiency,
   this must be done "in place", i.e., without creating a second array.
 */
void reverse(char* inString) {
    int tail = std::strlen(inString) - 1;
    int head = 0;
    char tmp;
    while (head < tail) {
        tmp = std::move(inString[head]);
        inString[head] = std::move(inString[tail]);
        inString[tail] = std::move(tmp);
        head++;
        tail--;
    }
}






/*
   Takes a pointer to the first character of c-string char array, a target char
   and a replacement char as arguments.
   This function finds all instances of the char 'target' in the string and replace them
   with 'replacementChar'. It returns the number of replacements that it makes. If the
   target char does not appear in the string it should return 0.
 */
int replace(char* inString, char target, char replacementChar) {
    int count = 0;
    int indexer = 0;
    while (inString[indexer] != '\0') {
        if (inString[indexer] == target) {
            inString[indexer] = replacementChar;
            count++;
        }
        indexer++;
    }
    return count;
}






/*
   Takes a pointer to the first character of c-string char array as an argument.
   This function returns true if the argument string is a palindrome. It returns false
   if it is not. A palindrome is a string that is spelled the same as its reverse. For
   example "abba" is a palindrome. So are "hannah" and "abc cba".
 */
bool isPalindrome(const char* inString) {
    int tail = std::strlen(inString) - 1;
    int head = 0;
    bool palindrome = true;
    while (head < tail) {
        if (inString[head] != inString[tail])
            palindrome = false;
        head++;
        tail--;
    }
    return palindrome;
}






/*
   Takes a pointer to the first character of c-string char array as an argument.
   This function converts the c-string parameter to all uppercase.
 */
void toupper(char* inString) {
    int indexer = 0;
    while (inString[indexer] != '\0') {
        inString[indexer] = std::toupper(inString[indexer]);
        indexer++;
    }
}






/*
   Takes a pointer to the first character of c-string char array as an argument.
   This function returns the number of letters in the c-string
 */
int numLetters(const char* inString) {
    int indexer = 0;
    int count = 0;
    while (inString[indexer] != '\0') {
        if (std::isalpha(inString[indexer]))
                count++;
        indexer++;
    }
    return count;
}






/*
   Getting the last index of the letter 't' in: This is my test string
   Last index is 17
   Printing char at last-index-of: t

   Reversing test string: This is my test string
   which results in: gnirts tset ym si sihT
   Reversing again should bring things back to normal: This is my test string

   Replacing all 't's with 'x's in test string: This is my test string
   There were 3 replacements resulting in: This is my xesx sxring
   We can use lastIndexOf() to check whether any 't's still remain.
   If there are 0 't's it should return -1: -1
   Replacing all 'x's with 't's to bring things back to normal: This is my test string
   There should be the same number of replacments as there were before: 3

   Testing test string which is NOT a palindrome. Should return false: false
   Testing 'aba' which is a palindrome. Should return true: true
   Testing 'a' which is a palindrome. Should return true: true
   Testing 'ab' which is NOT a palindrome. Should return false: false
   Testing 'aa' which is a palindrome. Should return true: true

   Converting test string to upper case: This is my test string
   Which gives us: THIS IS MY TEST STRING

   Finding in number of lettings in test string: 18

   Testing all functions on empty c-strings for sanity check:
   LastIndexOf(): -1
   No output to show for reverse() for empty string:
   replace(): 0
   isPalindrome(): true
   	       Empty strings are palindromes because they read the same forwards and backwarsds.
   No output to show for toupper()
   numLetters(): 0
 */

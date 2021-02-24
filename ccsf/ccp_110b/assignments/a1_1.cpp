/*
Name: Keith Kirkpatrick
Class: CS 110B Programming Fundamentals: C++
Date: February 7th, 2021
Instructor: Dave Harden
File: a1_1.cpp
Usage:
  Prompts user to enter the a date in the following format: month/day/2-digit-year
  If the day * month are equal to the year, it tells the user that it's a magic date.
 */

#include <iostream>

int main() {
    std::cout << "Enter a date in the format month/day/2-digit-year: ";
    unsigned short month, day, year;
    char slash;
    std::cin >> month >> slash >> day >> slash >> year;
    if (month * day == year) {
        std::cout << "Hey! That's a magic date! :)" << std::endl;
    } else {
        std::cout << "That date isn't magical... :(" << std::endl;
    }
    return 0;
}

/*
Enter a date in the format month/day/2-digit-year: 5/10/50
Hey! That's a magic date! :)
Enter a date in the format month/day/2-digit-year: 7/7/7
That date isn't magical... :(
 */

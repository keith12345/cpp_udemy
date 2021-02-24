/*
Name: Keith Kirkpatrick
Class: CS 110B Programming Fundamentals: C++
Date: February 18th, 2021
Instructor: Dave Harden
File: a3_1.cpp
Usage:
   Asks user if they're ready to play a guessing game where the computer guesses numbers
   between 1 and 100 until it finds the number that the user guessed.
   Instructions are provided throughout regarding which inputs are required to indicate
   specific commands to the program.
   Once the computer wins (which, it ultimately will, if you're honest), it will ask
   you if you'd like to play again.
 */




#include <iostream>
using namespace std;


const int LOWER_BOUND = 1;
const int UPPER_BOUND = 100;


void playOneGame();
int getMidpoint(const int& low, const int& high);
void getUserResponseToGuess(const int& guess, char& result);
//void updateBoundsAndGuess(int& low, int& high, const char& result, int& guess);
void updateBounds(int& low, int& high, const char& result, const int& guess);
void updateGuess(const int& low, const int& high, const char& result, int& guess);





int main() {
    char response;

    cout << "Ready to play (y/n)? ";
    cin >> response;
    while (response == 'y') {
        playOneGame();
        cout << "Great! Do you want to play again (y/n)? ";
        cin >> response;
    }
}






/*
   Gets the mid point between two numbers
   The program will always round down:
   e.g. (5 + 2) / 2 = 3
 */
int getMidpoint(const int& low, const int& high) {
    return (low + high) / 2;
}






/*
   Prints the programs guess for the user to read.
   Then provides instructions for how the user is to respond to the guess.
   Nothing is returned as as the result is passed by reference and changed in-place.
 */
void getUserResponseToGuess(const int& guess, char& result) {
    cout << "My guess is "
         << guess
         << ". "
         << "Enter 'l' if your number is lower, "
         << "'h' if it is higher, "
         << "'c' if it is correct: ";
    cin >> result;
}





/*
   Given a low bounds variable, higher bounds variable, user result, and guess by the
   program, this function adjusts the bounds based on the response (increasing/decreasing
   as necessary) and provides a new guess based on the updated bounds.
   Nothing is returned as low, high, and guess are passed by reference and changed in-place.

   Ended up not using this function the program could be more modular in a way that makes
   it more intuitive.
   This combined functionality is less likely to useful to another programmer in another
   context than each function on its own.
 */
/*
void updateBoundsAndGuess(int& low, int& high, const char& result, int& guess) {
    if (result == 'h') {
        low = guess + 1;
        guess = getMidpoint(low, high);
    } else if (result == 'l') {
        high = guess - 1;
        guess = getMidpoint(low, high);
    }
}
 */






/*
 * Given a result from the user, this function updates the bounds accordingly,
 * setting the upper bounds to n-1 if the guess was high and the lower bounds
 * to n-1 if the guess was low
 */
void updateBounds(int& low, int& high, const char& result, const int& guess) {
    if (result == 'h') {
        low = guess + 1;
    } else if (result == 'l') {
        high = guess - 1;
    }
}






/*
 * Given a result from the user and a set of bounds, adjusts the guess by calling
 * the `getMidpoint()` function
 */
void updateGuess(const int& low, const int& high, const char& result, int& guess) {
    if (result == 'h') {
        guess = getMidpoint(low, high);
    } else if (result == 'l') {
        guess = getMidpoint(low, high);
    }
}







/*
   Initializes lower and upper bounds based on the constants provided within the program's
   source code.
   Prompts the user to think of a number between 1 and 100 and performs the guessing as
   described in the file comment.
 */
void playOneGame() {
    cout << "Think of a number between 1 and 100." << endl;
    char responseToGuess;
    int low = LOWER_BOUND;
    int high = UPPER_BOUND;
    int guess = getMidpoint(low, high);
    do {
        getUserResponseToGuess(guess, responseToGuess);
        updateBounds(low, high, responseToGuess, guess);
        updateGuess(low, high, responseToGuess, guess);
    } while (responseToGuess != 'c');
}






/*

   Ready to play (y/n)? y
   Think of a number between 1 and 100.
   My guess is 50. Enter 'l' if your number is lower, 'h' if it is higher, 'c' if it is correct: h
   My guess is 75. Enter 'l' if your number is lower, 'h' if it is higher, 'c' if it is correct: h
   My guess is 88. Enter 'l' if your number is lower, 'h' if it is higher, 'c' if it is correct: l
   My guess is 81. Enter 'l' if your number is lower, 'h' if it is higher, 'c' if it is correct: h
   My guess is 84. Enter 'l' if your number is lower, 'h' if it is higher, 'c' if it is correct: l
   My guess is 82. Enter 'l' if your number is lower, 'h' if it is higher, 'c' if it is correct: h
   My guess is 83. Enter 'l' if your number is lower, 'h' if it is higher, 'c' if it is correct: c
   Great! Do you want to play again (y/n)? y
   Think of a number between 1 and 100.
   My guess is 50. Enter 'l' if your number is lower, 'h' if it is higher, 'c' if it is correct: l
   My guess is 25. Enter 'l' if your number is lower, 'h' if it is higher, 'c' if it is correct: h
   My guess is 37. Enter 'l' if your number is lower, 'h' if it is higher, 'c' if it is correct: l
   My guess is 31. Enter 'l' if your number is lower, 'h' if it is higher, 'c' if it is correct: h
   My guess is 34. Enter 'l' if your number is lower, 'h' if it is higher, 'c' if it is correct: h
   My guess is 35. Enter 'l' if your number is lower, 'h' if it is higher, 'c' if it is correct: h
   My guess is 36. Enter 'l' if your number is lower, 'h' if it is higher, 'c' if it is correct: c
   Great! Do you want to play again (y/n)? n

 */

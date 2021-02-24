/*
Name: Keith Kirkpatrick
Class: CS 110B Programming Fundamentals: C++
Date: February 12th, 2021
Instructor: Dave Harden
File: a2_1.cpp
Usage:
  Deals the player two cards. The player can continue to draw cards until they either
  reach 21 or bust. The program automatically exists with a victory if you reach 21 and
  automatically loses if they go above 21.
  The player may also stop drawing cards.
  Once the player has either busted, achieved 21, or decided to stop playing the hand,
  the player will have the option to play another hand.
  Once the player ends, they will see a breakdown of their score.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

const short MIN_RAND = 1;
const short MAX_RAND = 10;
const short MAX_VALUE = 21;

int main() {
    std::srand(time(0));
    short firstCard;
    short nextCard;
    short total;
    char hitMeAgain;
    char playAgain = 'y';
    int wins = 0;
    int losses = 0;
    int playedItSafe = 0;

    while (playAgain == 'y') {

        firstCard = (std::rand() % (MAX_RAND - MIN_RAND + 1)) + MIN_RAND;
        nextCard = (std::rand() % (MAX_RAND - MIN_RAND + 1)) + MIN_RAND;
        total = firstCard + nextCard;

        std::cout << "First cards: " << firstCard << ", " << nextCard << std::endl;

        do {
            std::cout << "Total: " << total << std::endl;
            std::cout << "Do you want another card? (y/n): ";
            std::cin >> hitMeAgain;
            if (hitMeAgain == 'y') {
                nextCard = (std::rand() % (MAX_RAND - MIN_RAND + 1)) + MIN_RAND;
                std::cout << "Card: " << nextCard << std::endl;
                total += nextCard;
            }
        } while (hitMeAgain == 'y' && total < MAX_VALUE);

        if (total > MAX_VALUE) {
            std::cout << "Oops! Your total it " << total << "... Bust!" << std::endl;
            losses += 1;
        } else if (total == MAX_VALUE) {
            std::cout << "Congratulations! You got 21!!" << std::endl;
            wins += 1;
        } else {
            std::cout << "Sorry, " << total
                << " is close but not quite good enough..." << std::endl;
            playedItSafe += 1;
        }

        std::cout << "Would you like to play again? (y/n): ";
        std::cin >> playAgain;
        std::cout << std::endl;
    }
    std::cout << "Your summary for the session:"
        << "\n\tWins: " << wins
        << "\n\tLosses: " << losses
        << "\n\tPlayed it safe: " << playedItSafe
        << std::endl;
}

/*

First cards: 4, 4
Total: 8
Do you want another card? (y/n): y
Card: 4
Total: 12
Do you want another card? (y/n): y
Card: 1
Total: 13
Do you want another card? (y/n): y
Card: 1
Total: 14
Do you want another card? (y/n): y
Card: 2
Total: 16
Do you want another card? (y/n): y
Card: 2
Total: 18
Do you want another card? (y/n): y
Card: 6
Oops! Your total it 24... Bust!
Would you like to play again? (y/n): y

First cards: 7, 1
Total: 8
Do you want another card? (y/n): y
Card: 10
Total: 18
Do you want another card? (y/n): y
Card: 4
Oops! Your total it 22... Bust!
Would you like to play again? (y/n): y

First cards: 7, 7
Total: 14
Do you want another card? (y/n): y
Card: 5
Total: 19
Do you want another card? (y/n): y
Card: 1
Total: 20
Do you want another card? (y/n): y
Card: 1
Congratulations! You got 21!!
Would you like to play again? (y/n): y

First cards: 9, 2
Total: 11
Do you want another card? (y/n): y
Card: 8
Total: 19
Do you want another card? (y/n): y
Card: 3
Oops! Your total it 22... Bust!
Would you like to play again? (y/n): y

First cards: 1, 5
Total: 6
Do you want another card? (y/n): y
Card: 9
Total: 15
Do you want another card? (y/n): y
Card: 8
Oops! Your total it 23... Bust!
Would you like to play again? (y/n): y

First cards: 1, 3
Total: 4
Do you want another card? (y/n): y
Card: 9
Total: 13
Do you want another card? (y/n): y
Card: 3
Total: 16
Do you want another card? (y/n): n
Sorry, 16 is close but not quite good enough...
Would you like to play again? (y/n): y

First cards: 9, 8
Total: 17
Do you want another card? (y/n): y
Card: 7
Oops! Your total it 24... Bust!
Would you like to play again? (y/n): y

First cards: 4, 3
Total: 7
Do you want another card? (y/n): y
Card: 9
Total: 16
Do you want another card? (y/n): y
Card: 4
Total: 20
Do you want another card? (y/n): n
Sorry, 20 is close but not quite good enough...
Would you like to play again? (y/n): n


Your summary for the session:
	Wins: 1
	Losses: 5
	Played it safe: 2

*/

/*
Name: Keith Kirkpatrick
Class: CS 110B Programming Fundamentals: C++
Date: February 7th, 2021
Instructor: Dave Harden
File: a1_1.cpp
Usage:
  Reads cards from the user (typically 5), then analyzes the cards and prints out the type of poker hand that they
  represent.

  Poker hands are categorized according to the following hand-types: Straight flush, four of a kind, full house,
  straight, flush, three of a kind, two pairs, pair, high card.

  The program ignores card suits, and face cards. The values that the user inputs will be integer values from LOWEST_NUM
  to HIGHEST_NUM.

  No input validation is performed
 */

#include <iostream>
#include <iomanip>




int LOWEST_NUM = 2;
int HIGHEST_NUM = 9;
int HAND_SIZE = 6;
int STRAIGHT_SIZE = 5;




// helper functions
void getHand(int hand[]);
int countOccurrences(const int hand[], const int number);
bool containsStraightHelper(int& indexer, const int hand[]);




// Hand checker functions
bool containsPair(const int hand[]);
bool containsTwoPair(const int hand[]);
bool containsThreeOfaKind(const int hand[]);
bool containsStraight(const int hand[]);
bool containsFullHouse(const int hand[]);
bool containsFourOfaKind(const int hand[]);






int main() {
    int hand[HAND_SIZE];
    std::cout << "Enter "
              << HAND_SIZE
              << " numeric cards, no face cards. Use "
              << LOWEST_NUM
              << " - "
              << HIGHEST_NUM
              << "."
              << std::endl;
    getHand(hand);

    if (containsFourOfaKind(hand)) {
        std::cout << "Wow, you got 4 of a kind!" << std::endl;
    } else if (containsFullHouse(hand)) {
        std::cout << "That's super good; you got a hull house!" << std::endl;
    } else if (containsStraight(hand)) {
        std::cout << "You got a straight! That's great!" << std::endl;
    } else if (containsThreeOfaKind(hand)) {
        std::cout << "Three of a kind... That's a pretty good hand." << std::endl;
    } else if (containsTwoPair(hand)) {
        std::cout << "Two pair; solid." << std::endl;
    } else if (containsPair(hand)) {
        std::cout << "You got a pair... that's not nothin'." << std::endl;
    } else {
        std::cout << "High card... you probably shouldn't bet..." << std::endl;
    }
}






/*
 * Counts the number of occurrences for a particular card.
 * Returns that number as an integer
 */
int countOccurrences(const int hand[], const int number) {
    int counter = 0;
    for (int i = 0; i <= HAND_SIZE; i++) {
        if (hand[i] == number) {
            counter += 1;
        }
    }
    return counter;
}






/*
 * Receives a pointer for an array of HAND_SIZE.
 * Reads input from the user and populates the array in the order input was received.
 * Does not return anything as array is modified in-place
 */
void getHand(int hand[]) {
    for (int i = 0; i < HAND_SIZE; i++) {
        std::cout << "Card " << (i + 1) << ": ";
        std::cin >> hand[i];
    }
}






/*
 * Counts the number of occurrences of each card in the playable range.
 * Takes a tally of the number of pairs that occur.
 * Returns true if at least one pair is found
 */
bool containsPair(const int hand[]) {
    int pairCount = 0;
    for (int i = LOWEST_NUM; i <= HIGHEST_NUM; i++) {
        if (countOccurrences(hand, i) == 2) {
            pairCount += 1;
        }
    }
    return pairCount >= 1;
}






/*
 * Counts the number of occurrences of each card in the playable range.
 * Takes a tally of the number of three-of-a-kinds that occur.
 * Returns true if at least one three-of-a-kind is found
 */
bool containsThreeOfaKind(const int hand[]) {
    int tripsCount = 0;
    for (int i = LOWEST_NUM; i <= HIGHEST_NUM; i++) {
        if (countOccurrences(hand, i) == 3) {
            tripsCount += 1;
        }
    }
    return tripsCount >= 1;
}






/*
 * Counts the number of occurrences of each card in the playable range.
 * Takes a tally of the number of four-of-a-kinds that occur.
 * Returns true if at least one four-of-a-kind is found
 */
bool containsFourOfaKind(const int hand[]) {
    int fourCount = 0;
    for (int i = LOWEST_NUM; i <= HIGHEST_NUM; i++) {
        if (countOccurrences(hand, i) == 4) {
            fourCount += 1;
        }
    }
    return fourCount >= 1;
}






/*
 * Counts the number of occurrences of each card in the playable range.
 * Takes a tally of the number of pairs that occur.
 * Returns true if 2 pairs are found.
 */
bool containsTwoPair(const int hand[]) {
    int pairCount = 0;
    for (int i = LOWEST_NUM; i <= HIGHEST_NUM; i++) {
        if (countOccurrences(hand, i) == 2) {
            pairCount += 1;
        }
    }
    return pairCount == 2;
}






/*
 * Counts the number of occurrences of each card in the playable range.
 * Uses an accumulator to track progress toward a full-house.
 * If a pair or three-of-a-kind are found, the accumulator has the number of card occurrences added to it.
 * (Note that when a pair is found, the function checks for three-of-a-kind and when three-of-a-kind is found
 * it checks for a pair. Before either is found it is continuously checking for both).
 * Returns true if the value of the accumulator is equal to 5.
 */
bool containsFullHouse(const int hand[]) {
    int acc = 0;
    for (int i = LOWEST_NUM; i <= HIGHEST_NUM; i++) {
        if (((acc == 0 || acc == 2) && countOccurrences(hand, i) == 3) || ((acc == 0 || acc == 3) && countOccurrences(hand, i) == 2)) {
            acc += countOccurrences(hand, i);
        }
    }
    return acc == 5;
}





/*
 * Helper function for containsStraight().
 * Receives an indexer by reference and const array of cards for the hand.
 * Counts the number of consecutive cards, including the starting card,
 * that appear in the hand.
 * The hand does NOT need to be sorted.
 * Indexer is passed by reference to avoid rechecking numbers in a range that are
 * incapable of completing a straight.
 * Returns the number of consecutive cards.
 */
bool containsStraightHelper(int& indexer, const int hand[]) {
    int counter = 0;
    while (countOccurrences(hand, indexer) > 0 && counter < STRAIGHT_SIZE) {
        counter += 1;
        indexer += 1;
    }
    return counter == STRAIGHT_SIZE;
}






/*
 * Receives a const array of cards for the hand.
 * For the first card in a series of consecutive cards in a hand, checks
 * whether that cards leads to a straight but calling the containsStraightHelper
 * function.
 * Returns a bool indicating whether a STRAIGHT_SIZE-card straight was ever found.
 */
bool containsStraight(const int hand[]) {
    bool doesContainStraight = false;
    for (int i = LOWEST_NUM; i <= HIGHEST_NUM; i++) {
        if (countOccurrences(hand, i) > 0 && !doesContainStraight) {
            doesContainStraight = containsStraightHelper(i, hand);
        }
    }
    return doesContainStraight;
}






/*
 *  » g++ -Wall a4_1.cpp  --std c++17 -o main && ./main
 * Enter 5 numeric cards, no face cards. Use 2 - 9.
 * Card 1: 2
 * Card 2: 2
 * Card 3: 2
 * Card 4: 3
 * Card 5: 4
 * Three of a kind... That's a pretty good hand.
 * (6si-py3) keith•ccsf/ccp_110b/assignments(main~!)
 *  » g++ -Wall a4_1.cpp  --std c++17 -o main && ./main
 * Enter 5 numeric cards, no face cards. Use 2 - 9.
 * Card 1: 2
 * Card 2: 3
 * Card 3: 3
 * Card 4: 3
 * Card 5: 3
 * Wow, you got 4 of a kind!
 * (6si-py3) keith•ccsf/ccp_110b/assignments(main~!)
 *  » g++ -Wall a4_1.cpp  --std c++17 -o main && ./main
 * Enter 5 numeric cards, no face cards. Use 2 - 9.
 * Card 1: 2
 * Card 2: 2
 * Card 3: 3
 * Card 4: 3
 * Card 5: 3
 * That's super good; you got a hull house!
 * (6si-py3) keith•ccsf/ccp_110b/assignments(main~!)
 *  » g++ -Wall a4_1.cpp  --std c++17 -o main && ./main
 * Enter 5 numeric cards, no face cards. Use 2 - 9.
 * Card 1: 2
 * Card 2: 2
 * Card 3: 3
 * Card 4: 3
 * Card 5: 4
 * Two pair; solid.
 * (6si-py3) keith•ccsf/ccp_110b/assignments(main~!)
 *  » g++ -Wall a4_1.cpp  --std c++17 -o main && ./main
 * Enter 6 numeric cards, no face cards. Use 2 - 9.
 * Card 1: 2
 * Card 2: 2
 * Card 3: 2
 * Card 4: 3
 * Card 5: 3
 * Card 6: 3
 * Three of a kind... That's a pretty good hand.
 * (6si-py3) keith•ccsf/ccp_110b/assignments(main~!)
 *  » g++ -Wall a4_1.cpp  --std c++17 -o main && ./main
 * Enter 6 numeric cards, no face cards. Use 2 - 9.
 * Card 1: 9
 * Card 2: 2
 * Card 3: 4
 * Card 4: 3
 * Card 5: 6
 * Card 6: 5
 * You got a straight! That's great!
 */

#include <iostream>
#include <iomanip>

int LOWEST_NUM = 2;
int HIGHEST_NUM = 9;
int HAND_SIZE = 5;

void getHand(int hand[]);
void initializeHand(int hand[]);
bool containsPair(const int hand[]);
bool containsTwoPair(const int hand[]);
bool containsThreeOfaKind(const int hand[]);
bool findStraightHelper(int& indexer, const int hand[]);
bool containsStraight(const int hand[]);
bool containsFullHouse(const int hand[]);
bool containsFourOfaKind(const int hand[]);

int main() {
    int hand[HIGHEST_NUM - LOWEST_NUM + 1];
    std::cout << "Enter "
              << HAND_SIZE
              << " numeric cards, no face cards. Use "
              << LOWEST_NUM
              << " - "
              << HIGHEST_NUM
              << "."
              << std::endl;
    initializeHand(hand);
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

void initializeHand(int hand[]) {
    for (int i = 0; i < (HIGHEST_NUM - LOWEST_NUM + 1); i++)
        hand[i] = 0;
}

void getHand(int hand[]) {
    int userInput;
    for (int i = 0; i < HAND_SIZE; i++) {
        std::cout << "Card " << (i + 1) << ": ";
        std::cin >> userInput;
        hand[userInput-2] += 1;
    }
}

bool containsPair(const int hand[]) {
    int pairCount = 0;
    for (int i = 0; i < (HIGHEST_NUM - LOWEST_NUM + 1); i++) {
        if (hand[i] == 2) {
            pairCount += 1;
        }
    }
    return pairCount >= 1;
}

bool containsThreeOfaKind(const int hand[]) {
    int tripsCount = 0;
    for (int i = 0; i < (HIGHEST_NUM - LOWEST_NUM + 1); i++) {
        if (hand[i] == 3) {
            tripsCount += 1;
        }
    }
    return tripsCount >= 1;
}

bool containsFourOfaKind(const int hand[]) {
    int fourCount = 0;
    for (int i = 0; i < (HIGHEST_NUM - LOWEST_NUM + 1); i++) {
        if (hand[i] == 4) {
            fourCount += 1;
        }
    }
    return fourCount >= 1;
}

bool containsTwoPair(const int hand[]) {
    int pairCount = 0;
    for (int i = 0; i < (HIGHEST_NUM - LOWEST_NUM + 1); i++) {
        if (hand[i] == 2) {
            pairCount += 1;
        }
    }
    return pairCount == 2;
}

bool containsFullHouse(const int hand[]) {
    int acc = 0;
    for (int i = 0; i < (HIGHEST_NUM - LOWEST_NUM + 1); i++) {
        if (((acc == 0 || acc == 2) && hand[i] == 3) || ((acc == 0 || acc == 3) && hand[i] == 2)) {
            acc += hand[i];
        }
    }
    return acc == 5;
}

bool findStraightHelper(int& indexer, const int hand[]) {
    int counter = 0;
    while (hand[indexer] > 0 && counter < 5) {
        counter += 1;
        indexer += 1;
    }
    return counter == 5;
}

bool containsStraight(const int hand[]) {
    bool doesContainStraight = false;
    for (int i = 0; i < (HIGHEST_NUM - LOWEST_NUM + 1); i++) {
        if (hand[i] > 0 && !doesContainStraight) {
            doesContainStraight = findStraightHelper(i, hand);
        }
    }
    return doesContainStraight;
}

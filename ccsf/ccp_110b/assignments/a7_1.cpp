/*
Name: Keith Kirkpatrick
Class: CS 110B Programming Fundamentals: C++
Date: March 21st, 2021
Instructor: Dave Harden
File: a7_2.cpp
Usage:
    Records the high-scores for a game.
    The number of scores to be entered must be specified.

    Twp dynamic arrays are then created according to the specified size.
    The user can then enter a player name and then the score for that player.

    Scores and names and then sorted in ascending order.

    Finally, names and scores are printed in pairs.
 */

#include <iostream>
#include <string>
#include <cassert>






// some struct
struct userScores {
	std::string name;
	int score;
};






// Helper funcs
void getSize(int& size);
void readData(userScores scores[], int size);
void sortData(userScores scores[], int size);
void displayData(const userScores scores[], const int size);






int main() {
    int size;
    getSize(size);
    userScores* scores = new userScores[size];
    readData(scores, size);
    sortData(scores, size);
    displayData(scores, size);
    delete[] scores;
}






/*
 * Prompts the user to enter a "size"
 * Returns that value as an integer
 */
void getSize(int& size) {
    std::cout << "How many scores will you enter?: ";
    std::cin >> size;
}






/*
 * Recieves an array of strings and array of scores as well as in integer which indicates their size.
 * Prompts the user to enter names and scores.
 * Names and scores are entere in pairs but are expected on separate lines
 * i.e. the score for a player should be entered immediately after that
 * player's name is entered
 */
void readData(userScores scores[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << "Enter the name for user #" << (i + 1) << ": ";
        std::cin >> scores[i].name;
        std::cout << "Enter the score for user #" << (i + 1) << ": ";
        std::cin >> scores[i].score;
    }
}






/*
 * Recieves an array of strings and array of scores as well as in integer which indicates their size.
 * Sorts both the names array and scores array in the descending order of the scores.
 */
void sortData(userScores scores[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i; j < size; j++) {
            if (scores[j].score > scores[i].score) {
                std::swap(scores[i], scores[j]);
            }
        }
    }
}






/*
 * Recieves a const array of strings and const array of scores as well as in const int which indicates their size.
 * Prints a declaration of "Top Scorers:" followed by a list of names and their respective scores
 */
void displayData(const userScores scores[], const int size) {
    std::cout << "\nTop Scorers:" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << scores[i].name << ": " << scores[i].score << std::endl;
    }
}






/*
   How many scores will you enter?: 4
   Enter the name for user #1: Suzy
   Enter the score for user #1: 600
   Enter the name for user #2: Kim
   Enter the score for user #2: 9900
   Enter the name for user #3: Armando
   Enter the score for user #3: 8000
   Enter the name for user #4: Tim
   Enter the score for user #4: 514

   Top Scorers:
   Kim: 9900
   Armando: 8000
   Suzy: 600
   Tim: 514
 */

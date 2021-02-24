#include <iostream>
#include <fstream>

const short SIZE = 4;

int main() {
    std::ofstream outputFile("text.txt");
    short arr[] = {1, 2, 3, 4};
    for (int i = 0; i < SIZE; i++) {
        outputFile << arr[i] << " ";
    }
    outputFile.close();
    std::ifstream inputFile;
    inputFile.open("text.txt");
    short n;
    if (inputFile) {
        while (inputFile >> n) {
            std::cout << n << " " << std::endl;
        }
    } else {
        std::cout << "File is empty" << std::endl;
    }
    inputFile.close();
}

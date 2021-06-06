#include <iostream>






void sortArray(int*, int upperBound, int lowerBound = 0);
int indexOfLowest(int* arr, int upperBound, int lowerBound = 0);
void printArray(int* arr, int size);






int main() {
    int arr[] = {6, 4, 5, 2, 3, 1};
    std::cout << "Printing original array" << std::endl;
    printArray(arr, 6);
    std::cout << "Sorting array..." << std::endl;
    sortArray(arr, 6);
    std::cout << "Printing sorted array" << std::endl;
    printArray(arr, 6);
    int arr1[] = {4,6,2,9,5,1,7,3};
    std::cout << "Printing original array" << std::endl;
    printArray(arr1, 8);
    std::cout << "Sorting array..." << std::endl;
    sortArray(arr1, 8);
    std::cout << "Printing sorted array" << std::endl;
    printArray(arr1, 8);
}






/*
 * Given an array with upperBound and lowerBound sorts the array
 * LowerBound has a default arg of 0
 */
void sortArray(int* arr, int upperBound, int lowerBound) {
    int lowestIndex;
    int tmp;
    if (lowerBound < upperBound) {
        lowestIndex = indexOfLowest(arr, upperBound, lowerBound);
        tmp = std::move(arr[lowestIndex]);
        arr[lowestIndex] = std::move(arr[lowerBound]);
        arr[lowerBound] = std::move(tmp);
        sortArray(arr, upperBound, ++lowerBound);
    }
}






/*
 * Returns the index of the lowest element in an array
 * within an optional lowerBound arg
 */
int indexOfLowest(int* arr, int upperBound, int lowerBound) {
    int lowestIndex = lowerBound;
    while (++lowerBound < upperBound) {
        if (arr[lowerBound] < arr[lowestIndex])
            lowestIndex = lowerBound;
    }
    return lowestIndex;
}






/*
 * Prints an array so I have some sort of clue as to what's going on
 * inside of my function (: ( <- meant to be an upside down smiley )
 */
void printArray(int* arr, int size) {
    std::cout << "[ ";
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << ", ";
    std::cout << "]" << std::endl;
}




/*
   Printing original array
   [ 6, 4, 5, 2, 3, 1, ]
   Sorting array...
   Printing sorted array
   [ 1, 2, 3, 4, 5, 6, ]
   Printing original array
   [ 4, 6, 2, 9, 5, 1, 7, 3, ]
   Sorting array...
   Printing sorted array
   [ 1, 2, 3, 4, 5, 6, 7, 9, ]
 */

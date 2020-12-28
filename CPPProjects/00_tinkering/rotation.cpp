#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print_vec(vector<vector<int>> matrix) {
    cout << "[ ";
    for (auto v: matrix) {
        cout << "[ ";
        for (auto n: v) {
            cout << n << ", ";
        }
        cout << "]," << endl << "  ";
    }
    cout << " ]" << endl;
}

int main() {
    // vector<vector<int>> matrix {{1, 2}, {3, 4}};
    // vector<vector<int>> matrix {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<vector<int>> matrix {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    print_vec(matrix);
    int size {static_cast<int>(matrix.size())};
    for (int i = 0; i < size / 2; i++) {
        for (int j = i; j < size - (i + 1); j++) {
            // int m {};
            // int n {};
            // int p {};
            // m = matrix.at(j).at(size-(i+1)); // save second position so can overwrite with first
            // matrix.at(j).at(size-(i+1)) = matrix.at(i).at(j); // overwirte second with first
            // n = matrix.at(size-(i+1)).at(size-(j+1)); // save third so can overwrite with second
            // matrix.at(size-(i+1)).at(size-(i+1)) = m; // overwrite third with second
            // p = matrix.at(size-(j+1)).at(i); // save fourth so we can overwrite with third
            // matrix.at(size-(j+1)).at(i) = n; // overwrite fourth with third
            // matrix.at(i).at(j) = p; // overwrite first with fourth
            // swap(matrix.at(i).at(j), matrix.at(size-(j+1)).at(i));
            // swap(matrix.at(size-(i+1)).at(size-(j+1)), matrix.at(size-(j+1)).at(i));
            // swap(matrix.at(size-(i+1)).at(size-(j+1)), matrix.at(j).at(size-(i+1)));

            // int temp = matrix.at(i).at(j);
            // matrix.at(i).at(j) = matrix.at(size-(j+1)).at(i);
            // matrix.at(size-(j+1)).at(i) = matrix.at(size-(i+1)).at(size-(j+1));
            // matrix.at(size-(i+1)).at(size-(j+1)) = matrix.at(j).at(size-(i+1));
            // matrix.at(j).at(size-(i+1)) = temp;


            // int temp = matrix.at(i).at(j);
            // matrix.at(i).at(j) = move(matrix.at(size-(j+1)).at(i));
            // matrix.at(size-(j+1)).at(i) = move(matrix.at(size-(i+1)).at(size-(j+1)));
            // matrix.at(size-(i+1)).at(size-(j+1)) = move(matrix.at(j).at(size-(i+1)));
            // matrix.at(j).at(size-(i+1)) = temp;

            matrix.at(i).at(j), matrix.at(size-(j+1)).at(i) = move(matrix.at(size-(j+1)).at(i)), move(matrix.at(i).at(j));
            matrix.at(size-(i+1)).at(size-(j+1)), matrix.at(size-(j+1)).at(i) = move(matrix.at(size-(j+1)).at(i)), move(matrix.at(size-(i+1)).at(size-(j+1)));
            matrix.at(size-(i+1)).at(size-(j+1)), matrix.at(j).at(size-(i+1)) = move(matrix.at(j).at(size-(i+1))), move(matrix.at(size-(i+1)).at(size-(j+1)));
        }
    }
    print_vec(matrix);
}

#include<algorithm>
#include<iostream>
#include<vector>
#include<numeric>
#include<string>
using namespace std;

void print_numbers(vector<int>* vec) {
    cout << "\nThe numbers in the vector are: [ ";
    for (auto n: *vec) {
        cout << n << " ";
    }
    cout << ']' << endl;
}

void add_number(vector<int>* vec) {
    int input {0};
    cout << "\nPlease specify the number to be added: ";
    cin >> input;
    cout << endl;
    (*vec).push_back(input);
}

void display_mean(vector<int>* vec) {
    int sum {0};
    float average {0};
    unsigned n {static_cast<unsigned>((*vec).size())};
    sum = accumulate((*vec).begin(), (*vec).end(), 0.0);
    average = sum / n;
    cout << "\nThe mean of the vector is: " << average << endl;
}

void display_smallest(vector<int>* vec) {
    unsigned v_size {static_cast<unsigned>((*vec).size())};
    int smallest {};
    if (v_size > 0) {
        smallest = (*vec).at(0);
        for (unsigned i {1}; i < v_size; i++) {
            if ((*vec).at(i) < smallest)
                smallest = (*vec).at(i);
        }
        cout << "\nThe smallest element is " << smallest << endl;
    } else {
        cout << "\nHow about giving me a vector next time, huh?" << endl;
    }
    return;
}

void display_largest(vector<int>* vec) {
    int max = *max_element((*vec).begin(), (*vec).end());
    cout << "\nThe largest element is " << max << endl;
}

int main() {
    vector<int> vec {};
    char c {'0'};

    do {
        cout << "\nP - Print numbers" << endl;
        cout << "A - Add a number" << endl;
        cout << "M - Display mean of the numbers" << endl;
        cout << "S - Dispaly the smallest of the numbers" << endl;
        cout << "L - Display the largest of the numbers" << endl;
        cout << "Q - Quit\n" << endl;
        cout << "Enter your choice: ";
        cin >> c;

        switch (c) {
            case 'p':
            case 'P':
                print_numbers(&vec);
                break;
            case 'a':
            case 'A':
                add_number(&vec);
                break;
            case 'm':
            case 'M':
                display_mean(&vec);
                break;
            case 's':
            case 'S':
                display_smallest(&vec);
                break;
            case 'l':
            case 'L':
                display_largest(&vec);
                break;
            case 'q':
            case 'Q':
                break;
            default:
                cout << "\nInvalid selection." << endl;
        }
    } while (c != 'q' && c != 'Q');
    cout << "Terminating program..." << endl;
}

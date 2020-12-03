#include <iostream>
#include <string>
using namespace std;

void print_string(const string s, int size);
void mutate_vector(string &s, int size);

int main() {
    string s {"testy"};
    int size {5};
    print_string(s, size);
    mutate_vector(s, size);
    print_string(s, size);
}

void print_string(const string s, int size) {
    for (int i {}; i < size; i++) {
        cout << s.at(i);
    }
    cout << endl;

}

void mutate_vector(string &s, int size) {
    for (int i {}; i < size; i++) {
        if (i % 2 == 0) {
            s.at(i) = 'x';
        }
    }
}

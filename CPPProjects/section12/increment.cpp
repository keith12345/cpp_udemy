#include <iostream>
using namespace std;

int main() {
    int arr[] {1, 2, 4, 5, 6, -1};
    int* p {arr};
    while (*p != -1) {
        cout << *p++ << endl;
    }

}

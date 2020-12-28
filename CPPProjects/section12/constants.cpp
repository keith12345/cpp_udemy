#include <iostream>
using namespace std;

int main() {
    int n {10};
    int* const p {&n};
    *p += 1; // does work
    int m;
    int a[10] {};

}

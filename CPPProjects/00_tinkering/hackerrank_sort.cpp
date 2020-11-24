#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int size {0};
    cin >> size;
    vector<int> vec (size, 0);
    int input {0};
    for (int i = 0 ; i < size ; i++) {
        cin >> input;
        vec.at(i) = input;
    }
    sort(vec.begin(), vec.end());
    for (auto output : vec) {
        cout << output << " ";
    }
    cout << endl;
    return 0;
}

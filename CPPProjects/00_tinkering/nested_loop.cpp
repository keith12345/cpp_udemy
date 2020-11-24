#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec {2, 4, 6, 8};
    int v_size {static_cast<int>(vec.size())};
    int v_size_2 {vec.size()};
    int v_size_3 = vec.size();
    unsigned int long num1 = -1;

    cout << num1;

    cout << v_size_2;
    cout << v_size_3;
    int result = 0;
    if (v_size < 2) {
        result = 0;
    } else {
        for (int i {0}; i < v_size-1; i++) {
            for (int j {i+1}; j < v_size; j++) {
                result += vec.at(i) * vec.at(j);
                cout << vec.at(i) << " * " << vec.at(j) << endl;
            }
        }
    }
    cout << result << endl;
}

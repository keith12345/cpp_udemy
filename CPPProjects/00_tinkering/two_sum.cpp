#include <vector>
#include <iostream>
using namespace std;

int main() {

    vector<int> nums {3, 2, 3};
    int target {6};
    int size {static_cast<int>(nums.size())};
    int i {1};
    int j {};
    bool end {false};
    for (; i < size; i++) {
        if (not end) {
            for (; j < i; j++) {
                cout << j << endl;
                if (nums[i] + nums[j] != target) {
                    // cout << i << ": " << nums[i] << ", " << j << ": " << nums[j] << endl;
                    //cout << i << " " << j << endl;
                    continue;
                } else {
                    cout << i << " " << j << endl;
                    int out[2] {i, j};
                    end = true;
                    break;
                }
            }
        j = 0;
        }
        else
            break;
    }
}

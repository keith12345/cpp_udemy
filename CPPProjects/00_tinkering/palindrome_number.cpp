#include <string>
#include <iostream>
using namespace std;

int main() {
    int x {};
    cin >> x;
    bool out = true;
    string s {to_string(x)};
    if (x < 0)
        out = false;
    else {
        int size {static_cast<int>(s.size())};
        int half_size {size/2};
        for (int i {}; i < half_size; i++) {
            out &= (s[i] == s[size-1-i]);
        }
    }
    return out;
}

#include <iostream>
#include <string>
using namespace std;

string reverse(string str) {
    string out;
    if (str.length() == 0)
        out = "";
    else {
        for (size_t i {str.length()-1}; ; i--) {
            out += str.at(i);
            if (i == 0)
                break;
        }
    }
    return out;
}

int main() {
    string str;
    getline(cin, str);
    size_t len {str.length()};

    for (size_t i {}; i < len; i++) {
        string buffer (len - i, ' ');
        char middle {str.at(i)};
        string sides = str.substr(0, i);
        cout << buffer << sides << middle << reverse(sides) << buffer << endl;
    }
}

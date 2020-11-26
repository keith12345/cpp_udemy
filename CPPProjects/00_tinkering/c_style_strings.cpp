#include <iostream>
#include <string>
using namespace std;

int main() {
    string s1; //empty
    string s2 {"Keith"}; // Keith
    string s3 {s2}; // Keith
    string s4 {"Keith", 3}; // Kei
    string s5 {s3, 2, 3}; // ei
    string s6 (3, 'X'); // XXX

    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;
    cout << s5 << endl;
    cout << s6 << endl;

    string part1 {"C++"};
    string part2 {"is a powerful"};

    string sentence;

    sentence = part1 + " " + part2 + " language";

    cout << sentence << endl;
    // sentence = "C++" + " is powerful"; // invalid operands of types 'const char [4]' and 'const char [13]' to binary 'operator+'


    string s7 {"Keith"};

    cout << s7[0] << endl;
    cout << s7.at(0) << endl; // K
    cout << s7.at(0) << endl; // K

    s7[0] = 'f';
    cout << s7 << endl; // keith
    s7.at(0) = 'l';
    cout << s7 << endl; // leith

    for (char c: s7)
        cout << c << endl;
    for (int c: s7)
        cout << c << endl;

    string s8 {"test"};
    char s9[7] {"tester"};
    cout << (s8.at(0) == s9[0]) << endl;


    string s10 {"This is a test"};

    cout << s10.substr(5, 2) << endl;
    string s11 {s10, 5 , 2};
    cout << s11 << endl;

    string s12 {"Another test"};
    cout << s12.find("test") << endl;
    cout << s12.find("yo") << endl;
    cout << s12.rfind("er") << endl;

    cout << s12.erase(0, 2) << endl;
    cout << s12.erase(5, 5) << endl;
    // cout << s12.clear() << endl; // won't work, can't print void
}

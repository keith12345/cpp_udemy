#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <random>
#include <algorithm>
#include <time.h>
using namespace std;

string cipher(string str, unordered_map<char, char> cipher_map) {
    string out;
    for (char c: str) {
        out += cipher_map[c];
    }
    return out;
}

void print(std::vector <int> const &a) {
   std::cout << "The vector elements are : ";

   for(size_t i=0; i < a.size(); i++)
       std::cout << a.at(i) << ' ';
}

int main() {
    srand ( time(NULL) );
    unordered_map<char, char> mapper;
    unordered_map<char, char> unmapper;
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 ";
    vector<int> vec (63);
    for (unsigned short i {}; i < 63; i++) {
        vec.at(i) = i;
    }
    vector<int> rand_arr = vec;
    random_shuffle(rand_arr.begin(), rand_arr.end());
    for (int n: vec) {
        mapper[alphabet.at(n)] = alphabet.at(rand_arr[n]);
        unmapper[alphabet.at(rand_arr[n])] = alphabet.at(n);
    }

    cout << "Enter a message that you want passed through a cipher" << endl;
    string in;
    getline(cin, in);
    string cipher_string = cipher(in, mapper);
    cout << "The encrypter message is:\n" + cipher_string << endl;
    string decipher_string = cipher(cipher_string, unmapper);
    cout << "The message again once decrypted:\n" + decipher_string << endl;
}

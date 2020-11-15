// #include <iostream>
// using namespace std;

// int main() {
//     float j;
//     for (int i {1}, j {0.5} ; i <= 5 ; i++, j *= 2) {
//         cout << i << " * " << j << " : " << (i * j) << endl;
//     }
// }


//int main() {
//    int number {};
//
//    cout << "Enter an integer less than 100: " << endl;
//    cin >> number;
//
//    while (number >= 100) {
//        cout << "That's equal to or greater than 100! Try again: " << endl;
//        cin >> number;
//    }
//}


#include <iostream>
#include <vector>
using namespace std;

int main() {
    //---- WRITE YOUR CODE BELOW THIS LINE----
    vector<int> vec {1, 2, 3, 4, 5};
    int count {0};
    int s = vec.size();
    while (count < s && vec.at(count) != -99) {
        count++;
    }


    //---- WRITE YOUR CODE ABOVE THIS LINE----
    //---- DO NOT MODIFY THE CODE BELOW THIS LINE-----
    return count;
}

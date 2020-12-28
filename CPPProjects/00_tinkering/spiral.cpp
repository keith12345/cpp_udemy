#include <iostream>
using namespace std;

// void printer(int* a, int size) {
//     int i {0};
//     int j {0};
//     while (i < size and j < size) {
//         while (i < size) {
//             cout << a[i++][j] << " ";
//         }
//     cout << endl;
//     i = 0;
//     j++;
//     }
// }

int main() {
    int dim = {10};
    int arr[dim][dim] {};
    int to_place {dim*2};
    char last_direction {'u'};
    int i {0};
    int j {0};
    int counter {1};
    int placer = {0};
    while (to_place > 0 && i < dim && j < dim) {
        placer = to_place-- / 2;
        if (counter == 1) {
            arr[0][0] = counter++;
            placer -= 1;
        }
        if (last_direction == 'u') {
            for (int k = 0; k < placer; k++) {
                arr[i][++j] = counter++;
            }
            last_direction = 'r';
        } else if (last_direction == 'r') {
            for (int k = 0; k < placer; k++) {
                arr[++i][j] = counter++;
            }
            last_direction = 'd';
        } else if (last_direction == 'd') {
            for (int k = 0; k < placer; k++) {
                arr[i][--j] = counter++;
            }
            last_direction = 'l';
        } else if (last_direction == 'l') {
            for (int k = 0; k < placer; k++) {
                arr[--i][j] = counter++;
            }
            last_direction = 'u';
        }
    }
    cout << sizeof(*(arr[0])) << endl;
    i = 0;
    j = 0;
    while (i < dim) {
        while (j < dim) {
            cout << arr[i][j++] << " ";
        }
        cout << endl;
        j = 0;
        i++;
    }
}

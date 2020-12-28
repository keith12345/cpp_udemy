#include <iostream>
#include <vector>
using namespace std;

int* n_by_n_prod(int* a1, int* s1, int* a2, int* s2) {
    int* out {nullptr};
    out = new int[*s1 * *s2];
    int counter {0};
    for (int i = 0; i < *s1; i++) {
        for (int j = 0; j < *s2; j++) {
            out[counter++] = a1[i] * a2[j];
        }
    }
    return out;
}

void print_array(int* arr, int* size) {
    for (int i = 0; i < *size; i++)
        cout << arr[i] << " ";
}

int main() {
    int arr1[] {1, 2, 3, 4, 5};
    int arr2[] {10, 20, 30};
    int s1 {5};
    int s2 {3};
    int* res {nullptr};
    res = n_by_n_prod(arr1, &s1, arr2, &s2);
    int size {s1 * s2};
    print_array(res, &size);
    delete [] res;
}

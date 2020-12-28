#include <iostream>
using namespace std;

int main() {
    int n {10};
    cout << (&n)[4] << endl;
    int* p {&n};
    cout << p[4] << endl;

    int arr[] {1, 2, 3, 4, 5};
    p = &(arr[0]);
    cout << p[4] << endl;
    p = arr;
    cout << p[4] << endl;
    cout << *(&(arr[0])+4) << endl;
    cout << &(arr[0]) << endl;
    cout << (&(arr[0])+1) << endl;
    cout << (&(arr[0])+2) << endl;
    cout << (&(arr[0])+3) << endl;
    cout << (&(arr[0])+4) << endl;


    double d {10};
    cout << (&d)[4] << endl;
    double* pp {&d};
    cout << pp[4] << endl;

    double arr2[] {1.0, 2.0, 3.0, 4.0, 5.0};
    pp = &(arr2[0]);
    cout << pp[4] << endl;
    pp = arr2;
    cout << pp[4] << endl;
    cout << *(&(arr2[0])+4) << endl;
    cout << &(arr2[0]) << endl;
    cout << (&(arr2[0])+1) << endl;
    cout << (&(arr2[0])+2) << endl;
    cout << (&(arr2[0])+3) << endl;
    cout << (&(arr2[0])+4) << endl;
}

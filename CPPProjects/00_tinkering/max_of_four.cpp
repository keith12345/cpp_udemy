#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int max_of_four(int a, int b, int c, int d) {
    int max = 0;
    vector <int> vec {a, b, c, d};
    const int vec_size = vec.size();
    for (int i = 0; i < vec_size; i++) {
        if (vec.at(i) > max) {
            max = vec.at(i);
        }
    }
    return max;
}

int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    fflush(stdin);
    int ans = max_of_four(a, b, c, d);
    printf("%d \n", ans);
    fflush(stdin);

    return 0;
}

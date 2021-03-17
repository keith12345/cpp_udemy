#include <iostream>


class Test {
    public:
        static int count;
        int test = 1;
        Test() { count++; }

};

int Test::count = 0;

int main() {
    Test t = Test();
    Test tt = Test();
    std::cout << tt.count << std::endl;
    std::cout << t.count << std::endl;
}

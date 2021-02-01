#include <iostream>
#include <memory>
#include <vector>

class Test {
    private:
        int data;
    public:
        Test(int data=0)
            : data {data} {
                std::cout << "Test Constructor (" << data << ")" << std::endl;
            }
        int get_data() const {
            return data;
        }
        ~Test() {
            std::cout << "Test Desctructor (" << data << ")" << std::endl;
        }
};

int main() {
    Test* t0 = new Test {50};
    std::cout << (*t0).get_data() << std::endl;
    delete t0;
    std::unique_ptr<Test> t1 { new Test {100} };
    std::cout << (*t1).get_data() << std::endl;
    std::unique_ptr<Test> t2 = std::make_unique<Test>(150);
    std::cout << (*t2).get_data() << std::endl;
    //t1 = t2; // Not allowed to copy!!
    t1 = std::move(t2); // But this is allowed!
    if (!t2) {
        std::cout << "t2 is a nullptr" << std::endl;
    }
    std::unique_ptr<Test> t4 = std::make_unique<Test>(200);

    std::vector<std::unique_ptr<Test>> vec;
    //vec.push_back(t1); // would fail
    vec.push_back(std::move(t1));
    vec.push_back(std::move(t4));


    std::vector<std::unique_ptr<Test>> vec1;
    vec1.push_back(std::make_unique<Test>(10));
    vec1.push_back(std::make_unique<Test>(20));
    //for (auto t: vec1)            // would fail because it's making a copy!!
        //std::cout << (*t).get_data() << std::endl;
    for (const auto &t: vec1)
        std::cout << (*t).get_data() << std::endl;
}

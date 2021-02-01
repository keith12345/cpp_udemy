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
    std::shared_ptr<Test> ptr = std::make_shared<Test>(100);
    std::cout << "Use count: " << ptr.use_count() << std::endl;

    {
        std::shared_ptr<Test> ptr1 {ptr};
        std::cout << "Use count: " << ptr.use_count() << std::endl;
        {
            std::shared_ptr<Test> ptr2 {ptr};
            std::cout << "Use count: " << ptr.use_count() << std::endl;
            ptr.reset();
        }
        std::cout << "Use count: " << ptr.use_count() << std::endl;
        std::cout << "Use count: " << ptr1.use_count() << std::endl;
    }
    std::cout << "Use count: " << ptr.use_count() << std::endl;

    std::cout << "Vector stuff" << std::endl;
    std::vector<std::shared_ptr<Test>> vec;
    std::shared_ptr<Test> ptr4 = std::make_shared<Test>(400);
    std::shared_ptr<Test> ptr5 = std::make_shared<Test>(500);
    std::shared_ptr<Test> ptr6 = std::make_shared<Test>(600);
    vec.push_back(ptr4);
    vec.push_back(ptr5);
    vec.push_back(ptr6);
    std::cout << ptr4.use_count() << std::endl;
    std::unique_ptr<std::vector<std::shared_ptr<Test>>> vec2;
    vec2->push_back(ptr4);
}

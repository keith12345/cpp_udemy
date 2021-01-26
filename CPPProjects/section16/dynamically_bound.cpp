#include <iostream>
#include <memory>

class Base {
    public:
        virtual void say_hello() const {
            std::cout << "Hello - I am a base class" << std::endl;
        }
        virtual ~Base();
};

class Derived: public Base {
    public:
        void say_hello() const {
            std::cout << "Hello - I am a derived class" << std::endl;
        }
        virtual ~Derived();
};

class Double_Derived: public Derived {
    public:
        void say_hello() const {
            std::cout << "Hello - I am a deeper derivation" << std::endl;
        }
        virtual ~Double_Derived();
};

void greetings(const Base& obj) {
    std::cout << "Greetings:" << std::endl;
    obj.say_hello();
}

int main() {
    Base b;
    b.say_hello();
    Derived d;
    d.say_hello();

    greetings(b);
    greetings(d);

    Base* ptr = new Derived();
    ptr->say_hello();

    std::unique_ptr<Base> ptr1 = std::make_unique<Derived>();
    ptr1->say_hello();

    Base* dd = new Double_Derived();
    dd->say_hello();

    greetings(*dd);
}

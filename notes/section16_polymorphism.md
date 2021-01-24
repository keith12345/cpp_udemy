# Polymorphism

## What is Polymorphism

* Polymorphism
    * compmlile-time / early binding / static binding - all ways of saying "before the program runs"
    * run-time / late binding / dynamic binding - all ways of saying "while the program runs"
* Runtime polymorphism
    * being able to assign different meanings to the same function at run-time
* Allows us to program more abstractly
    * Let c++ figure out which function to call at run-time
* Not the default int c++, run-time polymorphism is achieved via:
    * inheritance
    * base class pointers of references
    * virtual functions


Polymorphism is considered fundamental to OOP.
Overloading functions and operators are examples of polymorphism.

If something occurs at compile-time instead of runtime, the program will be faster when it actually runs. 
But sometimes we want to sacrifice some speed for flexibility...

### Types of Polymorphism

* Compile time
    * function overloading
    * Operator overloading
* Run-time
    * Function overriding

Non-polymorphic example using static binding using the following class hierarchy:
```
                ------------
                | Account  |
                ------------
                | withdraw |
                ------------
                      ^
                      |
           -----------------------
           |                     |
     ------------          ------------
     | Savings  |          | Checking |
     ------------          ------------
     | withdraw |          | withdraw |
     ------------          ------------
           ^      
           |      
     ------------ 
     |  Trust   | 
     ------------ 
     | withdraw | 
     ------------ 
```

Example 1:
```c++
Account a;
a.withdraw(1000);           // Account::withdraw()

Savings b;
b.withdraw(1000);           // Savings::withdraw()

Checking c;
c.withdraw(1000);           // Checking::withdraw()

Trust d;
d.withdraw(1000);           // Trust::withdraw()

Account* p = new Trust();
p->withdraw(1000);          // Account::withdraw()
                            // should be
                            // Trust::withdraw()

```

Because `p` is a pointer to an Account object, it contains the address of an account object. Because `p` "is-a" account,
it is able to hold the `Trust` object.  
But when we call methods off of `p`, it's thinking of `p` as `Account`, not `Trust`, which "is-a" type of account, so it
will call the `Account` `withdraw` method.

What's happened here is that the compiler has "bound" the the `Account::withdraw()` method to `p` at compile time.


Example 2:
```c++

void display_account(const Account& acc) {
    acc.display(); // will always use Account::display()
    // note that none of the objects were even pointers!
    // They were simply passed by reference!
}

Account a;
a.display(1000);

Savings b;
b.display(1000);

Checking c;
c.display(1000);

Trust d;
d.display(1000);
```

To avoid only calling the `Account::display_account()` method, you can check to see what type of account it is and then
call the correct method if a `switch` or `if`/`else` block.  
That said, it's pretty ugly, not abstract, and wouldn't be able to handle new functions.

To cleanly handle any potential object, you'd need to use run-time/dynamic polymorphism.  

The actual code blocks above remain the same, you simply change how the class is built.

To do this, you use virtual functions, which tells the compiler not to bind the call at compile time, but instead defer
the binding to run-time.  
The program will determine exactly what `p` is pointing to, and call the relevant method.


```c++
#include <iostream>

class Base {
    public:
        void say_hello() const {
            std::cout << "Hello - I am a base class" << std::endl;
        }
};

class Derived: public Base {
    public:
        void say_hello() const {
            std::cout << "Hello - I am a derived class" << std::endl;
        }
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
    delete ptr;

    std::unique_ptr<Base> ptr1 = std::make_unique<Derived>();
    ptr1->say_hello();
    // Smart pointers delete themselves
}

// Hello - I am a base class
// Hello - I am a derived class
// Greetings:
// Hello - I am a base class
// Greetings:
// Hello - I am a base class
// Hello - I am a base class
// Hello - I am a base class
```

Even smart pointers can't help but to be statically bound!


## Using a Base Class Pointer

As we've gone over above, in order to  use polymorphism, we must be using a base class pointer or a base class
reference, and we must declare the methods we want bound dynamically as virtual functions.

## Virtual Functions

* Redefined functions are bound statically
    * The Base class method will be defaulted to 
* Overridden functions are bound dynamically
    * This is when we declare that a function is `virtual`
    * Virtual functions are overridden functions
* Virtual functions are overridden
* Allows us to treat all objects generally as objects of the Base class


The below code is the same as the above except for the inclusion of the `virtual` keyword:  
```c++
#include <iostream>
#include <memory>

class Base {
    public:
        virtual void say_hello() const {
            std::cout << "Hello - I am a base class" << std::endl;
        }
};

class Derived: public Base {
    public:
        void say_hello() const {
            std::cout << "Hello - I am a derived class" << std::endl;
        }
};

class Double_Derived: public Derived {
    public:
        void say_hello() const {
            std::cout << "Hello - I am a deeper derivation" << std::endl;
        }
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

// Hello - I am a base class
// Hello - I am a derived class
// Greetings:
// Hello - I am a base class
// Greetings:
// Hello - I am a derived class
// Hello - I am a derived class
// Hello - I am a derived class
// Hello - I am a deeper derivation
// Greetings:
// Hello - I am a deeper derivation
```

Note that only the base-most class needs to declare the function as virtual and all subsequent derivations will treat it
as a virtual function. This is referred to as being implicitly virtual.  
However, it's seen as best practice to always indicate that derived methods are virtual.  

Note that the virtual keyword is required both in the prototype in the header file and the function definition. Without
it it would be considered a redefinition.

## Virtual Desctructors

Whenever you have virtual functions you also need virtual destructors.

* Problems can happen when we destroy polymorphic objects
* If a derived class is destroyed by deleting its storage via the base class pointer, and the class uses a non-virtual destructor, then the behavior is undefined in the c++ standard.
* Derived objects must be destroyed in the correct order (starting at the correct desctructor!)

How do we solve this?

*  If a class has virtual fuctions, always provide a public virtual destructor
*  If the base class destructor is virtual, all derived classes destructors must be virtual.

The problem is that, when destructors are called, the program simply doesn't know which to destructor is the right one
to call so, it'll play it safe, and call the base desconstructor.

With virtual destructors, just like virtual functions, you only need to declare it in the base class. However, again,
just like virtual functions, it's best pratice to declare it each time.

Note that virtual constrcutors are not a thing.

## Override Specifier

* We can override base class virtual functions
* The function signature and return must be EXACTLY the same
* if they are different then we have _redefinition_ and **not** _overriding_ (or maybe just a definition!)
    * Remember the "redefined" functions are statically bound at compile-time as opposed to "overridden" functions which are dynamically bound at run-time
    * Even something like not include `const` somewhere will be a redefinion!
* You can address the potential for silly mistakes with the override specifier with ensures that you overriding and not redefing.
    * This is a c++11 addition

```c++
#include <iostream>
#include <memory>

class Base {
    public:
        virtual void say_hello() const {
            std::cout << "Hello - I am a base class" << std::endl;
        }
        virtual ~Base() {};
};

class Derived: public Base {
    public:
        void say_hello() {
            std::cout << "Hello - I am a derived class" << std::endl;
        }
        virtual ~Derived() {};
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
}

// Hello - I am a base class
// Hello - I am a derived class
// Greetings:
// Hello - I am a base class
// Greetings:
// Hello - I am a base class
// Hello - I am a base class
// Hello - I am a base class
```

If we add the override specifier but the prototype doesn't match a base class prototype, you'll get the following
warnings/errors for the base and derived prototypes respectively:

```
Hidden overloaded virtual function 'Base::<function_name>' declared here: different qualifiers ('const' vs unqualified)  override_specifier.cpp:14:26: error: non-virtual member function marked 'override' hides virtual member function

'void Derived::<function_name>()' marked 'override', but does not override
```

```c++
#include <iostream>
#include <memory>

class Base {
    public:
        virtual void say_hello() const {
            std::cout << "Hello - I am a base class" << std::endl;
        }
        virtual ~Base() {};
};

class Derived: public Base {
    public:
        void say_hello() const override {
            std::cout << "Hello - I am a derived class" << std::endl;
        }
        virtual ~Derived() {};
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
}

// Hello - I am a base class
// Hello - I am a derived class
// Greetings:
// Hello - I am a base class
// Greetings:
// Hello - I am a derived class
// Hello - I am a derived class
// Hello - I am a derived class
```

## Final Specifier

* When used at the class level - prevents a class from being derived from
    * Can be done for better compiler optimization or to ensure that objects are copied safely without slicing.
* when used at the method level - prevent virtual method from being overridden in the derived class
    * Also done for better compiler optimization.


```c++
class My_Class final {
    . . . 
    // cannot be derived from
};

class Derived final: Public Base{
    . . . 
    // cannot be derived from
};
```

Trying derive from the above and compile will result in a compiler error.

Note that different compilers can compile virtual functions slightly differently from each other. 

## Pure Virtual Functions and Abstract Classes

* Abstract class
    * Cannot instantiate objects
        * If you have an abstract class `Shape`, you can't directly instantiate Shape objects... You need to Derive a class, (maybe `Square`?) which you could then instantiate.
    * These classes are used as base classes in inheritance hierarchies
    * Often referred to as "Abstract Base Classes"
* Concrete classes
    * These are classes that you can instantiate from (but might still be too general for you to want to)
    * All of their member functions are defined.
        * Account -> Checking Account
        * Character -> Boss


What makes it an Abstract Base Class?  
It must contain at least one pure virtual function.

### Pure Virtual Functions

* Used to make a class abstract
* Specified with `=0` in its declaration
    * `virtual void func() = 0;`
    * Whatever class has this function is now an Abstract Base Class and cannot be instantiated
* Typically does not provide implementation
    * Typically up to the derived Concrete class to define this behavior.
    * That said, it is possible to give them an implementation


How to derive a class from an Abstract Base Class such that it becomes a concrete class?  

* Derived class **must** override the virtual functions from the base class
    * If the derived class does not do this it is also an Abstract class
    * In a way it provides a checklist of functions that must be declared for the object to be a concrete class. 

```c++
Shape shape;                    // Would not work
Shape* ptr = new Shape();       // Would not work

Shape* ptr = new Circle();       // Would work
ptr->draw();                     // Would work
ptr->rotate();                   // Would work
```
 

```c++
#include <iostream>
#include <vector>

class Shape {
    private:
    public:
       virtual void draw() const = 0;
       virtual void rotate() const = 0;
       //virtual void flip() const = 0;
       virtual ~Shape() {};
};

class Rectangle: public Shape {
    public:
        virtual void draw() const override {
            std::cout << "------\n|    |\n------" << std::endl;
        }
        virtual void rotate() const override {
            std::cout << " -\n| |\n| |\n| |\n| |\n -" << std::endl;
        }
        virtual ~Rectangle() {};
};


class Square: public Shape {
    public:
        virtual void draw() const override {
            std::cout << " ----\n|    |\n|    |\n ----" << std::endl;
        }
        virtual void rotate() const override {
            std::cout << " ----\n|    |\n|    |\n ----" << std::endl;
        }
        virtual ~Square() {};
};

int main() {
    // Shape s; // cannot declare variable 's' to be of abstract type 'Shape'
    Shape* rect = new Rectangle();
    rect->draw();
    rect->rotate();

    Shape* sqr = new Square();

    std::vector<Shape*> shapes {rect, sqr};

    for (const Shape* s: shapes) {
        std::cout << "Printing Shape:" << std::endl;
        s->draw();
        std::cout << "Printing rotated Shape:" << std::endl;
        s->rotate();
    }

}

// ------
// |    |
// ------
//  -
// | |
// | |
// | |
// | |
//  -
// Printing Shape:
// ------
// |    |
// ------
// Printing rotated Shape:
//  -
// | |
// | |
// | |
// | |
//  -
// Printing Shape:
//  ----
// |    |
// |    |
//  ----
// Printing rotated Shape:
//  ----
// |    |
// |    |
//  ----
```

If we uncommented `virtual void flip() const = 0;` we'd get the following warning and error:  
``` 
Unimplemented pure virtual method 'flip' in 'Rectangle'  pure_virtual_funcs_abcs.cpp:25:23: error: allocating an object of abstract class type 'Rectangle'

invalid new-expression of abstract class type 'Rectangle' 
```

## Abstract Classes as Interfaces

What does it mean to use a class as an interface?

* An abstract class that has only pure virtual funtions
    * These functions provide a general set of services to the user of the class
    * (They are provided as public)
* Each subclass is free to implement these services as needed
* Every service (method) must be implemented
* The service type information is strictly enforced


c++ does not provide true interfaces.  
Abstract base classes and Pure Virtual Functions are used to achieve this end.

> In java, abstract classes are used for partial abstraction. 
> Unlike abstract classes, interfaces are used for full abstraction.
>
> Abstraction - a process by which you show only "relevant" data and "hide" unnecessary details of an object from the
> user.

In java, methods in abstract classes can have a body, while they do not in c++ (right?).  
Only in interfaces in java are methods guaranteed not to have a body.


Sometimes interfaces classes are preceded with a capital "I" simply to indicate that they are an interface class:  
```c++
class I_Shape {
    public:
        . . . 
};
```

```c++
#include <iostream>

class I_Printable {
        friend std::ostream& operator<<(std::ostream &os, const I_Printable& obj);
    public:
        virtual void print(std::ostream& os) const = 0;
};

std::ostream& operator<<(std::ostream& os, const I_Printable& obj) {
    obj.print(os);
    return os;
}

class Account: public I_Printable {
    public:
        virtual void withdraw(double amount) {
            std::cout << "In Account::withdraw" << std::endl;
        }
        virtual void print(std::ostream& os) const override {
            os << "Account dipslay" << std::endl;
        }
        virtual ~Account() {};
};

class Checking_Account: public Account {
    public:
        virtual void withdraw(double amount) override {
            std::cout << "In Checking_Account::withdraw" << std::endl;
        }
        virtual void print(std::ostream& os) const override {
            os << "Checking_Account dipslay" << std::endl;
        }
        virtual ~Checking_Account() {};
};

int main() {
    Account* acc = new Account();
    std::cout << *acc << std::endl;
    Account* acc2 = new Checking_Account();
    std::cout << *acc2 << std::endl;
    I_Printable* acc3 = new Checking_Account();
    std::cout << *acc3 << std::endl;
    //acc3->withdraw(100.0); // Will not work
    acc2->withdraw(100.0);
}

// Account dipslay
// 
// Checking_Account dipslay
// 
// Checking_Account dipslay

```

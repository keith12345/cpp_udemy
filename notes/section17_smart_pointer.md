# Smart Pointers

## What are they

* Objects
* Can only point to heap-allocated memory
* automatically call delete when no longer needed
* Adhere to RAII principles

Smart Pointer Types:

* Unique Pointers `unique_ptr`
* Shared pointers `shared_ptr`
* weak pointers `weak_ptr`
* auto pointers `auto_ptr` - Deprecated


## Basic usage

Uses `memory` header:  
```c++
#include <memory>
```

Defined by class templates
* Wrapper around raw pointer
* Overloaded operators
    * `*` dereference
    * `->` member selection
    * Pointer arithmetic not supported
        * `++`
        * `--`
        * etc.
* Can have custom deleters


Not that different compilers handle raw pointers differently (advanced).

```c++
{
    std::smart_pointer<Some_Class> ptr = ...

    ptr->method();
    cout << (*ptr) << endl;
}
// pointer destroyed
```

## RAII

RAII - Resource Acquisition Is Initialization

* Common idiom or pattern used in software design based on container object lifetime
* RAII objects are allocated on the stack
* Resource Acquisition - Just doing a basic thing like:
    * Open a file
    * allocate memory
    * acquire a lock
* Is initialization
    * The resource is acquired in a constructor
* Resource relinquishing
    * happens in the destructor
        * Close the file
        * De-allocate the memory
        * Release the lock

Smart Pointers are examples of RAII classes as RAII is the idiom they follow with regard to memory resources. 

## unique_ptr

Simple and efficient smart pointer.

`unique_ptr<T>`
* Pointer to an object of type `T` on the heap
* It is unique - the can only be one `unique_ptr<T>` pointer pointing to the object on the heap
* Owns what it points to
* Cannot be assigned or copied
* CAN be moved
    * Makes them great for placing in things like vectors
* When the pointer is destroyed, what it points to is automatically destroyed


`unique_ptr` - creating, initializing, and using

```c++
{
    std::unique_ptr<int> p1 { new int {100} };
    std::cout << *p1 << std::endl;      // 100
    *p1 = 200
    std::cout << *p1 << std:::endl;     // 200
}
```

Note that you can refer to the same spot in memory with both a smart pointer and a raw pointer but this is considered to
be bad practice.  

```c++
{
    std::unique_ptr<int> p1 { new int {100} };
    std::cout << p1.get() << std::endl;      // Will return a memory address
    p1.reset();                              // p1 is not a nullptr
    if (p1):
        std::cout << *p1 << std:::endl;      // Won't execute
}
```

the `get()` method isn't usually necessary but can come in handy if you're working with libraries that use raw pointers.

### One way to initialize

```c++
{
    std::vector<std::unique_ptr<int>> vec;
    std::unique_ptr<int> ptr { new int {100} };
    vec.push_back(ptr);            // Error - copy not allowed
    vec.push_back(std::move(ptr)); // allowed!!
}
```

### concise smart pointer initialization

```c++
{
    std::unique_ptr<int> p1 = make_unique<int>(100);
    std::unique_ptr<Account> p2 = make_unique<Account>("Keith", 5000);
    auto p3 = make_unique<Player>("Hero", 100, 100);
}
```

### Comparing Approaches

```c++
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

// Test Constructor (50)
// 50
// Test Desctructor (50)
// Test Constructor (100)
// 100
// Test Constructor (150)
// 150
// Test Desctructor (100)
// t2 is a nullptr
// Test Constructor (200)
// Test Constructor (10)
// Test Constructor (20)
// 10
// 20
// Test Desctructor (10)
// Test Desctructor (20)
// Test Desctructor (150)
// Test Desctructor (200)
```

## Shared Pointers

* Provides shared ownership of heap objects
* `shared_ptr<T>`
    * Points to an objects of type `T` on the heap
* It is not unique - there can be many `shared_ptr`s pointing to the same object on the heap
* Establishes shared ownership relationship
* CAN be assigned AND copied
* CAN be moved
* Doesn't support managing arrays by default
* When the use is zero, the managed object on the heap is destroyed

```c++
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> p1 { new int {100} };
    std::cout << p1.use_count() << std::endl;       // 1

    std::shared_ptr<int> p2 {p1};
    std::cout << p1.use_count() << std::endl;       // 2
    std::cout << p2.use_count() << std::endl;       // 2

    p1.reset();
    std::cout << p1.use_count() << std::endl;       // 0
    std::cout << p2.use_count() << std::endl;       // 1

    std::vector<std::shared_ptr<int>> vec;
    std::shared_ptr<int> ptr { new int {100} };
    vec.push_back(ptr);                             // We just made a copy!
    std::cout << ptr.use_count() << std::endl;      // 2
}
```

Quick note on history: 
* Make unique is somewhat recent, introduced in c++ 14
* Make shared has been around a bit longer, c++ 11

Quick note on syntax:
While both of the below do the same thing
```c++
std::shared_ptr<int> p1 { new int {100} };
std::shared_ptr<int> p2 = std::make_shared<int>(100);
```
the compiler is apparently able to generate more efficient code when `make_shared` is used.

## Weak Pointer

* Provides a non-owning "weak" reference
* `weak_ptr<T>`
    * pointers to an objects of type `T` on the heap
* Does not participate in owning relationship
* always created from a `shared_ptr`
* Does NOT increment of decrement reference use count
    * In other words, they don't effect the lifetime of the objects to which they point
* Use to prevent strong reference cycles which could prevent objects from deleting
* Can be useful for things like iterator pointers that traverse through a list of nodes
    * It doesn't own them, just visits the temporarily

### Avoiding circular references

Sometimes you can have two classes where each class refers to the other:
* A refers to B
* B refers to A
* Shared ownership prevents heap de-allocation

```
             A                         B
    |---------------|      |---------------|
    | shared_ptr<B> | ---> |               |
    |               | <--- | shared_ptr<B> |
    |---------------|      |---------------|
```

Note that when these two objects go out of scope, they will be destroyed from the stack, but the allocation of heap
memory will persist. Each of these references keep the other alive.

```
            A                      B
    |---------------|      |-------------|
    | shared_ptr<B> | ---> |             |
    |               | <--- | weak_ptr<B> |
    |---------------|      |-------------|
```

Now, because `weak_ptr` doesn't count toward the `shared_ptr.use_count()`, it will know to be deleted when the object is
deleted from the stack after going out of scope.

#### Example circular reference:

```c++
#include <iostream>
#include <memory>

class B;

class A {
    private:
        std::shared_ptr<B> b_ptr;
    public:
        void set_B(std::shared_ptr<B>& b) {
            b_ptr = b;
        }
        A() { std::cout << "A Constructor" << std::endl; }
        ~A() { std::cout << "A Deconstructor" << std::endl; }
};

class B {
    private:
        std::shared_ptr<A> a_ptr;
    public:
        void set_A(std::shared_ptr<A>& a) {
            a_ptr = a;
        }
        B() { std::cout << "B Constructor" << std::endl; }
        ~B() { std::cout << "B Deconstructor" << std::endl; }
};

int main() {
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();
    a->set_B(b);
    b->set_A(a);
}

// A Constructor
// B Constructor
// Note that the deconstructors were never called!!!!
```

To solve this problem we simply change one of the pointers to a weak pointer:
```c++
#include <iostream>
#include <memory>

class B;

class A {
    private:
        std::shared_ptr<B> b_ptr;
    public:
        void set_B(std::shared_ptr<B>& b) {
            b_ptr = b;
        }
        A() { std::cout << "A Constructor" << std::endl; }
        ~A() { std::cout << "A Deconstructor" << std::endl; }
};

class B {
    private:
        std::weak_ptr<A> a_ptr;   // Here ya go!!
    public:
        void set_A(std::shared_ptr<A>& a) {
            a_ptr = a;
        }
        B() { std::cout << "B Constructor" << std::endl; }
        ~B() { std::cout << "B Deconstructor" << std::endl; }
};

int main() {
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();
    a->set_B(b);
    b->set_A(a);
}

// A Constructor
// B Constructor
// A Deconstructor
// B Deconstructor
```

## Custom Deleters

_Note that this is relatively uncommon_

* Sometimes when we destroy a smart pointer we need more than to just destroy the object on the heap...
* c++ smart pointers allow you to provide custom deleters
* Lots of ways to achieve this:
    * Functions
    * Lambdas
    * ...


Note that if you use custom deleters, you can't use `make_shared` or `make_unique` when instantiating your object. The 
thinking is that if you need a specialized way to delete your objects, you probably also need a specialized way to
create them.

Custom deleter using a fuction:
```c++
void my_deleter(Some_Class *raw_pointer) {
    // your fancy deleter code
    delete raw_pointer;
}

shared_ptr<Some_Class> ptr { new Some_Class{}, my_deleter };
```

Custom deleter as a lambda expression:
```c++
std::shared_ptr<int> n1 ( new int {20}, [] (int* ptr) {
        std::cout << "Using lambda deleter" << std::endl;
        delete ptr;
    }
);
```

This can come in handy if you're using pointers to C structures in C frameworks which don't have destructors. This
allows you to properly manage that memory while still using shared/unique pointers and such. 

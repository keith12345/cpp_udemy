# Pointers and References

What is a pointer? Simply a variable.

Other variables and even functions can be at the address that a pointer is pointing to.

Like other variables, the variable that a pointer is pointing to must have a type.

If a pointer points to a variable or function directly... why not just use it directly?  
If you can, you should... But, when accessing data that's outside of a particular function, it's more efficient to point to that data.

Pointers are more efficient... especially when it comes to accessing members of arrays.

Memory can be allocated dynamically from the heap or the free store dynamically at run time. That memory doesn't have a variable name associated with it, so, the only way to access it is through a pointer. 

If you're working with embedded systems, devices drivers, or other systems software, sometimes you need to access a specific memory address or range of memory addresses. The best way to do that is with pointers.

```c++
// declaring a pointer variable
int *x;
double *y
char *c;
string *s;
```

Note that all pointer variables should be initialized during declaration. Otherwise, they'll have garbage data.


```c++
int *x {};
double *y {nullptr};
char *c {nullptr};
string *s {nullptr};
```

An unitialized pointer will just point to any random location. You could point to some location in memory and accidentally corrupt critical files. `nullptr` allows us to point **nowhere**, which is much different from pointing **anywhere**. 

`nullptr` was introduced in c++11 and represents address `0`. 

## Accessing pointer address

Two important operators:  
* `&` - address of operator
* '*' - indirection operator (also called the dereferencing operator)

Both unary operators.  
The address of operator allows you to access the address of the operand. The address that you're evaluating to must be a "l-value"; it must be contents.

Initializing a pointer to the address of an l-value:  
```c++
int* p {nullptr};
int x {10};
p = &x;
```

```c++
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int* p;
    cout << "Value stored at *p is " << *p << endl;
    cout << "The address of *p is " << &p << endl;
    cout << "The address that *p is pointing to is " << p << endl;
    cout << "The size of *p is " << sizeof(p) << endl;
    p = {nullptr};
    cout << "Setting p to a nullptr." << endl;
    cout << "The address that *p is pointing to is " << p << endl;

    int n {10};
    cout << "Declaring and initializing a new variable, n" << endl;
    cout << "The value of n " << n << endl;
    cout << "The memory address of n " << &n << endl;
    p = &n;
    cout << "Setting p - &n" << endl;
    cout << "The value of p " << p << endl;
    cout << boolalpha;
    cout << "p == &n " << (p == &n) << " and *p == n " << (*p == n) << endl;
}

// Value stored at *p is 1
// The address of *p is 0x7ffd9ea96f80
// The address that *p is pointing to is 0x7ffd9ea97070
// The size of *p is 8
// Setting p to a nullptr.
// The address that *p is pointing to is 0
// Declaring and initializing a new variable, n
// The value of n 10
// The memory address of n 0x7ffd08bca2cc
// Setting p - &n
// The value of p 0x7ffd08bca2cc
// p == &n true and *p == n true

```

Note that all pointers, regardless of what they're pointing to, take up the same amount of space. They could point to an object that's 100 gigs.. when when you do `sizeof(some_pointer)` it will always be the same amount (`8` bytes on my machine, `4` bytes on the instructor's machine).

A pointer **is not the thing that it points to**.... It is a pointer... It is its own type. It is just a variable. 

All pointers that we've declared so far are typed pointers. The alternative would be to have a `void pointer`. They're used more in C, apparently.

I feel like one of the most important, if not the most important thing to remember about pointers and references, is that a _variable_ is simply a _dereferenced reference_ to an l-value.

You can also think of the `sizeof()` operator not actually showing the size of a variable, but rather the size of the location in memory that a variable is referencing. 

People give c++ a hard time for using `*` to both deference and declare pointers... it be what it be. 

## Dynamic Memory Allocation:

Certain tools, like vectors (vs. arrays) and strings (vs. c-style strings) handle this for us. But there may be times 
when you need to allocated memory dynamically from the heap manually. 

All memory that's allocated dynamically via a pointer comes from the heap or the free-store. 

The `new` keyword is used to allocate storage at run-time:  
```c++
int* int_ptr {nullptr};
int_ptr = new int; // allocates an integer on the heap
delete int_ptr; // make sure this is an address that was allocated using `new`... not sure what happens if it's not.. 

int* array_ptr {nullptr}; 
array_ptr = new int[size];
delete [] array_ptr;
```

Note that when you're done with the variable in question, you must deallocate the storage so that it's available to the rest of the program. 

```c++
#include <iostream>
using namespace std;

int main() {
    int* p {nullptr};
    p = new int;
    *p = 10;
    cout << *p << endl;
    delete p;
}
```

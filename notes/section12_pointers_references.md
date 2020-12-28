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
* `*` - indirection operator (also called the dereferencing operator)

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
    cout << "address of a pointer: " << &p << endl;

    int* q {nullptr};
    q = p;
    cout << "p and q: " << p << " " << q << endl;
    int** r {nullptr};
    r = &p;
    cout << "r " << r << endl;
    cout << "de-reference *r " << *r << endl;
    cout << "Double de-reference **r " << **r << endl;
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
// address of a pointer: 0x7ffe8aafa210
// p and q: 0x7ffe8aafa20c 0x7ffe8aafa20c
// r 0x7ffe8aafa210
// de-reference *r 0x7ffe8aafa20c
// Double de-reference **r 10

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

### **Warning**

If instead of doing `delete p;` we did `p = nullptr;` we would eliminate our ability to access that location in memory without actually making that memory available.

This would be a memory leak and can lead to inefficient code.

## An interesting relationship between arrays and pointers

All that an array is is a reference to a location in memory. The values of the array are locations relative to that location in memory... So, can we trick c++ into thinking that a reference to a variable of some type is actually is actually an array of the type of that variable?

```c++
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
}

// 21944
// 21944
// 5
// 5
// 5 // Note that in this example we're increasing the memory location by 4 integers... not for bits. See below
// 0x7ffcf09af310
// 0x7ffcf09af314
// 0x7ffcf09af318
// 0x7ffcf09af31c
// 0x7ffcf09af320

```

This happens because arrays aren't really arrays... They're just pointers to the address of the starting location of a block of memory.

There are actually names for this... 
* Array offset
* pointer offset
* subscript notation (normal [] subscripting)
* offset notation ( *(some_array/pointer + index) )

Note that array and pointer offset will automatically increment memory addesses according to the variable type at the first index of the array.

## Pointer Arithmetic

Only makes sense when you're using raw arrays. 

The increment and decrement operators (`++`, `--`) can be used to traverse arrays:  
```c++
int_ptr++;
int_ptr--;
```

The `int_ptr` variable will be incremented so that it points to the next element in contiguous memory. Increments will be of the variable type's size. 

You can also:  
```c++
int_ptr += n;
```

and even:  
```c++
int n = int_ptr1 - int_ptr2;
```
As long as the two pointers are of the same data type. 


Apparently a fairly common behavior is to dereference and increment a pointer in the same step. 
```c++
#include <iostream>
using namespace std;

int main() {
    int arr[] {1, 2, 4, 5, 6, -1};
    int* p {arr};
    while (*p != -1) {
        cout << *p++ << endl;
    }

}
```

Note that `(*p)++ != *p++`. In the first we're accessing the value at the pointer and then incrementing it. In the next, we're incrementing the pointer itself. 

## Passing pointers to a function

There severals ways that you can use constants and pointers together:
* pointers to constants
* pointers that are constants and point to non-constants
* pointers that are constants and point to constants 

```c++
#include <iostream>
using namespace std;

int main() {
    int n {10};
    int* const p {&n};
    *p += 1; // does work
    int m;
    p = &m; // will throw a read-only compiler error
}
```

## Passing pointers to a function

```c++
void double_data(int *p)
void double_data(int *p) {
    *p *= 2;
}

int main() {
    int n {10};
    double_data(&n);
    cout << n << endl; // returns 20
    int* p {nullptr};
    p = &n;
    double_data(p);
    cout << n << endl; // returns 40
}
```

## Returning a Pointer from a function

Returns a type as specified in the function declaration:
```c++
int* max(int* i, int* j) {
    int* out {nullptr};
    if (*i > *j) 
        out = i;
    else
        out = j;
    return out;
}

int main() {
    int a {10};
    int b {20};
    int* largest_int {nullptr};
    largest_int = max(&i, &j);
    cout << largest_int << endl;
}
```

You can also return a pointer by returning dynamically allocated memory.

```c++
int* create_array(size_t size, int init_value = 0) {
    int* new_storage {nullptr};

    new_storage = new int[size];
    for (size_t i = 0; i < size; i++)
        *(new_storage + i) = init_value; 
    return new_storage;
}
```

using pointer offset notation but could also use pointer subscript

Note that you should **never** return addresses of or pointers to local variables. Local variables are stored on the stack
and disappear once the function is terminated. 

## Potential Pointer Pitfalls

* uninitialized pointers
* dangling pointers
    * pointer that is pointing to released memory
    * might happen when:
        * 2 pointers point to the same data
        * 1 pointer releases the data with delete
        * the other pointer accesses the released data
    * or:
        * pointer points to memory that is invalid (pointer pointing to local variable that no longer exists) 
* not checking if `new` failed to allocate memory
    * if this happens, an exception should be thrown, terminating your program
    * dereferencing a pointer that's pointing to null will crash a program.
* leaky memory
    * forgetting to release allocated memory with delete
        * if you lose your pointer to the storage allocated on the heap you have no way to get that storage again
    * memory is orphaned - a memory leak results in an orphaned block of memory.
    * Sounds like this sort of thing applies mostly (if not entirely) to memory that's allocated dynamically on the heap.
    * Not as much of an error nowadays because we have so much more memory but still not good.

Smart pointers:
More in the section on OOP

## More on references

what is a reference:
* alias for a variable
* must be initialized to a variable when declared
* cannot be null
* once iniitlaized cannot be to refer to a different variable
* very useful as function parameters
* might be helpful to think of a reference as a constant pointer that is automatically deferenced when it's used.

References and pointers sound similar but they're not.  
A reference is an alias for a variable. Whenever you use a reference, you're using the variable is refers
to. 

When you use a range-based for-loop without references, you'r only modifying a copy of the data. See below
```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nums {1, 2, 3};

    for (int n: nums) {
        n += 1; // Will actually give a warning, "n set but never used", because we're only changing the copy
    }

    for (int n: nums) {
        cout << n << " "; // 1, 2, 3
    }
}
```

But, when you use the address-of operator, you create a reference and can access that data directly:  

```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nums {1, 2, 3};

    for (int &n: nums) {
        n += 1;
    }

    for (int n: nums) {
        cout << n << " "; // 2, 3, 4
    }
}
```

Similar to pointers, if we want to be memory efficient but don't want to risk mutation, you can declare the reference a `const`.

```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nums {1, 2, 3};

    for (int const &n: nums) {
        n += 1; // will throw a compiler error
    }

    for (int const &n: nums) {
        cout << n << " "; // but would print faster/more efficiently
    }
}
```

A reference is another variable name for the same memory location. It doesn't have its own memory address. On the other hand, a pointer has its own memory location, and the value that it stores is the memory location of the thing that it's pointing to. 

References are constants in that the location in memory that they're pointing to cannot be changed.

## l-value and r-value

l-values:
* value that have names and are addressable
* modifiable if they are not constants
r-values:
* can be defined by exclusion... anything that's not an l-value is an r-value
* a literal
* temporary value 

Weird ways you might screw with references and r-values: 
```c++
#include <iostream>
using namespace std;

int square(int &n) {
    return n*n;
}

int main() {
    int num {10};

    cout << square(num) << endl; // gives you 100, no problem

    cout << square(5) << endl; // Error- can't reference an r-value
}
```

## When to use which:

### pass by value:
* when the function does not modify the actual parameter
* the parameter is small and efficient to copy like simple types (int, char, double, etc.)

### Pass by reference using a pointer
* when the function does modify the actual parameter
* and
* the parameter is expensive to copy
* and
* it's okay for the pointer to have a nullptr value (important at the end of lists and trees)

### Pass by reference using a pointer to `const`
* when the function does not modify the actual param
* and
* the param to expensive to copy
* and 
* it's okay for the pointer to be a nullptr


### Pass by reference using a pointer to `const`
* when the function does not modify the actual param
* and
* the param to expensive to copy
* and 
* it's okay for the pointer to be a nullptr
* and
* you don't want to modify the pointer itself

### references as parameters
* when the function does modify the actual param
* and
* the param is expensive to copy
* and
* the param will nevr be nullptr

### pass-by-reference using a `const` reference
* when the function does not modify the actual param
* and
* the parameter is expensive to copy
* and
* the param will never be nullptr


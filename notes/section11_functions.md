# Functions

## Random

The `<random>` header file is seen as the most robust RNG in c++ but `<cstdlib>` has it's own version.  

Random number generators are _not_ randomly seeded by default in c++; to see you should use the following:  
```c++
#include <cstblib>
#include <ctime>

srand(time(nullptr))
```

Not sure if this is required for the `<random>` header or just `<cstdlib>`.

Different systems actually have their own maximum random number which you can actually access via a constant.

```c++
#include <iostream>
using namespace std;

int main() {
    cout << RAND_MAX << endl;
}

// 2147483647
```

## Why declare types

Types need to be declared in c++ because all of the information needs to be known at compile time because functions are built to take and give certain types of input/output... and because code is not run prior to or during compilation, the only way to know what the types are is to be told.

### Function prototypes

* tells the compiler what it needs to know without a full function definition
* also called forward declarations
* Placed at the beginning of a program
* also used in our own header files...

When doing forward declarations you don't actually need to specify variable names, you actually just specify function names and types:  
```c++
void function_name(int a, std::string b);
// can also be
void function_name(int, std::string);
// That said, standard practice is to include the variable names
```

Trying to figure out exactly where they're useful... Looks like if you want to define a function at the bottom of a file, then you can provide the function definition at the top...

## Function parameters

Parameters - How we refer to values in a function definition
Arguments - What we call values passed to a functions

### Pass data to functions

By default, data is passed to functions by value. A copy of the data is made and passed to the function when it is run. This is safer by slower and uses more memory.

### Formal vs Actual Parameters

Formal - the parameters defined in the function's definition, function header
Actual - the parameters used in the function call, the arguments... They're literally just the arguments passed to a function but "Actual Parameters" is the fancy name.

An example to illustrate the difference:
```c++
void param_test(int formal) {
    cout << formal << endl;
}

int main() {
    int actual {10};
    param_test(actual);
}
```

 ### Default arguments

 Default arguments can be added to the function prototype _or_ the function definition... **NOT** both.  
 It's considered best practice to specify default arguments in the functions prototype.  
 Just like python, positional arguments must come before default arguments.

 ```c++
double calc_cost(double base_cost, double tax_rate = 0.06);

double calc_cost(double base_cost, double tax_rate) {
    return base_cost += (base_cost * tax_rate);
}

int main() {
    double cost {};
    cost = calc_cost(200.0);
    cout << cost << endl;
    cost = calc_cost(200.0, 0.08);
    cout << cost << endl;
}
 ```

### Function overloading

Similar/same/different function with the same name that operates similarly/differently based on the type of argument that is passed. 

A good example of this is `print()`... c++ doesn't (seem) to has a `print()` function that handles multiple types... but you could simply create on if you wanted.  

Function overloading is a type of polymorphism.

The compiler essentially tells the functions with the same name apart based on the arguments provided (both the type and the number).

Note that the distinction between two functions _cannot_ be the return type. 

If possible, the compiler will promote types to higher domains when appropriate, e.g.:  
`chat -> int`  
`float -> double`  
`c-style-string -> std::string`  

Note that you can't use overloaded arguments with more than a single default argument and using default arguments at ll _might_ be poor practice... At least for the first parameter.

## Passings arrays to functions

When you pass an array to a function you're not actually passing the entire array to a function, just the memory address of the first element in the array.

Specifying an array as the type taken by a function;  
```c++
void print_array(int numbers []);
```

The following wouldn't work because it wouldn't know how big the array is:  
```c++
int main() {
    int nums[] {1, 2, 3, 4, 5};
    print_array(nums);
}
```

Without a sentinal value, which is something that vectors have, there's no way of knowing when to stop iterating.  
A sentinel value is a special value, `\0` in strings... not sure what they are in vectors.

```c++
int main() {
    int nums[] {1, 2, 3, 4, 5};
    print_array(nums, 5);
}

void print_array(const int nums [], size_t size) {
    for (size_t i {}; i < size; i++) {
        cout << nums[i] << endl;
    }
}
```

Note that the above example has a `const` to avoid accidentally mutating the area.

Technically you can kinda think of arrays passing a memory location as a pass-by-value as you're passing the "value" of a the memory location... kind of a strech but whatevs.

## Passing by reference

By passing the vector by reference using the ampersand we're able to mutate it in-place. This is because vectors automatically make a copy.

```c++
#include <iostream>
#include <vector>
using namespace std;

void print_vector(const vector<int> v);
void mutate_vector(vector<int> &v);

int main() {
    vector<int> v {1, 2, 3, 4, 5};
    print_vector(v);
    mutate_vector(v);
    print_vector(v);
}

void print_vector(const vector<int> v) {
    cout << "[ ";
    for (int n: v) {
        cout << n << ", ";
    }
    cout << " ]" << endl;

}

void mutate_vector(vector<int> &v) {
    int size {static_cast<int>(v.size())};
    for (int i {}; i < size; i++) {
        if (i % 2 == 0) {
            v.at(i) = 10;
        }
    }
}


// [ 1, 2, 3, 4, 5,  ]
// [ 10, 2, 10, 4, 10,  ]

```

Arrays pass the memory location by value but as you're indexing through an array, you're accessing the references to those locations in memory directory, as a result any mutation will persist:

```c++
#include <iostream>
#include <vector>
using namespace std;

void print_vector(const int arr[], int size);
void mutate_vector(int arr[], int size);

int main() {
    int arr[] {1, 2, 3, 4, 5};
    int size {5};
    print_vector(arr, size);
    mutate_vector(arr, size);
    print_vector(arr, size);
}

void print_vector(const int arr[], int size) {
    cout << "[ ";
    for (int i {}; i < size; i++) {
        cout << arr[i] << ", ";
    }
    cout << " ]" << endl;

}

void mutate_vector(int arr[], int size) {
    for (int i {}; i < size; i++) {
        if (i % 2 == 0) {
            arr[i] = 10;
        }
    }
}

// this has the same output as the above
// [ 1, 2, 3, 4, 5,  ]
// [ 10, 2, 10, 4, 10,  ]

```

C-style string are (like) arrays:

```c++
#include <iostream>
#include <vector>
using namespace std;

void print_string(const char arr[], int size);
void mutate_string(char arr[], int size);

int main() {
    char arr[] {"testy"};
    int size {5};
    print_string(arr, size);
    mutate_string(arr, size);
    print_string(arr, size);
}

void print_string(const char arr[], int size) {
    for (int i {}; i < size; i++) {
        cout << arr[i];
    }
    cout << endl;

}

void mutate_string(char arr[], int size) {
    for (int i {}; i < size; i++) {
        if (i % 2 == 0) {
            arr[i] = 'x';
        }
    }
}

// testy
// xextx

```

```c++
#include <iostream>
#include <string>
using namespace std;

void print_string(const string s, int size);
void mutate_string(string &s, int size);

int main() {
    string s {"testy"};
    int size {5};
    print_string(s, size);
    mutate_string(s, size);
    print_string(s, size);
}

void print_string(const string s, int size) {
    for (int i {}; i < size; i++) {
        cout << s.at(i);
    }
    cout << endl;

}

void mutate_string(string &s, int size) {
    for (int i {}; i < size; i++) {
        if (i % 2 == 0) {
            s.at(i) = 'x';
        }
    }
}

// testy
// xextx

```

## Scope

Local scope and block scope

function parameters have block scope. Only visible within the block ({}) where they're declared. Local variables are only available in the scope where they're declared. You can see outside of a scope but not into another scope.

### Static local variables

There's one exception to the above and that's static local variables: 
```c++
static int n {10};
```

Preserved between function calls, only initialized in the first call.

```c++
#include <iostream>
using namespace std;

void print() {
    static int n {100};
    cout << n << endl;
    n += 1;
    cout << n << endl;
}

int main() {
    cout << "Round 1" << endl;
    print();
    cout << "Round 2" << endl;
    print();
}

// Round 1
// 100
// 101
// Round 2
// 101
// 102

```

### Global Scope

Anything declared outside of a function or class has global scope and can be accessed anywhere. Global constants are 
okay but people try to avoid global variables.

Note that you don't need a reason for there to be another level of local scope:

```c++
int main() {
    some scope
    {
        nested scope
        {
            Deeper nested scope
        }
    }
}
```

There doesn't need to be a loop or an if statement or anything like that to have additional scope.

## How do function calls work

Functions use the "function call stack":
* analogous to s stack of books
* LIFO - Last In First Out
* push and pop (Stack terminology... not sure how it's relevant to the function stack)

Stack Frame of Activation Record
* Basically a collection of information that represents an active function
    * This is where parameters, local variables, return address are stored
    * Each time a function is called, an activation record is created and it's pushed onto the call stack. when the 
    function terminates we pop the activation record off of the call stack and now the function that called that 
    function is at the top of the call stack.
* Function must return control to function that called it
* Each time a function is called we create a new activation record and push in on stack
* Wehn a function terminates we pop the activation record and return
* Local variables and function parameters are allocated on the stack
* The stack is finite in size. Too many function calls will result in you running out of stack space (stackoverflow)

## Memory Allocation

```
  --------------------------------
  |                              |
  |       Heap - Free Space      |
  |       or Free store          |
  |                              |
  |                              |
  |                              |
  |------------------------------|
  |                              |
  |         Stack - Where        |
  |     Functions are called     |
  |                              |
  |------------------------------|
  |        Stack Variables       |
  |------------------------------|
  |                              |
  |          Code Area           |
  |                              |
  --------------------------------
```

When a function is called, space is pushed onto the stack for the return value of that function. 
Space is also pushed onto the stack for the function parameters and the return address of the function. 
Control is then transferred to the function that was called (this is done via an assembly language instruction called jump).

The function that was called then pushes the address of the previous activation record. 
Not totally sure what this means but it's basically moving a stack pointer so that you know where the top of the stack is. 
It also pushes any register values that need to be restored (not really sure what this means).

When the code is finished you restore the register values so that main is where it was before. 
You restore the previous activation record so that main is where it was before.
You store the result of that function in the address allocated when the function was called. 
And control is transferred back to main. 

Main also pops the parameters and the return values from the stack 

## Inline functions

Sometimes it can actually be more effort for the compiler to perform all of the steps required to perform a function 
than it actually takes to perform the function. 
One solution to this is inline functions. You might not want to do this when you're called a function many times 
which will eventually result in large binaries. Compilers now generally know when to and when not in line a function.

```c++
inline int add_nums(int a, int b) {
    return a + b;
}

int main() {
    int result {0};
    result = add_nums(100, 200);
    return 0
}
```

Inline functions are generally declared in header files because they must be available to every source file that uses 
it. (Not sure if there's some significance to this that I'm missing... seems obvious).

## Recursion

Don't forget about your "base case". Your base is what allows to you exit from a function so you don't recurse infinitely.

Recursion technically exists when you have two activation records on the same stack for the same function (they don't need to be sequential).

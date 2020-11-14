# Varialbes

## What is a variable
An abstraction of a memory location
Two main properties are **type** and **value**

## Declaring and Initializing Variable
There are built-in variable types:
```
int age;
double;
string name;
```

But because c++ is object oriented, we can do stuff like:
```
Account keiths_accounts;
Person keith;
```

### Naming
Just like python, can contain letters, numbers, underscores
cannnot start with a number
Cannot use reserved keywords
c++ is case sensitive

And has parallels to python: cannot redeclare a name in the same scope

### Initializing
It's generally better to declare variable as-needed.. Not all at the beginning of a function
Variables need to be declared before they're initialized ... but that doesn't mean they need to be on separate lines.
This is valid:
```
int age;
age = 21;
```
But these are more concise
```c++
int age = 21; // C-like initialization
int age (21); // Constructor initialization
int age {21};// C++11 list initialization syntax.. Apparently has some benefits and is the encouraged initializationz
```

If you surpass the values that it can take, it'll give you a warning. With other assignment types it might not actually throw an error.

When you declare without initializing, you're assigning a memory location (of the appropriate size. It knows how to size it because of the type specified). When something is "deleted" it's not actually deleted... The reference to a particular location in memory is removed... But whatever data was there is still there. So, when you declare a variable, it's given a memory location and there's not guarantee that there isn't anything there, you might have been assigned the location of some of variable (not totally sure if this is how it works... want to check).

```c++
#include <iostream>

int main() {
    int test;
    std::cout << "Unitialized test: " << test << std::endl;
    std::cout << "Test mem location: " << &test << std::endl;
    int* test_pointer= &test;
    std::cout << "Printing what is at that location in memory: " << *test_pointer << std::endl;
    test = 10;
    std::cout << "Assigned test to 10: " << test << std::endl;
    std::cout << "Checking to see if same mem location: " << &test << std::endl;
    std::cout << "Checking value at that location: " << *test_pointer << std::endl;
}


// Unitialized test: 21856
// Test mem location: 0x7ffc8f6e941c
// Printing what is at that location in memory: 21856
// Assigned test to 10: 10
// Checking to see if same mem location: 0x7ffc8f6e941c
// Checking value at that location: 10
```

## Global Variables
Global variables, unline local variables, are automatically initialized to zero

## Primitive Types
char - one byte, 8 bits, 256 possible combinations
char16_t - at least 16 bits
char32_t - at least 32 bits
wchar_t - can represent the largest available character set

Both signed and unsigned integers can be stored in the `char` datatype

In the below-listed types, the non-bolded keywords are options and do not impact the type
signed **short** int - 16 bit integer
signed **int** - 16 bit integer
signed **long** int - 32 bit integer
signed **long long** int - 64 bit integer
**unsigned short** int - 16 bits
**unsigned int** - 16 bits
**unsigned long** - 32 bits
**unsigned long long** - 64 bit

All of the above types are **at least** the specified number of bits
Note that these types are **signed** by defualt. To be **unsigned**, you must specify.

## Bools
c++ is similar to python in that it has truthy and falsy bools.
`0` is always `False` (and probably `null`) and everything else is `True`.

## String vs Char???
Strings and characters actually need to be indicated in different ways!
string receive double (and or single quotes??) while `char`s receive single quotes.

## Look up CLimit and CFloat mantissa

# Chapter 1 short answers

* Explain the difference between an object file and an executable file.
Machine code but not yet linked to external libraries

The job of the **control unit** is to fetch instructions, carry out the operations commanded by the instructions, and produce some outcome or resultant information. 


Internally, the CPU consists of the **arithmetic logic unit (ALU)** and the **control unit**

Words or names defined by the programmer are called **named identifiers**

The three primary activities of a program are **input**, **processing**, and **output**

A **hierarchy chart** is adiagram that graphically illustrates the structure of a program.

# Chapter 2

How would each of the following numbers be represented in E notation?

`3.287 * 10^6 -> 3.287E6`  
`7.65941 * 10^-3 -> 6.65941E-3`  

Variable names may be up to 31 characters long!!!

int east = 1, west = 1... etc

int east, west, noth, south, east = west = south = north = 1;

`std::cout << std::setw(8) << std::fixed etc..`

Chaper 4:

Flag variable is used as a signal in programming to let the program know that a certain condition has met  
e.g. `initialized = true;`

The logical operators have left to right associativiity

The expression that is tested by a `switch` statement must have a **boolean** value

The expression that is tested by a `switch` statement must have a **break statement** 

Al program will "fall through" a case section if it is missing the **break** statement.

```c++
#include <iostream>

int main() {
    int t = 5;
    {
        int t = 10;
        std::cout << t << std::endl;
    }
    std::cout << t << std::endl;
}
5
10
5
```

compared to:  

```c++
#include <iostream>

int main() {
    int t = 5;
    {
        t = 10;
        std::cout << t << std::endl;
    }
    std::cout << t << std::endl;
}
5
10
10
```

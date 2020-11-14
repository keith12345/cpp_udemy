# Identifiers, Operators, and Keywords

<< - Stream insertion operator - used to insert whatever is on the right right of it into that stream
>> - Stream extraction operator - takes something from the console and stores in a variable
:: - Scope resolution operator -
; -

# Preprocessor Directives

Pre-processes source code before the compiler sees it
Steps:
1. Strips all comments from the source code and replaces them with a single space
2. Then looks for pre-processor directives and executes them
    * All pre-processor directors begin with `#`
3. Pre-processor statement include things like `if/else`
    * A pre-processor statement might check to see the operating system of the mahcine your on to deteremin which software to install/run
4. The pre-processor doesn't actually understand any of the c++ code. It simply follows the pre-processor directives and gets the source code ready for the compiler (which does understand c++)

# The main() function

The name main matters!
Unlike some other languages, you have need to name your entrypoint main
A return of `0` indicates that the program ran successfully.
There are essentially two different versions of main:
* The first version takes no inputs
* The second version takes inputs from the command line
    * The inputs are of two types, `argc` which means "argument count", the number of arguments passed into the program
    * the second is `argv` which stands for "argument vector" and is a vector of the length specified by `argc`

# Namespaces

Namespaces are used to indicate where a function/class/etc. can from and allow us to avoid naming conflicts
Namespaces allow developers to group their code entities into a namespace scope.
python avoids this by accessing functions/modules through the package name, e.g. `numpy.array()`
As mentioned earlier, `::` is called the scope resolution operator. It allows us to indicate with namespace we want to use


We can specify that we want to use a particular namespace using a namespace directive:

```
using namespace std;
```

This allows us to refer to things from that namespace (like `cin` and `cout`) without specifying the namespace using the resolution operator.

Similar to python, you specify particular functions that you'd like to use, rather than simply importing everything by using the `using` directive:
```c++
using std::cout;
using std::cin;
using std::endl;
```

# Basic I/O

The `io` in `<iostream>` stands for input/output...
We've used `cin` and `cout` and the insertion and extraction operators (`<<`, `>>`) a bit but other standards are `cerr` and `clog`

In c++ you should use an endline operator (either `std::endl;` or `"\n"`) to flush the stream. If the stream is buffered, it may not get written to the console it's flushed.
Note that `"\n"` doesn't actually flush the buffer but emulates that behaviour

The buffer - Characters are not actually read _directly_ from your keyboard... They're stored in a buffer. The buffer needs to be created before the next input can be read or output can be written.

```c++
#include<stdio.h>
#include<conio.h>
void main()
{
  int v1,v2;
  clrscr();
  printf("\n Enter v1: ");
  scanf("%d",&v1);
  printf("\n Enter v2: ");
  scanf("%d",&v2);
  printf("\n v1+v2=%d ",v1+v2);
  getch();
}


Enter v1: 10

Enter v2: 20

v1+v2=30

// running the program again
Enter v1: 10 20 30

Enter v2: (nothing)

v1+v2=30
```

In the second run of the program, the secnod variable is stored in the buffer and accessed from the first run of `cin`, it didn't need to be entered.

but if we flush the buffer:

```c++
#include<stdio.h>
#include<conio.h>
void main()
{
  int v1=0;
  int v2=0;
  clrscr();
  printf("\n Enter v1: ");
  scanf("%d",&v1);
  printf("\n Enter v2: ");
  fflush(stdin); // here's where we flush
  scanf("%d",&v2);
  printf("\n v1+v2=%d ",v1+v2);
  getch();
}


Enter v1: 10 20 30

Enter v2: (nothing)

v1+v2=10 //10+0=10
```

Then there's no input stored to be read and we get the intuitive behavior.

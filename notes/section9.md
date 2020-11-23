# Controlling Program Flow

Refers to:  
* Sequence - simply writing operations in a defined order
* Selection - if/else, switch, conditional operation (`?`)
* Iteration - looping: for loop, while loop, do while loop

## if:

I think we go this...

A few things syntax notes:  
If you're only executing one statement, you do not need curly brackets:  
``` c++
if (expr)
    statement;
```

However, if you have a block statement (multiple lines of code/statements), then you need curly brackets:  
```c++
if (expr) {
    statement1;
    statement2;
}
```

## if/else:

...

## nested ifs:

Because indentation is disregarded by the compiler we need to be careful of dangling `else` statements.

In both of the below examples, the `else` statement will apply to the second if statemnt:  
```c++ 
if (expr1)
  if (expr2)
    statement1;
  else 
    statement2;
```
Same as:  
```c++ 
if (expr1)
  if (expr2)
    statement1;
else 
  statement2;
```

## Switch statement:

Switch statement syntax:  
```c++
switch (control_expression) {
  case expression_1; statement_1; break;
  case expression_2; statement_2; break;
  case expression_3; statement_3; break;
  ...
  case expression_4; statement_4; break;
  default: statement_default;
}

```

Both the control expression and the case statements must evaluate to integral or enumeration types.  
More on constants below but essentially they must be constants or literals. **This is because they must be known at compile time.**

When the value in the control expression matches the value in the case statement, the code is executed.  
Note that break statements are not "required".

### break statement
Once the first case statemnt is satisfied, all statements will be executed until the break statement is reached.
```c++
#include <iostream>
using namespace std;

int main() {
    int a {2};

    switch (a) {
        case 1:
            cout << "1 was selected" << endl;
        case 2:
            cout << "2 was selected" << endl;
        case 3:
            cout << "3 was selected" << endl;
        case 4:
            cout << "4 was selected" << endl;
            break;
        default:
            cout << "None of 1, 2, 3, 4 were selected" << endl;
    }
}
```
Will output:  
```
2 was selected
3 was selected
4 was selected
```

Should be clearly documented if this behavior is ever intentional.

### Elaborate case statements

Just like an if/else, case statements can include elaborate logic, of if/else/case statements, loops, etc.

### Enum

Note that all constants with an `enum` should be handled by case statemnts. Depending on the compiler, compilation will not necessarily fail but it will at least give a warning. Extraneous values can within an `enum` can be handled in the `default`.

### Default

The `default` acts as a catch-all else statement. Just like an else, the default statement is optional, but, again, best practice is to include it.

### Conditional Operator:

The conditional operator (`?`) is a ternary operator, this means that it operates on three operands.  
1. Condition expression (usually in parens)
2. evaluation expression 1
3. evaluation expression 2

Written in the form:  
```c++
(conditional_expression) ? expression1 : expression2
```

It's basically a very concise if/else.

While it's possible to nest expressions with the conditional operator, it's considered best practice not to do so.

Example code:  
```c++
#include <iostream>
using namespace std;


int main() {
    int num {};

    cout << "enter an integer: " << endl;
    cin >> num;

    cout << num << " is " << ( (num % 2 == 0) ? "even" : "odd" ) << endl;
    // prints "4 is even"
}
```

### Loops

`for` loop (range based `for` loop) and `while` loop are all extant in python.

The only loop that's different is the `do-while` loop. `while` loops check whether a condition is true at the start of a loop, `do-while` loops check if a condition is true at the _end_ of a loop.

for loop syntax:

```c++
for (initialization; condition; increment) {
  statement;
}
```

The semi-colons are required but the expressions are _actually optional_.

The variable can be declared at or prior to initialization.
Whether or not you declare `i` within the initialization of the `for` loop depends on whether or not you want `i` to be accessible outside of the loop. Generally you probably won't want it accessible outside of the loop.

The most common increments are `++i` and `i++` but you can increment in any way you like, e.g. `i += 2`.

**Note on arrays** - if you're iterating through an array, make sure that your index goes up to either less than the length of the array or less than or equal to the length of the array (don't wanna corupt data...). If you go beyond the array it's called an "off by one" error.

You're also not confined to defining just a single variable in a loop. But do note that if you are using multiple variables, they must be of the same type:  
```c++
#include <iostream>
using namespace std;

int main() {
    for (int i {1}, j {1} ; i <= 5 ; i++, j *= 2) {
        cout << i << " * " << j << " : " << (i * j) << endl;
    }
}
// 1 * 1 : 1
// 2 * 2 : 4
// 3 * 4 : 12
// 4 * 8 : 32
// 5 * 16 : 80
```

**Note on condition expressions in loops** - greater than andd less then will throw a warning when comparing different types (e.g. signed and unsigned integers). A common place where we find unsigned integers is with `vector.size()`. To avoid those, simply initialize an `unsigned` instead of an int.

### Range based for loops

I actually found this name a little confusing. I thought of range based for loops as being akin to python's `for i in range(n):` but range based `for` loops in c++ actually refer to loops that iterate through structures more like python's `for c in ['a', 'b', 'c']:`.  
Range-based for loops were added in c++11.

Example code:  
```c++
for (int score : scores) {
   statement;
}
```

While it's generally good practice to specify the types of your variables, there's also the `auto` keyword which allows implicit typing:  
```c++
for (auto score : scores) {
    statement;
}
```
This is used more when dealing with complex types.

## While Loop

Example code:  
```c++
int i {1};

while (i <= 5) {
  count << i << endl;
  ++i;
}
```

While loop asking for input:  
```c++
#include <iostream>
using namespace std;

int main() {
    int number {};

    cout << "Enter an integer less than 100: " << endl;
    cin >> number;

    while (number >= 100) {
        cout << "That's equal to or greater than 100! Try again: " << endl;
        cin >> number;
    }
}
```

### Do While Loop:

Example code:  
```c++
do {
  statements;
} while (expression);
```

A do-while loop is a post test loop (the condition is tested at the end of the loop) which guarantees that your loop executes at least once.

We can re-write the input validation loop more cleanly using a do-while loop:

```c++
#include <iostream>
using namespace std;

int main() {
    int number {};

    do {
        cout << "That's equal to or greater than 100! Try again: " << endl;
        cin >> number;
    } while (number >= 100);
}
```

Note that `number` needs to be declared outside the scope of the do-while loop. Not doing so will result in a compiler error.

### Continue and Break

Just like python. 

continue - No further statements are executed, immediately jump to the next iteration of the loop

break - No further statements are executed, immediately terminate the loop.

### Infinite loops:

ya know...

Code example:  
```c++
for (;;) {
    statements;
}

// or

while (true) {
    statements;
}
```

### Nested loops:

mhmmm...


## Miscellaneous:

### Block statements:

They introduce a new level of scope.

Technically, everything defined inside of a function is a block statement

```c++
if (expr) {
  int a {3};
}
cout << a << endl; // would throw error: 'a' was not declared in this scope
```

### <iomanip>

Can be used to set precision of your output:  

```c++
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    float a {12.999};
    cout << fixed << setprecision(2);
    cout << a << endl; // outputs 13.00
    float b {10.125};
    cout << b << endl; // note that it's not perfect... this will output 10.12
    float c {10.1250001};
    cout << c << endl; // also outputs 10.12
    float d {10.125001};
    cout << d << endl; // finally outputs 10.13
}
```

### Integral types:

* integer values; signed and unsigned
* bools
* chars
* members of an enumerated type (interpreted as an integer by the compiler)
* bit fields

More on integral types [here](https://www.cs.auckland.ac.nz/references/unix/digital/AQTLTBTE/DOCU_032.HTM)

The instructor says the `enum` statements are the integral type.

### Enum example:

```c++
#include <iostream>
using namespace std;

int main() {
    enum Color {
        red, green, blue
    };

    Color screen_color {green};

    switch (screen_color) {
        case red: cout << "red" << endl; break;
        case green: cout << "green" << endl; break;
        case blue: cout << "blue" << endl; break;
        default: cout << "How'd we get here" << endl;
    }
}
```


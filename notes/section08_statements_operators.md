# Statements and Operators

Statements refers to things like:  
* variable declaration
* return statements
* IO statements

There are also block statements and compound statements.

Operators:  
Just assignment operators, arithmetic, equality, etc.  

## Expressions and Statements:  

An expression (or series of expressions) become a statement when terminated by a semi-colon.

### Expressions:  

* Most basic building blocks in programmin
* essentially a sequence of operators and operands that specifies a computation

Examples:  
* a string or numerical literal like `34` or `hey`
* variables
* mathematical operations

### Statements:

* Complete line of code that performs some action
* Typically terminated with a semi-colon
* Typically contains expressions
* Potential statement types:
    * expressions
    * null
    * compound
    * selection
    * iteration
    * declaration
    * jump
    * try blocks
    * etc.

Examples:  
``` c++
int x; // declaration
num  = 12; // assignment
2 + 2; // expression
if (a > b) cout << "a is greater than b"; // if - has both statements and expressions 
; // null statement - actually used sometimes, apparently
```

### Operators:

Most are binary (operate on two operands)  

There are some unary operators:  
``` c++
int a = 10;
int b = -a; // unary minus - results in b = -10, changes the sign of the operand

a = b = 20; // chained assignment

a++ // postfix increment
++a // prefix increment

a-- // postfix decrement
--a // prefix decrement

bool t = true;
bool f = !t // NOT(!) operator - reverses logical state of operand

int a;
int *ptr; // indirection operator - used to store a reference to a location in memory
ptr = &a // Address of operator - used to obtain a reference to a variable/const location in memory

sizeof(a) 
sizeof a 
```

Note that both the "address of" operator and the "indirection operator" are considered "pointer" operators.  
There are also relation operators (`==`, `>`, etc), logical operators (`if`).  

Member access is considered another type of operator, i.e. subscripting something.  

Note that there's a difference between assignment and initialization:  
* initialization - defining a variable to have a specific value either at the same time as or immediately after declaration.
* assignment - ascribing to a new value to a previously defined variable.

## Arithmetic operators:

I think we understand this already...

Just know that c++ shares all of the same arithmetic operators as python (even the modulo `%`).  
Actually, that's not totally true... I don't think it has float division (not necessary because of static typing).

## Increment and Decrement Operators:

When used with an integer or a float, simply increases or decreases it by one.

Two different types of notation - prefix and post-fix.  
When used in isolation, prefix and postfix do the same thing, e.g.:  

```c++
i++; // these two are essentially the same
++i;
```

The prefix and postfix notation determine when in the order of operation the variable is incremented or decremented.  

```c++
#include <iostream>

int main() {
    int j;
    int k;
    int i = 1;
    j = i++;
    k = ++i;

    std::cout << "i = " << i << std::endl; // i = 3
    std::cout << "j = " << j << std::endl; // j = 1
    std::cout << "k = " << k << std::endl; // k = 3
}
```

Note that you should never use either increment or decrement twice in the same expression.

## Mixed type expressions:

Operators must occur on same-type operands. If differing-type operands are used, c++ will convert (coerce) one of them.

Conversion can be explicit (done by the programmer) or implicit (done by the program).

c++ has higher and lower domains - higher domains hold larger values, lower domains hold smaller values.  
Conversion happens to a higher domain automatically as the lower value will fit inside the higher domain.  
`short` and `char` types are always converted to integers.

Order of promotion:  
`char < short < int < long < long long`  
`int < float`  
`long < double`  
`long long < long double`

While conversion is changing any one domain to another domain, promotion is the conversion of any domain to a higher domain while demotion is conversion to a lower domain, e.g.:

```c++
int num;
money = 23.16; // 23.16 gets demoted to 23.
```

### Type casting:

To get an average of two ints where the average might require a floating point, at least one of the two numbers must be converted.  
```c++
int total_amount {100};
int total_number {8};
double average {0.0};

average = total_amount / total_number;
cout << average << endl; // displays 12

average = static_cast<double>(total_amount) / total_number;
cout << average << endl; // displays 12.5

// This is the old way of doing things and is not as robust as static_cast
// static_cast does a check in ensure that the value you are trying to convert
// is actually able to be converted to the specified type.

average = (double)total_amount / total_number;
```

## Testing for equality:

Largely the same as python...

By default, bools are output as either `0` or `1`, if you want to output bools as `true` and `false` you need to do the following:  
```c++ 
std::cout << std::boolalpha;
std::cout << std::noboolalpha; // to go back to zeros and ones
```

Note that they are both part of `iostream`. 

c++ will do implicit conversion for things like `10.0  == 10`  
note that the compiler will likely eveluate to true for things like `2 = 1.99999999999999999`

## Relational Operators:

Also, mostly the same as python 

## Logical operators:

Three logical operators:  
* `!` - not
* `&&` - and
* `||` - or

Note that you can actually use the keyword syntax but most programmers stay away from it.

Order of precedence:  
1. `not`
2. `and`
3. `or`

Order of precedence is like the PEMDAS or logical operators.

Like python, c++ also has short-circuiting.  
Short-circuiting is when subsequent operations are only performed when their value will impact the result of an statement.

``` c++
false && true; // will short-circuit
true || true; // will short-circuit
true && true; // will not short-circuit
true && false // will not short-circuit
false && false; // will short-circuit
```

## Compound Assigment:

Also similar to python. Supports things like:

```c++
int a {5};
a += 3;
cout << a << endl; // returns 8
```

Most of these are pretty intuitive: `*`, `/`, `%`, `+`, `-`

These a little bit less so:  
`&=` - Obtain the bitwise AND of the first and second operands; store the result in the object specified by the first operand.  
`^=` - Obtain the bitwise exclusive OR of the first and second operands; store the result in the object specified by the first operand.  
`|=` - Obtain the bitwise inclusive OR of the first and second operands; store the result in the object specified by the first operand.  

and these are pretty weird:  
`<<=` -  Shift the value of the first operand left the number of bits specified by the value of the second operand; store the result in the object specified by the first operand. The shifted bits are replaced by zeros.  
`>>=` - Shift the value of the first operand right the number of bits specified by the value of the second operand; store the result in the object specified by the first operand. The shifted bits are replaced by zeros.  

But that's more because the insertion and extraction operators are weird (when used outside of `cin`/`cout`).

## Operator Precedence:

what does precedence mean in terms of programming? Higher precedence operations are performed first.  
Official documentation on operator precedence [here](https://en.cppreference.com/w/cpp/language/operator_precedence).

Most operators perform operations left to right but there are a few exceptions.  

If there are two different operators with the same precedence, associativity is used to determine which operations are performed first.  
```
expression1 (l->r operator) expression2 (l->r operator) expression3  // operates on expressions 1 and 2 first
expression1 (r->l operator) expression2 (l->r operator) expression3  // operates on expressions 2 and 3 first
```

## Miscellaneous:

### l-values and r-values:

Idea use in programming languages, comes from the fact that two operands appear on the left and right hand side of an assignment operator, e.g. `a = 10;`. Here, `a` is the "l-value", the value on the left-hand side, while `10` is the r-value, or the value on the right hand side.  
In simplest terms, l-values and r-values are the values on the left and right hand sides of an assignment operator. A more accurate definition is that an l-value is a location in memory while an r-value is the value that will be stored at that location in memory.  
There are other key differences, such as l-values persist beyond the expression in which they are used while r-values only exist inside of that expression.  
When an l-value is used, it is a de-referenced reference to a location in memory at which point the value stored at that location is accessed.

Note that constants kinda of mess this up... A `const` l-value is a "non-modifiable" l-value which supports referencing but not assignments.  
There are "non-l-values" which are values that are never assigned, and because they are never assigned, they are not contents. E.g. the result of `4 * 5;` would be a non-l-value because it is never assigned while the `4 * 5;` in `a = 4 * 5;` _would_ be an l-value because it is assigned and is therefore contents.

If you try to store a value in an r-value, you'll get an error stating that "l-value required as left operand of assignment"

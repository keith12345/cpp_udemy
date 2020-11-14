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

Just know that c++ shares all of the same arithmetic operators as python (even the modulo `%`)
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
i = 1;
j = i++; // j = 1
k = ++i; // k = 3
```

Note that you should never use either increment or decrement twice in the same expression.

## Miscellaneous:

### l-values and r-values:

Idea use in programming languages, comes from the fact that two operands appear on the left and right hand side of an assignment operator, e.g. `a = 10;`. Here, `a` is the "l-value", the value on the left-hand side, while `10` is the r-value, or the value on the right hand side.  
In simplest terms, l-values and r-values are the values on the left and right hand sides of an assignment operator. A more accurate definition is that an l-value is a location in memory while an r-value is the value that will be stored at that location in memory.  
There are other key differences, such as l-values persist beyond the expression in which they are used while r-values only exist inside of that expression.  
When an l-value is used, it is a de-referenced reference to a location in memory at which point the value stored at that location is accessed.

Note that constants kinda of mess this up... A `const` l-value is a "non-modifiable" l-value which supports referencing but not assignments.  
There are "non-l-values" which are values that are never assigned, and because they are never assigned, they are not contents. E.g. the result of `4 * 5;` would be a non-l-value because it is never assigned while the `4 * 5;` in `a = 4 * 5;` _would_ be an l-value because it is assigned and is therefore contents.

If you try to store a value in an r-value, you'll get an error stating that "l-value required as left operand of assignment"

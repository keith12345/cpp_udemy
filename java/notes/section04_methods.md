# Methods

## Comparison Operators

Sometimes when creating classes we need to make sure that they inputs have been supplied correctly to a class/method; to
test we perform **parameter validation**. An example is that you might want to check if a `null` is passed in place of a
required argument. 

## Logical operators

`&&` - and  
`||` - or
`!` - not - sometimes called the **logical complement** operator

The above three logical operations can be referred to as **conjunction**, **disjunction**, and **negation**
respectively.

Note that java has short-circuiting. The right operator is only evaluated when the left-operand is `true` in and
operation and similar with or but first needs to be `false`.

This can help with null-checking:
```java
// instead of
if (s.age > 21) {
    ...
}
// you can do
if (s != null && s.age > 21) {
    ...
}
```

## Bitwise Operators

These operate on the individual **bits** of operands. 

They work on both **integer primitives** (operand promotion applies) and **booleans** although, they are rarely use on
booleans. 

These are typically used in embedded systems (think apple watch) where there's limited memory.  

They are also used in **hash tables** likes java's `HashMap` and in compression and encryption.

* `&` - bitwise `AND` - returns `1` if both inputs are `1` 
* `|` - bitwise `OR`
* `^` - bitwise `XOR`
* `~` - bitwise `NOT`

```java
int x = 12;
x -> 00000000 00000000 00000000 00001100 
int y = 9;
y -> 00000000 00000000 00000000 00001001 
int z = (x & y); // returns `8`
z -> 00000000 00000000 00000000 00001000 // the fourth to last bit is the only one that's shared 
int z = (x | y); // returns `13`
z -> 00000000 00000000 00000000 00001101 // needs either bit
int z = (x ^ y); // returns `5`
z -> 00000000 00000000 00000000 00000101 // returns what either of them have but no both or neither
int z = (~x);
z -> 11111111 11111111 11111111 11111001 // returns everything that x doesn't have
```

All bitwise operators are non-short-circuit operators. 

There are also bitwise compound operators:
`&=`  
`^=`  
`|=`  

Note that while people don't typically use bitwise operators with booleans, they all work except for `~` for which you
would simply use `!`. They are also actually referred to as logical operators when used on booleans, they are only
called bitwise operators when used on integer primitives. When used with booleans, however, they no longer have the
short-circuit property that the typical logical operators have. 

## Bit-shift operators

`<<` - left-shift  
`>>>` - unsigned right-shift
`>>` - signed right-shift

They are binary operators.  
They shift the operand by the number of bits specified in the right operand.

```
     6 -> 00000000 00000000 00000000 00000110 
6 << 1 -> 00000000 00000000 00000000 00001100 = 12
```

Zeroes are inserted a lower-order bits.

Shifting to the left by 1 is the same as multiplying by 2. 

```
6 << 1 -> 6 * 2**1 -> 12
6 << 3 -> 6 * 2**3 -> 48
```

Unsigned right-shift does the exact opposite of left-shift.  
Shifting to the left by 1 is the same as dividing by powers of 2.

Signed right-shift is the same as unsigned right-shift but it is padded with **MSB** or the **Most Significant Bit**.
Signed preservers sign. The most significant bit is the first bit. It is called the most significant bit because it has
the greatest impact on the value of the integer. 

Compilers replace mathematical operators with bitwise operators for speed.

They are also used in:
* hash tables
* embedded programming
* games programming
* systems with no floating point support

Bitwise operators can also be used in compound assignment notation:
`<<=`  
`>>>=`  
`>>=` 

## switch statement

```java
int month = 3;
switch (month) {
    case 1: System.out.println("January");
            break;
    case 2: System.out.println("February");
            break;
    case 3: System.out.println("March");
            break;
    default: System.out.println("Another month");
}
```

The only restriction on switch statements is that it must evaluate to an integer, 
string, or enum (_not_ `long`).
* byte
* short
* char
* int

**OR** a `String` as of Java 7.

**Boxed primitives** or **wrapper classes** are also allowed. 
* byte -> Byte
* short -> Short
* char -> Character
* int -> Integer

If the switch statement ever evaluates to `null`, you'll get a nullPointerException.

Some good-to-knows:
* Values that case statements are checking for must be known at compile time.
    * This means that you can't use variables but you can use initalized **constant expressions**
    * Constant expressions are declred using the **final** reserved keyword. 
* value must be within the range of the data type in the switch expression
* value must be unique
* cannot be null


## When to use a switch

* readability
* intent
    * Can help indicate when only a single variable is important
* Speed
    * faster due to single condition and constant case labels
    * given `n` conditions, `if` time complexity up to `O(n)`, switch is always `O(1)` (constant time)
        * When n conditions > 100, `if` -> `switch` no longer considered a micro-optimization

## Ternary

short if/else where the if/else each have only one expression

```java
int x = 10;
int x = 7;
int min = (x < y) ? x : y;
```

Generally used for readability.

```java
String greeting = "Hello " + (user.isMale() ? "Mr. " : "Ms. ") + user.name();
```

There are used a lot in logs for ease. 

The ternary operator is an expression, but it cannot be expressed as an expression statement.  
(post/pre-increment are expression statements).

What this means in effect is that you can't do:
```java
(boolean-expression) ? true-expr ; false-expr;
```

It needs to be part of some assignment statement or a method invocation.  

## For loops

All of the rules are just like c++, optional/multiple declarations, checks, increments etc.

You can actually do some fancy stuff with this multiple declarations. Here's reversing a list:  
```java
int[] intArray = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
for (int i = 0, j = intArray.length-1, middle = intArray.length >>> 1; i < middle; i++, j--) {
    int temp = intArray[i];
    intArray[i] = intArray[j];
    intArray[j] = temp;
}
```

## for each

* Cleaner syntax
* no performance penalty (could actually be better for arrays)
* eliminates some opportunity for errors (mostly through copy/paste)
* preferred for nested iterations

Maybe not readable... Just remember that everything in the condition expression gets evaluated with each iteration. 

```java
int[] die1 = {1, 2, 3, 4, 5, 6};
int[] die2 = {1, 2, 3, 4, 5, 6};

for (int i = 0; i < die1.length; i++} {
    for (int j = 0; j < die2.length; j++} {
        System.out.println(die1[i] + " " + die2[j]);
    }
}

for (int i : die1) {
    for (int j : die2) {
        System.out.println(i + " " + j);
    }
}
```

When to use a traditional `for`?
* Need the index
* Need to transform the array 
* Parallel (multiple array) iteration
* backward iteration

## Breaks statements

Break exits the immediately enclosing loop of switch statement. But what if you want to exit an enclosing switch
statement or loop? For that you'd need to use a **labeled break**.  
To do the, the code block for which you break needs to be labeled. Labels are any valid java identifiers. 

```java
outermost: for (int i = 0; i < 10; i++) {
   for (int j = 0; j < 10; j++) {
       if (i == 5 && j == 5) {
           break outermost;
       }
   }
}
```
you can do it inside any scope:
```java
someLabel: {
    break someLabel;
}
```

## Recursion

Whenever a program is invoked in java, it gets memory allocated on the **stack**. Whenever a program calls a method,
that method gets memory allocated in a **stack frame**. A stack frame is in the stack.  
Whenever a recursive method gets a **stack overflow** error it is actually the stack frame that has overflowed.


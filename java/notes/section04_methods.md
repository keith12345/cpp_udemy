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
string, or enum.
* byte
* short
* char
* int

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



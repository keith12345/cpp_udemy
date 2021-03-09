# Classes, Objects, and their Members

## Classes and Objects

Objects are created from classes. An object is an instantiation of a class(???).

OOP has it roots in the 60  
Meant to help model real-world scenarious in a more natural way.  
* Studet register for course which is in a department  
* Customer buy a product  


Each of these things have attributes and perform actions. 

Data attributes for a particular instance are typically referred to as the **state of the instance**.  
The actions that can be performed are referred to as **behavior** and are performed with methods.  
There are also nested classes and nested interfaces but that's later.  

**Class members** can refer to both variable and methods. 

```java
class Student {
    // variable declarations
    int id;
    String name;
    string gender;

    // method definitions
    boolean updateProfile(String newName) {
        name = newName;
        return true;
    }
}
```

Test our one method:  
```java
class StudentTest {
    public static void main(String[] args) {
        // 1. creating a new student object called 's' using keyword 
        // 'new' keyword. The type of the object is Student.
        Student s = new Student();

        // 2. Setting the student's state
        s.id = 1000;
        a.name = "joan";
        s.gender = "male";

        // 3. updating profile with correct name
        s.updateProfile("john");
    }
}
```
The above is not using a constructor but constructors are the default way to initialize state for an object.

## Absolute Java Basics

First letter of class name has to be letter, underscore or **$** (no joke).  
The remaining characters can be the above as well as numbers.  

Don't use any reserved keywords!! 

```java
/*
Jave has block
quotes just
like c++!!
/*
```

## Variables

**primitive variables** are basically variables that are as primitive as possible, like an `int` or a `char`... There
are no number or character types that are more "primitive" than those. 

Variables that hold objects are referred to as **object references**. 

**Interfaces** are another type of object reference. 

Note that you have create a Student object you need the keyword `new` like so:
```java
Student s = new Student();
```
but we didn't need that with a String type:
```java
String name = "keith";
```
More on this^^ later.

**Literals** are just raw data:
```java
int id = 100;
boolean flag = true;
String name = "Keith";
```

When you define a variable and give it a value it is a **declaration statement**. 

Note that assignment cannot take place within the body of a class, only declarations are allowed. Assignment it must be
within a method. 

## Primitive Types

* `boolean`
* numerical:
    * Integer
        * `byte`
        * `short`
        * `int`
        * `long`
    * Floating-point
        * `float `
        * `double`
    * Character
        * `char`
        * Also considered a numeric type as it is stored as an unsigned `int`


## Integer data type

* byte
    * 8 bits
    * -2^7 -> 2^7-1
    * -128 -> 127
* short
    * 16 bits
    * -2^15 -> 2^15-1
    * -32768 -> 32767
* int
    * 32 bits
    * -2^31 -> 2^31-1
* long
    * 64 bits
    * -2^63 -> 2^63-1


Each number is -2^n -> 2^n-1 where "n" is the number of bits. The first bit indicates whether or not it's positive, zero
is included as a positive number.  
The left-most bit is frequently referred to as the **most significant bit**.

The number of bits is the bit depth.

The default value for all integers types the default value is 0. Note that local variables do not get any default value;
and class variables get a default variable.

Note that to assign to a `long` you actually need to indicate that that number is meant to be a long, you have to cast
it.  
```java
long 2234567890; // compilation error
long 2234567890L; // Needs to `L` to work
```

This is because there are two different types of **integer literals**. **Integer Literal** and **Longer Literal**.

Note that, like python, java allows underscores to improve the readability of long numbers:  
(Java 7+)  
```java
long 1_000_000_000_000L;
```

If you ever need to see the max and min values for a numerical type you can do:  
```java
int minValue = Integer.MIN_VALUE;
int maxValue = Integer.MAX_VALUE;
```

Integer is a type of class that comes with the java library that's called a **Boxed Primitive** (or a **Wrapper 
Type**?).   
Every primitive type (all 8) has an associated box primitive type.

Java supports **Hexadecimal notation**, which starts with `0x` (not case sensitive) and then the hexadecimal number, as
well as binary, which starts with `ob` (also, not case sensitive) and then the binary number:
```java
int intHex = 0x0041; // 65, 16^0 * 1 + 16^1 * 4
int intBinary = 0b01000001; // also 65, see below
int intOctal  = 0101; // also 65, 8^0 * 1 + 8^1 * 0 + 8^2 * 1
```

The binary is a bit more compliated.  
Each digit represents a different number that you add to the sum of the number:
```
 128  64  32  16   8   4   2   1
   0   1   0   0   0   0   0   1
```
You sum where there are ones and that gives you your number.

You can also specify these types as `long` as well as use underscores to separate characters in the number.

## Floating Point Numbers

* `float`
    * 32 bits
    * -3.4E38 -> 3.4E38
    * default 0.0f
    * precision 6-7 decimal digits
* `double`
    * 64 bits
    * -1.7E308 -> 1.7E308
    * default 0.0d
    * 15-16 decimal digits

Note that `double`s can be significantly larger than `long` even though they have they same number of bits _and_ need to
store additional precision.  
This is achieved through the three parts that `double`s have:
* 1 bit for sign
* 11 bits for the exponent
* 52 bits for the mantissa

The **mantissa** is the number that will be multiplied by the nth power of 10:  
mantissa * 10^n  
or  
mantissaEn  

For the max value of a double:  
mantissa = 1.7
n = 308

Generally even if you're not working with big numbers you actually probably want to stick with double because it has
greater precision that float. 

### Weird floating pointer weaknesses

```java
import java.math.BigDecimal;

class FloatingPointWeaknesses {

    public static void display() {
        System.out.println(1 - 0.9);
        System.out.println(0.1 + 0.02);

        double price = 1000;
        double discountPercent = 0.9;
        double discountAmount = price * discountPercent;
        System.out.println(price - discountAmount);
        System.out.println(price * (1 - discountPercent));

        BigDecimal first = new BigDecimal("0.1");
        BigDecimal second = new BigDecimal("0.2");
        System.out.println(first.add(second));
    }

    public static void main(String[] args) {
        display();
    }
}
// 0.09999999999999998
// 0.12000000000000001
// 100.0
// 99.99999999999997
```

As you can see, it srews up money. The a specific class called BigDecimal that you should use.

## Char

String is not a primitive type in Java. The closest thing to it is `char`.
Needs single character and single quotes.

Chars are stored as 16 bit unsigned integers.

ASCII is basically only english characters. Unicode emcompasses 2**16 characters. All characters across all languages
globally.  
It does this by storing every character with a hexadecimal number called **code point**. That number maps to a
hexadecimal value which is stored internally as an integer.  
Java uses UTF-16 as its **encoding scheme**.

You can assign chars using a **unicode escape sequence**.  
e.g.:  
```
char c = 'B'; 
char c = 66;
char c = '\u0042'; // case sensitive 'u'
// All the same thing ^^^
// 0042 -> 0000 0000 0100 0010
```

It makes sense to use the unicode escape sequence if you're trying to use a character that you editor cannot display.

## Bool

Auto-initiliazed to `false`.  
Note that bit-depth varies from one JVM to another. Could be 1,4, etc. 

## Variable types

There are two types of variables:
* primitives
* object references

Role varies based on where it's declared, e.g. class level vs function level

**Instance variables** hold state, they're called instance variables because they're related to the instance of a class.  

**Local variables** are declared within a particular method.

**Static variables** or class variables, which are specific to a class, (vs. specific to a particular instance of a
class) apply to all instances of a particular type of class.  
Note that static variables can actually be accessed directly through the class object and do not need to be accessed
through an instance of that class.

Another note is that instance and static variables are also referred to as **fields** or **attributes**. Attributes is
likely the more common term between the two.

## Casting

Only possible with numeric to numberic (cannot cast boolean).  
Casting can be both implicit or explicit.  

**Widening** conversion is when you go to a **higher-order** type like `int` -> `long`.  
**Narrowing** conversion is the opposite.

implicit:
```java
int x = 65;
long y = x
float z = x
```

explicit:
```java
long x = 100;
int y = (int) x;
```

The compiler does not now that at run-time that `x` will be compatible with `int` so you have to tell it explicitly.

Note that there can actually be some loss of information with implicit casting but it's pretty rare.

## Object References

The following creates a student object where `s` is the object reference.  
```java
Student s = new Student();
```

The type of the variable is referred to as **reference type**.  
With primitives, the type of variable is the **primitive type**.

There are two categories of references types. References types, as mentioned as above, and **interfaces**. 

The declaration of `Student s` tells the program to allocate space for a reference variable `s` that points to a student
object. `new Student()` tells the program to allocate space for the actual student object.  Then the assignment operator
assigns the memory address of the created object to the variable name.

Objects are stored in a special chunk of memory by the JVM... the **heap**!  
Bit-depth for different object references can actually vary from one JVM to another.  

The **default value** for an object reference is `null` and is referred to as a **null reference**.

Performing an operation on a null reference will give you a **NullPointerException**. 

## Statements

They end with semi-colons.  
They are commands to be executed.  
They change program state to some degree.  
They are made of one or more expressions.

Note on recognizing **expressions**, each expressions is ultimately evaluated to a single value at run-time.

## Three types of statements

* Declarations
    * e.g. `int count = 25;`
* Expression statements
    * e.g. `count = 25;`, `getCount();`, `count++`
    * Assignments, invocation, increment, respectively
* Control flow statements
    * if/then, case


Only declarations can exist in the body of a class.  
Think how python allows invocation when assigning in `__init__`... Java does not allow this.

Note that while only declarations are allowed, there are many types of declarations:
* Field declarations
* Method declarations (this is just defining methods normally within the class)
* Constructor declarations
* Nested class & interface declarations
* Instance and state initializers

## Arrays

**Arrays** are container objects that store a fixed number of values of a single type.

Note that an array in java is actually an object while an array in c++ is simply a pointer.  

Declaring arrays is somewhat similar to c++ with some key differences.  
c++:
```c++
int scores[4];
```
For Java, both of the below work:
```java
int[] scores = new int[4];
int scores[] = new int[4];
```

Like c++ you can also initialize with values but size _must_ be inferred in Java whereas it can be specified in c++:  
c++:
```c++
int scores[4] {90, 80,97, 96};
```
For Java, both of the below work:
```java
int[] scores = new int[] {90, 80,97, 96};
int scores[] = new int[] {90, 80,97, 96};
```
Or you can just do c++-like initialization:
```java
int[] scores = {90, 80,97, 96};
int scores[] = {90, 80,97, 96};
```

Note that the syntax in the above example can only be used in a declaration statement. You cannot use it to re-initalize
an array. The below examples will actually throw errors:
```java
int[] scores = {90, 80,97, 96};
scores = {1, 2, 3, 4};
```

Arrays in java do not have a length method but they do have a length attribute:
```java
arr.length(); // does not work
arr.length; // works
```

This stuff about c++ isn't really true... Syntax is the same as java when creating objects on the heap. The other way of
doing things (basically, without `new`) creates the array on the stack.  
With Java, you have no choice but to create it on the heap (I think... even when you use the c++ stack syntax).

## 2-d arrays

```java
int[][] myArray = new int[4][2]; // int[n rows][n cols]
```
Java implements this as a single 4-element array, each element in the array points to a 2-element array.

Basically, the type of the array is an array of int arrays. It is a one-dimensional array where each element points to
another array.

Note that the number of columns does not need to be consistent from row to row:
```java
int[][] myArray = new int[2][];
myArray[0] = new int[5];
myArray[1] = new int[2];
```

This is convenient when storing thins like symmetric matrices:  
```
---------------------
|  7 | -2 |  6 |  2 |         
| -2 |  3 | 20 | 11 |         
|  6 | 20 |  9 |  5 |         
|  2 | 11 |  5 | -4 |         
---------------------
```

Note that the length attribute can also be used on a 2-d array but will only return the number of rows. 

## Methods

Objects have both **state** and **behavior**. State is object attributes/variable while behavior is the methods that one can call
off of an object. 

Note that the return type is not part of a method signature, just the method name and parameters.

Nit-picky terminology....  
When we're talking about a method definition, we refer to the input variables as **parameters** or **formal parameters**.  
In terms of method-invocation, when we call a method, we call them **arguments** or **actual parameters**.   
**Parameters** and **arguments** are the more common names.  
Think: a method has parameters, you pass it arguments.

Note that when calling a method that accepts a list as an argument.. just look:  
```java
int a = someMethod({1, 2}); // won't work
int a = someMethod(new int[] {1, 2}); // Would need to do this
```

## Method Types

### Instance Methods

**Instance methods** are methods of an instance of a class.  
We use the dot operator on an object reference to access instance methods of the object.  

An absence of the static keyword declaring a method as a **static methods** implies that the method is an instance
method. Static methods do not have any impact on object state. They have access to neither methods no variables from
within the class. This means that you cannot invoke an instance method from the same class. 

If they can't access other methods or variables, then what's their point? They are **utility methods**, meaning that
they typically take arguments as input and generate some sort of output. That said, static methods _can_ access static
variables as they are not object-specific. (Again, **static variables** are variables that are shared among all objects
of the same class). 

Static methods can directly access _other static methods_ from the same class. 

The main method is an example of a static method. As a result of this fact, `main` can only directly access other static
methods. It cannot access instance methods directly as instance methods _must_ be accessed through an instance of a
class. 

A static method in Java is as close to a function in python as you can get.

## How data is passed to methods in java

```java
void updateId(int newId) {
    newId += 1;
}

int id = 1000;
updateId(id);
System.out.println(id); // will print 1000


void updateId(Student s) {
    s.id += 1;
}

Student s = new Student();
s.id = 1000;
updateId(s);
System.out.println(s.id); // prints 1001
```

Literals/primites are ALWAYS passed by value. Objects are ALWAYS passed by object reference (which is still
technically pass-by-value). 

**Primitives** have 3 components, **logical name**, **memory address**, and a **value**. The logical name is simply the
name used to refer to variable in source code. The compiler converts logical names to memory addresses. 

## Method Overloading

The function signature must be different... Remember which part the function signature is. 

## Methods: varargs

Before Java 5, a method could only be invoked with a fixed number of args.  

Java 5 added **varargs**, which refers to variable length arguments. 

The varargs must be the last (or only) parameter of the method. 

```java
void foo(boolean flag, int... items) { ...
```

An array of any size of a series of comma-separated arguments can be passed:
```java
foo(true, new int[] {1, 2, 3});
foo(true, 1, 2, 3);
```

If the args are passed as comma-separated-values they are converted to an array. 

Why not just accept an array as an argument like:
```java
void foo(boolean flag, int[] items);
```
Varargs can simplify things a bit:
```java
// this
foo(true, 1, 2, 3);
// is easier than
foo(true, new int[] {1, 2, 3});
// and this
foo(ture);
// is easier than
foo(true, null);
// or
foo(true, new int[] {});
```

`printf` is an example of an elegant function implemented using varargs:

```java
System.oout.printf("DOB: %d/%d/%d", 1, 1 1991);
```

Note that in the `main` function you can actually sub the array parameter with a varargs parameter:  
```java
// from
public static void main(String[] args) {...
// to
public static void main(String... args) {...
```

## Constructors

The purpose of a **constructor** is to initialize the state of an object. 

Just like c++, if you don't make your own constructor, the compiler will make one for you with no parameters. 

Constructors have the same name as a class; parameters are optional. Constructors do not have return types.

**no-args constructor**. 

Note that if you create a constructor that takes args, java will not automatically create a no-args constructor. 

Note that return statements are occassionally used in constructors:
```java
class Student {

    Student(int id) {
        if (someCondition) {
            ...
            return;
        }
        // reachable code
    }
}
```

You might do this if you only want part of the constructor to execute if some condition is not met. 

Note that when overloading constructors you can use `this()` to access other constructors. The `this()` statement must
be the first statment and it can only appear once in the overloaded constructor. 


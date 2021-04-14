# Packages, String, and Information Hiding Design Principle

Note that people sometimes use the term **Encapsulation** and **Information Hiding** interchangeably. They are not the
same thing.

## Java API

The **Java API** is a library of well-tested classes.  
As of Java 8 there are about 4240 classes.  
These are part of the JDK and JRE. 

Classes are grouped into **packages**. A package is basically a directory on the file-system.  
Some common packages:
* `java.lang` - contains things like `String`, `Class`, and `Objectc`
* `java.util` - contains things like `ArrayList` and `HashMap`, all of the data structures
* `java.io` - contains things like `File` and `BufferedReader`
* `java.net` - networking
* `java.sql` - databases

Packages not only help with organization but also with **name scoping**. Java has two different packages called `Date`:
* `java.util.Date`
* `java.sql.Date`

Security - You might want certain aspects of a class to only be accessible from within the package. 

## Accessing packages

Pretty much always use `import`.  
Sometimes people will use the `fully-qualified` class name but that's rare. 

You can import specific classes **import on demand** with:
```java
import java.lang.*
```

This imports all of the classes from a package. 

`*` import can break your code at all. e.g.
```java
import java.util.*;
import java.sql.*;
```

Java won't know which `Date` to use.

This can be especially problematic when Java is updated and new classes are added, creating conflicts where they did not
exist before.  
It's generally better to use explicit imports so you know exactly where something came from. 

the **Fully-qualified** class name import would look like:
```java
java.util.ArrayList list = new java.util.ArrayList();
```

This wouldn't make sense with `ArrayList` because there's only one but if you wanted to use `Date` from both `java.util`
and `java.sql` you would need to do:
```java
java.util.Date utilDate = java.util.Date;
java.sql.Date sqlDate = java.sql.Date;
```

You could also explicitly import one and use the full-qualified class name for the other. Conflicts can also be resolved
with `import *`. The explicitly imported class name will take precedence. 

### Any problem with lots of imports
* Does not make your class bigger
* does not affect runtime performance 
* Compiler simply replace class names with fully-qualified names

Note that the `java.lang` package is import by default. All classes within it can be directly accessed without import.


## Create Packages & Classpath Management

To create a package you need a **package name** which is simply the keyword `package` followed by the name of the
package/package path. e.g.:
```java
package com.keith.utils;
//or
package com.semanticsquare.basics;
```

The package statement must be the first statement in the class and there can be only on package statement.  
Note that a package name is part of the class name. In a package statement you must have the full-qualified class name.  
Note that once you add your class to a package, you cannot simply run that class from the directory in which it's
stored. You _must_ run it from the root directory.

For example, if we create a package and it's stored in `javaindepth/src/com/semanticsquare/basics/` and it specifies
that it's part of `com.semanticsquare.basics`, then we need to run it from `javaindepth/src/` with the command:
```shell
java com.semanticsquare.basics.Basics;
```
You can also add `javaindpeth/src/` to your `CLASSPATH` to be able to run that command from anywhere.

Note that to compile this I actually had to compile it from the containing directory (I actually used the relative path 
from within `javaindepth/src`):
```shell
javac com/semanticsquare/basics/Basics.java
```

Note that third-party libraries also needed to have their locations specified in the `CLASSPATH`. It's only things like
`java.util` that don't need to be specified. 

If you don't have your classpath specified, you can actually do the following:
```shell
javac -cp
javac -classpath <root-dir-to-src>
```


So, it looks like anything that doesn't have a dependency other than `java.<utils/lang/etc.>` can just be compiled from
it's dir regardless of the classpath.  
If you don't specify the classpath, you can't compile anything that has a dependency other that
`java.<utils/lang/etc.>`.
If you have your classpath set to the current dir, everything else needs to be compiled from the `src` dir using the 
full path (note that this will only work dependencies specified as part of that package. Any third party dependencies
would need the classpath specified).  
If you have the appropriate classpath(s) specified, you can compile anything from anywhere.
Basically:
```shell
// Compiling a dependency that has no fancy dependencies

// for something without dependencies
(6si-py3) keith•java/javaindepth/src(main~!)
 » javac com/semanticsquare/basics/Student.java

// or
(6si-py3) keith•com/semanticsquare/basics(main~!)
 » javac Student.java

// Compiling something with a local dependency

//If you're using the current dir as the classpath:
(6si-py3) keith•java/javaindepth/src(main~!)
 » javac com/semanticsquare/basicstest/Basics.java

// and if you have the class set to:
// /home/keith/Documents/cpp_udemy/java/javaindepth/src
(6si-py3) keith•com/semanticsquare/basicstest(main~!)
 » javac Basics.java

// Note that it won't work at all if you don't have any classpath

// Then you can run from src
(6si-py3) keith•java/javaindepth/src(main~!)
 » java com.semanticsquare.basicstest.Basics

// or anywhere else!
(6si-py3) keith•~()
 » java com.semanticsquare.basicstest.Basics

```

You can compile everything within a dir using:
```shell
javac com/semanticsquare/basics/*.java
```

In simplest terms, for a compiled package to accessed, the package root must be specified in the classpath.

IDEs should handle all this shit on their own


## Naming Packages

The standard is basically the domain name in reverse.  
There's nothing special about the nested folders other than the fact that it reduces possibility of naming conflicts.


* lowercase alpha (rarely number)
* short (fewer than 8 characters)
* meaningful abbreviations, e.g. util for utilities
* acronyms are generally okay, e.g. Abstract Window Toolkit
* generally single-word
* never start with java(x)


## Access levels

they help with:
* meaningful organization
* name scoping
* _security_

When no access level is specified it is referred to as simply **default access** level.

Security refers to which packages are accessible outside of the package.  
They may be sensitive or simply irrelevant in many use-cases.

The default case is for classes to be private. If you only want a class accessible from inside a package then you just
do: 
```java
class someClass { ...
```

### Accessibility for class members

Inside the class:
```java
private int id = 4;
```
Inside the package: (Sometimes referred to as **package private**).
```java
int id = 4;
```
Inside package only + _any_ subclasses
```java
protected int id = 4;
```
Accessible anywhere (inside or outside the package):
```java
public int id = 4;
```

Private functions might be things like confirming that a list isn't empty as part of some other public method.

## String

Strings are in `java.lang.String;`.  
Remember that when anything is in `java.lang` it is a fundamental part of java.  

A **string literal** is a series of 0 or more characters enclosed in double quotes.

Remember that **character literals** are single characters enclosed in single quotes.  

Technically string literals are passed as **string objects**. Objects of the `java.lang.String`.  

You can actually also make a string object from a **character array**.
```java
char[] cArray = {'h', 'e', 'l', 'l', 'o'};
String s = new String(cArray);
```
create an empty object and then assigning something:
```java
String s = new String();
String s = new String("hello");
```
but the recommended approach is to simply do:
```java
String s = "Hello";
```

Internally string objects store text as character arrays. 

Java uses **UTF-16** for char which means that a string is a sequence of unicode characters. 

String are technically **immutable**. 

In short, they are immutable sequences of unicode characters.  

Note that the only objects that can be assigned with literals are strings and box primitives. 
e.g.:
```java
String s = "hello";
Integer i = 42;
```

### memory

all string created using string literals are stored in a special area of memory called **string pool**.  
(This doesn't happen to string created using the `new` keyword.  

If two string objects are created by the same string literal then they would both be represented by the same string in
the string pool.  
But if you create two objects of the same string using the `new` keyword then they will be represented by different
string objects.  
The string pool allows saving of memory. 

## String Manipulation

All basic stuff but one thing.

We can use `java.util.String` to look at the difference between an instance method and a static method.  

An **instance method** is any method that you call off of an object. Something like:  
```java
String s = "something  ";
s = s.trim();
```

Remember that, in relation to python, a **static method** is basically a non-member function associated with an object.  
These types of methods can be useful when there's a method that is not performed on an instance of a particular object
but is related to it. e.g.:
```java 
String s = String.valueOf(1.3);
```

## 3rd party utilities

* `apache.commons.lang` - 
* google's `guava` string utility classes

## String Pool and Interning

The main benefit of using the string pool is to save on memory.

* Strings (when created via string literal) 
    * are in the **string pool** which is in heap memory. 
        * There is only _one_ string pool.
        * The string pool is sometimes called the **string table**
        * All objects are stored on the heap but only strings created by string literal are stored in the string pool.  
    * Literals with the same content _share storage_
        * Even if they're in completely different classes or _even_ completely different packages
    * The process of building the string pool is referred to as **string interning**
    * Each string in the string pool is an **intern**
    * String interning exists in Python, Ruby, C#, JavaScript, etc.
* String (via new)
    * Stored in the same way as a regular object 
    * No shared storage even when they have the same content 

all of the below will refer to the same object in memory
```java
String s1 = "hello";
String s2 = "hello";
String s3 = s1;
```
As a result, the following would all evaluate to `true`:
```java
s1 = s2;
s1 = s3;
s2 = s3;
```
But if we were to create the following:
```java
String s4 = new String("hello");
String s5 = new String("hello");
```
Then the following would return `false`:

When `new` is used to create a new string object, a copy of that string will actually be created in the String pool and
a new object will be created in heap memory that is not string pool which will point to that locaion in string pool
memory.

So, in if not String object of "hello" exists, then creating one using `new` would result in two new objects.One in 
String pool memory and one in regular heap memory.  
If one already existed in String pool memory, then creating one using new would result in only a single new object.  
If no object existed, creating one without new would result in a single new object.  
If an object existed, creating one with new would result in no new objects.

### Interning

The first time the JVM encounters a string literal it:
* creates a new String object with the given literal
* Invokes the `intern()` method to see if an object already exists
    * it won't exist as this is the first time it's been encountered so it 
        * adds the new string to the string pool
        * returns a reference to the new object

The string intern method is basically:
```java
if (string in stringPool) {
    return existingReference;
} else {
    newStringReference = createNewStringRference();
    return newStringReference;
}
```

If the string object already exists:
* creates a new String object with the given literal
* Invokes the `intern()` method
* returns a reference to the original string object with that content
* the string object that was created in the first step is abandoned and will be garbage collected

### Weird situations with interning

The below demonstrates **explicit interning**.

```java
String s = "hel" + "lo"; // interned because known at compile time
String s1 = "lo";
String s2 = "hel" + s1; // not interned as variables are evaluated at run-time
```

Now let's say you wanted that to be interned if possible
```java
s2 = s2.intern();
```
After doing this, there will be nothing pointing to the location that `s2` was originally pointing to on the heap and 
that will subsequently be garbage collected.

Doing manual/explicit interning doesn't actually accomplish much of anything... just let the JVM do its thing.

The one exception to the is in NLP where it's possible that many identical strings could be created.

While combining a string literal and a variable won't perform constant folding:
```java
String s1 = "hello";
String s2 = "hel" + "lo";
String s3 = "lo";
String s4 = "hel" + s1; // not interned as variables are evaluated at run-time
final String s5 = "lo";
String s6 = "hel" + s5; // allows constant folding

s1 == s2; // true
s1 == s4; // false
s1 == s6; // true
```

## String Immutability

Why are strings immutable?  

### Interning

This allows for string interning!  
If you could change stuff it would be a whole mess!  

### Concurrency

Immutability alow allows concurrency/multi-threading (similar to list comprehension??).  
You can share a String object when multi-threading without any concern that the string will be changed elsewhere during
the operation.

### Security

Security is also a concern. Mutable strings in objects in security applications could lead to vulnerabilities.  
An example of where this could lead to a vulnerability is with `FileInputStream()`. If you were to pass a string, then
authenticate, then change the string, you might be able to access something that you're not supposed to be able to
access.

## String Concatenation

Basic string concatenation just uses the plus operator:
```java
String s = "hel" + "lo"; // hello
String s1 = "hello " + 123; // hello 123
String s2 = "hello " + 123 + 10.5; // hello 12310.5
String s3 = 123 + 10.5 + " hello"; // 133.5 hello
```

### Actually mutate strings?

#### StringBuilder

Introduced in Java4

```java
StringBuilder sb = new StringBuilder();
sb.append("hello");
sb.append(" world!");
String s = sb.append(" Good").append(" morning").toString();
```

So, we've created a String in a few different steps using a StringBuilder and then we convert the StringBuilder object
to a String using the `toString()` method and assign that to a String object `s`.

StringBuilder has other methods like:
* length
* delete - deleting characters between two indices
* insert - inserting at a particular index
* reverse
* replace

`append()` and `toString()` are the most commonly used methods.

Note the StringBuilder is not **synchronized**. As a result, you might need to be some funky stuff to support concurrent
operations.

#### StringBuffer

Was used before the introduction of StringBuilder in Java 5.  
Deprecated and should not be used.  

StringBuilder is the recommended alternative mostly because it is faster.  
StringBuffer is synchronized and, because of that, it slows down the program.  
It's slower because synchronization ensures that only one thread is modifying the StringBuffer at any given moment.
This ended up being a pain because programmers were apparently using it mostly in single-threaded applications and not
sharing it across threads.

So, for multi-threading, use StringBuffer. For single-threading, use StringBuilder.

StringBuilder is built to be largely compatible with StringBuffer (i.e. it has all the same methods that work in all the
same ways).

## String Concatenation Performance

Using the plus operator is a fine way to combine a few strings. That said, it should not be used to combine more than a
few strings unless performance is irrelevant.

With each concatenation using the plus operator:
* Contents of both string are copied
* new StringBuilder is created and appended with both strings
* return string via a `toString()`

This can be both time consuming (O(N^2)???) and space consuming (due to all of the copies).  

In a benchmark using 16500 iterations:  
> StringBuider = 300x faster than the String + operator  
> StringBuilder = 2x faster than StringBuffer  

## Information hiding

It's better to write a good program than a fast one.  
A good program can be made faster later if necessary. 

Encapsulation is core to good OOP, but does not result in good design in and of itself.  

let's say you have the following class:
```java
public class Student {
    public int id;
    public String name;
    public String gender;

    public boolean updateProfile(String name) {
        this.name = name;
        return true;
    }
}
```

By declaring all objects attributes as public variables it results in **tight coupling**.

### Tight Coupling

* Can't enforce **invariant**, or a set of valid variables for a value
    * can't retrict something like gender because that attribute can be accessed directly
* Can't change **data representation**
    * Can't change gender from String to int as the client program might still try to access it as a string

In public Classes, **accessor methods** should always be used in place of **public fields**. 

```java
public boolean setGender(String gender) {
    assert (gender in genderList);
    this.gender = gender;
    return true;
}

public String getGender() {
    return gender;
}
```

The first method is an **accessor** method and the second is a **setter** method.

**Loose coupling** is things like type-checking take place for you automatically and you're the programmer doesn't even
need to know the implementation details. There's no meddling directly with data fields.






# Packages, String, and Information Hiding Design Principle

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



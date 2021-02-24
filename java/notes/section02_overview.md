# Java: A High-Level Overview

byte-code vs. machine code - the main different is that machine code is a set of instructions in machine language
(or binary) which can be directly executed by a CPU white bytecode is a non-runnable code generated be compiling a
source code that relies on an interpreter to get executed (i.e. JVM).

## Platform dependency

### operating system

Different operating systems use different executable file formats: 
* PE - windows - Portable executable 
* ELF - Linux - Executable and linkable format

System calls
* file opening
* paths
* directory information
* printing to console

### Hardware

Processor
* x86
* ARM


## Interpreter

A type of program for executing source code  

It is essentially a virtual machine that emulates a CPU. 
The virtual machine does this similar to have the CPU to executes machine language in the fetch and execute cycle.

### Fetch and execute

* CPU
* memory
* disk

#### CPU Fetch and execute life-cycle

When the program first gets executed/started, it gets loaded in to memory (typically as machine code).  
The machine code to a sequence of instruction where each instruction is a series of `0`s and `1`s.  
The CPU then fetches an instruction from memory and executes it. The CPU may also fetch any data needed to execute the
instruction.  
Any data resulting from the execution of an instruction will the be sent back to memory.  
The CPU then fetches the next instruction and then executes it.  
This is done until all instructions have been executed... This is basically the fetch and execute life-cycle. 

#### Interpreter Fetch and execute life-cycle

Also fetches instructions from memory.  
Unlike the CPU cycle, the instruction is a statement in the source code.  
The Interpreter has to determine what is necessary to carry out that statement. (This and the above are also done by a
compiler).  
Interpreters maintain a library of compiler machine code and it just executes the appropriate pre-compiled machine code.  
Reiterating - the interpreter **does not generate machine code**. It simply uses it own compiled machine code to
accomplish what the interpreted source code directs.

One main advantage of the interpreter is platform independence. An interpreter specific to that platform is the only
thing that's required... then any code written in that interpreted language can be executed. 

### Pros and cons:

Pros:
* Platform independence
* no compilation step
* easier to update (don't need to re-write, compile locally, and then deploy... just re-write)

Cons:
* Orders of magnitude slower than compiled code
    * Memory access operations are costly
    * Source code is reinterpreted every time
* Interpreter is loaded into memory with the source code 
    * So, you literally have an extra program running (not actually a big deal but good to know)

Java manages to take the fast execution from compiled languages and achieves platform independence similarly to
interpreted languages.  

Java source code is first compiled by the java compiler into java bytecode. It's not the machine code the most compilers
product but rather an intermediate format. That java byte code can then be interpreted by any system that has a java
interpreter installed. 

Interpreted language:
1. source code
2. interpreter
3. results

Java:
1. source code
2. java compiler
3. java bytecode
4. java interpreter
5. results

The java interpreter is know as the **JVM**. The Java Virtual Machine. Every JVM is platform specific but all java
bytecode can run on all JVMs.  
Essentially, platform independent interpreters help achieve platform independence.  

The main difference between the java interpreter and other interpreters is that java interpreter interprets java 
bytecode instead of source code.

Note that while JVM is als an interpreter and the bytecode is interpreted, java bytecode is compact (literally smaller
files, you can move things across networks faster. This is partially because of low network speeds when java was created
and the desire to move bytecode between different devices), compiled, and optimized (to some degree) in ways that other 
interpreted languages are not. Because it is already compiled, things like syntax checking have already been performed.

The JVM also performs some additional optimization called Just-in-time (JIT) compilation. (Done at execution time by the
JVM).

## JVM

Why is it called "virtual"? The JVM is an "abstract computing machine". It's like a real CPU (computing machine). It has
an instruction set, which executes, which is the java byte code.  
Also manipulate memory at run-time.   

Core Responsbilities of the JVM:
* Loading & interpreting java bytecode
* security
    * as mentioned above, bytecode was meant to downloaded across networks, need to make sure nothing is harmful
* Automatic memory management - unlike c and c++
    * java is not only easier but also safer (no leaks!!)


Note that there is an instance of a JVM for each program that is running.  

### JVM Architecture:

* We have a program called Hello.java  
* We compile it into bytecode which is called Hello.class  
* We then was to run it so we type `java Hello` into the command line.  
* An instance of JVM is then launched and memory is allocated for the JVM. This JVM memory is called **runtime data areas**. There are two types of memory here.. **Heap** memory and **Method Area** memory. 
* The JVM then need to load Hello.class, the bytecode from Hello.java.  
* To do this, the JVM invokes a component called **Class Loader** which locates Hello.class and loads the corresponding bytecode into memory. The bytecode is the verified by the **Bytecode Verifier**. It ensures that the loaded file is not corrupted.  
* The instructions to execute are then passed to the execution engine which contains the JIT Compiler and the Interpreter.  
* The JVM also performs other operations such as garbage collection to reclaim memory that's no longer pointed to by any variables and has a security manager to ensure there's no malicious code. If you want to restrict any bytecode from accessing your file-system, the security manager can ensure this by running the bytecode in a more restricted environment called the sandbox environment.  

Other components that constitute a JVM are:
* Within the runtime data areas (memory)
    * JVM Stack
    * PC
    * Native Method Stack
* Between the JVM and runtime data areas
    * netive method interface
    * native method libraries


### JIT Compiler

* bytecode interpretation is much faster
    * Java butecode is compact, compiled, and optimized
* Just-in-time (JIT) compilation
    * Identify frequently executed bytecode - **hotspots**
    * JIT converts these hotspots to machine code
    * This machine code is then cached. 
    * Cached machine code has faster execution because it is not reinterpreted every time it runs
    * This caching is referred to as **dynamic compilation**


Basically, after running a thousand times it would be like, "oh wait, I keep using this stuff, why do I keep
interpreting?" and then convert that block of code into machine code. If it keeps getting executed, futher optimization
may be performed. Other possible adjacent methods might not be executed that often and will be re-interpreted every
time.

How it actually works can be different/more complex but this is the gist.  

## Java SE

* Java SE - **Java Standard Edition**
    * Used to develop standalone applications for desktops & servers
* Java EE - **Java Enterprise Edition**
    * Large-scale applications for servers
    * Large numbers of users using the server at any given moment. 
        * e.g. amazon
    * _Built on top_ of Java SE
    * This is all for when you need more than what jave SE offers
    * It's now called **Jakarta EE** (Eclipse renamed it)
* Java ME - **Java Micro Edition**
    * Applications for resource-constrained devices
        * e.g. phone
    * Uses a subset of Java SE


### Java SE Language Specifications

* JLS  - **Java Language Specifications**
    * Defines the syntax and semantics of the language and the rules of the language
    * Written by the language designers including James Gosling
    * It's a pretty intense book...
* JVMS - **Java Virtual Machine Specification**
    * Defines how a JVM should work
    * Also specifies the bytecode instruction set
* **Java API Specification**


The official specification is the **Oracle JDK**, the **Oracle Java Development Kit**  
There's also the **OpenJDK**. You have to pay for the Oracle JDK if you're using it for commercial purposes.  
Other specifications are:
* AdoptOpenJDK
    * Provides an additional JVM called **OpenJ9** which was originally developed my IBM.
* Amazon Corretto
* Red Hat's OpenJDK


This are all free JDKs^^  
All open JDKs are part of the OpenJDK project. Was originally proprietary to Oracle but Oracle made it open source.  
All of these open source providers include the Java API and a JVM implementation called **Hotspot**. (Hotspot is written in
c++).

A JDK contains the JVM, that Java API (the java library), and Dev tools like the java compiler.  
The JDK is also referred to as the Java SDK - **Java Software Development Kit**. An SDK is more general than JDK or Java
SDK.  

The JVM and Java API together comprise the JRE - **Jave Runtime Environment**

You can actually download a JRE separately because you might only need to run Java code, not develop it.  
This only existed until Java SE 10.  

For Java 11 SE and onwards they've created a tool called jlink. This can be used to create a custom JRE which can
actually be smalled than a regular JRE.  

JSR - **Java Specification Request** - the features in a particular java release, e.g. Java SE 14 has JSR 389.

The Process of developing the JSR is called the JCP - **Java Community Process**

## Releases

two a year, march and september, this process started with Java 10.  
Before that releases were much less frequent, sometimes many years.  
They weren't agile... innovation slowing... They were trying to big out big releases (8 was pretty big, 9 also big).  
The big releases were slowing the release of smaller features. So they started doing the frequent releases that were
much smaller, fewer changes and small releases. 

Java 1: 250 classes, slow 1996  
Java 1.1: 500 classes, little faster 1997  
Java 2: > 1500 classes, much faster (JIT) - 1998  
Java 5: 2500 classes, generics, multi-threading - 2004  

There are also preview features, they're not standard and may actually be removed afterward. 

## Setting the Classpath Environment Variable

Simply a path on the file system for locating java classes, can include more than on path. It's used in both
compilation and execution.  

Note that with class paths, it checks them in order and will go with the first one it finds. 

classpath = `/foo:/bar`

So, first it would check `foo` then it'll check `bar`.

Only required when running things from the command line.  
Note that classpath is assumed to be the current directory if no classpath exists.  
You can add a dot `.` to the classpath so that it will check the current directory.  
If a classpath does exist and none of the paths is a dot, then it will not assume the current directory. 

## Writing a Java Program

### Structure

Java programs consist of classes. Each java program must have at least one.  
From a class you can create one or more objects. An object is central to object oriented programming. 

what constitutes a class:
* variable declarations
* constructors - statements
* methods - statements
* nested classes - statements


Quick note:  
You file name and class name don't actually need to be the same **unless!** it's a public class (which is the standard).

### The main method

program starts running at `main()`  
When you run something from command line:  
`> java HelloWorld`  
* JVM loads the bytecode of HelloWorld.class into memory
* then it invokes `main()`
* Must be declared as `public`, `static`, and `void`.
    * Without this it can still compile, just can't execute 
    * (maybe unless you call that specific function? I don't have a main in my UDFs...)
* From `main()` we invoke other code that doesn't necessarily have a main method.
* Program ends when the `main()` method ends.




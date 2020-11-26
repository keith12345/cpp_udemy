## c++ Stings

Part of the standard namespace.  
Part of the standard template library.  
Contiguous in memory with dynamic sizes.  
Work with input and output streams.  
Can be converted to c-style strings if necessary but are safer.  
Standard operators work similarly with c++ styles to that in python (`+`, `=`, etc.)

```c++
#include <string>

string s1; //empty
string s2 {"Keith"}; // Keith
string s3 {s2}; // Keith
string s4 {"Keith", 3}; // Kei
string s5 {s3, 2, 3}; // ith - uses starting index and length
string s6 (3, 'X'); // XXX - remember that this is called constructor syntax
```

Note that cpp strings are always automatically initialized to empty strings

### Concatenation

```c++
string part1 {"C++"};
string part2 {"is a powerful"};

string sentence;

sentence = part1 + " " + part2 + " language";
  //  C++ is a powerful language

sentence = "C++" + " is powerful"; // will not work as they are compiled as string literal
```

### Subscription

```c++ 
string s7 {"Keith"};

cout << s7[0] << enddl;
cout << s7.at(0) << endl; // K
cout << s7.at(0) << endl; // K

s7[0] = 'k';
cout << s7 << endl; // keith
s7.at(0) = 'l';  
cout << s7 << endl; // leith
```

We can also iteraget over a string:  

```c++
for (char c: s7) 
    cout << c << endl;
// l
// e
// i
// t
// h
```

We can also do some janky shit like this:

```c++
for (int c: s7) 
    cout << c << endl;
// 108
// 101
// 105
// 116
// 104
```

Note that it looks like some versions of c++ (or perhaps different compilers) will actually print the null character.

### Implicit conversion

c++ will actually implicitly convert/coerce types for c-style strings/chars/string literals when compared with a c++ style string.



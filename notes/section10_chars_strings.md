# Chars and Strings

## Character Functions

* takes a single character as input
* they either perform a conversion or return a bool about the character

Example bool functions:
```
isalpha() - True if 'c' is a letter
isalnum() - true is 'c' is a digit or a number
isdigit() - True is 'c' is a digit
islower() - True if 'c' is lowercase
isprint() - true if 'c' is a printable character
ispunct() - True if 'c' is a punctuation character
isupper() - true is 'c' is an uppercase letter
isspace() - true is 'c' is whitespace
```

Character conversion functions:
```
toupper()
tolower()
```

## C-style strings

in simplest terms, they are a series of characters stored contiguously in memory.  
They're implemented as an array of characters, so you can you array-style subscription syntax. They are terminated with a null value (character with a value of `0`). This looks like `\0`.
Terminating null-values are automatically added even if you don't speicify them.
C-style strings are frequently referred to as "zero" or "null-terminated" strings. 

Refresher - we've been using string literals so for. A string literal is a series of characters wrapped in double quotes. String literals are constants.

To create a mutable c-style string, you would need to specify that string as an array;  
```c++
char my_name[] {"keith"};
```

Note that with the above char array, it will only allocate enough space in memory for `6` characters with the 6th character a null. If we want to be able to add to a string, we need to initialize in such a way that there' si sextra space:  
```c++
char my_name[8] {"keith"};
```

The above will leave room for three terminating nulls, two of which can be utilized to extend the string `keith`.

Not initialize strings is generally not a good thing. Given the below:  
```c++
char my_name[8];

// you would not be able to do

my_name = "keith";

// because nothing has been initialized, you're not sure what you're going to get (might not even be nulls)
// So you'd want to write

strcpy(my_name, "keith"); 

// This essentially copies the string over element by element. 
// If you're going to declare but not sure what you want to contents to be, the right approach would be

char my_name[8] {};

// If we do the above, we can then do the following:

my_name = "keith";
```

There are other functions in the c-string library for:  
* copying
* concatenation
* comparison
* searching
* etc.

Note that any time you're using c-strings, they _must_ be terminated in a null.

```c++
#include <cstring>
strcat(some_string, "something");  // concatenation
strlen(some_string);
strcmp(something, "something"); // Compares strings. Returns -1 for different 
```

There are other general purpose functions in `cstdlib` which are used to convert strings to other (numerical) types. Some different c-string libraries to include are:
```c++
#include <cstring> // for c-string style function
#include <cctype> // for character-based functions
#include <cstdlib> // converting to numeric
```

## String functions

```c++
strcpy(string2, string1); // note that this copies from right to left
strcat(string2, "more string"); // This concats the string on the right to string2
strcmp(string1, string2); // to check whether these are identical
```

### Get line

`cin` only gets the first non-space-separate string... but what if you want moar?

```c++
char some_string[50] {};
cin.getline(some_string, 50); // This will take the first 50 characters of input
```

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

### String Methods 

#### substring

```c++
string s10 {"This is a test"};

cout << s10.substr(5, 2) << endl;
string s11 {s10, 5 , 2};
cout << s11 << endl;
```

Both output `"is"`

#### Substrings

`.find()` returns the index of the first instance of a particular string:

```c++
string s12 {"Another test"};
cout << s12.length() << endl;
cout << s12.find("test") << endl;
// returns 8
cout << s12.find("yo") << endl;
// supposedly should return string "npos" but in my case returned a MASSIVE number
cout << s12.rfind("er") <<
// returns 5
cout << s12.erase(0, 2) << endl; // argument are starting index and length of string of delete
cout << s12.erase(5, 5) << endl;
cout << s12.clear() << endl; // won't work, can't print void
// other test
// other
```

Note that, just like python, c++ supports command assignment (`+=`) string concatenation.

Taking input is slightly different with c++ strings from how it is with c-strings.  

```c++
cin.getline(s13, 50); // c-style string
getline(cin, s14); // Reads until \n
getline(cin, s15, 'x'); // read entire line until 'x'
```

### Implicit conversion

c++ will actually implicitly convert/coerce types for c-style strings/chars/string literals when compared with a c++ style string.

```c++
string s8 {"test"};
char s9[7] {"tester"};
cout << (s8.at(0) == s9[0]) << endl;
// prints 1
```

## Miscellaneous

### size_t

When a program has no way of knowing how large a number might get, it will be of the type `size_t`, at least when dealing with things like the length of an array of vector. `size_t` is necessarily unsigned:  
```c++
char some_string {"This is my string"};
size_t l = strlen(some_string);
```


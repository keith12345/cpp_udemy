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


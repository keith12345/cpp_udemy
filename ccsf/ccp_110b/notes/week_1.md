    ## Vocab

    * `<<` - stream insertion operator
    * stream - series of characters
    * `>>` - stream extraction operator
    * assignment statement - essentially remember that assignment is not an equation
        * in assignment, instead of saying something "equals", say something "gets" a value
        * assignment statement structure = `<variable> = <expression>;`
    * literal constant - literal value - literal - value - all refer to e.g. some number, a char, etc
    * double - don't use float... careful about measuring equality with doubles
    * implicit conversion - int promoted to double when operating with double, but narrowed to fit into declared variable when assigned
    * chars are numbers under the hood... this works: `for (char ch = 'A'; ch <= 'Z'; ch++)`
    * constant styling:
        * global constants should be all uppercase separated with underscores
        * Should be declared at the top of the file
    * whitespace - spaces, newline, horizontal tab, vertical tab **remember new line**
    * CPU - what actually runs a program. Each type of CPU has its own machine language.
    * control unit - One of the two main parts of a CPU
        * coordaintes all of the computer's operations
        * responsible for determining where to get the next instruction and regulating the other major components
    * arithmetic and logic unit - alu - the other of the two main parts of the CPU
        * designed to perform mathematical operations
    * fetch/decode/execute cycle - the running of a program
        * fetch - the CPU's control unit fetchers, from main memory, the next instruction in the sequence
        * Decode - the instruction is encoded in the form of a number The control unit decodes and generate electic signal
        * Execute - signal routed to appropriate component of computer, signal causes component to perform an operation
        * rinse and repeat
    * main memory - RAM - computer's work area, where cmoputer stores a program and its data while it is running.
    * bit - binary digit 0 typically tiny electrical components that can hold either a positive or a negative charge
    * secondary storage - harddrive
    * two main categories of software
        * system software - programs that control and manage basic operations of a computer
            * Operating system - manages devices connected, allows data to be saved and retrieved from storage devices, allows programs to run
            * Utility program - performs specialized task to enhance computer's operation of safeguards data.. Virus scanner, file compressions, data backup
            * software development tools - compilers and IDEs
        * Application software - programs that make the computer useful for every-day tasks - powerpoint
    * 5 major hardware components of a computer
        * motherboard, CPU, GPU, RAM, storage
    * Low-level language - machine code / byte code - c++ has low-level capabilities
    * source code - something that a human wrote
    * source file - where source code is saved
    * preprocessor - reads source code, searches for preprocessor statements
    * pre-processor statement - basically something beginning with a `#`
    * compiler - this is where syntax errors are found, compiler will produce object code or an object file
    * Object file - like executable code but has unresolved external references. Combine with the unresolved external references will make it an executable file
    * Linker - combine object file with necessary library routines to create an executable file which a computer can run
    * portability - usability of the same software in different environments
    * Things common across all programming languages
        * Key words - reserved words with a special meaning in a language
        * Programmer-Defined Identifiers - symbolic names created by the programming, func names, variables
        * Operators - + - etc
        * Punctuation - ; , : etc
        * Syntax - puttin' everything in the right place
    * define variable - causes a variable to be created in memory
    * declare variable - does not necessary cause a variable to be created in memory
    * Three step process of a computer program
        * gather input, perform process, output
    * line vs. statement - a line can be empty...
    * Four main items to identify when defininf what a program should do
        * purpose, input, process, output
    * Visaulize a program running
        * pseudocode
    * hierarchy chart
        * structure and flow of a program
    * desk-checking
        * read though a program or portion of it, step through each statement, write down what is happening to debug
    * `//` - beginning of comment
    * `#` beginning of preprocessor directive
    * `<>` - encloses a filename when used with `#include` directive
        * note that they do not require semi-colons because they are not statements, they are directives
    * `;` marks the end of a statement
    * common escape sequences:
        * `\n` - new line
        * `\t` - horizontal tab
        * `\a` - alarm - causes the computer to beep
        * `\b` - backspace - cursor backs up
        * `\r` - return - go to next line
        * `\\` - print a `\`
        * `\'` - single quite
        * `\"` - double quote
    * don't forget about types:
        * **short** int 
            * typically 2 bytes
            * -32,768 -> 32,768
        * **unsigned short** int
            * typically 2 bytes
            * 0 -> 65,535
        * **int**
            * typically 4 bytes
            * -2,147,483,648 -> 2,147,483,647
        * **unisigned** int
            * typically 4 bytes
            * 0 -> 4,294,967,295 
        * **long** int
            * typically 4 bytes
            * -2,147,483,648 -> +2,147,483,647
        * **unsigned long** int
            * typically 4 bytes 
            * 0 -> 4,294,967,295 
        * **long long** int
            * typically 8 bytes
            * -9,223,372,036,854,775,808 -> 9,223,372,036,854,775,807
        * **unsigned long long** int 
            * typically 8 bytes 
            * 0 -> 18,446,744,073,709,551,615
        * **float**
            * typically 4 bytes
            * `-3.4E-38 -> 3.4E-38`
        * **double**
            * typically 8 bytes
            * `-1.7E-308 -> 1.7E308`
        *  **long double**
            * typically 8 bytes but up to 10
            * `-1.7E-308 -> 1.7E308` but up to `-3.4E4932 -> 1.1E4832`
        * Note that you can specify types like this:
            * `long amount = 32L;`
            * `long long amount2 = 32LL;`
            * `float amount = 32F;`
        * Remembers that `char`s are just fancy integers mapped to characters
            * `s = 'a'` - stores `char` `a` -> `65`, is 1 byte
            * `s = "a"` - stores `string` `a\0` -> `65, 0`, is 2 bytes
        * Remember that `\0` terminates string literals
        * Note that all double and float are signed
        * the `e` can be uppercase or lowercase
* Other ways to express numbers
    * hexadecimal - base 16
        * precede by `0x`:
        * `0xF4` would be a hexadecimal `F4`
    * octal - base 8
        * preceded by a `0`
        * `031` would be an octal `31`
* big numbers:
    * given `47,281.97`
    * `4.728197 x 10^4` in scientific notation
    * `4.728197` is called the mantissa and is multiplied by a power of `10`
    * computer typically use `E` notation to represent floating-point values.
    * In `E` notation, `47,281.97` or `4.728197 x 10^4` becomes `4.728197E4`
    * works for negatives as well: `0.00072` or `7.2 x 10^-4` becomes `7.2E-4`
* initialization techniques:
    * `int value = 5;` - most common
    * `int value(5);`
    * `int value {5};` c++11 or higher (does type checking)
* Associativity - when to operands have the same preference, perform left to right
* c++ does **not** have a power operator - uses `<cmath>`
* remember casting `static_cast<DatType>(value);`
* `iomanip` stuff
    * `setw(n)` establishes print field of `n` spaces
    * `fixed` dispalys float-point numbers in fixed-point notation
    * `showpoint` - causes a decimal point and trailing zeros to be displayed, even if there is not fractional part
    * `setprecision(n)` - sets precision of floating point numbers
    * `left` causes subsequent output to be left-adjusted
    * `right` causes subsequent output to be right-adjusted
* `std::getline(std::cin, var)` - to get whole line of input
* `std::cin.get()` - `cin <<` cannot capture things like spaces and new lines (so you can't skip a `cin <<`)
    * you can do a "Press any key to continue" with `cin <<`
    * This also means that a `std::cin.get()` following a `cin <<` will capture the new-line character...
        * If you want it to capture something other than that new-line character you'l have to clear the buffer


Remember why this happens:
```c++
#include <iostream>
#include <string>
using namespace std;

int main() {
    int num1;
    int num2;
    string mystring;

    cout << "Enter two integers: ";
    cin >> num1;
    cin >> num2;
    cout << "You entered " << num1 << " and " << num2 << endl;
    cout << "Enter a string: ";
    getline(cin, mystring);
    cout << "You entered: " << mystring << endl;
}

// Enter two integers: 45 56
// You entered 45 and 56
// Enter a string: You entered:
```

This means that my explanation of program 2.9a was not quite complete. When the user types "45<space>56" and presses 
enter, what goes into the input stream is
45<space>56\n
That a total of six characters in the input stream. The six characters are 4, 5, <space>, 5, 6, \n. Make sure you 
understand what the six characters are and why.

Furthermore, this means that at the conclusion of program 2.9a, there was still a newline character (\n) sitting in the
input stream. In program 2.9a, this didn't matter to us. Everything worked fine. However, when we execute the getline()
function in program 2.9b, the very next character in the input stream is a newline character. So the getline() function
places an empty string into the variable mystring, consumes (skips over) the newline character, and then execution goes
on to the next statement in the program.

You can clear it up with `cin.ignore();`

all of the below inputs and extractions would result in the same variables:
```c++
// extraction one
cin >> hours >> payrate;
// extraction two
cin >> hours;
cin >> payrate;

// input one
~~~78~~~~49~~~\n
// input two 
~~~78~~\n~49~~~\n
// treat tildes as spaces
```
Any combination of the above would result in the same thing.

Note that when extracting an int, the extraction operator will stop extractor once the input cannot be an `int`. If it's
extracting a double, it'll stop when it can't be a `double`... etc..

pop quiz!  

Suppose that i is an int variable, ch a char variable, and x a double variable. What would be assigned to i, x, and ch 
if the following statement were executed?  
`cin >> x >> ch >> i;`
First the stream extraction operator would skip over all of the leading whitespace. It would then extract the double 
value 13.72 to place into the variable x. It would stop reading the value for x when it reached the character "w" 
because "w" cannot be part of a double value. It would then read the single character "w" and place it into the 
variable ch. It would then begin looking for an int variable to place into the variable i. It would skip over all of the 
whitespace which appears after the "w", but would not find an int value for i. So it would the stop and wait for the 
user to enter more data into the input stream.


## More on the compiler/linker:

* Programmer writes source
* compiler into binary. executable binary = executable program
* executed by machine

* compiler errors start with the letter `C`
* linker errors start with the letters `LNK`

When a compiler receives a source file:
* Evaluates all pre-processor statements
    * e.g. performs all includes
* Performs contsant folding - i.e. combines any constants possible so that time is not wasted running the program
* Then the compiler compiles everything including all of the include libraries
    * Compilers have a few settings to determine how this actually happens
        * Solution Configuration
            * Set of rules that applies to the building of a project
            * Typically set to debug
            * The two defuault options are typically debug and release
                * Something to know about debug vs release is that debug **does not** optimize your code **on purpose**
                    * if, for example, you initialize a variable in one step and then return it in another, this will happen in two steps in debug mode but _should_ happen in a single step in release mode.
                    * Again, this is to make your code easier to debug, but it will run slower without these optimizations.
                    * Note, that there are actually other steps that the compiler takes to make your code even more verbose (apparently)
        * Solution Platform
            * What platform are we targeting with our current compilation
            * typically x86 or win32 (these are actually the same thing in this use case)
                * technically Win32 is an API of windows, a set of OS functions provided by windows
                * x86 is a processor architecture / CPU family
            * The two default options are typically x64 and x86 
            * Other projects might target android as a platform
    * Note that header files do not get compiler, they get "included" and then compiled where they were incluced.
    * Each cpp file get compiled individually into an object file. typically *.obj or *.o
        * each compiled file is called a translation unit, a translation unit results in an object file
        * c++ doesn't care about files... those are just something for humans. c++ takes those files and puts it into a form that it can work with
        * java expects class name to be tied to file name and folder heirarchy to be tied to a package... c++ doesn't care
        * if you include other cpp files in your main cpp files, you're going to end up with one translation unit and one results object file
            * This elucidates, to some degree, the difference between a translation unit and a cpp file
            * If you don't include your other cpp files then you'll need to add prototype declarations for any functions that you. 
                * Your compiler will trust that these functions do in fact exist and will look for them while performing linking. 
                * As long as the function that you declared exists in another .cpp that's been compiled to an obj file, the linker will find it and add it to the executable
                * Note that if you declare a prototype for a function the doesn't exist, you won't get a compiler error but instead you'll get a linker error because it's the linker that tries to find the function decraled with that prototype.
            * I can't tell if there's another wrong with include multiple other cpp files... you might just get multiple declarations which you can solve by `inline`ing them.
    * Once these cpp file get compiled, they need to be linked via the linker

Linker:
* Takes all of the obj files and combines them into one .exe file
* When linking, how does the linker know which file ro actually... run..?
    * it needs an entry point, e.g. the `main` function
    * The entry point doesn't actually have to be called main
* If you declare a prototype to something incorrectly or to something that doesn't exist but you never use that function, it won't actually generate an error because it won't try to link
* if you define a function but never use it (as oppose to declare a prototype) and then function has an error or uses a function that has an invalid prototype that can't be linked, this will cause an error as the compiler doesn't know that it might not be used elsewhere by _a different_ cpp file
    * Note that you can actually avoid this with the `static` keyword
    * when used to define a function outside of a class, `static` gives the name "internal linkage", meaning that it is only accessible with the translation unit that contains the definition.
        * This is why if there's something that's incorrect in the function definition but it's not used within that file, you won't actually get any compiler errors
    * if a `static` function is defined in a header file and included for multiple cpp files, then each of those cpp files will essentially have their own version of that function
    * Another typical way to go about this is to use `inline` which basically copy and pastes the function "in-line" wherever that function's name appeared
    * Maybe the best way is to make sure that the include appears in only a single translation unit whenever possible
    * There should typically be a way to avoid using `inline` and `static` in these ways
* note that there's also two different types of linking
    * static linking
    * dynamic linking
    * More on these later....

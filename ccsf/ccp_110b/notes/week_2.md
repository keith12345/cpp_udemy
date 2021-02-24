pretest loop - a `while` loop is a pretest loop meaning that it tests the condition before it start
counter - variable that is regularly incremented or decremented in a loop
post-test loop - a `do-while` loop is a post-test loop meaning that it checks the condition to determine whether it should run again
conditional loops - executes as long as a condition is met/exists
count-controlled loop - a loop using a counter is a count-controlled loop - a for loop
loop-header - the first line of a for-loop, not that **all** expressions can be eliminated in a loop header
initialization expression - the first expression in the loop header
test-expression - the second expression in a loop-header
update-expression - the third expression in the loop header
multiple-initialization - e.g. `for (int i = 1, int j = 1; i < 5; i++, j++) { ...` 
sentinel - special value that cannot be mistaken for the member of a list, signals that there are no more values
writing data to a file - literally just saving data
reading data from a file - ya know
two types of files - text files and binary files
text file - typically encoded in ASCII or Unicode
binary file - contains data not converted to text
sequential-access file - access data from the beginning of file to the end of the file; can't skip to the end. Think cassette
random-access file - direct-access file - you can jump directly to any piece of data in the file. Think CD
`<fstream>` - defines the types `otstream`, `ifstream`, and `fstream`
`ostream` - output file stream, when writing data
`ifstream` - input file stream, when you want to open an existing file, Note that it will return `false` if there is no more data to read
`fstream` - file stream, used to open files for reading, writing, or both
`break` - only impacts the loop it's in, not any outer loops
`continue` - stops current iteration of a loop and goes directly to next iteration

function parts - return type, name, parameter list, body
global variable - any variable defined outside all the functions in a program. Taboo.
global constants - generally fine. Note that you can temporarily "override" constants with local variables
static local variables - a variables that persists in a function between function calls
default arguments - e.g. `int func(int var = 10, char s = 't') { ...`. Must be a literal or a named constant. Note that
if an argument is left out of a function call (because it has a default value), all following arguments must also be
left out. When a function has a mix of default and non-default args, default args must be declared last.
`exit();` - completely terminates a program no matter how much is left... the nuclear option. Uses `<cstdlib>` takes an exit code argument. `EXIT_FAILURE` and `EXIT_SUCCESS` are available named constants.
stubs - dummy function that is called instead of the actual function it represents
drivers - programs that tests a function by simply calling it. If the function accepts the args, the drives passes the test

off-by-one error - basically when you're indexing an array and you screw up and index past the last element
range-variable - built-in implicit variable that in range-based for-loops `for (dType rangeVar: array) { ...`
push_back() - append to a vector
pop_back() - remove from the end of a vector
clear() - remove contents of vector
empty() - determines whether a vector is empty




```c++
std::ifstream inputFile;
inputFIle.open("Customers.txt"); // allows you to read data from Customers.txt

inputFile >> var; // this saves the first line out text to a variable named var
int n;
inputFile >> n; // While text is stored as a string, if it is a number it can be read directly into a numerical variable

std::ofstream outputFile;
outputFile.open("Employees.txt"); // allows you to write data to Customers.txt

outputFile << "You can just throw some text in there\n";

outputFile << "Or a variable: " << var << std::endl;

std::ifstream inputFile("Customers.txt"); // also valid
std::ofstream outputFile("Employees.txt");

inputFile.close();

int linesInFile = 10;
for (int i = 0; i < lineInFile; i++) {

// print a whole file
while (inputFile >> var) {
    std::cout << var << std::endl;
}

std::ifstream inputFile;
int n;

inputFile.open("missing_file.txt");

if (inputFile) { // can also use inputFile.fail()
    // do some operation . . . 
} else {
    std::cout << "File empty" << std::endl;
}
```

Why use `inputFile.close();`? Most operating systems temporarily store data in a _file buffer_ before it is written to a
file. A file bugger is a small "holding section" of memory to which file-bound data is first written. When the buffer is
filled, all the data stored there is written to the file. This improves the system's performance. Closing a file causes
any unsaved data that may still be held in a buffer to be saved to its file.  
Some operating systems also limit the number of files that may be open at one time. Whne a program closes files that are
no longer being used, it will not deplete more of the operating system's resources than necessay.

Note that pre-c++11, filenames needed to be C-strings.  
You can convert easily:
```c++
std::string str;
std::ostream outputFile(str.c_str());
```

Note that `break` and `continue` and generally seen as bad practice.  


```c++

const int months = 12;
int days[months] = {31, 38, 31, 30, ... 31};

std::cin >> days; // does not work, must be done one at a time
std::cout << days; // does not work, must be done one at a time

//implicit sizing

int nums[] = {1, 2, 3, 4};

const int array_size = 10;
int numbers[array_size];
int count = 0;
std::ifstream;

inputFile.open("numbers.txt");

while (count < array_size && inputFile >> numbers[count])
    count++;

inputFile.close();

cout << "The numbers are: ";
for (count = 0; count < array_size; count++)
    std::cout << numbers[count] << " ";
std::cout << std::endl;
return 0;

for (count = 0; count < array_size; count++)
    numbers[count] = count;

std::outputFile.open("saved_numbers.txt");

for (count = 0; count < array_size; count++)
    outputFile << numbers[count] << std::endl;

outputFile.close();
```

Assigning elements of one array to another
```c++

const int SIZE = 4;
int oldValues[SIZE] = {10, 100, 200, 300};
int newValues[SIZE];

newValues = oldValues; // Will not work!!

for (int i = 0; i < SIZE; i++) 
    newValues[i] = oldValues[i];
```
Simply copying one whole array to another doesn't work because the "array" is actually the memory address of the first
element and you can't assign an array pointer to another memory address.

Note that with partially filled arrays you either need a sentinel value or to keep track of the count of elements in the
array.

identical initializations
```c++
int hours[3][2] = {{8,5}, {2, 3}, {2, 9}};
int hours[3][2] = {8, 5, 2, 3, 2, 9};

// 2.d arrays to funcs
void showArray(const int numbers[][COLS], int rows) {
    ...
}
```

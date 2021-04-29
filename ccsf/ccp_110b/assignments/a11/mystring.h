/*
Object storing a cstring.
Abstracts away management of heap memory and providers useful operators.

Public Attributes:

    None

Public Member Funcions:

    MyString();

        pre: Default constructor.
        post: Creates and empty string and assigns a value of 0 to length

    MyString(const char*);

        pre: Single args constructor.
        post: Allocates enough memory on the head for the passed cstring and stores the
            length of that string.

    MyString(const MyString& obj);

        pre: Copy constructor.
        post: Returns a deep copy of the passed MyString.

    MyString operator=(const MyString& obj);

        pre: Assignment operator
        post: Returns a deep copy of the MyString object.

    ~MyString();

        pre: Deconstructor - Called when MyString object is out-of-scope
        post: De-allocates memory for MyString object's char array and strLength int

    int length() const;

        pre: Called on instantiated string object
        post: Returns the stored length of the char array

    friend std::ostream& operator<<(std::ostream& os, const MyString& str);

        pre: Called on instantiated string object
        post: Allows the string to be printed using the std::ostream insertion operator

    char operator[](const int& index) const;

        pre: Called on instantiated string object. Uses zero indexing. Index passed must be
            greater than zero and less than the length of the string.
        post: Allows subscription and access/returning of the specified index from a string
            object.

    char& operator[](const int& index);

        pre: Called on instantiated string object. Uses zero indexing. Index passed must be
            greater than zero and less than the length of the string.
        post: Allows subscription and access/modification of the specified index of the
            string object.

    friend bool operator<(const MyString& leftObj, const MyString& rightObj);

        pre: Friend function comparing 2 MyString objects. cstrings will be promoted to
            MyString objects if/when necessary.
        post: Returns True when the ASCII value(s) of the first object are lower than
            that of the second object.

    friend bool operator<=(const MyString& leftObj, const MyString& rightObj);

        pre: Friend function comparing 2 MyString objects. cstrings will be promoted to
            MyString objects if/when necessary.
        post: Returns True when the ASCII value(s) of the first object are lower than
            or equal to that of the second object.

    friend bool operator>(const MyString& leftObj, const MyString& rightObj);

        pre: Friend function comparing 2 MyString objects. cstrings will be promoted to
            MyString objects if/when necessary.
        post: Returns True when the ASCII value(s) of the first object are greater than
            that of the second object.

    friend bool operator>=(const MyString& leftObj, const MyString& rightObj);

        pre: Friend function comparing 2 MyString objects. cstrings will be promoted to
            MyString objects if/when necessary.
        post: Returns True when the ASCII value(s) of the first object are greater than
            or equal to that of the second object.

    friend bool operator==(const MyString& leftObj, const MyString& rightObj);

        pre: Friend function comparing 2 MyString objects. cstrings will be promoted to
            MyString objects if/when necessary.
        post: Returns True when the ASCII value(s) of the first object are equal to
            that of the second object.

    friend bool operator!=(const MyString& leftObj, const MyString& rightObj);

        pre: Friend function comparing 2 MyString objects. cstrings will be promoted to
            MyString objects if/when necessary.
        post: Returns True when the ASCII value(s) of the first object are not equal to
            that of the second object.

Private Attributes:

    char* str - The stored cstring

Private Member functions:

    None

The "Big-Three" member functions:

    The big-three member functions required whenever a programmer creates a class using
    dynamic memory are Assignment Operator, the Copy Constructor, and the Deconstructor.

    Assignment Operator:

        This is used to take the value of one object and assignment then to another
        object, e.g.:
            MyString str = "some string";
            MyString str1;
            str1 = str;

        The compiler-generated copy assignment operator will only do a shallow copy
        which results in both objects pointing to the same locations in memory.
        We crreate our own assignment operator to allow deep-copying.

    Copy Constructor

        There are three situations in which C++ uses a copy constructor. When an
        object is passed by value, when an object is returned, and during
        initialization.

        The compiler-generated copy constructor will only do a shallow copy
        which results in both objects pointing to the same locations in memory.
        We crreate our own copy constructor to allow deep-copying.

    Deconstructor

        When space is allocated on the heap it is not automatically de-allocated when
        the object in question is now longer in scope.
        To free up this memory we must make available the memory that was used by
        the object in question.
        Whenever an object leaves scope, the deconstructor is called, it is at this
        point that we can delete the variable stored on the heap and free the memory
        for later use.

 */


#include <iostream>
#include <cstring>

namespace cs_mystring {
    class MyString {
        private:
            char* str;

        public:
            // Constructors/Assignment/Deconstructors
            MyString();
            MyString(const char*);
            MyString(const MyString& obj);
            MyString operator=(const MyString& obj);
            ~MyString();
            int length() const;

            ////// Operators //////

            friend std::ostream& operator<<(std::ostream& os, const MyString& str);

            // subscripting operators
            char operator[](const int& index) const;
            char& operator[](const int& index);

            // comparison operators
            friend bool operator<(const MyString& leftObj, const MyString& rightObj);
            friend bool operator<=(const MyString& leftObj, const MyString& rightObj);
            friend bool operator>(const MyString& leftObj, const MyString& rightObj);
            friend bool operator>=(const MyString& leftObj, const MyString& rightObj);
            friend bool operator==(const MyString& leftObj, const MyString& rightObj);
            friend bool operator!=(const MyString& leftObj, const MyString& rightObj);
    };
}


/*
----- Testing basic String creation & printing
string [0] = Wow
string [1] = C++ is neat!
string [2] =
string [3] = a-z

----- Testing access to characters (using const)
Whole string is abcdefghijklmnopqsrtuvwxyz
now char by char: abcdefghijklmnopqsrtuvwxyz
----- Testing access to characters (using non-const)
Start with abcdefghijklmnopqsrtuvwxyz and convert to ABCDEFGHIJKLMNOPQSRTUVWXYZ

----- Testing relational operators between MyStrings
Comparing app to apple
    Is left < right? true
    Is left <= right? true
    Is left > right? false
    Is left >= right? false
    Does left == right? false
    Does left != right ? true
Comparing apple to
    Is left < right? false
    Is left <= right? false
    Is left > right? true
    Is left >= right? true
    Does left == right? false
    Does left != right ? true
Comparing  to Banana
    Is left < right? true
    Is left <= right? true
    Is left > right? false
    Is left >= right? false
    Does left == right? false
    Does left != right ? true
Comparing Banana to Banana
    Is left < right? false
    Is left <= right? true
    Is left > right? false
    Is left >= right? true
    Does left == right? true
    Does left != right ? false

----- Testing relations between MyStrings and char *
Comparing he to hello
    Is left < right? true
    Is left <= right? true
    Is left > right? false
    Is left >= right? false
    Does left == right? false
    Does left != right ? true
Comparing why to wackity
    Is left < right? false
    Is left <= right? false
    Is left > right? true
    Is left >= right? true
    Does left == right? false
    Does left != right ? true

----- Testing copy constructor and operator= on MyStrings
original is cake, copy is fake
original is cake, copy is fake
after self assignment, copy is Copy Cat
Testing pass & return MyStrings by value and ref
after calling Append, sum is Binky
val is winky
after assign,  val is Binky
 */

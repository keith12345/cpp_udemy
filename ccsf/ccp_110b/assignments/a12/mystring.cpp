/*
   CLASS INVARIANT:

   There are two private data members in this class. "str" represents the dynamic string
   stored by within the object. "MAX_INPUT_SIZE" is a static constant which represents
   the maximum size of a string that can be read as input.
   There are no public data members.
   Additional memory is allocated as necessary when concatenation operations are performed,
   e.g. `+=` and `+`.
   Individual characters can be accessed and replaced via subscription which performs
   bounds checking.
   Logical operators can be used to compare MyString objects to other MyString objects
   as well as c-strings.
*/






#include <cstring>
#include <cassert>
#include "mystring.h"
#include <istream>
#include <ostream>

namespace cs_mystring {




    // constructors

    MyString::MyString() {
        this->str = new char[1];
        std::strcpy(this->str, "");
    }






    MyString::MyString(const char* str) {
        this->str = new char[strlen(str) + 1];
        std::strcpy(this->str, str);
    }






    // Copy constructor
    // Second of the big 3
    MyString::MyString(const MyString& obj) {
        this->str = new char[strlen(obj.str) + 1];
        std::strcpy(this->str, obj.str);
    }






    // Deconstructor
    // Third of the big 3
    MyString::~MyString() {
        delete [] this->str;
    }






    // public methods

    int MyString::length() const {
        return strlen(str);
    }






    void MyString::read(std::istream& is, const char& delimeter) {
        char inputStr[MyString::MAX_INPUT_SIZE + 1];
        is.getline(inputStr, MyString::MAX_INPUT_SIZE, delimeter);
        delete [] this->str;
        this->str = new char[std::strlen(inputStr) + 1];
        std::strcpy(this->str, inputStr);
    }






    // overloade operators

    // Assignment operator (takes an existing object and assigns the values of another object to it)
    // First of the big 3
    MyString MyString::operator=(const MyString& obj) {
        if (this != &obj) {
            delete [] this->str;
            this->str = new char[strlen(str) + 1];
            std::strcpy(this->str, obj.str);
        }
        return *this;
    }






    // Subscription operators

    char MyString::operator[](const int& index) const {
        assert(index >= 0 && index < static_cast<int>(strlen(str)));
        return this->str[index];
    }






    char& MyString::operator[](const int& index) {
        assert(index >= 0 && index < static_cast<int>(strlen(str)));
        return this->str[index];
    }






    // Insertion and extraction operators

    std::ostream& operator<<(std::ostream& os, const MyString& obj) {
        os << obj.str;
        return os;
    }






    std::istream& operator>>(std::istream& is, MyString& obj) {
        char inputStr[MyString::MAX_INPUT_SIZE + 1];
        is >> inputStr;
        delete [] obj.str;
        obj.str = new char[std::strlen(inputStr) + 1];
        std::strcpy(obj.str, inputStr);
        return is;
    }






    // concatenation operators

    MyString operator+(const MyString& leftObj, const MyString& rightObj) {
        char str[std::strlen(leftObj.str) + std::strlen(rightObj.str) + 1];
        std::strcpy(str, leftObj.str);
        std::strcat(str, rightObj.str);
        return MyString(str);
    }






    MyString& MyString::operator+=(const MyString obj) {
        char* str = new char[std::strlen(this->str) + std::strlen(obj.str) + 1];
        std::strcpy(str, this->str);
        std::strcat(str, obj.str);
        delete [] this->str;
        this->str = str;
        return *this;
    }






    // Comparison operators

    bool operator<(const MyString& leftObj, const MyString& rightObj) {
        return std::strcmp(leftObj.str, rightObj.str) < 0;
    }






    bool operator<=(const MyString& leftObj, const MyString& rightObj) {
        return std::strcmp(leftObj.str, rightObj.str) <= 0;
    }






    bool operator>(const MyString& leftObj, const MyString& rightObj) {
        return std::strcmp(leftObj.str, rightObj.str) > 0;
    }






    bool operator>=(const MyString& leftObj, const MyString& rightObj) {
        return std::strcmp(leftObj.str, rightObj.str) >= 0;
    }






    bool operator==(const MyString& leftObj, const MyString& rightObj) {
        return std::strcmp(leftObj.str, rightObj.str) == 0;
    }






    bool operator!=(const MyString& leftObj, const MyString& rightObj) {
        return std::strcmp(leftObj.str, rightObj.str) != 0;
    }

}

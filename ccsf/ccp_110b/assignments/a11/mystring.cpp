#include <cstring>
#include <cassert>
#include "mystring.h"
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






    char MyString::operator[](const int& index) const {
        assert(index >= 0 && index < static_cast<int>(strlen(str)));
        return this->str[index];
    }






    char& MyString::operator[](const int& index) {
        assert(index >= 0 && index < static_cast<int>(strlen(str)));
        return this->str[index];
    }






    std::ostream& operator<<(std::ostream& os, const MyString& obj) {
        os << obj.str;
        return os;
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

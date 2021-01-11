#include <cstring>
#include <iostream>
#include "Mystring.h"

Mystring::Mystring()
    :str{nullptr} {
        std::cout << "Is this one a null constructor?" << std::endl;
        str = new char[1];
        *str = '\0';
    }

Mystring::Mystring(const char* s)
    :str {nullptr} {
        std::cout << "Using constructor initialization" << std::endl;
        if (s==nullptr) {
            str = new char[1];
            *str = '\0';
        } else {
            str = new char[std::strlen(s)+1];
            std::strcpy(str, s);
        }
    }

Mystring::Mystring(const Mystring& source)
    :str {nullptr} {
        str = new char[std::strlen(source.str)+1];
        std::strcpy(str, source.str);
        std::cout << "Using copy constructor" << std::endl;
    }

Mystring::~Mystring() {
    std::cout << "Using deconstructor" << std::endl;
    delete [] str;
}

void Mystring::display() const {
    std::cout << this->str << " : " << this->get_length() << std::endl;
}

int Mystring::get_length() const {
    return std::strlen(str);
}

const char* Mystring::get_str() const {
    return this->str;
}

Mystring& Mystring::operator=(const Mystring& source) {
    std::cout << "Calling assignment constructor" << std::endl;
    if (this == &source)
        return *this;

    delete [] str;
    str = new char[std::strlen(source.str) + 1];
    std::strcpy(str, source.str);

    return *this;
}


Mystring& Mystring::operator=(Mystring&& source) {
    std::cout << "Move assignment operator" << std::endl;
    if (this == &source) {
        return *this;
    }

    delete [] str;
    str = source.str;
    source.str = nullptr;

    return *this;
}

//Mystring Mystring::operator-() {
    //char* buff = new char[std::strlen(str) + 1];
    //std::strcpy(buff, str);
    //for (size_t i=0; i<std::strlen(buff); i++)
        //buff[i] = std::tolower(buff[i]);
    //Mystring temp {buff};
    //delete [] buff;
    //return temp;
//}

//bool Mystring::operator==(const Mystring& source) {
    //if (std::strcmp(str, source.str) == 0) {
        //return true;
    //}
    //else {
        //return false;
    //}
//}

//Mystring Mystring::operator+(const Mystring& source) const {
    //char* buff = new char[std::strlen(this->str) + std::strlen(source.str) + 1];
    //std::strcpy(buff, this->str);
    //std::strcat(buff, source.str);
    //Mystring out {buff};
    //delete [] buff;
    //return out;
//}

Mystring operator-(const Mystring& obj) {
    char* buff = new char[std::strlen(obj.str) + 1];
    std::strcpy(buff, obj.str);
    for (size_t i=0; i<std::strlen(buff); i++)
        buff[i] = std::tolower(buff[i]);
    Mystring temp {buff};
    delete [] buff;
    return temp;
}


bool operator==(const Mystring& obj1, const Mystring& obj2) {
    return (std::strcmp(obj1.str, obj2.str) == 0);
}


Mystring operator+(const Mystring& obj1, const Mystring& obj2) {
    char* buff = new char[std::strlen(obj1.str) + std::strlen(obj2.str) + 1];
    std::strcpy(buff, obj1.str);
    std::strcat(buff, obj2.str);
    Mystring out {buff};
    delete [] buff;
    return out;
}


std::ostream& operator<<(std::ostream& os, const Mystring& obj) {
    os << obj.str; // if friend function
    // os << obj.get_str(); // if not friend function
    return os;
}

std::istream& operator>>(std::istream& is, Mystring& obj) {
    char* buff = new char[1000];
    is >> buff;
    obj = Mystring{buff};
    delete [] buff;
    return is;
}

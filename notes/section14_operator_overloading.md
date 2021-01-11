# Operator Overloading

The only operator that the compiler provides a default implementation for is the assignment operator. This is because the compiler must be able to assign one object to another.  
All other operators that can be overloaded must be explicitly defined in the program. 

Operator overloading is considered syntactic sugar because we're still calling methods and functions behind the scenes. 

## Disambiguating Constructors and assignment operators

* Copy Constructor
    * Prototype:
        * `Object(const Object& source);`
    * Default:
        * compiler generated element-wise copy
    * Data type:
        * works with l-values (?) and l-value references
    * What it does:
        * Allocates memory for the value that we want to store. 
            * When memory needs to be allocated for pointers in a class, it is done is in constructors
        * Creates a deep copy, two identical objects pointing to different location in memory
        * Nothing deleted, just assign the copied value to the new pointer `*this->attribute = *source.attribute;`
* Copy Assignment operator 
    * Prototype:
        * `operator=(const Object& source)`
    * Default:
        * compiler generated element-wise copy
    * Data type:
        * works with l-values (?) and l-value references
    * What it does:
        * creates a deep copy, two identical objects pointing to different locations in memory
        * Nothing deleted, just assign the copied value to the new pointer `*this->attribute = *source.attribute;`
* Move assignment operaotr
    * Prototype:
        * `operator=(Object&& source)`
    * Default:
        * copy assignment operator
    * Data type:
        * r-value references
    * What it does
        * Deletes references to values that the assignee object is pointing to 
        * Points pointers to locations that r-value object is pointing to
        * Points r-value object variables to null pointers (critical... not sure what happens if you don't) I Think it
            you don't point it to null, then, when it goes out of scope, the program this that everything that the
            out-of-scope object was pointing should be deleted. You have to point it somewhere else so that the program
            doesn't think that it should be deleted with the rest of that object.
    * How to call:
        * `object = Object(p1, p2);`
        * `object {Object(p1, p2)};`

## Operators that cannot be overloaded (and other fun facts):
* `::` - scope resolution operator
* `:?` - conditional operator
* `.*` - pointer to member operator
* `.` - dot operator
* `sizeof`

And just because it can be overloaded doesn't mean it should.

Precedence and associativity of operators cannot be changed.

The "arity" of an operator cannot be changed - e.g. can't go from binary to unary

You can't create new operators

You can't overload primite types (`int`, `double`)

Operators can be overloaded using global functions and member methods. The assignment operator, for example, needs to be overwritten using a member method.

## Assignment Operator

c++ creates a compiler-generated default assignment operator if one is not created in the program. 

By default, member-wise shallow copying si performed. Without raw pointers, this will typically be fine.

When creating an assigment operator:  
```c++
// Mystring.h
Type& operator=(const Type &rhs);
// Mystring.cpp
Mystring& Mystring::operator=(const Mystring& rhs) {
    if (this == &rhs)
        return *this;

    delete [] str;
    str = new char[std::strlen(rhs.str) + 1];
    std::strcpy(str, rhs.str);

    return *this;
}
```

Once doing this you can perform the following types of assignment:  

```c++
s2 = s1;
s2.operator=(s1);
```

Note that the `this` keyword refers to the assignment on the left-hand side of the assignment operator. `rhs` in this case stands for "right-hand-side".

Because we're making a deep copy, we copy/assign the attributes from the right-hand-side object to the left-hand-side object.

The left-hand-side object will be overwritten. We de-allocate anything it refers to on the heap, then we allocate new space of the appropriate size, then we copy the new value over. 

The initial if/then simply checks to see whether we're assigning the object to itself, if so, we simply return the original object. 

## Move assignment 

The previous assignment operator works with l-value references; it also makes sense to have something 
that works with r-value references. 

If you don't create a move constructor, the copy constructor will be used by default. Move constructors, however, can be much more efficient than copy constrcutors. 

```c++
Mystring s1;
s1 = Mystring {"Frank"};
```

```c++
// Mystring.h
Mystring& operator=(Mystring&& rhs);
// Mystring.cpp
Mystring& Mystring::operator=(Mystring&& rhs) {
    if (this == &rhs)
        return *this;

    delete [] str;
    str = rhs.str;

    rhs.str = nullptr;
    return &this;
```

The right-hand-side will be an r-value reference, the right-hand-side can't be const because the value will be modified when the data is moved.  
The declaration for the Mystring class returns a string object by reference and expects an r-value reference to a Mystring object. 

## Other operators

```c++
Number Number::operator-() const;
Number Number::operator++();        // pre-increment
Number Number::operator++(int);     // post-increment
bool Number::operator!() const;

Number n1 {100};
Number n2 = -n1;
n2 = ++n1;
n2 = n1++;
```

"cpp simply provides a parameter that isn't used for the post-increment".  
A [post](https://stackoverflow.com/questions/15244094/c-overloading-for-both-pre-and-post-increment) on stackoverflow mentions cpp takes a dummy `int` parameter simply to disambiguate between pre and post-increment.

### binary operators

Binary operators use the `this` keyword to refer to one object and take the other object as an 
argument.  
The `this` keyword refers to the object on the left and the positional arg refers to the object on the left.  
The sum and difference operators return the newly created objects by value.

Note that when implementing binary operators as member functions, there must be an object of the member-function-class must be on the left-hand side (if there is one on the left-hand side then a constructor can create one on the right hand side in the case of something like Mystring).

This behavior can be circumvented with non-member operators.

## Non-member functions

These are typically declared as friends of a class so that they have access to class members. (You 
could use getter methods to access things but it just seems more legit to implement them as friends).

### Sometimes it doesn't make sense for something to be a member

When using member methods, the object always needs to be on the left-hand side. The insertion and extraction operators traditionally have `cin` and `cout` on their left. Implementing insertion and extraction operators as member methods prohibits this.  
E.g. you'd need to do:  
```c++
Mystring test;
test << cout;
Mystring test2;
test2 >> cin;
```
Which just looks weird...

```c++
// Mystring.h
friend std::ostream& operator<<(std::ostream& os, const Mystring& obj);
// Mystring.cpp
std::ostream &operator<<(std::ostream& os, const Mystring& obj) {
    os << obj.str; // if friend function
    // os << obj.get_str(); // if not friend function
    return os;
}
```

Note that when the operator is not a friend of the class, the only association the operator has with the class is the fact that it takes a Mystring object as an argument. That's what it means to have overloaded it in this context.

Same with extractor operator:  
```c++
// Mystring.h
friend std::istream& operator>>(std::istream& is, Mystring& obj) {
// Mystring.cpp
std::istream& operator>>(std::istream& is, Mystring& obj) {
    char* buff = new char[1000];
    is >> buff;
    obj = Mystring{buff}; // assumes copy and move assignment overloaded operators
    delete [] buff;
    return is;
}
```

Note the difference between the pre and post-increment operators. One returns a reference while the other returns a value:  
```c++
Money& Money::operator++() {
    this->cents += 1;
    return *this;
}

Money Money::operator++(int) {
    Money temp (*this);
    operator++();
    return temp;
}
```

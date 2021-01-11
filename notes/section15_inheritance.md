# Inheritance

## What is inheritance

* creating new classes from existing classes
* Contains data and behaviour from existing classes
* Re-using behaviours that have been tested and we know they work (assuming someone else built it and tested it).  
* Done without modifying the source code of the original class.  

Related classes:
* palyer -> enemy -> boss
* account, savings account, checking account
* shape, line, oval
* person, employee, student

Account example:
* account
    * balance, deposit, withraw
* Savings accounts
    * + interest rate
* Checking account
    * + minimum balance, per-check fee
* trust account
    * + interest rate

These could all be implemented separately or we could create an account class and build the other 
accounts based on it.

## Terminology and Notation

* Inheritance
    * process of creating new classes from existing classes
    * mechanism to reuse
* single inheritance
    * a new classe is created from a single class
* Multiple inheritance
    * a new class is created from two (or more) other classes
* Base class (parent class, super class)
    * the class being extended or inherited from
* Derived class
    * the class being created from the base class
    * will inherit attributes and operations from the base class.
* "Is-A" relationship
    * Public inheritance
    * an oval is a shape, a savings account is an account, etc
    * derived classes are subtypes of their base classes
    * can used a derived class object wherever we use a base class object
* Generalization
    * combining similar classes into a single, more general class based on common attributes
* Specialization
    * creating new classes from the existing classes providing more specialized attributes or operations
    * opposite of generalization
* Inheritance of Class hierarchies
    * organization of our inheritance relationships
* Root class
    * Class that is not derived from another class
    * Other classes are derived from it
* transitive inheritance
    * If `b` is derived from `a` and `c` is derived from `b`
    * `c` is a `b`
    * `b` is an `a`
    * **and** `c` is an `a`
    * "Is-A" relationship^

## Inheritance vs Compisition

* Both reuse existing classes
* public Inheritance
    * "is-a" relationship
        * Employee is a person
        * checking account is an account
        * circle is a shape
* Composition
    * "has-a" relationship
        * person has an account
        * player has a special attack
        * circle has a location

For example, I think if we make a class that uses a vector or a string, that is an example of composition.

## Dering classes from existing classes

* Access specified
    * derived classes can be public, private and protected
        * public
            * most common
            * establishes "is-a" relationship between derived and base classes
        * private and protected
            * establishes "derived class **has a** base class" relationship
            * "Is implemented in terms of" relationship
            * Different from composition
    * If none is provided, private inheritance is used

```c++
class Base {
    // Base class members . . .
};

class Derived: access-specifier Base {
    // Derived class members . . . 
};
```

Note that the presence of private and protected is different from most other programming languages. 
Most other languages only have public inheritance.   
This course doesn't actually go into private and protected.  

## Protected Members and Class Access

```c++
class Base {
    protected:
        // protected base class members
};
```

* Accessible from the Base class itself
* accessible from classes Derived from Base
* Not accessible by objects of Base or Derived

Protected and Private class members are basically the same unless inheritance is involved.  

**Base class**  
* public: `a`
* protected: `b`
* private: `c`

Access in a derived class using **public** inheritance:  
* public: `a`
* protected: `b`
* `c` - **no access**

Same class using **protected** inheritance:
* **protected**: `a`
* protected: `b`
* `c` - **no access**

Same class using **private** inheritance:
* **private**: `a`
* **private**: `b`
* `c` - **no access**

Note that if a class is a friend, it will have access to everything: public, protected, _and_ private.  

## Constructor and Deconstructor inheritance

* derived class inherits from base class
* base part of the derived class **must** be initialized **before** the derived class is initialized
* when a derived object is created
    * base class constructor executes
    * derived class constructor executes

Destructors are invoked in the reverse order

### What do derived classes NOT inherit

* Base class constructors
* base class destructors
* base class overloaded assignment operators
* base class friend functions

That said, the base class constructors, destructors, and overloaded assignment operators can invoke 
their base-class versions.

C++11 allows explicit inheritance of base 'non-special' constructors with
* `using Base::Base;` anywhere in the derived class declaration
    * Lots of rules involved, often better to define constructors yourself.
        * Default copy and move constructors are not included 
        * each inherited constructor has the same access specifier as its corresponding base class constructor 
        * If you provide an overloaded constructor then the base class overloaded constructor is not inherited
* special constructors are the default copy and move constructors that the compiler generates automatically. 
    * a constructor in which values are assigned is not a special constrcutor and _will_ be copied.  

If you want variables to be assigned by a constructor on initialization, you either need to use `using Base::Base;` in your class definition in the header file or you need to make a constructor that explicity assigns that value.

Remember that the base class constructor that's called is determined by the arguments that we pass to it.

```c++
class Base {
    public:
        Base();
        Base(int);
        . . .;
};

Derived::Derived(int x)
    : Base(x), {optional initializers for Derived} {
    // code
};
```

## Copy/Move constructors and Operator =  with Derived Classes

* Not inherited from the base class
* Remember that you may not need to provide your own
    * default compiler-provided versions may be sufficient
* We can explicitly invoke the base class versions from the derived class

Due to "is-a" relationships, we can pass a derived class to a base class constructor. A base class 
constructor takes a base class object as its argument, but because a derived class _is_ a base, it can be passed.  
The compiler uses something called "slicing" where it _slices_ out the base part of the derived object. 

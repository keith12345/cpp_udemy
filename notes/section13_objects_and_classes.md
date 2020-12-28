# Objects and Classes

## What is OOP

Procedural programming:

Modularize by creating many functions that each specify a process of action for the 
program to perform.   
Procedural programs are essentially a colletion of functions.  
Data is declared separate from fucntions 

Limitations:  
Functions must know about the structure of the data.  
Changes in data formatting could require overhaul of functions.  

Procedural programming doesn't have super intuitive encapsulation of different sections.  
Harder to re-use code from one program in another program. 

Encapsulation - objects contain data and operations that work on that data. Extension of the ADT (abstract data type).

A fundamental aspect of OOP is re-usability... that is not the case for procedural programming. 

Inheritance is another strength of OOP.  
Inheriting traits and creating/modifying traits to make the class suit your need.

Development time (largely due to planning) and run-time are both typically longer for OOP
applications. 

## Declaring classes and objects

Objects are created from classes and represent a specific instance of the class from which they're created. 

Declaration:
```c++
class Class_Name 
{
    // attributes
    string name;
    int health;
    int xp;

    // methods
    void talk(string text_to_say);
    bool is_dead();
};
```

Creating an instance of that class:
```c++
Player frank;
Player hero;

Player *enemy = new Player();
delete enemy;

vector<Player> players {frank};
players.push_back(hero);
```

## Accessing class members

There are two ways to do this:  
* dot operator - member of operator - typical python `this_class.that_attribute`
* member of pointer operator - arrow operator - used when the accessing the object via a pointer

```c++
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Player {
public:
    string name;
    int health;
    int xp;

    void talk(string str) {
        cout << name << " says "<< str << endl;
    }
    void do_damage(int damage) {
        health -= damage;
        cout << "You now have " << health << " health" << endl;
    }
};

int main() {
    Player* keith = new Player();
    (*keith).name = "Keith";
    (*keith).health = 100;
    keith->xp = 13;
    (*keith).talk("yo");
    keith->do_damage(10);
}
```

## Class member access modifiers

`public:` - anything after this declaration will be visible/accessible outside of the class's methods. 
`private:` - anythig after is private
`protected` - used with inheritance, works pretty much the same as private but differences become apparent with inheritance

## Implementation

methods can be implemented outside of the class definition `Class_name::method_name`  
People even separate specification/declaration from implementation:
* `.h` file for the class declaration
* `.cpp` file for the class implementation

To avoid re-declaration, you use `#ifndef` followed by the symbol name. Practice is to put it in all uppercase with precending and ending underscores. Or you can just yuse `#pragma once` instead of that ugly mumbo jumbo. 
```c++
// Player.h

#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Player {
public:
    string name;
    int health;
    int xp;

    void talk(string str);
    void do_damage(int damage);
};

#endif


// Player.cpp
#include "Player.h"


void Player::talk(string str) {
    cout << name << " says "<< str << endl;
}
void Player::do_damage(int damage) {
    health -= damage;
    cout << "You now have " << health << " health" << endl;
}
```

Include with `<>` is for system header filers with include with double quotes is for header files that are local to the proejct. 

Always include `.h` files, never `.cpp`.

## Constructors and Desctructors

### Constructors

* Special member methods invoked during object creation  
* Commonly used for initialization.  
* Easy to recognize, they have the same name as the class.  
* They do not specify a return type  
* They can be overloaded.

### Destructors

* special member method
* same name as the class but preceded with a tilde `~`
* invoked automatically when an object is destroyed
* no return type and no parameters
* cannot be overloaded (no reason to, anyway)
* useful to release memory and other resources

When classes are created on the stack, deletion will happen once the object is out of scope. When you create from the head/free_store, you need to use the `delete` reserved keyword. 

If you don't create a default constructor and destructor, cpp will create empty versions of them for you. 


This is kind of a constructor example... We've created overloaded constructors but the 
constructors are actually assigning variables to previoiusly created attributes.  
```c++
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <iostream>
#include <string>

class Player {
public:
    std::string name;
    int health;
    int xp;

    Player() {
        name = "None";
        health = 10;
        xp = 0;
    }

    Player(std::string name) {
        name = name;
    }

    Player(std::string name, int health, int xp) {
        name = name;
        health = health;
        xp = xp;
    }

    void talk(std::string str);
    void do_damage(int damage);

};

#endif
```

For ideal run time the attributes will be assigned before the constructor body executes.   
This is done via constructor initialization lists.  
Below, we now include the constructors in the `Player.cpp` file.
Note that, while this is faster, it prevents you from allocating from the heap within your class (or 
so it seems, at least) which is considered best-practice.

```c++
#include "Player.h"


Player::Player()
    : name {"None"}, health {10}, xp {0} {
}

Player::Player(std::string name)
    : name {name}, health {10}, xp {0} {
}

Player::Player(std::string name, int health, int xp)
    : name {name}, health {health}, xp {xp} {
}


void Player::talk(std::string str) {
    std::cout << name << " says "<< str << std::endl;
}
void Player::do_damage(int damage) {
    health -= damage;
    std::cout << "You now have " << health << " health" << std::endl;
}
``` 

Note that initialization takes place in the order specified in the constrcutor prototype rather than the constructor definition.

## Delegating Constructors

A lot of the code within the different constructors is identical, cpp allows you to avoid that. 

```c++
#include "Player.h"


Player::Player()
    : Player("None", 10, 0) {
}

Player::Player(std::string name)
    : Player(name, 10, 0) {
}

Player::Player(std::string name, int health, int xp)
    : name {name}, health {health}, xp {xp} {
}


void Player::talk(std::string str) {
    std::cout << name << " says "<< str << std::endl;
}
void Player::do_damage(int damage) {
    health -= damage;
    std::cout << "You now have " << health << " health" << std::endl;
}
```

Note that this only works from the initialization, it does not work from the body of the constructor function.

How to organize: 
```c++
// Player.h

#pragma once
#include <iostream>
#include <string>

class Player {
public:
    std::string name;
    int health;
    int xp;

#include "Player.h"

int main() {
    Player villain = Player("Qamudo");
    villain.talk("I will destroy you!");

    Player* hero = new Player("hero", 400, 250);
    hero->do_damage(12);
    Player schmope {"schmope", 5, 1};
    schmope.do_damage(10);

}

    Player(std::string name = "None", int health = 10, int xp = 3);

    void talk(std::string str);
    void do_damage(int damage);

};

// Player.cpp


#include "Player.h"

Player::Player(std::string name, int health, int xp)
    : name {name}, health {health}, xp {xp} {
}

void Player::talk(std::string str) {
    std::cout << name << " says "<< str << std::endl;
}
void Player::do_damage(int damage) {
    health -= damage;
    std::cout << "You now have " << health << " health" << std::endl;
}

// usage

#include "Player.h"

int main() {
    Player* hero = new Player("hero", 400, 250);
    hero->do_damage(12);
    Player schmope {"schmope", 5, 1};
    schmope.do_damage(10);
}

```

## Copy Constructor

Needed when passing or return something by value.  
These can also be generated automatically by the compiler.  

The default copy will do a member-wise copy and is generally what you want... this becomes an issue 
if you're using pointers. In such cases, only the pointer will be copied, not the data that it's 
pointing to.  
This is what's referred to as a shallow copy rather than a deep copy. 

Best practices:  
* always provide a copy constructor when your class has raw pointer members
* provide the copy constructor with a `const reference` parameter
* Use STL classes as member attributes as they already provide copy constructors
* Avoid using raw pointer data members if possible

```c++
// player.h

#pragma once
#include <iostream>
#include <string>

class Player {
public:
    std::string name;
    int health;
    int xp;


    Player(std::string name = "None", int health = 10, int xp = 3);
    Player(const Player &source);

    void talk(std::string str);
    void do_damage(int damage);

};

// player.cpp

#include "Player.h"

Player::Player(std::string name, int health, int xp)
    : name {name}, health {health}, xp {xp} {
}

Player::Player(const Player &source)
    : name {source.name},
      health {source.health},
      xp {source.xp} {
      }

void Player::talk(std::string str) {
    std::cout << name << " says "<< str << std::endl;
}
void Player::do_damage(int damage) {
    health -= damage;
    std::cout << "You now have " << health << " health" << std::endl;
}

```

## Shallow vs. deep copy

The main issue with shallow copying is not the modification of pointer members (those can just be 
consts if necessary) but rather with deletion of the object from which the new object is copied. 
In such cases, the memory will be freed up and who knows what'll happen...

```c++
// initiliazation that can perform a deep or shallow copy
Player::Player(std::string name_val, int health_val, int xp_val)
  : name {name_val} {
    health = new int;
    xp = new int;
    *health = health_val;
    *xp = xp_val;
}

// shallow copy
Player::Player(const Player &source)
  : name {source.name} {
    health = source.health;
    xp = source.xp;
}

// deep copy
Player::Player(const Player &source)
  : name {source.name} {
    health = new int;
    xp  = new int;
    *health = *source.health;
    *xp = *source.xp;
}

// Looks like you can also do this for a deep copy

Player::Player(const Player &source)
  : Player::Player(source.name, std::move(*source.health), std::move(*source.xp)) {}
```

It looks like the name `source` is arbitrary and you can just use `s` or whatever you want.

## Move Constructors

One of the most pervasive features in c++11

move semantics can allow us to create temporary values (which are inadvertently r-values) that are faster to assign that l-values.

If no move constructor is called, then a copy constructor will be used. 

The compiler may perform copy elision which eliminates unnecessary copying (this can be apparent if you think there should be copying somewhere but you don't actually see it in the compiled code).

Return value optimization is an example of this, that's when the compiler generates code that doesn't create a copy of a return value from a function. This makes the code more efficient. 

### r-value references

* used in moving semantics and perfect forwarding
* move sementic is all about r-value references
* used by move constructor and move assignment operator to efficiently move an object rather than copy it
* `&&` - r-value references operator.
    * remember that l-value references are declared using a single ampersand.

```c++
int x {100};
int& l_ref = x; // l-value reference to 100
l_ref = 10; // change the value at that reference to 10

int &&r_ref = 200; // r-value reference to 200
r_ref = 300; // r_ref is now 300

int &&x_ref = x; // will give a compiler error
```

```c++
void fun(int& num);

int x {100};
func(x); // this works
func(200); // this doesn't
```

Now we try with r-value references
```c++
void fun(int&& num);

int x {100};
func(200); // this works
func(x); // this doesn't
```

Move constructors simply copy the address of the resource from the source object to the current object rather than copying the content at that address (moves the pointer from one object to another).

A move constructor essentially steals the source data and then nulls out the source data's pointer.

## `this` pointer

* `this` is a reserved keyword
* contains the address of the object - it's a pointer to the object
* can only be used in class scope
* all member access is done via the `this` pointer
* uses:
    * access data member and methods
    * determine if two obejcts are the same
    * can be dereferenced (*this) to yield the current object
    * It basically works the way `self` does in python

For example
```c++
void Account::set_balance(double bal) {
    balance = bal;  // this->balance(bal) is implied
}

// this wouldn't work: (or if it did it's still ambiguous)

void Account::set_balance(double balance) {
    balance = balance;
}

// but if you wanted the parameter to be named "balance" you could do:

void Account::set_balance(double balance) {
    this->balance = balance; // here we're clearly saying that we're setting the 
} // object balance to the new balance parameter
```

To compare whether two objects are the same:
```c++
int Account::compare_balance(const Account& other) {
    if (this == &other) 
        std::cout << "The same objects" << std::endl;
}
```

## using const

The compiler plays it safe and can assume that there's a possibility that some function could change 
the value of a variable and, as a result, will not allow that method to be called.

```c++
const Player villain {"Villain", 100, 55};

void display_player_name(const Player& p) {
    cout << p.get_name() << endl;
}

display_player_name(villain); // will throw a compiler error
```

To circumvent this we need to let the compiler know that certain methods will not modify the object:
```c++
class Player {
    private:
        ...
    public:
        std::string get_name() const;
        ...
};
```

The `const` after the prototype (and definition, not shown) basically indicate to the cmopiler that 
the function in question is `const` object compatible. 

Doing this is an example of a practice that people refer to as "const correctness"

## Static class members

* class data members can be declared as statis
    * a single data member that belongs to the class, not any particular instance of that class
    * use to store class-wide information
* Class functions can be declared as static
    * independent of any objects
    * can be called using the class name

Note that this static member is not necessary a `const`. You could create a static variable to track the number of instances of a particular class. 

Typically declared as private  
c++ forbids in-class initializattion of non-const static members

initializize in the .cpp file:  
`type Class_Name::varaible {value};`

## Struct vs class

struct comes from `c`  
Essentially the same as `class` but in a `struct` members are public by default.

Everything that can be done in a class can be done in a struct. 

When to use a struct vs a class:  
* struct
    * for passive objects with public access
    * don't declare methods in a struct
* class
    * use class for active objects with private access
    * implement getters/setters as needed
    * implement member methods as neededo

## Friends of a class

There's some controversy about friends in c++  
The controversy is about encapsulation and whether friends violate cancellation or enhance it. 

* friend
    * a function or another class that has access to private call members
    * and
    * that function or class is not a member of the class that it's accessing
* function
    * can be regular non-member functions
    * can be member methods of another class
* class
    * another class can have access to private class members

Essentially; complete a total access to all public and private data members of a class. 

* friendship must be granted NOT taken
    * declared explicitly in the class that is granding friendship
    * declared in the function prototype with the keyword `friend`
* frienship is not symmetric
    * if `a` is a friend of `b`, `b` is not necessarily a friend of `a`
* friendship is not transitive
    * if `a` is a friend of `b`
    * and
    * `b` is a friend of `c`
    * `a` is _not necessarily_ a friend of `c`

One example of why this is convenient is that a `friend` method does not need to go through public 
setters and getters to get class information.  
You can even mutate variables via `friend` methods.

You can also declare methods in one class to be a friend of another:
```c++
class Player {
    friend void Other_class::display_palyer(Player& p);
    std::string name;
    int health;
    int xp;
public:
    ...
};

class Other_class {
    ...
public:
    void display_palyer(Player& p) {
        std::cout << p.name << std::endl;
        std::cout << p.health << std::endl;
        std::cout << p.xp << std::endl;
    }
};

class Player {
    friend class Other_class; // Other_class will have access to all methods in Player
    std::string name;
    int health;
    int xp;
public:
    ... 
};
```

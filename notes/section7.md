# Arrays and Vectors

Arrays and vecotrs are both examples of compound data types, data types that store other pieces of data with the same or a different type.

## Arrays

### Properties of Arrays:
* Both arrays and vectors are compound or structured data types. 
* This means that they are a datatype that is composed of other data types. 
* All elements of an array must be the same type.
* Arrays must be of a fixed size.  
* Sounds like you should be able to store objects in arrays (think iterating through a random forest)
* Array allocations are contiguous in memory (this allows fast access).
* Arrays are zero indexed.
* If you try to index out of range I think you get an errors
* When you print an array (not the contents of that array) you actually get the memory address of that array
* Note that some compilers actually place limits on the number of dimensions that arrays can have

### Declaring and Initializing Arrays:
`<type> <name> <[size]> <array>;`  
e.g.:
`int test_scores [3] {77,87,89};`  

Let's say you wanted to initialized an Array and know the length but you don't know what you want to values to be. You can initialize the array to `0`:  
`int test_scores [10] {0};`  
You can also just leave the curly braces empty:  
`int test_scores [10] {};`  
This can also come in handy if you only know what the first part of the array will be:  
`int test_scores [10] {77,87,89};`  
Here, the remainining values in the array will be initialized to `0`.  

Finally, maybe you're getting your array from another variable, so you don't actually know how long it is but you have the values that will populate the array, you can simply not specify the length of the array:  
`int test_scores [] {77,87,89,92,50,23,89,70,80,19};`

### Selecting elements by index is just same as python:  
``` c++
int test_scores [] {77,87,89};
// to get the second score:
cout << "Second score in array: " << test_scores[1] << endl;
// > Second score in array: 87

```
Select elements in this way is called **array subscripting**.

In an example above we mention initializing an array at `0` because we don't know the values yet. We assign by selecting the index:  
``` c++
cin >> test_scores[0];
cin >> test_scores[1];
cin >> test_scores[2];
```

We can also assign without `cin` as follows:  
```
int arr [10] {};
arr[0] = 100;
arr[9] = 1000;
```

### More notes on indexing arrays:  
Arrays are stored as contiguous chunks of memory. We know that the name of an array (as far as cpp is concerned) is its address in memory. We also know that when we initialize an array, we know the type and the size of that type. With that information we can understand how indexing actually works.  
If an array is stored at location `1000` and its type is `int` (this size of which is `4` bytes), then we simply increment the memory location by `4` to get the next index of the array.  
So, the 7th element of an array stored at memory location `1000` would be:  
`some_array[(7-1)*4]`  
This will get you something at memory address `1024`, the seventh element of that array.  
So, when you try to index something that is beyond the bounds of the array, you're trying to access some location in memory and you have no idea what that thing might be.

### Multi-dimensional arrays
Similar to declaring single demensional arrays but both dimensions are specified. For example:  
``` c++
int move_rating [3][4];
```
Would create a `4 x 3` array.

## Vectors

About vectors in c++
* Vectors are part of the C++ STL
* A vector in c++ is an object
    * Referred to more specifically as "an object oriented container in the standard template library"
* Vectors are similar to arrays but also have methods like `sort`, `reverse`, `erase`, `find`, `size`, etc.
* You must `#include <vector>`
    * Note that `<vector>` is also part of the `std` namespace
    * Use `using namespace std;` in place of the scope resolution operator
* Because vectors are an object oriented template class, the type must be specified in angled brackets (`<>`) 
* On initialization, vectors will automatically set integers in an array to `0`
* You can declare an array with as many elements as desired and instantiate them all with a specified value
* They're dynamic in size and can grow in shrink in run-time as needed
* Stored continguously in memory like arrays (they're basically a wrapper for an array)
* **Does not perform bounds checking** (at least when using square bracket subscripting (`[]`))
* Can access indices using the `.at()` method.
* Note that the dot (`.`) in `.at()` is referred to as the dot operator. This method of indexing also uses zero indexing.
* `.at()` also supports assignment
* when creating a vector of vectors and adding a vector to that vector of vectors, the default behavior is to make a copy of that vector.

### Constructor initialization syntax. 
Unlike arrays, you can easily initialize all indices in a vector to a specific value. For example:  
``` c++
vector <double> hi_temps (365, 80.0);
```
Would declare a vector of length 365 and instantiate all values at `80.0`.

### Adding to vectors 
To add a new element to the end of an array, you use the `.push_back()` method:  
``` c++
vector <int> test_scores {100,95,99};
test_scores.push_back(80);
vest_scores.push_back(90);
```

### A vector of vectors (of something)
``` c++
vector <vector<int>> movie_ratings 
{
    {1, 2, 3, 4},
    {1, 2, 4, 3},
    {3, 4, 1, 2}
};
```


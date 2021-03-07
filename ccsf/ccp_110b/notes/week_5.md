automatic vs. static variables.  

**Automaitc** variables and stack variables. Their memory is automatically allocated and de-allocated as a program runs.  
**Static variables** and variables that are stored in heap memory. All **global variables** are stack variables. You can
also make a variable a global variable by using that **static** keyword. When the word "static" applies to something it
does not mean that the thing it applies to is unchanging, it means that the storage for that thing has been "statically"
allocated, i.e. that it has been allocated on heap memory and will not automatically de-allocate.

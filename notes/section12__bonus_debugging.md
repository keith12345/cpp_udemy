# Debugging in vim

Run debugging with gdp

1. load the package in vim - `:packadd termdebug`
2. compile for debugging - `% gcc -g <fine_name.cpp> -o debug_binary`
3. `:termdebug --binary` - you don't need to specify the binary but you can
4. load the binary into gpd - `:file <path/to/binary>`

## Basic commands:

### From within the file:
* :Run - runs the file with breakpoints. Runs straight through in no breakpoints specified
* :Start - simply starts the program, doesn't run any code. Like starting where the beginning is a breakpoint
* :Break - adds a breakpoint
* :Clear - removes a breakpoint
* :Next - executes the next line
* :Step - steps into the highlighted function
* :Over - 
* :Continue - 
* :Finish
* :Stop


### From within gdp:
* print <variable> - print the specified variable
* print *<array_name>@<array_size> - dereferences and prints the specified number of elements in an array
    * You can even do this for things like `print argc` and `print *argv@<n_args>`
* refresh - if your display ever gets 
* break <function_name> - sets a breakpoint at the indicated function
* watch <variable_name> - lets you know any time the specified variable changes
* clear <binary_name> - removes all breakpoints
* backtrace full - tells you exactly which functions were called and prints everything out
* Ctrl-d - quit

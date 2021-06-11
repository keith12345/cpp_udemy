# Processes

What is a process?  
A **process** is an instance of an executing program. Sometimes the terms **task** and 
**job** are used in place of process. 

A process has certain attributes like:
* a state of execution
    * Program counter
    * stack
    * used to schedule/stop processes
* it has requirements to run like memory
    * data
    * register state
    * occupies state in memory
* There can also be required hardware components
    * i/o devices like disks
    * network devices 


## More on What a process is

Remember that an OS manages hardware on behalf of applications.  

A **application** is a program that's on disk, in flash memory, or even in the cloud, 
but it's not executing, it's ultimately a **static entity**. 

Once an application is launched, it's loaded in memory, it's starts executing, at which
point it is a process and is an **active entity**.  

If the same program is launched more than one then multiple processes will be created 
(but with different states).  

A process reprents the **execution state** of an active application.  
This doesn't necessarily mean that it's *running*. It could be waiting on user input or
waiting on another process that's running on the CPU.

## What does a process look like

It includes all of the code, data, variables, that the application needs to allocate.  
Every element needs to be uniquely identifiable by its address.  

An OS abstraction used to encapsulate all of the process state is an address space.  

An **address space** is defined by a range of addresses from `V0` to some `Vmax` and
different types of process state will appear in different regions in the address space.

Address space:

```
        |---------------|
 Vmax   |     Stack     |
        |---------------|
        |      ^^       |
        |      ||       |   Virtual
        |     Heap      |   addresses
        |      ||       |   used by
        |      vv       |   processes
        |---------------|
        |     data      |
        |---------------|
 V0     |     text      |
        |---------------|
```

The code to run the app (referred to in the above as "text") occupies the lowest level
of the address space.  
There's also data available when the process is first initialized.  
These two things, the "data" and the "text" are **static state** and are available 
when the process first loads.  

Then, during execution, the process dynamically creates some state; allocates memory,
stores stuff as per results, reads data from files.  
All of that is done in the **heap**.  

In the above the heap is shown as a continuous block but, in reality, in may not be 
a contiguous block. 

Portions might not have any meaning for a particular process and that process may not
even be allowed to access them.  

The **stack** is dynamic and grows and shrinks during executions. It is a **LIFO** 
(last is first out) queue. 

## Process Address Space

The addresses within the address space are referred to as **virtual addresses** because 
they don't have to correspond to actual locations in physical memory.  
Instead, the memory management hardware and OS components responsible for memory
management, like page tables, maintain a mapping between the virtual addresses and the
physical addresses.  
The OS basically has a lookup mapping a process's location (the virual address) in
memory to a hardware location (the physical location) in memory.

By using this type of mapping, we decouple the layout of the data in the virtual address 
space from how it's layed out in physical memory (the physical layout can pretty wonky
due to what things like the compiler might be doing to store stuff).

Two processes are able to have address ranges that are overlapping because they don't
correspond to physical locations. 

## How does the OS know what a process is doing?

If an OS stops a process, it must know what it was doing when it was stopped so it
can start again from that same point.  

Before applications can execute code, it must be compiled.  
Binary is produced. This binary is not necessarily executed sequentially (there could
be jumps, loops, interrupts, etc).  
The CPU must know where in this process the program is; this is called the **program
counter**, or just **PC**.  
The program counter is maintained in the CPU while the process is executing in a 
**register**.  
There are other registers that are also maintained on the CPU.  
This register may have information like addresses for data, status info, or other stuff 
that affects the sequence of execution.  
These are all parts of the state of the process or the state of execution.  
Another piece of state that defines what a process is doing is the process stack.  
The top of a stack is defined by the **stack pointer**. We need to know the top of the 
stack because of its LIFO behavior.  

To maintain all of this information for every single process, the OS maintains what's 
referred to as a **process control block**, a **PCB**. 

## What is a process control block (PCB)

A Process Control Block is a data structure that the operating system maintains for
every one of the processes that it manages. 

* Process state
* process number
* program counter
* registers
    * memory limits
    * memory mappings
    * list of open files
    * priority
    * signal mask
    * CPU scheduling info
        * how much time it should be allocated now
        * how much time in the future
    * etc...


The PCB is created/initialized when the process is created and the program counter will
point to the very first instruction in that process.

Certain fields are upcated when process state changes.  
If a process requests additional memory, the OS will establish a new valid virtual to 
physical memory mappings for this process (not common compared to other changes).  

The program counter on the other hand changes on every single instruction.  
Because it changes so frequently, we wouldn't want to OS to write to the PCB each time.
This is handle via a dedicated register that the CPU has, which it uses to track the 
current program counter for the currently executing process.  
This PC register will get automatically updated by the CPU on every new instruction.  

That said, it's OS's job to collect and save all information that the CPU maintains for
a process, and to store it in the Process Control Block structure whenever that
particular process is no longer running on the CPU. 

## How is the PCB used?

If you have one CPU that needs to go back and forth between executing two different 
things it'll load the PCB of the executing process into the CPU register as necessary,
then, which it switches back to the other process, it will load that proceess's PCB
into the CPU register.  
Each time this switch between processes is performend, it is doing what's called a 
**context switch**. 

## What is a context switch

A context switch is the mechanism used by the OS to switch the context of execution from
one process to the context of another process.  

The operations are expensive:
* there are direct costs 
    * the number of cycles that need to executed to simply load and store instructions
* Indirect costs:
    * cold cache
    * cache misses

Processor cache - The are multiple caches/levels of caches. L1, L2, ... Ln.  
Access to processor caches is on the order of cycles while access to memory is on the 
order of hundreds of cycles.  
We the required data is in the cache, people say "the cache is hot."  
When performing a context switch, some or all of the data required by one process will
be replaced by the process that's switching in.  
So, the next time the other process goes to execute, it's data will not be in the 
cache. It will then have to read data from memroy. This is called a **cache miss**.  
When it's in this state, it's referred to as a **cold cache**.  

For these reasons, you generally want to limit the frequency of context switches. 

## Process Lifecycle

When a process is running, it can be interrupted and context switched.  
At this point the process is idle but is in what's called a **ready-state**. It is ready
to execute but it is not the current process that is running from the CPU.  
At some point, the scheduler will schedule that process again, at which point it would
move into the running state.  

Other states that a process can be in:
* **new**
    * This is when the OS will perform admission control
    * if it's determined that it's okay, the OS will allocate and initiate a PCB and initial resources for the process
* **ready**
    * ready but not actually executing on the CPU. 
        * This means that it can execute the process but isn't currently executing it
    * Has to wait in this ready state until the scheduler is ready to run it on the CPU
* **Running**
    * once the schedule moves it from the ready process to run on the CPU
    * from here a few things can happen
        * **Ready**
            * the running process is interrupted and a context switch is performed
        * **Waiting**
            * Might need to wait for some large operation (reading something from disk)
            * Waiting on a time
            * Waiting on keyword input
        * **Terminated**
            * When a running process finishes all operation in the program
            * encounters some sort of error. 


## Process Creation

Processes can create child processes.  
All processes come from a single root. Any process that creates another process is a 
parent to that process. 

Root processes (there's a single root process (I guess?) but there are other root
processes) which will be privileged processes.  

Once the initial boot process is done and the OS is loaded on the machine, it will
create some number of initial processes.  

When a user logs into a system, a user shell process is created.  
Then when a user types in commands line `ls` or `vim`, new processes get spawned from
that shell parent process.  

Most OSs support two basic mechanisms for process creation. A process can create a child
from either of these two mechanisms. 
* Fork
    * copies the parent PCB into new child PCB
    * child then continues execution at instruction after fork
* exec
    * replace child image
    * load new program and start from first instruction

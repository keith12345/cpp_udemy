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

An **application** is a program that's on disk, in flash memory, or even in the cloud, 
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

An OS abstraction used to encapsulate all of the process state is an **address space**.  

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

Certain fields are updated when process state changes.  
If a process requests additional memory, the OS will establish a new valid virtual to 
physical memory mappings for this process (not common compared to other changes).  

The program counter on the other hand changes on every single instruction.  
Because it changes so frequently, we wouldn't want to OS to write to the PCB each time.
This is handle via a dedicated register that the CPU has, which it uses to track the 
current program counter for the currently executing process.  
This PC register will get automatically updated by the CPU on every new instruction.  

That said, it's the OS's job to collect and save all information that the CPU maintains for
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
When the required data is in the cache, people say "the cache is hot."  
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

## Role of the CPU Scheduler

Before a process can execute it must be in a ready state.  
That said, there will typically be multiple processes in a ready state in the queue.  
How to decide which process actually gets to run on the CPU?  

The **CPU Scheduler** decides what to run. It decides which should run and for how long.

To manage the CPU, the OS must be able to **preempt**, to interrupt the currently
executing process and save its current context. (This process is called **preemption**).

The CPU will have a scheduling algorithm which decides which of the ready processes
should be run next.  

Once that process is chosen, the OS must dispatch this process on to the CPU and switch
into its context to that process can start executing.  

Due to the scarcity of available CPU time, the scheduler must ensure that no time is 
wasted on scheduling between processes and other OS operations.  

The overall design must be efficient (limit downtime) and algorithms must be efficient
to reduce computational complexity, and data structures must also be efficient so
time isn't wasted reading from and writing to them.  

information that the scheduling algorithm might look at is:
* priority
* previous run-time
* etc.

## Length of a process

If we want to run the scheduler as few times as possible to reduce downtime switching
back and forth between tasks... but we don't want things to sit around and not finish
if there's a long process running, then we need to know how long each process should
run.  
The longer each process runs, the less frequently the scheduler is invoked.  

Given two processes:

`Tp` - time to run process
`Tsched` - time to run scheduler

```
useful CPU work == total processing time / total time == (2 * Tp) / (2 * Tp + 2 * Tsched)
```

If processing time and scheduling time are equal, then only 50% of the time in this 
example was actually spent doing anything useful.

If the process time is 10x schedule time and it switches twice, then it's doing useful
work 91% of the time. 

Scheduling Design Decisions:
* What are appropriate time slice values
* metrics to choose next process to run

## What about I/O

How do I/O operations affect scheduling?  

The OS manager how processes access resources on that hardware platform.  
This includes I/O devices like:
* keywords
* network cards
* disks
* etc.

In this diagram a process makes an I/O request (1), the OS (2) delivers that request (3), 
then **places the process** on the I/O queue that's associated with that particular 
device (4).  
The process is now waiting in the I/O queue.  
The process will remain waiting in the queue until the device completes the operations, 
(i.e. the I/O event is complete, request has been responded to).  
Once that request has been met, the process is ready to run again. Depending on the
current load in the system, it may be placed in the ready queue, or it may be scheduled
on the CPU if there's nothing else waiting in the ready queue before it.

```
               |---------------|1                                        
           ----| Process makes |                                         
           |   |  I/O request  |
           |   |---------------|                     2                 
           v                                   ///////--------------->         
-------->|-------------|                       / CPU /                                 
         | Ready Queue |---------------------->///////---|                             
      |->|-------------|                                 |       
      |                        4                 3       |                             
      |  ///////   |-----------|   |-------------|<------|                                      
      |--/ I/O /<--| I/O Queue |<--| I/O Request |                                             
         ///////   |-----------|   |-------------|                                             
```

Process can make their way into the ready queue in a number of different way.  
* A process which was waiting on an I/O event and ultimately found its way into the ready queue
* A process which was running on the CPU but its time slice expired
* When a new process is created via the for queue 
* Process was waiting for interrupt

Things that are not the resposbility of the Scheduler 
* Maintaining the I/O queue
    * This is because the scheduler handles operations once they occur but has no control over when they occur
    * One exception to this is timer interrupts
        * The scheduler determines when a process will be interrupted
        * This is how it makes the decision to context switch
* decision on when to generate an event that a process is waiting on
    * These are external events that the scheduler is waiting on are generated externally, nothing to do with the scheduler

## Can Processes Interact

An OS must provide mechanisms to allow processes to interact with one another.  
More and more applications nowadays are structured as multiple processes.  
So, these multiple processes have to be able to interact to contribute to a common
goal of a more complex multi-process application.  

For example, a web server and a database can both function on the same machine.  
The web server might provide a UI where a customer can enter information, that will
then make a call the the database.  

Remember that the OS goes through a lot of effort to ensure that processes are isolated
from one another.  
They each have a separate address space, the OS controls the amount of CPU power
each process gets, which memory is allocated and accessible to each process.  
As a result, communication methods have to be built around these protection 
mechanisms.  

The mechanisms are called **inter-process communication** mechanisms or **IPC** 
mechanisms. They:
* Transfer data/info between address spaces
* Maintain protection and isolation
* provide flexibility and performance

A Particular mechanism that is supported is **message-passing IPC**.
* OS provides communication channel, like a shared buffer
    * Processes write (send) / read messages to/from that buffer/shared communication channel


```
               Processes
 --------------             ------------                         
 | Web Server |             | Database |                                
 --------------             ------------                               
    |                                |                                
====|================================|===                             
    |                                |                                
    |    ------------------------    |                         
    ---->| Shared Communication |<----                         
         |       Channel        |
         ------------------------                              
    ------       -------                                                  
    | MM |       | CPU |
    ------       -------                                                  

        Managed by the OS
```

The advantage in this situation is that everything is managed by the OS.  
The downside is that there's a lot of processing to handle the communications.

The solution to this problem is to create a **Shared Memory (Channel) IPC**:
* OS establishes a shared channel and maps it into each process address space
    * Boxes in the illustration overlap to demonstrate this
* Processes directly read/write from this memory
* OS is out of the way!!

```
            --------------------
 --------------   Shared    ------------                         
 | Web Server |   Memory    | Database |                                
 --------------   Space     ------------                               
            --------------------                                      
                                                                      
=========================================                             
                                                                      
    ------       -------                                                  
    | MM |       | CPU |
    ------       -------                                                  

```

The primary disadvantage to this approach is that the OS, because it's been removed from
the equation, no longer supports fixed/well-defined APIs.  
As a result, this approach is more error-prone, or simply requires re-implementation of
existing code to utilize a shared memory region this way. 


# Summary

A process (task/job) is some application that has been launched and is now an active entity.
The OS manages multiple processes simultaneously and uses a data structure called a Process Control Block to track the status of each process.
Processes can typically be created in two ways, via fork and (copies a parent and then continue execution at current instrucition) and exec (load new program and start from first instruction).
The OS has to switch between processes occasionally and will use PCB to preserve process state so that it can pick up where it left off.
The scheduler uses algorithms to decide which task to run when and for how long. It takes things into account like priority and previous run-times.
Sometimes processes need to interact, this can either be via the OS, where the OS manager communications, or through a shared address space, where each process has access to the same space and can easily read/write without going through the OS (more efficient, error prone because not utilizing robust OS APIs for communication.


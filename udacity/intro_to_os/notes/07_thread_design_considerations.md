# Thread Design Considerations

## Kernel vs User-level Threads

### Quick refresher on kernel-level support

Supporting threads at the kernel-level means that the OS itself is multi-threaded.

The OS kernel maintains some abstraction of a thread data structure to represent threads.  
It performs operations like:
* synchronization
* scheduling
* etc.

This allows threads to share physical resources.

### Quick refresher on user-level support

Supporting threads at the user level means that there is a user-level library that is linked with the application and
provides management of run-time support for threads.
* data structure that's needed to implement the thread abstraction
* provide scheduling/synchronization/etc. needed for resource management

You can use any number of libraries and they'll support scheduling mechanisms, resource management, etc. in
differen ways.

## Thread-related data structures

### Single Process

Process is described by process-related state in the **PCB** or **process control block**.
* virtual address mapping
* stack
* register pointers

User-level threads, or **ULT**s have their own data structure containing:
* UL thread-id
* UL register pointers
* UL thread stack

When there are multiple kernel-level threads, or **KLT**s, the **PCB** gets split up. One part for the whole kernel and other parts
for each individual thread.

**PCB**:
* virtual address mappings
* information related to the whole process

**KLT**:
* stack
* register pointers

Kernal level threads act a little virtual CPUs.

### Multiple processes

Copies of the relevant data structures, **ULT** data structures, **PCB**s, **KLT** data structures, are required for
each process that's running to represent every single aspect of every single process.

If the system has multiple CPUs then there also needs to be a data structure to represent each CPU. 
The relationship between **KLT**s and the CPU also needs to be maintained. 
* Which CPU was a KLT last run/scheduled on 
* Does the KLT have an affinity to a particular CPU
* tracks pointers from CPUs to their current/typical threads

The kernel may need to switch between kernel-level-threads that belong to different processes. The kernel will determine
that they point to a different process control block. They will have different virtual address mappings, it will
invalidate the existing mappings and restore new ones. 

### Hard and Light Process State

When two KLTs belong to the same address space, there's information in the PCB that is relevant for the entire process,
there's also information that is specific to a single KLT.  
This includes information about:
* **Signals**
* **system call args**

When context switching between these two KLTs, there's a portion of the PCB that we want to preserve, e.g. the virtual
address mappings, then there's the portion that's specific to the particular KLT, and it depends on the ULT that's 
currently executing.

All of the above information regarding ULT/KLT structures and PCBs can be put into two categorie. **Light process
state** and **Hard process state**. 

In terms of the PCB, the **hard process state** is the information that is relevant for all of the ULTs that execute 
within a process. The **light process state** is the information for the subset of the ULTs that are currently
associated with a particular KLT. 

### Raionale for multiple data structures

With a single process control block:
* large continuous data structure
* private copies for each entity
* saved and restored on each context switch
* update for any changes

These factors respectively limit:
* scalability
* overheads
* performance
* flexibility

With multiple data structures:
* smaller data structures
* easier to share
* on context switch only save and restore that needs to change
* user-level library need only update a portion of the state

### User-level thread data structures

_Stein and Shah version - not the same as posix threads_.

During thread creation, a **thread ID**, or **TID** is returned.  
This doesn't actually point directly to the thread data structure as is typically implied. Instead, it's actually an
index in a table of pointers. That table of pointers then actually pointers to the actual thread data structure.  

This actually solves a potential problem: 
* If the thread ID were a pointer, then that pointer would just point to some corrupt memory and you can't really trouble shoot. 
* By having the thread ID indexed into a table, we can encode some information into the table entry that can provide meaningful feedback or an error message. 
* The error that more typically occurs is that, when there are multiple ULTs, the stack of one of those will continue growing until information that from thread overwrite information for another thread. 
    * the tricky part is that the error is not detected by the thread that did the overwriting, but rather by the thread that was overwritten, and it might not even be detected until some time after it was overwritten

The solution introduced by Stein and Shah was to include a **red zone** which separate information about different
threads. This refers to a portion of the virtual address space that's not allocated.  
So, if a thread is running and its stack is increasing, and it tries ot write to an address that basically falls in the
red zone region, then the OS will cause a fault.  
The means that when there's a problem, it's more easily detected by the thread that's executing, which makes it easier
to do root-cause analysis and fix the problem.

### Kernel-level data structures

#### Process

For each process we maintain information about that process
* list of kernel-level threads that execute in that kernel-level address space
* virtual address space, i.e. what are the mappings that are valid between virtual and physical memory
* user credentials if this person is trying to access a file
* signal handlers - more or this later

#### LWP

**Light-weight process** / **LWP** data structure
* user-level registers
* system call args
* resource usage info
* signal mask

Similar to ULT, but visible to kernel. Not needed when process not running.  

If we want to find the aggregate resource usage for the entire process, we need to iterate through all of the LWPs that
are associated with it. 

#### KLT

Kernel level data structure - kernel-level information
* kernel-level registries
* stack pointer
* scheduling info
* pointers to associated LWPs, CPU structures

Information needed even when process not running -> not swappable. 

#### CPU

* current thread
* list of KLTs
* dispatching and interupt handling information

On the **SPARC** architecture mentioned in the Solaris paper, there are extra registers, and its implemented such that
there is one dedicated register that is used to point to the current thread at any given moment.  
During a context switch, that register is updated, but it allows the CPU to access that register and immediately start
tracking through pointers to find the right info.  
This is in contrast to having to access memory, read the CPU structure, and the read the current thread information,
etc.

Note that if we havce information about the CPU, once we know the current thread, we can find out information about all
of the different data structures that are needed to rebuild the entire process state. 

## Basic thread management interactions

### Example

Let's say that some user-level process has 4 threads, but only 2 are ever running concurrently.  
If the OS has a limit on the number of kernel-level threads that it can support, it would be nice if the user-level
process actually said, that it only actually needs 2 thread.  
When the process starts, a standard number of threads may be allocated, e.g. 1.  
The process will request addition kernel-level threads, with a process called set_concurrency.  
In response to this system call the kernel will create additional threads and it will allocate those to this process.  

Now let's say that two of the threads in that application get blocked (meaning that both kernel-level threads are
blocked as well).  
Now the entire process is blocked because it only had two kernel-level threads.  

This is staying blocked because the user-level library doesn't know what's happening in the kernel.  
It would have been useful if the kernel notified the user-level library before it blocks the kernel-level threads.  
The user-level library would then be able to look at its run queue, see that there are multiple runnable user-level
threads, let the kernel know, and then make a system call to request more kernel-level threads of LWPs.  
The kernel would then be able to allocate a third KLT, and then the library could start scheduling the remaining
user-level threads onto the associated LWP.  
Eventually, when the blocking process ends and the two blocked threads are freed, the application will then have 3
threads but only two will be used by the user-level library.  
The kernel can then tell the kernel-level library that the user-level library no longer has access to that third KLT,
and can't schedule on it. 

Important things to keep in mind here:
* The user-level library does not know what is happening in the kernel
* the kernel does not know what is happening in the user-level library

Solaris created system calls that allow the kernel and ULT to interact and coordinate.  
This is basically how the kernel-level and user-level thread managemenet interact and coordinate.

### Lack of thread management visibility

What the kernel sees:
* KLTs
* CPUs
* KL scheduler

What the UL library:
* ULTs
* Available KLTs

If it's a 1:1 relationship, then each ULT gets its own KLT.  
But even if it's many:many, a ULT can still be **bound** to a KLT.  
This is similar to what would be done in a multi-CPU system is a particular KLT needs to be permanently associated with
a CPU. In that case, it's called **thread pinning**. 

### Issues on multiple CPUs

#### Priority

When you have multiple threads running on different CPUs, a thread that's running on one CPU may need to impact a thread
that's running on a different CPU.  
This might happen if different ULTs have different priorities and a ULT needs to preempt a KLT from a lower priority
KLT.  
Note that we cannot directly modify the registers of one CPU when operating on another CPU.  
If a thread is currently running it might not check to see if there's something higher-priority waiting to run. but the
thread on another CPU may realize that there's something high-priority that should run so we need to signal from the 
context of one thread on one CPU to the context of another thread (the lower priority one that should be preempted) on 
another CPU to tell it that there's a higher priority ULT waiting needs to run.

#### Synchronization

Let's say there's a ULT (ULT1) running on a KLT (KLT1) and that ULT has a mutex. Some other ULTs may be blocked and 
there's another ULT (ULT4) running on a separate KLT (KLT4).  
ULT4 wants the mutex but it's still locked by ULT1.  
Normal behaviour would be to place ULT4 on the queue associated with that mutex.  
The tricky thing in this example is the KLT1 and KLT4 might be running on different CPUs.  
If the critical section is very short for the operation that ULT1 is running on KLT1, then it's possible that by the
time ULT4 is context switched and placed on the queue associated with the mutex, that the mutex is already freed.  
In cases like this, it might make sense for the thread to just spin on the CPU and burn a few cycles waiting for that
mutex to become available.  
* So, for short critical sections, don't block, spin.  
* For long critical sections, perform the default behavior where the thread is properly blocked, placed on the queue

Mutexes which sometimes results in the thread just spinning and other times actually blocking **adaptive mutexes**.  
This only really makes sense on mutli-CPU systems because whether or not we spin depends on whether or not the owner of
the mutex is actually running on another CPU.  
This won't be the case on a single CPU system (I'm honestly not sure why not).

This is also a good example of why it's good to store information about the owner of a mutex and the critical sections
that it locks as it can help us decide if we should spin or block. 

### Not destroying threads?

Whenever a thread is finished getting used, it should be destroyed and the associated memory should be freed.  
But thread creation/initilization takes some time, so it actually makes sense to re-que the data structure for a thread
as if we're re-using the actual threads.  
The way this is done is that when a thread exists, it's not immediately destroyed.
* Put on **"death row"**
* periodically destroyed by a **reaper thread**.
* if a request for a thread comes in while a thread is on death row and before it has been reaped, then its data structure and stack can be reused.

## Interrupts and Signals

### Differences between the two

**Interrupts** are events that are generated externally by the components other than the CPU (I/O devices, timers, other
CPUs). It's basically a notification that some event has occurred.  
The types of interrupts that occur are dependent on the physical platform: the types of devices that are connected,
details of hardware architecture, etc.  
Note that they also appear **asynchronously**, as in they are not in direct response to something that happened on the
CPU.  

**Signal** are events that are triggered by software that's running on the CPU.  
Types of signal depend largely on the OS.  
Signals can appear both **synchronously** (in response to a specific action that took place on the CPU), at which
point a synchronous signal is generated, and asynchronously.  

### Similarities

* They both have **unique ID**s depending on the hardware or OS.  
* They can be **masked**, and disabled/suspened via corresponding mask. 
    * per-CPU interrupt mask - associated with a CPU ecause interrupts are delivered to the CPU as a whole
    * per-process signal mask - per-process because signal masks are associated with specific processes
    * This will disable or suspend the notification that an interrupt or a signal is delivering. 
* If the mask indicates that the signal/interrupt is enabled, then that will result in invoking the corresponding **handler**.
    * interrupt handler set for the entire system by OS
    * signal handlers set per process basis by process

#### Quick simile

An **interrupt** is a like a snowstorm warning for a toy-shop, some external event.  

A **signal** might be more like a battery low warning, something generated from within.  

Each of these warnings: 
* need to be handled in specific ways
    * toy-shop - safety protocols, hazard plans, etc.
    * OS - interrupt/signal handlers
* can be ignored
    * toy-shop - just continue working
    * os - interrupt/signal masks
* can be expected or unexpted
    * toy-shop - might happen regularly or irregularly. 
    * os - appear sync or async

### Interrup Handling

When a disk, for example, wants to send a notification to the CPU, it sends an interrupt message between the
interconnect that connects the disk to the CPU complex.  
The particular message that's sent is called a **message signal interrupter**, or **MSI**. That message can carried on
the same interconnect that connects the devices to the CPU complex.  
Based on the interrupt message, the interrupt can be uniquely identified so we know, based on this information, exactly
which deivces generated the interrupt.  

The interrupt interrupts the execution of the thread that was executing on top of the CPU. If the interrupt is enabled,
a table is referenced containing the starting addresses of the interrupt handling routines. 

```
INT - 1 : handler-1-start-address
INT - 2 : handler-2-start-address
...     :
INT - n : handler-n-start-address
...     :
```

Remember that the exact interrupts that can occur depend on the hardware, and how they're handled is specified by the 
OS. 

### Signal Handling

When might you get a signal? - Trying to access an illegal location in memory.  
This will generate a **SIGSEGV** error, `#11` in linux.  
The process that executes is similar to what's handled in interrupts. 

```
SIGNAL - 01 : handler-01-start-address
SIGNAL - 02 : handler-02-start-address
...         :
SIGNAL - 11 : handler-11-start-address
...         :
```

As with interrupts, remember that the exact signal that can occur depend on the hardware, and how they're handled is 
specified by the OS.

The OS specifies default actions for handling signals:
* terminate
* ignore
* terminate and core dump
    * Might do this so that one can insepct the core dump and determine the reason for the process crash
* stop a process
* continue a stopped process

For most signals, a process is aloowed to install its own custom handling routine.  
There are system/library calls that allow a process to do this.  
Certain signals are exceptions to this, we say that they cannot be **caught**. Something that you cannot **catch** will
always kill a process.  

Synchronous signals:
* SIGSEGV - access to protected memory
* SIGFPE - divide by zero
* SIGKILL - kill process id
    * can be directed to a specific thread

Asynchronous:
* SIGKILL - kill process id
    * both sync (directed signal) and async (cause process to terminate)
* SIGALARM - maybe timeout from timer expiring

### Why disable Interrupts or Signals

The problem with interrupts and signals is that they're executed in the context of the thread that was inerrupted.  
What this means in practice is that they're handled on the thread stack.  

* Given some program that has a Program Counter and a thread stack.  
* There's some sort of interrupt of signal
    * program counter changes -> points to first instruction of the handler
    * Stack pointer remains the same
    * This can even be nested, e.g. multiple interrupts or signals and they will keep executing nestedly on the stack of the thread
* If it needs to access state that some other thread might be accessing, then we need to use mutexes. 
    * however, if the thread that was interrupted already had the same mutex, then we have a deadlock
        * The interrupted thread will not release the mutex until the handling routine completes the execution on its stack and returns
        * That can't happen because it's blocked on the mutex
    * Basically, 
        * there's a thread running and that thread blocks a mutex
        * There's an interrupt/signal
        * That interrupt of signals results in a handler running that needs access to the same mutex that the interrupted thread was using
* A simple solution is to prevent the handling code from using mutexes
    * but that doesn't work in practice because sometimes it _needs_ to block something
* The robust solution to this is to use masks that allow us to enable or disable whether the handling code can interrupt the executing mutex
    * these are the **interrupt masks** and **signal masks**
* The mask is a bit-map showing which interrupts/signals are blocked
* When an event occurs
    * the mask is checked
    * if masked, wait until the mask value changes
    * if not mask, proceed with the handler invocation
* To prevent the deadlock situation, the thread will
    * mask any signals/interrupts that require any of the mutexes that it will lock
    * execute the critical section
    * unlock the mutex
    * an-mask the relevant signals/interrupts

This means that they're handled on the thread stack and can cause certain issues that will make it more logical to
disable interrupts and signals.  

### More or masks

* Interrupt masks are per CPU.  
    * If a mask disables interrupt, the hardware interrupt routing machanism will not deliver interrupt to the CPU.  
* Signal masks are per execution contect, (ULT on top of KLT)  
    * If a mask disables a signal, kernel sees mask and will not interrupt corresponding thread

### Quick note on interrupts on multi-core/CPU systems

### Types of signals

#### One-shot signals

One property of these signals is that we know that is there are multiple instances of the same signal that will occur,
they will be handled at least once. It's possible to have a situation in which only one signal of a particular kind
occurred, vs. `n` signals of that same kind occurring, then only execution of the actual signal handler is performed.

The other thing about one-shot signals is that the handling routine must be re-enabled every single time.  
e.g. if the process wants to install some custom handler for a particular signal, then invoking the operation will mean
that one the signal occurs, the process-specific handling routine will be invoked.  
Any future instances of that signal will be handled by the default operating system action.  

#### Real-time Signals

If `n` signal raised, then handler is called `n` times. 

#### The differences?

Real-time signals basically queue-up while one-shot signals actually kinda override the default behavior. 

## Handling interrupts as threads

Remember that when an interrupt occurs, there's a possibility of a deadlock.  
This happens because the interrupt handling routine was waiting on something/trying to lock a mutex by a thread was
interrupted by that interrupt routine.  
A similar situation could have happened for the signal handling routine.  

A way to handle this is to allow interrupts to become threads.  
This should happen every time they're potentially performing blocking operations.  

If it's in a thread, it has its own context, its own stack, and can therefore remain blocked.  
That way, the thread scheduler can schedule the original thread on the CPU.  

Eventually the original thread will unlock the mutex and, at that point, the thread that corresponds to the interrupt
handling routine will be free to actually execute. 

Biggest pain point might be the dynamic thread creation.  
You only _might_ need to create a thread for a handling routine if it comtains locks, so, if it doesn't, it'll just be
executed on the stack of the executing thread. 

A way around the thread-creation pain-point is to pre-create/initialize thread structures that are meant specifically
for supporting interrupt routines. 

## Top half and Bottom half

When an interrupt first occures, 

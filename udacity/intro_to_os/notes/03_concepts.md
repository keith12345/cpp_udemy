# Concepts

## What is an operating system?

There isn't a single definition of what an operating system is.

Operating systems are basically the set of software that sits between all of your applications and the hardware on your
machine.

The operating system hides the complexities of the underlying hardware from the applications (and their developers).

* Has priveleged access to underlying hardware
* hides hardware complexity
* managers hardware on behalf of one or more applications according to predefined policies
* ensures that applications are isolated and protected from each other

Operating systems handle two things primarily, **abstraction** and **arbitration**.

Abstraction focuses on hiding system details. Arbitration focuses on managing system use.

Distributing memory between multiple processes is an example of arbitration because the OS is acting as a manager,
deciding who's handling what.

Supporting different types of speakers or switching between hard disks and SSDs is an example of abstraction because the
OS acts as a communicator/translator between applications and the hardware components with which the applications are
interacting.

## Different types of operating systems

Some are more desktop/server. Others are more embedded (smartphones/android/iOS/Symbian, maybe Roku?), others still are for things like mainframes.  

Everything the extends from what Bell Labs made in the '80s are UNIX-based OSs. This includes:
* Mac OS X (**BSD** - which Berkeley System Distribution of UNIX)
* Linux

## OS Elements

Standard abstrations that an OS might handle:
* process
* thread
* file
* socket
* memory page
Standard mechanisms
* create
* schedule
* open
* write
* allocate

Abstractions and mechanisms correlate with each other, e.g. open, which is a mechanism, is used on files, which are an
abstraction. 

An OS will also have **policies** to determine how these machanisms will be used to access the underlying hardware.
* least-recently used (LRU)
* least-frequenty used (LFU)
* random
* Earliest deadline first (EDF)


Using a memory page as an example of an abstraction, we can use certain mechanisms associated with it.  
We can allocate memory for it in DRAM, and then map it to a process, the process can then access the actual physical
memory associated with the contents of that page.  
This page can be moved to different locations within DRAM or even moved to disk if we need to make room for something
else in **physical memory** (DRAM), also referred to as **main memory**.
Lastly, we can use policies (e.g. LRU) to determine what is moved to disk. This is frequently referred to as
**swapping**. 

## Design Principles

### Separation of mechanism and policy

* Implement flexible mechanisms to support many policies
    * e.g. LRU, LFU, Random

Then you want to optimize for common use-cases
* where will the OS be used
* what will the user want to execute on that machine
* what are the workload requirements


## OS Protection Boundary - User/Kernel level

### user-level

User-level is not privileged.

Applications operate on unprivileged user-level. 

### kernel-level

Kernel level is privileged.

Because the OS must have direct hardware access, it must have direct kernel level access. 

Hardware access is only ever directly via the kernel. 



Switching between user-level and kernel-level access is supported by hardware on most modern platforms (not really sure
what this means, tbh).

If user-level applications try to access hardware directly it'll actually do something called **causing a trap**.  
The application will be interested and the hardware will switch control to the operating system at a specific location
(not sure what that means either...).  
The OS can then grant access or terminate the process if it was trying to do something illegal.  

In addition to the trap method, the interation between the applications and the OS can be via a **system call
interface**. The OS export a system call interface - a ste of operations that the applications can explicity invoke if
they want the OS to perform certain **services** of privileled access on their behalf.  
Examples of system calls are:
* open (a file)
* send (a socket)
* malloc (allocate memory)


Operating systems also support **signals**, a mechanism for OSs to pass notifications into the applications. 

## System calls

We start at some user process (1).  
That user process needs to access hardware so it needs system access.  
It then makes a system call (2). 
During the system call, control is passed to the OS, in privileged mode, and the OS
will perform the operation and return the results to the process. (3)  
Executing the system call involves changing the execution context from the user 
process to that of the OS kernel.  
During this time, whichever arguments are required are passed.  
Then you jump around in the memory of the kernel so that you can go through
the instrubtion sequence that corresponds to that system call.  
With the system call, control is passed to the OS, which operates in privileged mode,
and it can perform whatever operation was specified in the system call.  
Once the system call completes, it returns the result and control back to 
the calling process (4).  
During this time, execution context is changed from the kernel mode into the user mode
while also passing any arguments to the user address space, and then, jumping to the
exact same location in the execution of the user process where the system call was
made from.

```
  -------------------------------------------------------------------
  | User Process   1                        2                    4  |
  | ----------------         ----------------     ----------------  |  user mode 
  | | user process |  --->   | calls system |     | return from  |  |  (mode
  | |  executing   |  --->   |     call     |     | system call  |  |  bit = 1)
  | ----------------         ----------------     ----------------  |
  -----------------------------------||--------------^^--------------
                                     ||              ||
  -----------------------------------vv--------------||--------------
  | Kernel                          trap           return           |
  |                             mode bit = 0    mode bit = 1        |  kernel
  |                                  ----------------3              |  mode
  |                                  |   exeucte    |               |  (mode
  |                                  | system call  |               |  bit = 0)
  |                                  ----------------               |
  -------------------------------------------------------------------
```

To make a system call, an application must:
* write arguments
* save relevant data at well-defined locations
    * necessary so that the OS kernel can, based on the system call number, can determine:
      * which arguments 
      * how many arguments it should retrieve
      * where the arguments are.
* make the system call using the system call number 


Arguments can either be passed directly between the user program and the OS or passed 
indirectly by specifying their address.


```
                        register
                     -------------
                     |     X     | 
                     -------------
     User program      ^       |            OS
 -------------------   |       |   -------------------
 | X: parameters   |   |       |   |                  |
 |    for call     |   |       |   |                  |
 |                 |   |       |   |                  |
 |                 |   |       |   |                  |
 | load address X  |---|       |-->| ---------------- |     Code for
 |                 |               | |use parameters| | <-- system 
 |                 |               | |from table X  | |     call 13
 | system call 13  |-------------->| ---------------- |
 |                 |               |                  |
 |                 |               |                  |
 -------------------               -------------------
```

in **synchronous mode** the process will wait until the system call completes. 

Most important thing for this lesson is that there are some basic steps in making an
OS call and obtaining the results.

## Crossing the OS boundary

User/kernel transitions are a necessary step in application execution.  
The kernel is the intermediary when performing any and all interactions with hardware.  

Due to the amount of instruction that's required, it can take ~50-~100 ns on a 2GHz machine
running linux to perform the necessary ineraction for a user application to perform
the user/kernel transition.  

Another burden of these transitions is that they impact the hardware cache usage.  
Application performance is very dependent on the ability to use the hardware cache.  

> "If accessing cache is on the order of a few cycles, 
> accessing memory can be on the order of hundreds of cycles."

When performing a system call, or when crossing into the operating system in general, 
the OS, while executing, will likely bring content that it needs in the cache.  
This will replace some of the application content that was in the hardware cache 
before that transition was performed.  
This will impact application performance. (Because it will no longer be able to acess
data that's in the cache, it will have to go to memory).  
Ultimately, these transition ain't cheap. 

## OS services

What does an OS actually do?  
> They provide applications with access to the underlying hardware
> of a machine. 
> It does this by exporting a number of services.

These **services** are directly linked to some components of the hardware.  

**Scheduling** to control access to the CPU.  
The **memory manager** is responsible for allocating the underlying physical memory
to one or more co-running applications. (And it also makes sure they don't overwrite
each other's content).  
A **block device driver** is responsible for access to HDDs and SSDs.  

The OS also "exports" **higher-level services** that are linked with **higher-level
abstractions**, as opposed to those that are linked with abstractions that map directly 
to specific hardware components. 

**File** is an example of an abstraction. OSs integrate file systems as a service.  

Summary:  
An OS will have to incorporate a number of services to provide applications and application
developers with a number of useful types of functionality. 

(All Unix examples.. screw windows)
* Process management
  * `fork()`
  * `exit()`
  * `wait()`
* files management
  * `open()`
  * `read()`
  * `write()`
  * `close()`
* device manipulation
  * `ioctl()`
  * `read()`
  * `write()`
* Information maintenance
  * `getpit()`
  * `alarm()`
  * `sleep()`
* communcation
  * `pipe()`
  * `shmget()`
  * `mmap()`
* protection
  * `chmod()`
  * `umask()`
  * `chown()`
* etc.

## Monolithic OS

Original design. 

All services and every type of hardware is already part of the OS.  
Could have several file systems where they're optimized for different purposes:
* sequential workloads (sequentially accessing files when reading and writing)
* random IO (common with databases)


The benefit is that everything is included.  
Everything is packaged at the same time which results in compile-time optimizations.  

The downside is 
* lack of ability to customize
* low portability
* hard to manage
* large memory footprint
    * can result in poor performance


## Modular OS

Linux is a good example of this.  
Has basic services and APIs but other things can be added as "modules".  
You can decide to use different file-systems or schedulers.  
This is possible because there are basic interfaces that any OS must implement to be part of the
OS.  
Then dynamically, depending on the workload, we can install a module that implements this
interface in a way that makes sense for this workload.  

If performing database operations we can run a file-system that's good for random file access. If 
we need something else, we can dynamically install new modules in the OS.  

The benefits are that the OS is easier to maintain and upgrade, it has a smaller memory
footprint, and has lower resource needs. All of these things ultimately mean that there's
more space left for applications to do their thing. 

The weakness is that the **indirection** resulting from modularity can impact performance. 
(Everything might have to go through multiple interfaces before anything can get done).  
While this takes away some room for optimization, the impact is typically minimal.  
Maintenance can sometimes be difficult when random modules are buggy and because they can 
be written in a variety of languages.

## Microkernel

These only require the most basic primitives at the OS level.  

Can represent executing applications, their address space, and its context (i.e. a thread).  

All other software components, applications like databases, file systems, device drivers, etc, will 
exist outside of the OS kernel at a user level (unprivileged).  

Because none of these things actually have direct kernel access, lots of inter-process
interactions are required.  

As a result, **IPC**, or **interprocess communications** are one of the core abstractions 
that a micro-kernel would support (along with addresses spaces and threads).  

Micro-kernels are useful because they're super small and **verifiable** (i.e. easy to 
test that code actually works on it).  
This is most useful in some environments where it's critical that for the OS to behave
properly. Examples of this are embedded devices or control systems.  

They generally have low portability due to how customized they are to the underlying hardware.  
This means that there are more one-off versions of a micro-kernel specialized for different 
platforms makes it harder to find common components of software (which leads to software 
complexity).  

## Linux Architecture
 
```
|-------------------------|---------------------------------------------|
| User interface          |   Users                                     |
|-------------------------|---------------------------------------------|--------------|
| Library Interface       |   Standards utility programs                |      ^       |
|                         |   (shell, editors, compilers, etc)          |     User     |
|-------------------------|---------------------------------------------|     Mode     |
| System Call Interface   |   Standard Library                          |      |       |
|                         |   (open, close, read, write, fork, etc)     |      v       |
|-------------------------|---------------------------------------------|--------------|
|                         |   Linux Operating System                    |      ^       |
|                         |   (process management, memory managmenet    | Kernel Mode  |
|                         |   file system, IO, etc)                     |      v       |
|-------------------------|---------------------------------------------|--------------|
|                         |   Hardware                                  |
|                         |   (CPI, memory, disks, terminals, etc)      |
|-------------------------|---------------------------------------------|
```

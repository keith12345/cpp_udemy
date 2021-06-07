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
they want the OS to perform certain services of privileled access on their behalf.  
Examples of system calls are:
* open (a file)
* send (a socket)
* malloc (allocate memory)


Operating systems also support **signals**, a mechanism for OSs to pass notifications into the applications. 

## System calls

We start at some user process (1).  
That user process needs some system access.  
It then makes a system call (2). 
During the system call, control is passed to the OS, in privileged mode, and the OS
will perform the operation and return the results to the process. 

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




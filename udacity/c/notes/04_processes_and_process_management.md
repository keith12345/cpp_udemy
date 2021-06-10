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


### More on what a process is

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

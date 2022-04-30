# Vocab

socket - an abstraction used to refer to an interface to a network  
files - abstration used to refer to refer to data stored on a disk  

The data structure under the hood for these two things is actually identical and is called a **file descriptor**.

event - input on a file descriptor 

An event in the context of a web server is an input on any of the file descriptors associated with it.  
(Any of the files or any of the sockets that are accessed as a result of the event). 

Given that there's an event in a system, how do you determine which file desriptor has inputs?

Something about a `select()` call that takes a range of file desriptors and returns the first one that has input on it.  
(Regardless of whether it's a file or a socket). 

`poll()` is an alternative. 

Not uncommon for very few file descriptors to have inputs. 

`epoll()` is a new thing - has performance improvements on `poll()` and `select()`.


## Benefits of event driven model

single address space flow of control

smaller memory requirements, no context switching
 
no synchronization

# asynchronous i/o operations

when a system call is made, the kernel captures enough info about the caller and where and where and how the data should
be returned once it becomes available. 

Async calls provide caller with opp to proceed executing something and come back later to check on the result. e.g.
1. start reading something from disc
2. do something else
3. come check if the data has been read
4. do something else
5. check if data is read
6. use data

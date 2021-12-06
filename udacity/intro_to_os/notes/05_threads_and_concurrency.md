# Threads and Concurrency

Processes, as they've been discussed so far, only work on a single processor.  
To take advantage of multiple processors, that process needs to have multiple
**execution contexts**.  
The execution contexts within a single process are called **threads**. 

Questions to answer - how are threads different from processes?

## Thinking about threads

Active entity executing a unit of work, a unit of a process. Many entities can work 
together on different units of work that are required to complete a task (think workers 
on assembly line doing specific tasks). 

These entities work simultaneously on different parts of the problem (they can either be on 
different occurrence of the same problem, or working on a different step of that problem).

These entities need to be coordinated. Hardware (I/O devices, CPUs) and access to data 
needs to be coordinated to prevent issues. 

## Process vs Thread

A process has it's **Process Control Block** or **PCB**.
A single-threaded process is represented by its address space.  
This will contain all of the virtual to physical address mappings for the process, 
its code, its data, heap, etc.  
Also represented by the execution context which has information on registers, stack
pointer, program counter, etc. 

Threads represent multiple, independent execution contexts.  
They're part of the same virtual address space which means that they share all of the 
virtual to physical address mappings. 

They share all of the same code, data, and files... but will potentially execute 
different instructions, access different portions of that address space, operate on 
different portaions of the input, and differ in other ways.  

This means that each thread will need to have a different program counter, stack
pointer, stack, thread-specific registers.  

For each thread, we need separate data structures to represent this per-thread info.

To represent this, the OS will have a more complicated process control block 
structure.  
It will have all information that's shared among threads
* virtual address mappings
* code
* data
* etc
Separate information about each execution context in that process:
* program coutner
* stack pointer
* stack
* registers, etc

## Why are threads useful

**Parallelization** - Each thread processing a different chunk of data.  
* Just brute forcing to get something done faster

**Specialization** - Each thread working on a completely different portion of the program. 
* threads can specialize in different tasks
    * can help take advantage of caches.

A benefit of partitioning which operations and handled by different threads, or on each
CPU, comes from the fact that performance is dependent on how much state can be present
in the processor cache.  
Each thread has access to its own processor cache.  
If a process is **specialized**, it'll have more state relevant to that operation stored
in the cache.  

If we use a multi-process application without using multi-threading, we'd have address
space allocations and four execution context allocations.  
A multi-threaded solution results in threads sharing an address space, but they still
each have their own execution context.  
This _is_ beneficial though, because the address space information can take up
substantial memory.  

**Multi-threading is more memory efficient than multi-processing.**

Because of the increase in memory efficiency, you're less likely to need to perform
swaps from disk which allows boosts execution time.  
Inter-process communications are also more costly.  
Communication and synchronization among threads in a single process is performed via
shared variables in that same process address space, so that costly inter-process
communication is not required. 

## Are threads useful on a single CPU
Or how about when the number of threads is greater than the number of CPUs. 

If there is idle time (e.g. reading from disk) between tasks within a single thread that 
exceeds the time it takes to perform a context switch and start executing on that new 
thread, and THEN perform another context switch and go back to the original thread.

So, if `(idle_time) > ((time_to_context_switch * 2) + other_task_duration)` then it makes
sense to switch.  
This is referred to as **hiding idling time**.  

One of the most costly steps in the context switch is the time that's required to create
the new virtual to physical address mappins for the new process that will be scheduled.  
Because threads share an address space, it's not necessary to recreate new virtual to
physical address mappings. So, this step is avoided when switching between threads.  

Related to this, this means that the time to context switch between threads is less than
the time to context switch between processes.  

In short, multi-threading, on a single CPU (or where # threads > # CPUs) allows us to
hide more or the latency that's associated with IO operations.

## Benefits of multi-threading: Applications and OS

By multi-threading an OSs kernel, we allow the OS to support multiple execution contexts.  
This is particularly useful when there are multiple CPIs, so that the OS context can
execute concurrently on different CPUs in a multiprocessor or multicore platform.  

The OSs threads may run on behalf of certain applications, or they may run OS level 
services like daemons of drivers. 


## Quick Quiz

**Threads** - can share a virtual address space
**Processes** - take longer to context switch
**Both** - have an execution context
**Threads** - usually result in hotter caches when multiple exist
* Data needed by one thread might already be brought into the cache by another thread
**Both** - make use of some communication mechanisms.

## Basic Threads Mechanisms

What do we need to support threads?

Must have a data structure that allows us to distinguish between threads and processes.  
Should allow identification of specific threads and to keep track of their resource
usage.  

Must have mechanisms to **create** and **manage** threads. There must also be mechanisms
to safely **coordinate** among concurrently running threads in the same address space.  

### To know the type of coordination required, we must know the potential issues

Individual processes each have their own address space.  
The program + OS will make sure that no access from one address space is allowed to
be performed on memory/state that belongs to another address space.

By their nature, separate processes cannot access the same space.  
By their nature, threads have access to the same space. This means that when and how
access is performed needs to be managed.  
The method for allowing access for only a single thread at a time is **mutual exclusion**.  
The way this is done is by use of an object called a **mutex**.  
OSs will also offer threads a mechanism to **wait** on other threads or until specific
conditions are met.  
**Condition variables** are used to handle this type of inter-thread coordination.  

Both the **mutex** mechanism and the **wait** mechanism are referred to as 
**synchronization** mechanisms. 

## Thread creation

(Stuff according to Andrew D. Birrell)

**Thread type** - hypothetical data structure for tracking threads
* All information specific to a thread and that can describe a thread
    * Contains **thread identifier** used to ID a specific thread
    * Register values:
        * program counter
        * stack pointer
    * etc.

This info can be used to prioritize/debug/manage threads.

For thread creation, Birrell proposes a **fork** call with two parameters (different 
from the Unix OS fork call).  
```
fork(proc, args)
```
Where **proc** is the procedure that the created thread will start executing and the
relevant args for the procedure. 

So, if you have a thread `t0`, and you call `fork()`, a new thread, `t1` will be 
created. As a result, a new thread data structure of type **thread type** will be 
created.  
It's **program counter** or **PC** will point to the first instruction of the procedure
specified in the `proc` arg, and the `args` will be available on the stack of the thread.  
At this point, `t0` will execute the next operation after the `fork()` call, and `t1` 
will start the operation specified in the `proc` arg. 

Once the operation completes, the process has two threads, `t0` (parent thread) and `t1`
(the child thread).  

The response to `t1` will typically be stored in some part of the address space that's
accessible to all threads.  
And they have some mechanism to notify either the parent or some other thread that the
result is now available.  

But we also need a way to know that the thread is done so we know when to retrieve the
result (or, at least determine the status of the computation). 

To best terminate a thread, burrell proposes a `join(thread)` mechanism.  

When a parent thread calls **join()** with the thread ID of the child thread, it will be 
blocked until the child completes. The `join()` function will return the result of the 
childs computation to the parent that called it.  

All resources occupied by the child thread will be freed and the child thread will be
terminated. 

## Thread creation example

```
Thread thread1;
Shared_list list;
# safe_insert is a fake way to safely enter elements into a list while threading
thread1 = fork(safe_insert, 4);
safe_insert(6);
join(thread1);
```

Once the new thread is created with the specified operation and arg, the parent thread
will continue to execute and the child thread will also simultaneously execute.  
It is not clear which will execute first.  

If, by the time `join()` is called, `thread1` has already executed, it will join
immediately.  
If `thread1` has not executed, the parent will be blocked until `thread1` executes. 

In this case, because we're inserting into a shared list, we don't actually _need_ to
perform a join. 

## Mutual Exclusion - mutexes

A **mutex** is basically a lock or state that ensures that a data structure is only
accessed by a single thread at a time.  
Locking something is referred to as **acquiring a lock** or **acquiring a mutex**.   

Basics of a **mutex** data structure:
* indicates whether or not the object is in a locked state
* indicates the owner of the object (who currently has the lock)
* has a list of blocked threads

The portion of code potected by a **mutex** is referred to as the **critical section**. 
e.g.:
```
Lock (mutex) {
    Critical section
}
```
Most actual interfaces are more like:
```
Lock(mutex);

Critical section

unlock(mutex);
```

## Producer/Consumer 

Basically, what if you have a bunch of different threads that are all producing some 
output, e.g. adding to a list, and a single consumer thread, maybe it prints out
the contents of the list and clears it. 

In this example they're just adding their ID to the list.

```
// main
for i=0..10
    producers[i] = fork(safe_insert, NULL) // create producers
consumer = fork(print_and_clear, my_list) // create consuemer

// producers: safe_insert
Lock(m) {
    list->insert(my_thread_id)
} // unlock;
 
// consumer: print_and_clear (inefficient)
Lock(m) {
    if my_list.full -> print; clear up to limit of elements of list
    else -> release lock and try again later
} // unlock
```

The above example would be more efficient if we could just tell the consumer when the 
list is actually full so it's not just sitting around all day checking. 

## Condition variable

The idea behind a the construct of a **condition variable** is that there should be an 
easy way, in conjunction with **mutexes**, to control the behavior of concurrent 
threads.  

```
// consumer: print_and_clear
Lock(m) {
    while (my_list.not_full())
        // while the list is not full, the operation suspends itself
        // and waits for the list to become full
        Wait(m, list_full); // `wait` is waiting for `Signal` to indicate `list_full`
            my_list.print_and_remove_all();
} // unlock

// producers: safe_insert
Lock(m) {
    my_list.insert(my_thread_id);
    if my_list.full()
        Signal(list_full);
} // unlock
```

In the above example, the producers will notify the consumer via **Signal** once the list
is full so that it doesn't need to repeatedly check. 

In this example, the mutex must be automatically removed when we go into the **wait** 
statement, and automatically added when we leave the **wait** statement.  
That happens because we alread locked the mutex.  
Basically, we were in a locked scope for the mutex, but the list wasn't ready, so,
within the locked scope, we unlock the mutex so that the producers can execute their
code, and we wait until we get the `list_full` **Signal**.  
Once we get the list full signal, we leave the **wait** statement, the mutex is locked
again, we perform `print_and_remove_all()`, then we leave the locked scope,
which unlocks the mutex.

## Condition variable API

First, we need a data type the corresponds to the condition variable.  

Then these the wait construct, which takes the mutex and condition variable as args (in
which a mutex is automatically released and reacquired if we have to wait for the 
condition to occur).  
When a notification needs to be issued, it would be useful to be able to wake up threads
one at a time (via a **signal** API) or many/all threads (via a **broadcast** API). 

The condition variable data structure:
* reference to the mutex associated with the condition (e.g. so that wait knows what to unlock).
* waiting threads

## Quick quiz

Why use `while (my_list.not_full())` and not `if`?

* If there are multiple consumer threads, a different one could clear it leaving nothing for another consumer to print and clear
* Access cannot be guaranteed to the mutex once the condition is signaled, it may need to try again
* The state can change before the consumer has access again (maybe it's no longer full? some overlap with the first).
* It's "All of the above", btw



## Readers/Writer problem

With readers and writers, 0 or more readers can access at one time while
0 or 1 writers can access at one time.

Mutexes are too restrictive here because they allow only a single thread at a time to
access some space is memory... we want to allow multiple readers.

We can create a helper variable, as resource counter to indicate the availability
of the resource that we're writing to/reading from
* **free** - `resource_counter = 0`
* **reading** - `resource_counter > 0`
* **writing** - `resource_counter = -1`

So, rather than control access to the file with a mutex, we control who has access
to this **proxy variable**.

## Readers/Writer Example

```c
// READERS
Lock(counter_mutex) {
    while (resource_counter == -1)
        Wait(counter_mutex, read_phase);
    resource_counter++;
} // unlock
// ... read data ...
Lock(counter_mutex) {
    resource_counter--;
    if (readers == 0)
        Signal(write_phase);
} // unlock


// WRITER
Lock(counter_mutex) {
    while (resource_counter != 0)
        Wait (counter_mutex, writer_phase);
    resource_counter = -1;
} // unlock
// ... write data ...
Lock(counter_mutex) {
    resource_counter = 0;
    Broadcast(read_phase);
    Signal(write_phase);
} // unlock
```

Note that the reading and writing operations take place outside of the lock construct.
Access to the file is not actually controlled _directly_.  

With both the reader and the writer, we first perform a controlled operation in which the 
resource counter is updated. 

It's the updating of the resource counter that is the controlled operation.  

Once the thread finishes it's operation, it changes the counter accordingly.
If a reader was previously accessing the resource, it will decrement the 
`resource_counter` and if the `resource_count == 0`, then it will Signal to writers that 
it can write.  
If a writer was previously access the resource, it will set the `resource_counter = 0`,
and will **Broadcast** that all readers can access, then **Signal** that a writer can 
access (if no readers got to it first).


### Why do we need a `while` loop to check out resource counter

When the writer thread receives the signal for the `write_phase` variable, it will be
woken up.  
Internally, the writer will be removed from the wait queue that's associated with the
`write_phase` condition variable.  
The counter mutex will be reaquired before leaving the wait operation.  
Before actually changing anything, we need to check the `resource_counter` one more time
to ensure that no other reader/writer has gotten there.
This is because removing the thread from that queue that's associated with the `write_phase`
condition variable, and acquiring this `counter_mutex`, are two different operations, 
and it's possible that another reader/writer got there first.

## Critical Section Structure

In the above example, the locked sections are considered the **enter critical section**
and **exit critical section**.  
The read/write data sections are considered the "real" critical section if though that's
the only place where there isn't actually a lock.

Abstractly, what we're doing is:
```c
Lock(mutex) {
    while (!predicate_indicating_access_ok)
        Wait (mutex, conditional_var)
    update shared state => update predicate (maybe something that another thread is waiting on)
    signal and/or broadcast
        (cond_var_with_correct_waiting_threads)
} // unlock
```

Note that all of the gymnastics is required because mutexes don't inherently support
the readers/writer problem.

## Common Pitfalls

Make sure you document which mutex is for which file or whatever!

One mutex per variable.

Note that it's actually worse to use signal instead of broadcast by accident than the 
other way around.  
If you use signal when you mean to use broadcast, then you'll only wake up one thread
and all of the others will be left waiting (possibly indefinitely).  
If you use broadcast when you mean to use signal, you'll make up everything, which is
less efficient from a performance standpoint, but will ultimately give the desired
behavior assuming there are no other bugs. 

## Spurious (unnecessary) Wake Ups

Basically when you wake something up at a time that it would never actually be able to
execute, e.g.:

```c
// Bad writer
Lock(counter_mutex) {
    resource_counter = 0;
    Broadcast(read_phase);
    Signal(write_phase);
} // unlock

// Good writer
Lock(counter_mutex) {
    resource_counter = 0;
} // unlock
Broadcast(read_phase);
Signal(write_phase);
```

Restructuring this way is not always possible as with readers.  
Because readers need to check the value of `resource_counter` after they update it
(to see whether `resource_counter == 0` so it can `Signal(write_phase)`).  
If they unlock the counter it's possible for the counter to be modified before the signal
is made.  
Thus, it will have to stay locked until that check has also completed. 
```c
// for readers
Lock(counter_mutex) {
    resource_counter--;
    if (counter_resource == 0)
        Signal(write_phase);
} // unlock
```

## Deadlocks

**Deadlocks** happen when two or more competing threads are waiting on each other to 
complete, but none of them ever do/can.

Let's say you have two threads that need access to shared variables `a` and `b`.  
Before accessing these variables, they must lock the mutexes associated with each of 
those variables.  
But what if one locks the mutex for `a` first and the other locks the mutex for `b` first.  
This type of issue is referred to as a **cylce in the wait graph**.

Neither of the threads in this case will ever give up control of their mutex so the 
other can never get it.  

If access is not needed to both variables simultaneously, one solution is to always 
unlock the mutex for the current variable before locking the mutex for the next
variable. This is called **fine-grained locking**.  

If you only ever have one variable locked at a time, you want have a deadlock.  

If you need both/multiple locked simultaneously, you can have an order in which mutexes 
must be locked, so that two threads are never competing for one lock when they already
have a different lock. This is called maintaining a **lock order**.

It is also possible to have deadlock detection and recovery. To detect there's simply
an algorithm to see if any cycles have occurred.  
This requires tracking of state so that we actually have somewhere to **rollback** to.  
Rollback are expensive and something simply impossible. 

And there's literally something called the **ostrich algorithm** where you just kinda
wait and hope things get better...

## Kernel vs. User-level Threads

When kernel level threads exist, it means that the OS itself is multi-threaded.  

Kernel-level threads exist to not only support user-level threads, like an application
with multi-threading, but also OS level services like daemons.

For a user-level thread to execute, it must be associated with a kernel-level thread.
Then, the OS-level scheduled must schedule that kernel-level thread on a CPU. 

### Multi-threading Models

* **one-to-one** is where each user-level thread is associated with its own kernel-level
thread. This is when there is a kernel-level thread or a kernel-level thread is 
created for each user-level thread. 
    * pros:
        * OS sees/understands threads, synchronization, blocking, etc.
    * cons:
        * must go to OS for all operation
            * can be expensive
            * Every operation requires the crossing of the user-kernel boundary.
        * OS may have limits on plicies, e.g. number of threads
            * These are the policies that are supported on the kernel level
            * You can only do on the application level what is supported on the kernel-level
                * this has direct impacts on portability
* **many-to-one** is where all user threads are supported by a kernel-level thread 
    * pros
        * totally portable - doesn't depend on OS limits and policies
        * don't need to make system calls/rely on user-kernel transitions to make decisions regarding:
            * scheduling
            * synchronization
            * blocking
            * etc.
    * cons:
        * OS has no insights into application needs
        * OS may block entire process if one user-level thread blocks on I/O even if there are other threads that could execute
* **many-to-many** allows some user-level threads to be associated with one kernel-level process, others might have a
    **one-to-one** mapping (e.g. if they're some blocking I/O thing). It's called a **bound mapping** when one
    user-level thread is permamently associated with a single kernel-level thread.
    * pros
        * mostly the **bound threads/mappings** and **unbound threads/mappings**
    * cons
        * requires coordination between user-level and kernel-level thread managers
            * this is mostly to take advantage of performance opportunities.


## Scope of multi-threading

There are different level on which multi-threading is supported, at a system level or
within a single process.  
Each level affects the scope of the **thread management system**.  

At the kernel-level, there is **system scope** or system-wide thread management that's 
supposed by the OS-level thread managers (e.g. CPU scheduler). This means that the OS
thread managers look at the entire platform for making decisions as to how to allocate
resources to threads. 

One the user-level, a thread library that's linked to the process manages all of the 
threads that are within that process and only those threads. Different processes are
managed by different instances of the same library. 


If there are two processes, and those processes have threads with user-level scope,
the OS doesn't have visibility to them.  
So, at the OS-level, the resources/threads will probably be split 50/50 between the 
two different processes... Even if one of the processes have 8 threads and the 
other has 4.  
This means that that each of the 8 threads will get half of the CPU cycles of the 4 
threads. 

If you were to take 2 processes, one with 8 and the other with 4 threads, and give
them **system scope**, the OS would be able to allocate resources so that each
user-level thread gets an equal share of compute power (or whatever other policy the
kernel implements). 

## Multi-threading Patterns

* **boss-workers**
    * **boss** assigns work
    * **worker** performs entire task
    * Throughput is limited by the boss's ability to delegate
        * throughput = (1 / boss_time_per_order)
        * If this boss takes a while to delegate each task and workers are sitting around waiting for tasks, benefits are not being realized
    * Boss can decide who gets work by
        * tracking who's free, giving work to free workers
            * this creates more work for the boss because it has to know who's free
            * It also has to wait on workers to accept new work (like a handshake)
            * pros
                * workers don't need to synchronize amongst each other
            * cons
                * boss must track what each worker is doing
                * throughput will go down.. :(
    * Can establish a queue between boss and workers
        * similar to a **producer-consumer** queue where the boss is the only producer that produces work requests. Workers
            then pickup work from this queue.
        * Pros:
            * boss doesn't need to know details about who/what is free
            * no handshake necessary when handing off work
        * cons:
            * access to shared queue has to be synchronized between boss and workers
            * throughput can decrease if the queue is full and the boss has to wait before entering elements into the queue
        * Despite the syncronization difficulties, this has better throughput than boss-assignment
        * **worker/thread-pool**
            * on demand - basically make new workers when you need to. This can be very inefficient if new-worker-creation is slow
            * pool of workers - a pool of workers/threads is created upfront. 
                * The main drawback here is that you don't necessarily know how many threads/workers you need when you start. 
            * Dynamic pool of workers - make a new batch of workers if the current batch runs out
    * Overall pros and cons
        * pros
            * simplicity
        * cons
            * worker/thread-pool management
            * the boss ignores **locality**, it doesn't keep track of what each worker was doing last which fails to realize benefits that can be gained from performing similar tasks.
    * **boss-worker varians**
        * The above covers all workers created equal
        * We can also look at workers secialized for certain tasks
            * pros
                * this exploits **locality**. 
                * Each process is only accessing a subset of the state and that state is more likely to be present in the cache
            * cons
                * load balancing gets more complicated
* **pipeline**
    * threads assigned one subtask in the system
    * all tasks together == pipeline of threads
    * Like a Ford assembly line
    * multiple tasks concurrently in the system, in different pipeline stages 
    * Throughput dependent on weakest link
        * if there's a particularly slow step in the process, more resources/threads can be allocated to that specific thread
        * One way to go about this is to have a worker/thread-pool per stage
    * The **shared-buffer** or **queue** based approach is generall seen as the best way to manage work.
    * pros
        * specialization and locality 
    * cons
        * balancing and synchronization can be fairly complex to manage
            * note that there's more synchronization required to coordinate between workers in the same pool and between stages
* **layered**
    * each layer is a group of related sub-tasks
    * pros
        * specialization
        * less-fine grained than the pipeline resulting in a slightly lower syncrhonization requirements
    * Not suitable for all applications
        * not all processes have clean/logical groups

## Quick quiz - multi-threading patterns

For a 6-step process, there are two ways to approach it:
* **boss-workers** solution, where a worker processes a job in 120ms
* **pipeline** solution where each step takes 20ms

How long will it take these solutions to complete 10 jobs?  
How long to complete 11 jobs?

* **boss-workers**
    * 10 - 240ms
    * 11 - 360ms (120ms per batch, 5 in each batch because boss has to manage, 3 batches)
* **pipeline** 
    * 10 - 300ms
    * 11 - 320ms
        * 120ms to finish all 6 steps for the first job, 20ms more per job 
        * `(n_steps/n_workers * avg_step_duration) + ((total_jobs - 1) * avg_step_duration)`


# Summary

Work can be broken into different pieces and handled by threads.  
Threads can be on both the user-level and the kernel-level.  
Applications can be created to take advantage of multiple kernel-level threads or 
employ multiple user-level threads on a single kernel-level thread.  
There are also Combinations off these two approaches where there can be both multiple
user-level threads pointing to the same kernel-level thread while another user-level
thread is "bound" to a single kernel-level thread.

Threads can be executed in a variety of ways, these fall into 3 primary categories:
boss-worker, pipeline, and layered.  
Each has its own pros and cons. Boss-worker can be easier to setup but doesn't take
advantage of locality.  
Pipeline takes advantage of locality but requires greater synchronization.  
Layered combines some of the benefits of both but is not suitable for all 
circumstances. 

All of these approaches typically use a dynamic worker-pool that creates additional 
threads as they become necessary during program execution.

When performing work across multiple threads we use something called a mutex, which
locks access to certain shared variables to prevent things like accidentally 
overwriting data when modifying shared variables.  
The readers/writer problem is a specific scenario in which you want multiple non-modifying
threads to access a single variable (readers) OR a single modifying thread (writer) to
access that variable and update its value(s).  
The readers/writer problem uses condition variables, rather than a mutex, to determine
access.

Mechanisms called broadcast and signal are used to indicate to waiting threads that they
can now attempt to run.  
Broadcast notifies all threads while signal will notify only a single thread. 

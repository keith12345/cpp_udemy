# PThreads

What are they? **Posix Threads**

## PThread creation

PThreads:
```c
pthread_t aThread; // pthread_t is a type of thread
```

The object will have an ID, execution state, other relevant info.  
This is abstracted away by the library so that the dev doesn't have to worry about it.

PThread versions of Birrell's Fork:
```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, foo, NULL);
```

PThread versions of Birrell's join:
```c
int pthread_join(pthread_t thread, void **status);
```

Both `pthead_create` and `pthread_join` return a status indicating whether the operation
was successful.

### PThread attributes

There's a pthread_attr arg in the pthread_create func. 
This arg gives us flexibility to specify certain features of the newly created thread, e.g.:
* stack size
* scheduling policy
* priority
* inheritance (whether it inherits from the calling thread)
* joinable
* scope
    * system
    * process

Can pass a `NULL` if you just want default behaviors. 

#### Calls on PThread attributes

```c
int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_destroy(pthread_attr_t *attr);
pthread_attr_get_{attribute}(pthread_attr_t *attr, foo);
pthread_attr_set_{attribute}(pthread_attr_t *attr, foo);
// e.g.
pthread_attr_get_scope(pthread_attr_t *attr, int *scope);
```

#### Detachable threads

(Not considered by Birrell)

With joinable threads, the parent thread creates children threads and can join them at a later time.  
The parent thread should not terminate until the children threads have completed their execution and have been joined 
via the explicit join operation. 
If the parent thread exists early, the children threads can turn into zombies where the may have **completed** or
**died** but not **exited** or been **reaped** properly. 

With PThreads, it's possible for children threads to be detached from the parent.  
Once detached, these threads cannot be joined.  
If a parent exits, these threads are free to continue their execution normally.  
In this case, the parent and children thread are almost equivalents except that parents have some additional information
on the children threads.  

```c
int pthread_detach(pthread_t thread_to_detach);
```

Can also create a detached thread:
```c
pthread_attr_setdetachstate(attr, PTHREAD_CREATED_DETACHED);
// ...
pthread_created(..., attr, ...);
// and then the parent can just exit
void pthread_exit();
```

Example using pthread attributes:
```c
#include <stdio.h>
#include <pthread.h>

void *foo (void *arg) { /*thread main */
    printf("Foobar!\n")
    pthread_exit(NULL);
}

int main (void) {
    
    int i;
    pthread_t tid;

    pthread_attr_t attr; // attribute data structure is created
    pthread_attr_init(&attr); // and initialized
    // this modifies the attribute object so that when the pthread is created, 
    // it is created as a detached thread
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);  
    // Here we're modifying the scope just for kicks
    // This thread will have system scope
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    // The resulting attribute data structure is then passed to pthread_create
    // (not sure where the actual "thread" is... if that's a thing...
    pthread_create(NULL, &attr, foo, NULL);

    return 0;
}
```

## Compiling PThreads

Don't forget to include pthreads in your `main` file!
```c
#include <pthread.h>
```

When compiling, you'll need to pass one of `lpthread` of `pthread` as a flag:
```
gcc -o main main.c -pthread
gcc -o main main.c -lpthread
```

Tells it to link the pthread library _as well as_ configure the compilation for threads.

Note that it's particularly advisable to check returns or many functions when writing applications with multi-threading
(e.g. did this thing actually succeed at the thing it was trying to do).

## Thread creation examples

### Example 1

```c
#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 4

void *hello (void *arg) { /*thread main */
    printf("Hello Thread\n");
    return 0;
}

int main (void) {
    int i;
    pthread_t tid[NUM_THREADS];
    for (i = 0; i < NUM_THREADS; i++) {
        // each thread is just executing the function `hello`
        // The second arg is passed as a null (in place of an pthread_attr_t object)
        // as we're fine with just using default behavior.
        // It is because `hello` does not take any arguments that we 
        // pass NULL as the 4th argument in the pthread creation.
        pthread_create(&tid[i], NULL, hello, NULL);
    }
    // because the above threads are not detached, we must join them
    for (i = 0; i < NUM_THREADS; i++) { // wait/join threads
        pthread_join(tid[i], NULL);
    }
    return 0;
}
```

### Example 2

```c
#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 4

void *threadFunc(void *pArg) { /*thread main */
    // all threads will have their own copies of these two vars
    int *p = (int*)pArg;
    int myNum = *p;
    printf("Thread number %d\n", myNum);
    return 0;
}

int main (void) {
    int i;
    pthread_t tid[NUM_THREADS];
    for (i = 0; i < NUM_THREADS; i++) {
        // each thread is just executing the function `hello`
        // The second arg is passed as a null (in place of an pthread_attr_t object)
        // as we're fine with just using default behavior.
        pthread_create(&tid[i], NULL, hello, &i);
    }
    // because the above threads are not detached, we must join them
    for (i = 0; i < NUM_THREADS; i++) { // wait/join threads
        pthread_join(tid[i], NULL);
    }
    return 0;
}
```

Note that possible output for the above is:
```
Thread number 0
Thread number 2
Thread number 2
Thread number 3
```

This is because we're dealing with pointers and it's possible that the pointer is incremented twice because it's
assigned in the threadFunc function. 

It could also be the below if it's assigned in order but executed out of order
```
Thread number 0
Thread number 2
Thread number 1
Thread number 3
```

This can be referred to as a **data race** or a **race condition**. It occurs when one thread tries to read a variable
that another thread is modifying. 

## Mutexes

```c
pthread_mutex_t aMtutex;
```

### Lock a mutex

```c
// explicit lock
int pthread_mutex_lock(pthread_mutex_t *mutex);
// explicit unlock
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

Basic safe insert:
```c
list<int> my_list;
pthread_mutex_t m;
void safe_insert(int i) {
    pthread_mutex_lock(m);
    my_list.insert(i);
    pthread_mutex_unlock(m);
}
```

#### try_lock

```c
int pthread_mutex_trylock(pthread_mutex_t *mutex);
```

Attempts to perform a lock and will notify the calling thread if the mutex is not available.
Normally, if the mutex is already locked, the calling thread will wait, but this gives the calling thread the option to
do something else if and maybe come back later when the mutex might be free.

### init mutex

```c
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
// mutex attributes == specifies mutex behavior when
// a mutex is shared among processes
int pthread_mutex_init(pthread_mutex_t *mutex, NULL);
// Can also just pass NULL for default behavior
```

### Cleaning

You should always clean up any mutex related data structures. For mutexes, there is:
```c
int pthread_mutex_destroy(pthread_mutex_t *mutex):
```

#### Mutex safety tips

* shared data should always be accessed through a single mutex
* mutex scope must be visible to all threads (cannot be a private variable to a single thread, even main!)
* globally order locks
    * for all threads, lock mutexes in order to avoid deadlocks
* always unlock the (correct) mutex
    * not always caught by a compiler


## Pthread condition variables 

**Condition variables** are synchronication constructs which allow block threads to be notified once a specific
condition occurs. 

There are 3 associated operations:
* **condition**
* **wait**
* **signal**

```c
pthread_cond_t aCond;
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
```

A thread that's entering the wait operation (a thread that _must_ wait) will automatically release the mutex and place 
itself on the wait queue that's associated with the condition variable.  
When the thread is woken up, it will automatically re-aquire the mutex before actually exiting the wait operation.
Saying the above again in other words:  
The reason why the `pthread_cond_wait` function takes not only a **condition variable** as an argument, but also a
mutex, is because it releases the mutex while waiting on that condition variable.
```c
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
```

There's also:
```c
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);
```
Signal and broadcast _do not_ need to be passed the mutex because they assume that the mutex is unlocked and, if the
signaled/broadcasted thread is still locked (perhaps by a third thread), the signaled/broadcasted thread will wait until
the mutex is free.

### Other common methods used with condition variables

```c
// Gottta use this to allocate the data structure for the condition
// and initialize its attributes
// attributes might specify if the condition variables will be used only withs
// threads that belong to a single process or across shared processes.
// passing NULL for the attr just results in the default behavior
int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
int pthread_cond_destroy(pthread_cond_t *cond);
```

### Reminders for condition variables

* don't forget to notify waiting threads
    * predicate change -> signal/broadcast _correct_ condition variable
* when in doubt, use broadcast (some performance loss if done unnecessarily)
* you do not need to have a mutex to perform signal and broadcast operations.
    * As a result, might make sense to wait until after you've released a mutex to perform signal and broadcast ops


## Examples

### Producer-consumer problem

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUF_SIZE 3       // size of shared buffer

int buffer[BUF_SIZE];    // shared buffer
int add = 0;             // place to add next element
int rem = 0;             // place to remove next element
int num = 0;             // number of elements in buffer

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;        // mutex lock for buffer
pthread_cond_t c_cons = PTHREAD_COND_INITIALIZER;     // consumer waits on cv
pthread_cond_t c_prod = PTHREAD_COND_INITIALIZER;     // producer waits on cv


void *producer (void *param);
void *consumer (void *param);


int main(int argc, char *argv[]) {

    pthread_t tid1, tid2;  // thread identifiers

    if (pthread_create(&tid1, NULL, producer, NULL) != 0) {
        fprintf(stderr, "Unable to create producer thread\n");
        exit(1);
    }

    if (pthread_create(&tid2, NULL, consumer, NULL) != 0) {
        fprintf(stderr, "Unable to create consumer thread\n");
        exit(1);
    }

    // we're not creating detached threads so we gotta join later
    pthread_join(tid1, NULL);  // wait for producer to exit
    pthread_join(tid2, NULL);  // wait for consumer to exit
    printf("Parent quitting\n");
    return EXIT_SUCCESS;
}


void *producer(void *params) {
    int i;
    for (i = 0; i <= 20; i++) {
        pthread_mutex_lock(&m);
        // braces aren't necesssary but helps illustrate
        {
            if (num > BUF_SIZE) {  // overflow
                exit(1);
            }
            while (num == BUF_SIZE) {
                pthread_cond_wait(&c_prod, &m);
            }
            buffer[add] = i;
            add = (add+1) % BUF_SIZE;
            num++;
        }
        pthread_mutex_unlock(&m);

        // note that we wait until releasing the mutex to signal
        pthread_cond_signal(&c_cons);
        printf("producer: inserted %d\n", i); fflush(stdout);
    }

    return EXIT_SUCCESS;
}

void *consumer(void *param) {
    int i;

    while (1) {

        pthread_mutex_lock(&m);
        {
            if (num < 0) {  // underflow
                exit(1);
            }
            while (num == 0) {
                pthread_cond_wait(&c_cons, &m);
            }
            i = buffer[rem];
            rem = (rem+1) % BUF_SIZE;
            num--;
        }
        pthread_mutex_unlock(&m);

        // notify producer thread that there's now room in the buffer
        // consumer only consumed one element so it doesn't make sense to
        // broadcast
        pthread_cond_signal(&c_prod);
        printf("consumer value: %d\n", i); fflush(stdout);
    }
}
```


# Summary

pthreads, which stands for posix threads, are the standard threading library used in `c`.
Their functionality is similar to that described by Birrell.

This section covered the bases of creating pthreads, their relevant data types, compiling applications that use the pthread library.
Important concepts to note are the idea of detachable threads, which were not described by Birrell.
There are also many functions/objects that one should be familiar if they are to work with threads:
* attribute object (and relevant data types)
* set/get methods for attributes
* setting scope
* initializing attributes/threads/etc.
It also covered mutexes, conditional variables, and other associated methods.
importantly knowing the difference between signal and broadcast (when in doubt, use broadcast, but will slow down your program a bit).
Just like threads and attributes, mutexes also need to be initialized.
The pthread_cond_wait. It allows a thread to release control of a mutex while waiting on a conditional variable.

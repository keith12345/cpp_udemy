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

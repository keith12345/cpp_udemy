#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define READ_X_TIMES 15
#define WRITE_X_TIMES 20
#define NUM_WRITERS 5
#define NUM_READERS 5


pthread_mutex_t counterMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_read = PTHREAD_COND_INITIALIZER;
pthread_cond_t c_writ = PTHREAD_COND_INITIALIZER;

void* reader(void *param);
void* writer(void *param);

int resourceCounter = 0;
int add = 0;
char dbContents[WRITE_X_TIMES];

int
main(int argc, char *argv[])
{
    srand((unsigned int)time(NULL));

    pthread_t writers[NUM_WRITERS];
    for (int i = 0; i < NUM_WRITERS; i++) {
        if (pthread_create(&writers[i], NULL, writer, NULL) != 0) {
            fprintf(stderr, "Unable to create producer thread\n");
            exit(1);
        }
    }
    pthread_t readers[NUM_READERS];
    for (int i = 0; i < NUM_READERS; i++) {
        if (pthread_create(&readers[i], NULL, reader, NULL) != 0) {
            fprintf(stderr, "Unable to create producer thread\n");
            exit(1);
        }
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    return EXIT_SUCCESS;
}


void*
reader(void* param)
{
    while (add < WRITE_X_TIMES) {
        int randomTime = rand() % 5 + 1;
        sleep(randomTime);
        pthread_mutex_lock(&counterMutex);
        {
            while (resourceCounter == -1) {
                pthread_cond_wait(&c_read, &counterMutex);
            }
            resourceCounter++;
        }
        pthread_mutex_unlock(&counterMutex);

        printf("Reader:\n\tThe resource counter is currently %d\n", resourceCounter);
        printf("\033[1m%s\n\033[0m", dbContents); fflush(stdout);

        pthread_mutex_unlock(&counterMutex);
        {
            resourceCounter--;
            if (resourceCounter == 0) {
                pthread_cond_signal(&c_writ);
            }
        }
    }
    return EXIT_SUCCESS;
}


void*
writer(void* param)
{
    while (add < WRITE_X_TIMES) {
        int randomTime = rand() % 5 + 1;
        sleep(randomTime);
        pthread_mutex_lock(&counterMutex);
        {
            while (resourceCounter != 0) {
                pthread_cond_wait(&c_writ, &counterMutex);
            }
            printf("Writer:\n\tThe resource counter is currently %d\n", resourceCounter);
            fflush(stdout);
            resourceCounter = -1;
        }
        pthread_mutex_unlock(&counterMutex);
        char c;
        switch(add) {
            case 0: c = 'H'; break;
            case 1: c = 'e'; break;
            case 2: c = 'y'; break;
            default: c = 'o';
        }
        printf("The entered value is %c\n", c); fflush(stdout);
        dbContents[add] = c;
        add++;
        pthread_mutex_lock(&counterMutex);
        {
            resourceCounter = 0;
            pthread_cond_broadcast(&c_read);
            pthread_cond_signal(&c_writ);
        }
        pthread_mutex_unlock(&counterMutex);
    }
    return EXIT_SUCCESS;
}

#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "blockchain.h"

#include <string.h>
#include "hash_function.h"

#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_wait = PTHREAD_MUTEX_INITIALIZER;

pthread_t thr_list[10];

static void *
thread_func()
{
//    int s;

    /* Disable cancellation for a while, so that we don't
       immediately react to a cancellation request. */

    printf("I'm before the lock in func!\n");

    pthread_mutex_lock(&mutex);

    printf("I'm in the lock in func!\n");

    pthread_mutex_unlock(&mutex);

    printf("I'm after the lock in func!\n");


    /* sleep() is a cancellation point. */

    /* Should never get here. */
    return NULL;
}

int
main(void)
{

    int s;
    /* Start a thread and then send it a cancellation request. */
    for (int i = 0; i < 10; ++i)
    {
        s = pthread_create(&thr_list[i], NULL, &thread_func, NULL);
        if (s != 0)
            handle_error_en(s, "pthread_create");
    }
//    printf("core: %llu\n", UINT64_MAX);

    printf("I'm before the lock in main!\n");

    pthread_mutex_lock(&mutex);

    printf("I'm in the lock in main!\n");
    sleep(10);

    pthread_mutex_unlock(&mutex);

    printf("I'm after the lock in main!\n");



    /* Join with thread to see what its exit status was. */
    for (int i = 0; i < 10; ++i)
    {
        s = pthread_join(thr_list[i], NULL);
        if (s != 0)
            handle_error_en(s, "pthread_join");
    }

    printf("%d", UINT64_MAX==0xFFFFFFFFFFFFFFFF);

    exit(EXIT_SUCCESS);
}


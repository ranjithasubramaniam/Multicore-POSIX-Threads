/*
 * Sync_Basics_Mutex.c
 *
 *--------------------------------------------------------------------------------------------
 *  Objectives:
 *  + + Learn how to create Mutex Lock mechanism
 *  + Refer to this website for more info:
 *  	https://www.bogotobogo.com/cplusplus/multithreading_pthread.php
 *  --------------------------------------------------------------------------------------------
 *  Created on: Dec 10, 2018
 *      Author: suresh
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


//#define ENABLE_THREADS_MUTEX


#define N 5



/* ----------------------------------------------------------------------
 *  Notes:
 *  --------------------------
 * 1. A mutex lock is a mechanism that can be acquired by only one thread at a time.
 *   - For other threads to get the same mutex, they must wait until it is released by the current owner of the mutex.
 * 2. With the macro ENABLE_THREADS_MUTEX not defined, a race condition is caused.
 *   - i.e. before a thread prints out the counter variable, other thread increments it.
 * 3. With the macro ENABLE_THREADS_MUTEX defined, there is a proper access to the counter variable and the each thread
 *   - increments the counter variable five times.
 * 4. The variable count is declared as volatile to ensure that it is read from memory at each access
 *  - and written back to memory after each access
---------------------------------------------------------------------- */

/* Declare global variables */
pthread_mutex_t myMutex;

volatile int counter = 0;

void *child_thread(void *child_id) {

    for(int i = 0; i < 5; i++) {

    #ifdef ENABLE_THREADS_MUTEX
    pthread_mutex_lock(&myMutex);
    #endif

    /* Critical Section */
    counter++;

    /* Thread sleeps for 1s during which other threads change the counter value */
    #ifndef ENABLE_THREADS_MUTEX
    usleep(1);
    #endif

	printf("Worker_Thread: %ld Counter:%d\n", (long) child_id, counter);
    /* Critical Section */

    #ifdef ENABLE_THREADS_MUTEX
    pthread_mutex_unlock(&myMutex);
    #endif
    }

	return NULL;

}


int sync_basics_mutexes(void) {

	/* This variable is our reference our worker threads */

	pthread_t multiple_thread[N];

	/* Initialise the Mutex Variable */

	pthread_mutex_init(&myMutex,0);

	long id;

	for (id = 1; id <= N; id++) {

		/* Create worker threads which executes the start function Worker_Thread */

		if (pthread_create(&multiple_thread[id], NULL, &child_thread, (void*) id)) {

			fprintf(stderr, "Error creating thread\n");

			return 1;

		}

	}

	/* Destroy the Mutex Variable */
	 pthread_mutex_destroy(&myMutex);

	/* Exit the main thread but does not terminate the child threads*/
	pthread_exit(NULL);

	return 0;

}

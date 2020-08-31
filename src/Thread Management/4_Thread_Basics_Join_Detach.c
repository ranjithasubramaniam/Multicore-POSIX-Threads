/*
 * 4_Thread_Basics_Join_Detach.c
 *
 * *  --------------------------------------------------------------------
 *  Objectives:
 *  + Learn how to create thread attributes
 *  + Also to learn how to detach threads for independent thread execution
 *  + Refer to this website for more info:
 *  	https://www.bogotobogo.com/cplusplus/multithreading_pthread.php
 *  --------------------------------------------------------------------
 *
 *  Created on: Dec 10, 2018
 *      Author: suresh
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//#define STATE_THREADS_DETACHABLE PTHREAD_CREATE_DETACHED
#define STATE_THREADS_DETACHABLE PTHREAD_CREATE_JOINABLE

/* --------------------------------------------------------------------------------------------------------------------------------------------
 *  Notes:
 *  1. There are cases we have to re-synchronize our threads using pthread_join() before allowing the program to exit.
 *     - We need to do this if we want to allow one thread to return data to the thread that created it.
 *     - However, sometimes we neither need the second thread to return information to the main thread nor want the main thread to wait for it.
 *  2. We can create threads that have this behavior.
 *     - They are called detached threads, and we can create them by modifying the thread attributes or by calling pthread_detach().
 *     - The pthread_detach() routine can be used to explicitly detach a thread even though it was created as joinable.
 * ---------------------------------------------------------------------------------------------------------------------------------------------- */

void *workerThread(void *arg) {
	int i;
	for (i = 0; i <= *(int *) arg; i++) {
		printf("Worker Thread Counter Value: %d\n", i);
	}
	/*The counter value is returned as status*/
	pthread_exit((void*)i);
}

int thread_basics_join_detach(void) {
	int retStatus = 112;
	int arg = 911;
	pthread_t thread;

	/* Create a thread attribute*/
	pthread_attr_t attr;

	/* Initialize a thread attribute*/
	if (pthread_attr_init(&attr)) {
		fprintf(stderr, "Error creating thread attribute\n");
		return 1;
	}

	/* Set the detachable state of the thread*/
	/* Two states PTHREAD_CREATE_DETACHED, PTHREAD_CREATE_JOINABLE */
	if (pthread_attr_setdetachstate(&attr, STATE_THREADS_DETACHABLE)) {
		fprintf(stderr, "Error setting detachable state to thread attribute\n");
		return 2;
	}

	/* Create the thread along with its argument*/
	pthread_create(&thread, &attr, workerThread, &arg);

	/* Delete the thread attribute to free library resources*/
	if (pthread_attr_destroy(&attr)) {
		fprintf(stderr, "Error deleting the thread attribute\n");
		return 3;
	}

	/*This is used to check how the behavior changes when using join method*/
#if STATE_THREADS_DETACHABLE == PTHREAD_CREATE_JOINABLE
	pthread_join(thread, (void **) &retStatus);
#endif

	/* The return status is 112 if child thread is detached
	 * because the main thread does not get the incremented return status from worker Thread
	 * and 912 if joined */
	printf("\nReturn Status from Worker Thread: %d\n", retStatus);

	//This function allows to the child thread to exist independently
	pthread_exit(NULL);

}


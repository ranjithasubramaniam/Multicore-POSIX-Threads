/*
 * Thread_Basics_Termination.c
 *
 *  --------------------------------------------------------------------------------------------
 *  Objectives:
 *  + Learn how to terminate threads
 *  + Refer to this website for more info:
 *  	https://www.bogotobogo.com/cplusplus/multithreading_pthread.php
 *  --------------------------------------------------------------------------------------------
 *
 *  Created on: 07.12.2018
 *  Author: smuthuveerappan
 */

#include <pthread.h>
#include <stdio.h>
#include <thread_basics_termination.h>

// #define ENABLE_MAIN_THREAD_EXIT
// #define ENABLE_MAIN_THREAD_JOIN

/* ----------------------------------------------------------------------
 *  Notes:
 *  --------------------------
 * 1. Enable or disable the macro ENABLE_MAIN_THREAD_EXIT to check the below functionality.
 *
 *   -pthread_exit is used to explicitly exit a thread.
 *   -Typically, the pthread_exit() routine is called after a thread has completed its work and is no longer required to exist.
 *   -If main() finishes before the threads it has created, and exits with pthread_exit(),
 *   	the other threads will continue to execute.
 *   -Otherwise, they will be automatically terminated when main() finishes.
 *
 * 2. Enable or disable the macro ENABLE_MAIN_THREAD_JOIN to check the below functionality.
 *
 *   -The programmer is able to obtain the target thread's termination return status
 *   	if it was specified in the target thread's call to pthread_exit()
 *
 ---------------------------------------------------------------------- */

/* this function is run by the second thread */
void *increment_x(void *x_void_ptr) {

	int *x_ptr = (int *) x_void_ptr;
	/* increment x to 10000 */
	while (++(*x_ptr) < 10000) {
		printf(" x = %d from child\n", *x_ptr);
	}

	printf("x increment finished\n");

	/* The function returns the integer 911 as return_status */
	pthread_exit((void *) 911);
}

int thread_basics_termination(void) {

	int x = 0, y = 0;

	int return_status = 108;

	/* show the initial values of x and y */
	printf("x: %d, y: %d\n", x, y);

	/* this variable is our reference to the second thread */
	pthread_t inc_x_thread;

	/* create a second thread which executes increment_x(&x) */
	if (pthread_create(&inc_x_thread, NULL, increment_x, &x)) {
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	/* increment y to 100 in the first thread */
	while (++y < 100) {
		printf(" y = %d from parent\n", y);
	}

	printf("y increment finished\n");

#ifdef ENABLE_MAIN_THREAD_JOIN
	/* wait for the second thread to finish and then join*/
	if (pthread_join(inc_x_thread, (void **) &return_status)) {
		fprintf(stderr, "Error joining thread\n");
		return 2;
	}
#endif

	// show the results - x depends on the macro enable or disable states.
	printf("x: %d, y: %d\n", x, y);
	printf("Return Status: %d\n", return_status);

#ifdef ENABLE_MAIN_THREAD_EXIT
	/* This function makes the child thread to continue,
	 * even though the main thread exits*/
	pthread_exit(NULL);
#endif

	return 0;

}
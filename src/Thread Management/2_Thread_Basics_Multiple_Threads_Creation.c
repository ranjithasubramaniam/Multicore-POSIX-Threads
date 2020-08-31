/*
 *  Thread_Basics_Creation_Multiple_Threads.c *
 *  --------------------------------------------------------------------
 *  Objectives:
 *  + Learn how to create multiple threads
 *  + Refer to this website for more info:
 *  	https://www.bogotobogo.com/cplusplus/multithreading_pthread.php
 *  --------------------------------------------------------------------
 *  Created on: 07.12.2018
 *  Author: smuthuveerappan
 */

#include <pthread.h>
#include <stdio.h>
#include "thread_basics_creation_multiple_threads.h"

#define N 5

/* ----------------------------------------------------------------------
 *  Notes:
 *  --------------------------
 * + In the output, you may notice that the worker thread id is repeated.
 * + This is due to the fact, we pass the address of the id variable,
 * 	 as argument to the start function worker_thread(void *)
 * + As the loop iterates, the value of this memory location changes,
 *   possibly before the created threads can access it.
 * + This behavior can be corrected by passing the value as an argument.
 *   i.e. pthread_create(&multiple_thread[id], NULL, &worker_thread, id)
---------------------------------------------------------------------- */

/*This function is run by the worker thread */
void *worker_thread(void *child_id) {
	printf("This is worker_thread #%ld\n", *(long *) child_id);
	/* the function must return something - NULL will do */
	return NULL;
}

int thread_creation_multiple(void) {
	/* this variable is our reference our worker threads */
	pthread_t multiple_thread[N];

	long id;

	for (id = 1; id <= N; id++) {
		/* create worker threads which executes the start function worker_thread */
		if (pthread_create(&multiple_thread[id], NULL, &worker_thread, &id)) {
			fprintf(stderr, "Error creating thread\n");
			return 1;
		}
	}

	for (id = 1; id <= N; id++) {
		/* wait for worker threads to finish */
		if (pthread_join(multiple_thread[id], NULL)) {
			fprintf(stderr, "Error joining thread\n");
			return 2;
		}
	}

	return 0;

}

/*
 ============================================================================
 Name        : Thread_Concepts.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "hello_world.h"
#include "thread_basics_creation.h"
#include "thread_basics_creation_multiple_threads.h"
#include "thread_basics_termination.h"
#include "thread_basics_termination.h"
#include "sync_basics_mutexes.h"
#include "hello_world.h"

int main(void) {
	//	Hello World Program
	hello_world();

	//A basic thread program
	//thread_creation_basic();

	//A basic thread program that creates multiple threads
	//thread_creation_multiple();

	//A basic thread program that illustrates thread termination
	//thread_basics_termination();

	//A basic thread program that creates multiple threads that can be joined or detached
	//thread_basics_join_detach();

	//A basic thread program that illustrates the use of Mutexes in synchronization
	sync_basics_mutexes();

}


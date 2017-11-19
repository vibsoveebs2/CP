/********************************************************************************
 *	Authors: Jonathon Dahl, Vibhu Patel, Sanyukta Baluni			*
 *	CMPSC 473 - Programming Assignment 4					*
 *	Title: Multithreaded Program using Pthreads				*
*********************************************************************************/
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* global variables */
int day, ready, calicut_transactions;
int arrive[4]; 

/* thread synchronization */
sem_t rendezvous_lock;
sem_t rendezvous_cv[4];		

/* function definitions */
void *fun_empress(void *arg) {
	/* Why not make it easier and hard code it? For consistency! 
	   If the potential speedup was large enough I would reconsider..	*/
	int tid = atoi((char*) arg);	
	int arrival = arrive[tid];
	
	/* Semaphore pointers! (or Macros) For readability of course 		*/
	sem_t* my_cv = &(rendezvous_cv[0]);
	sem_t* merch1_cv = &(rendezvous_cv[1]);
	sem_t* merch2_cv = &(rendezvous_cv[2]);
	sem_t* merch3_cv = &(rendezvous_cv[3]);
	/* Relevant information */
	printf("Empress creation successful!\n");
	while(day < 11) {
		/* Wait for the merchants to arrive - SPIN LOCK - reconsider on a single threaded system */
		//while(ready-3 != 0);
		/* Wait for the merchants to trade */
		sem_wait(my_cv);

		/* WARNING - ENTERING CRITICAL SECTION */
		sem_wait(&rendezvous_lock);	// acquire the lock, I want to access the shared variables
		ready = 0;			// reset thread ready variable - day is changing, threads won't be ready

		if(day >= arrive[tid]) {
			/* Arrival message */
			if(day == arrive[tid]) printf("Empress arrived on day %d\n", arrive[tid]);
			
			/* empress is here, check arrivals */
			if(calicut_transactions > 0 || calicut_transactions < 0) {
				/* check for arrivals */
				if(calicut_transactions == 3) printf("We met everyone by day %d\n", day);
				else if(calicut_transactions > 0) printf("We bought some goods!\n");
				else printf("Alas, we were too late.. We missed some transactions!\n");

				/* Cases: All transactions complete - Missed a transaction */
				if(calicut_transactions == 3 || calicut_transactions < 0) day = 11;			 		
			}
		/* for simplicity, empress arrives at end of day and checks merchants status */
		} else if(day+1 == arrive[tid]) if(calicut_transactions != 0) calicut_transactions = calicut_transactions - 4;		
		// else - empress has not arrived! we don't know what's happening in calicut..

		day = day + 1;

		/* release the lock, tell all the merchants to get back to work - RESUME FROM CP */
		sem_post(&rendezvous_lock);	// release the lock, I'm done accessing the shared variables
		/* NOTE: END OF CRITICAL SECTION */
 		
		/* New day, wake up the merchants */
		sem_post(merch1_cv);
		sem_post(merch2_cv);
		sem_post(merch3_cv);	
	}

	/* Time to leave, did we miss anyone? */
	if(calicut_transactions == 3) printf("Good Job! We met everyone, time to go to Canton!\n");
	/* oh no! */
	else printf("Time to turn back to the US..\n");
	return NULL;					// we're done
}

void *fun_merchant(void *arg) {
	/* grab the thread id for me */
	int tid = atoi((char*) arg);

	/* INVALID - STOP AT ONCE */
	if(tid > 3 || tid < 1) { 
		printf("Invalid TID received: %d\n\tStopping execution, wrapping up!", tid);
		sem_wait(&rendezvous_lock);
		/* Fix this mess, stop all execution */
		day = 11;
		sem_post(&rendezvous_lock);
	}

	/* Semaphore pointers! (or Macros) For readability of course 		*/
	sem_t* empress_cv = &(rendezvous_cv[0]);
	sem_t* my_cv = &(rendezvous_cv[tid]);
	/* Relevant information */
	printf("Merchant (%d) creation successful!\tArrival Time: %d\n", tid, arrive[tid]);
	while(day < 11) {		
		/* WARNING - ENTERING CRITICAL SECTION */
		sem_wait(&rendezvous_lock);		// acquire the lock, I want to access the shared variables
		
		/* Regardless of the Empress's arrival, I will trade! */
		if(day == arrive[tid]) {
			calicut_transactions = calicut_transactions + 1;
			printf("Merchant (%d) sold his goods!\t\tDay: %d, Trans: %d\n", tid, day, calicut_transactions);		
		}

		ready = ready + 1;			// increase thread ready counter
		if(ready == 3) sem_post(empress_cv);	// signal the empress, the trading is done
		sem_post(&rendezvous_lock); 		// release the lock, I'm done accessing the shared variables
		/* NOTE: END OF CRITICAL SECTION */		
		
		/* Critical Point! */
		sem_wait(my_cv);		
	}
	return NULL;					// we're done
}

int getInput(char *argv[]) {
	FILE *fin;					// file handler
	fin = fopen(argv[1], "r");			// open the filename passed on the command line
	//fin = fopen("input1", "r");			// enable for debugging - hard code 
	if(fin == NULL) {				// check for illegal file
		printf("Error opening file:\n\tCheck file path and try again\n");
		return (-1);				// return error
	} else { 	/* get, separate, and store the values - Scanf returns the number of characters written */
		if(fscanf(fin, "%d, %d, %d, %d", &(arrive[0]), &(arrive[1]), &(arrive[2]), &(arrive[3])) != 4) {
			// wrong input format, output error and example
			printf("Error in input file:\n\tExample input: 1, 2, 3, 4\n");
			return (-1);			// return error
		}
	}  
	fclose(fin);
	return 0;	// success
}

/* MAIN */
int main(int argc, char *argv[]) {
	/* Initialize the semaphores! */
	sem_init(&rendezvous_lock, 0, 1);	// shared data lock1 
	sem_init(&(rendezvous_cv[0]), 0, 0);	// merch1 condition variable
	sem_init(&(rendezvous_cv[1]), 0, 0);	// merch2 condition variable 
	sem_init(&(rendezvous_cv[2]), 0, 0);	// merch3 condition variable
	sem_init(&(rendezvous_cv[3]), 0, 0);	// empress condition variable
	/* count the transactions, empress verifies transactions - invalid transactions are missed */
	calicut_transactions = 0;

	/* Day counter initialization */	
	day = 1;

	int rc = getInput(argv);	// open the file, separate the variables, and close the file
	if(rc != 0) return rc;		// problems? return the error	  

	pthread_t empress, merchant1, merchant2, merchant3;
	printf("main: begin thread creation\n");
	/* RELEASE THE THREADS! */
	rc = pthread_create(&empress, NULL, fun_empress, (void*) "0"); assert(rc == 0);
	rc = pthread_create(&merchant1, NULL, fun_merchant, (void*) "1"); assert(rc == 0);
	rc = pthread_create(&merchant2, NULL, fun_merchant, (void*) "2"); assert(rc == 0);
	rc = pthread_create(&merchant3, NULL, fun_merchant, (void*) "3"); assert(rc == 0);

	// join waits for the threads to finish
	rc = pthread_join(merchant1, NULL); assert(rc == 0); 
	printf("Merchant 1 rejoined!\t");
	rc = pthread_join(merchant2, NULL); assert(rc == 0);
	printf("Merchant 2 rejoined!\t");
	rc = pthread_join(merchant3, NULL); assert(rc == 0);
	printf("Merchant 3 rejoined!\t\n");
	rc = pthread_join(empress, NULL); assert(rc == 0);
	printf("Empress rejoined!\n");
	printf("main: exiting\n");
	return 0;   // return successfully
}

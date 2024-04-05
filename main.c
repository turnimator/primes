/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   main.c
 * Author: atle
 *
 * Created on April 4, 2024, 10:20 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

char *primes;
int nprimes;

static int semF = 0; // no go

/**
 *   populate the array from prime p
 **/
void *mark_from(void *p) {
	int n = *(int*) p;
	primes[n] = 'p';
	semF = 1;	// We have marked our first spot so the next thread can be started
	for (int i = n*2; i < nprimes; i+=n) {
		primes[i] = 'n';
	}
}

void print_primes() {

	for (int i = 0; i < nprimes; i++) {
		if (primes[i] == 'p') {
			printf("%d ", i);
		} else if (primes[i] == 'n') {
			// printf("%d,", i);
		} else {
			printf("%d ", i);
		}
	}

}

/*
 * 
 */
int main(int argc, char** argv) {
	pthread_t tid;
	if (argc < 2) {
		nprimes = 121;
	} else {
		nprimes = atoi(argv[1]);
	}
	primes = malloc(nprimes * sizeof (char));
	int first = 2;
	pthread_create(&tid, NULL, mark_from, (void *) (&first));
	for(int i = 3; i < (nprimes/2); i++){
		if (primes[i]==0){
			pthread_t tid2;
			semF = 0; // Set semaphore
			int j = i;
			pthread_create(&tid2, NULL, mark_from, (void *) (&j));
		}
		while(semF==0){
			; //printf("."); // Wait until thread clears semaphore
		}
		
	}
	pthread_join(tid, NULL);
	print_primes();
	free(primes);
	return (EXIT_SUCCESS);
}


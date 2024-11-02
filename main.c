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
#include <unistd.h>

char *primes;
long nprimes;

int noTasks = 0; // no go

/**
 *   populate the array from prime p
 **/
void *mark_from(void *p) {
    long n = *(long*) p;
    primes[n] = 'p';
    ++noTasks;
    for (long i = n * 2; i < nprimes; i += n) {
        primes[i] = 'n';
    }
    --noTasks;
}

void print_primes() {

    for (long i = 0; i < nprimes; i++) {
        if (primes[i] == 'p') {
            printf("\n%ld ", i);
        } else if (primes[i] == 'n') {
            // printf("%d,", i);
        } else {
            //printf("\n%d not initialized\n", i);
        }
    }
}

/*
 *
 */
int main(int argc, char** argv) {
    pthread_t tid;
    if (argc < 2) {
        nprimes = 10000000;
    } else {
        nprimes = atoi(argv[1]);
    }
    printf("Looking for primes up to %ld\n", nprimes);
    noTasks = 0;
    primes = malloc(nprimes * sizeof (char));
    long first = 2;
    pthread_create(&tid, NULL, mark_from, (void *) (&first));
    usleep(30);
    for (long i = 3; i < (nprimes); i++) {
        while (noTasks > 56) {
            printf("\r%d tasks active ", noTasks);
            usleep(30);
            noTasks--;
        }
        if (primes[i] == 0) {
            pthread_t tid2;
            long j = i;
            int fail = pthread_create(&tid2, NULL, mark_from, (void *) (&j));
        }
    }
    pthread_join(tid, NULL);
    print_primes();
    free(primes);
    return (EXIT_SUCCESS);

}

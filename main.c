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
#include <sys/time.h>

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
    pthread_detach(pthread_self());
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

pthread_t *tid;
int tid_idx = 0;

/*
 *
 */
int main(int argc, char** argv) {

    struct timeval start_time, end_time;
    long milli_time, seconds, useconds;


    if (argc < 2) {
        nprimes = 10000000;
    } else {
        nprimes = atoi(argv[1]);
    }
    char buf[256];
    printf("PPRIMES %s\n", getcwd(buf, 255));
    printf("Looking for primes up to %ld\n", nprimes);
    tid = malloc(nprimes * sizeof (pthread_t));
    noTasks = 0;
    primes = malloc(nprimes * sizeof (char));
    long first = 2;
    gettimeofday(&start_time, NULL);
    pthread_create(&tid[tid_idx++], NULL, mark_from, (void *) (&first));
    usleep(30);
    for (long i = 3; i < (nprimes); i++) {
        while (noTasks > 2048) {
            printf("\r%d tasks active ", noTasks);
            usleep(30);
            noTasks--;
        }
        if (primes[i] == 0) {
            long j = i;
            int fail = pthread_create(&tid[tid_idx++], NULL, mark_from, (void *) (&j));
            if (fail) {
                perror("Thread creation failed!");
            }
        }

    }
    /*
    gettimeofday(&end_time, NULL);
    seconds = end_time.tv_sec - start_time.tv_sec; //seconds
    useconds = end_time.tv_usec - start_time.tv_usec; //milliseconds
    milli_time = ((seconds) * 1000 + useconds / 1000.0);
    printf("%ld milliseconds elapsed. Press ENTER to see primes:", milli_time);
     */
    //getchar();
    print_primes();
    free(primes);
    return (EXIT_SUCCESS);

}

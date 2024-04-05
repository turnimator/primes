/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   main.c
 * Author: atle
 *
 * Created on April 4, 2024, 10:06 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int is_prime(int n)
{
    if (n <= 1){
        return 0;
    }
    for (int i = 2; i <= n/2; i++){
        if ((n%i)==0){
            return 0;
        }
    }
    return 1;
}


int main(int ac, char*av[]){
    if (ac<2){
		printf("Usage: %s number", av[0]);
		return -1;
	}
	printf("%s\n", (is_prime(atoi(av[1]))?"Yes":"No"));
}

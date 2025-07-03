#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

int abs_branch(int *a){
    if(*a >= 0){
        return *a;
    }
    else{
        return -*a;
    }
}

int abs_branchless(int *a){
    int mask = (*a >> 15);
    int val = (*a + mask) ^ mask;
    return val;
}
/*
        1(0000 0000 0000 0001) >> 15 => (1111 1111 1111 1100) = mask
    +     1111 1111 1111 1100
    =     1111 1111 1111 1101
    ^     1111 1111 1111 1100
    =     0000 0000 0000 0001

       -1(1111 1111 1111 1111) >> 15 => (1111 1111 1111 1111) = mask
    +     1111 1111 1111 1111
    =   1 1111 1111 1111 1110 (the overflow will be ignored) 
    ^     1111 1111 1111 1111
    =     0000 0000 0000 0001 = 1
    
*/

int main(){
    int a = 1; int b = -1;
    clock_t begin = clock();
    a = abs_branch(&a);
    b = abs_branch(&b);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("a = %d, b = %d, with branch: %f\n", a, b, time_spent);
    a = 1; b = -1;
    begin = clock();
    a = abs_branchless(&a);
    b = abs_branchless(&b);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("a = %d, b = %d,without branch: %f\n", a, b, time_spent);
    return 0;
}
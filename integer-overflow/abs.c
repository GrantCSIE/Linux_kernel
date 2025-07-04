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
    struct timespec start, end;
    int a = 1; int b = -1;
    clock_gettime(CLOCK_MONOTONIC, &start);
    a = abs_branch(&a);
    b = abs_branch(&b);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_spent = (double)(end.tv_nsec - start.tv_nsec);
    printf("a = %d, b = %d, with branch: %f nsec\n", a, b, time_spent);
    a = 1; b = -1;
    clock_gettime(CLOCK_MONOTONIC, &start);
    a = abs_branchless(&a);
    b = abs_branchless(&b);
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_spent = (double)(end.tv_nsec - start.tv_nsec);
    printf("a = %d, b = %d, without branch: %f nsec\n", a, b, time_spent);
    return 0;
}
// 
/*
branch operation will spend more time than branchless operation, 
    which will be easier to find the confidential info. by Timing Attack.

Details of the code:
    int clock_gettime(clockid_t clk_id, struct timespec *tp);

    clockid_t:
        CLOCK_REALTIME
            System-wide realtime clock. Setting this clock requires appropriate privileges.
        CLOCK_MONOTONIC
            Clock that cannot be set and represents monotonic time since some unspecified starting point.
        CLOCK_PROCESS_CPUTIME_ID
            High-resolution per-process timer from the CPU.
        CLOCK_THREAD_CPUTIME_ID
            Thread-specific CPU-time clock.

    timespec:
        struct timespec {
            time_t   tv_sec;       // seconds 
            long     tv_nsec;      // nanoseconds
        };
*/
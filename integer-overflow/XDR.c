#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define KSIZE 512
int *ele_src[KSIZE];

void *copy_elements(void *ele_src[], int ele_cnt, int ele_size) {
    void *result = malloc(ele_cnt * ele_size);
    if (result==NULL) return NULL;
    void *next = result;
    for (int i = 0; i < ele_cnt; i++) {
        memcpy(next, ele_src[i], ele_size);
        next += ele_size;
    }
    return result;
}
/*
    Details of malloc:
    The  malloc(), calloc(), realloc(), and reallocarray() functions return
       a pointer to the allocated memory, which is suitably  aligned  for  any
       type  that fits into the requested size or less.  On error, these func‐
       tions return NULL and set errno.
    
    Therefore, when ele_cnt is bigger than KSIZE, the size of result pointer can be larger than ele_src array.
    The outside of memory which can not be accessed in user mode will be copied without proper process.
    solution:

    void *copy_elements(void *ele_src[], int ele_cnt, int ele_size) {
        if (ele_cnt > KSIZE) return NULL; // add this line, which will check the number of accessed item.
        void *result = malloc(ele_cnt * ele_size);
        if (result==NULL) return NULL;
        void *next = result;
        for (int i = 0; i < ele_cnt; i++) {
            memcpy(next, ele_src[i], ele_size);
            next += ele_size;
        }
        return result;
}
*/

void create_test_case(){
    for(int i = 0; i < KSIZE; i++){
        ele_src[i] = malloc(sizeof(int));
        *ele_src[i] = i * 2;
    }
}

void normal_case(){
    int* result = copy_elements((void **)ele_src, KSIZE, sizeof(int));
    for(int i = 0; i < KSIZE; i++){
        printf("index %d item is %d\n", i, *result);
        result += 1;
    }
}

void abnormal_case(){
    int* result = copy_elements((void **)ele_src, pow(2, 17), sizeof(int));
    printf("index %d item is %d\n", KSIZE, result[KSIZE]);
}

int main(){
    create_test_case();
    normal_case();
    abnormal_case();
}
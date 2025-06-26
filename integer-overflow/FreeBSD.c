#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define KSIZE 1024
char kbuf[KSIZE];
int copy_from_kernel(void *user_dest, int maxlen) { // (void *) pointer can receive any type of pointer.
    int len = KSIZE < maxlen ? KSIZE : maxlen;
    memcpy(user_dest, kbuf, len);
    return len;
}
/*
    Details of memcpy:
    void *memcpy(void dest[restrict .n], const void src[restrict .n],
                    size_t n);
    "size_t" denotes an signed and unsigned integer in arm and x86 architectures, respectively.
    Therefore, in x86 architecture case, when it pass NEGATIVE maxlen, 
    the outside of memory which can not be accessed in user mode will be accessed.
    (Since this code is currently run in user mode, an "Segementation fault" will be occured)
*/

void create_test_case(){
    for(int i = 0; i < KSIZE; i++){
        kbuf[i] = i;
    }
}

void normal_case(char *user_dest, int size){
    int length = copy_from_kernel(user_dest, size);
    printf("user info. length = %d\n", length);
}

int abnormal_case(char *user_dest, int size){
    int length = copy_from_kernel(user_dest, size);
    printf("user info. length = %d\n", length);
    return length;
}

int main(){
    create_test_case();
    char *user_dest = (char*)malloc(KSIZE * sizeof(char));
    normal_case(user_dest, KSIZE);
    int target = abnormal_case(user_dest, (-1 * pow(2, 31)));
    printf("target info. = %c\n", user_dest[target]);
    return 0;
}

free(kbuf);

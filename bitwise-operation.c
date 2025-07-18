#define U2L(X) ((X) | (' ')) 
/*
    U2L(X):
    65(0100 0001) <=  X  <=  90(0101 1010) 
OR  32(0010 0000)  = ' ' =   32(0010 0000)
  = 97(0110 0001) <=  X' <= 122(0111 1010) 
*/  


#define L2U(X) ((X) & ('_')) 
/*
    U2L(X):
    97(0110 0001) <=  X  <= 122(0111 1010)
AND 95(0101 1111)  = '_' =   95(0101 1111)
  = 65(0100 0001) <=  X' <=  90(0101 1010) 
*/  

#define U2LL2U(X) ((X) ^ (' '))
/*
    U2LL2U(X):
    case 1: upper
     65(0100 0001) <=  X  <=   90(0101 1010) 
XOR  32(0010 0000)  = ' ' =    32(0010 0000)
    = 97(0110 0001) <=  X' <=  122(0111 1010)   
    case 2: lower
      97(0110 0001) <=  X  <= 122(0111 1010)
XOR   32(0010 0000)  = ' ' =   32(0010 0000)
    = 65(0100 0001) <=  X' <=  90(0101 1010) 
*/

#include<stdio.h>
#include<stdlib.h>

void swap(int *x, int *y){
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}

void L2U_test(){
    printf("%c\n", L2U('A'));
    printf("%c\n", U2L('a'));
}

void swap_test(){
    int x, y;
    x = 3; y = 4;
    swap(&x, &y);
    printf("x = %d, y = %d\n", x, y);
}

int main(){
    L2U_test();
    swap_test();
    return 0;
}
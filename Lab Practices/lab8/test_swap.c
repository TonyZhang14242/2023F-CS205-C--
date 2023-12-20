#include "myswap.h"
#include <stdio.h>
int main(){
    printf("Please input two number: ");
    int a = 3;
    int b = 6;
    scanf("%d %d", &a ,&b);
    printf("Before swap: %d %d\n", a, b);
    swap_two(&a,&b);
    printf("After swap: %d %d\n", a, b);
}
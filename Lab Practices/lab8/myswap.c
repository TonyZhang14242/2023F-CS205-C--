#include "myswap.h"

void swap_two(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
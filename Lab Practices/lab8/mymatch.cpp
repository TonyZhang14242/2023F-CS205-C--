#include "mymatch.h"
#define NULL 0
const char* match(const char* s, char ch){
    while (*s != '\0')
    {
        if (*s == ch){
            return s;
        }
        s++;
    }
    return NULL;
}
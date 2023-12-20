#include <stdio.h>

int main(){
    char c;
    int num;
    float f;
    printf("Please input a character:\n");
    scanf("%c", &c);
    printf("Please input an integer:\n");
    scanf("%d", &num);
    printf("Please input a float:\n");
    scanf("%f", &f);
    printf("The variables you entered are:\n");
    printf("The character is: %c\n", c);
    printf("The integer is: %d\n", num);
    printf("The float is : %f\n", f);
    return 0;
}
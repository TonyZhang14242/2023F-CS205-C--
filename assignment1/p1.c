#include <stdio.h>
#define PI 3.1415926

int main(){
    double angle;
    char type;
    double result;
    scanf("%lf %c",&angle,&type);
    if (type == 'r')
    {
        result = angle  / PI * 180;
    }
    else{
        result = angle / 180 * PI;
    }
    printf("%.2f\n", result);
    return 0;
}
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI (long double)3.14159265358979323846264338327L

long double calc_to_radius(long double angle, char type){
    long double result;
    if (type == 'd')
    {
        result = angle / 180 * PI;
    }
    else{
        result = angle;
    }
    return result;
}
long double calc_sine(long double x, int n){
    int i = 1;
    int cnt = 0;
    long double term1 = 1;
    long double term2 = x;
    long double term3 = 1;
    long double cur_result = 0;
    while (i <= n)
    {
        cur_result = cur_result + term1 * term2 / term3;
        cnt++;
        i+=2;
        term1 *= -1;
        term2 = powl(x,i);
        term3 = i * (i-1) * term3;
    }
    return cur_result;
}

long double calc_cosine(long double x, int n){
    int i = 0;
    int cnt = 0;
    long double term1 = 1;
    long double term2 = 1;
    long double term3 = 1;
    long double cur_result = 0;
    while (i <= n)
    {
        cur_result = cur_result + term1 * term2 / term3;
        cnt++;
        i+=2;
        term1 *= -1;
        term2 = powl(x,i);
        term3 = i * (i-1) * term3;
    }
    return cur_result;
}

int main(){
    int n;
    long double angle;
    char type;
    long double rad_result;
    long double sine,cosine;
    scanf("%Lf %d %c",&angle,&n,&type);

    rad_result = calc_to_radius(angle, type);
    //printf("%.2f", rad_result);
    sine = calc_sine(rad_result, n);
    cosine = calc_cosine(rad_result, n);
    if (fabsl(sine-0.00)<0.005)
    {
        printf("0.00\n%.2Lf\n", cosine);
    }
    else if(fabsl(cosine-0.00)<0.005){
         printf("%.2Lf\n0.00\n", sine);
    }
    else
    printf("%.2Lf\n%.2Lf\n", sine, cosine);
    return 0;
}
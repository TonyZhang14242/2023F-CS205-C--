#include <stdio.h>
#include <math.h>
#define PI (long double)3.14159265358979323846264338327L
int main(){
    int n;
    scanf("%d", &n);
    int len = 1 << n;
    double arr[n];
    double maxsine = -1;
    for (int i = 0; i < n; i++)
    {
        scanf("%lf", &arr[i]);
    }
    
    for (int i = 1; i < len; i++)
    {
        int j = i;
        int k = 0;
        double sum = 0;
        while (j)
        {
            if (j & 1)
            {
                sum += arr[k];
            }
            
            j = j >> 1;
            k++;
        }
        if (maxsine < sin(sum/180*PI))
        {
            maxsine = sin(sum/180*PI);
        }
        
    }
    printf("%.2f\n", maxsine);
    return 0;
}
#include "sale.h"
#include <iostream>
int main()
{
    SALES::Sales mysale;
    int n;

    std::cout << "Input n: ";
    std::cin >> n;
    if (n >= 5)
    {
        std::cout << "n is not correct!\n";
        std::abort();
    }
    double arr[n];
    std::cout << "Please input " << n << " double values: ";
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    SALES::setSales(mysale, arr, n);
    SALES::showSales(mysale, n);
}
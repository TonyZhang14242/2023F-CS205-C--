#include "sale.h"
#include <iostream>
namespace SALES{
    void setSales(Sales& s, const double ar[], int n){
        if (n >= 5)
        {
            std::cout << "n is not correct!\n";
            std::abort();
        }

        double sum = 0;
        int max_idx = 0;
        int min_idx = 0;
        for (int i = 0; i < n; i++)
        {
            s.sales[i] = ar[i];
            sum += ar[i];
            if (ar[i] > ar[max_idx])
            {
                max_idx = i;
            }
            if (ar[i] < ar[min_idx])
            {
                min_idx = i;
            }
            
        }
        s.max = ar[max_idx];
        s.min = ar[min_idx];
        s.average = sum/n;
    }

    void showSales(const Sales& s, int n){
        std::cout << "Sales: ";
        for (int i = 0; i < n; i++)
        {
            std::cout << s.sales[i] << " ";
        }
        std::cout << "\n";
        std::cout << "Average: " << s.average << std::endl;
        std::cout << "Max: "<< s.max << std::endl;
        std::cout << "Min: " << s.min << std::endl;
        
    }
}
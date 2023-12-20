#pragma once
namespace SALES{
    const int QUATERS = 4;
    struct Sales
    {
        double sales[QUATERS];
        double average;
        double max;
        double min;
    };
    void setSales(Sales& s, const double ar[], int n=4);
    void showSales(const Sales& s, int n=4);
}
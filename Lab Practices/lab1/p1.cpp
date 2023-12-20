#include <iostream>
#include <iomanip>

using namespace std;
int main()
{
    float a = 0.1;
    float b = 0.2;
    float c = 0.3;
    printf("%.2f\n%.2f\n%.2f\n", a, b, c);
    cout << setiosflags(ios::fixed) << setprecision(2) << a << endl << b << endl << c << endl;
}
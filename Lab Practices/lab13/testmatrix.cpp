#include "matrix.h"
#include <iostream>
using namespace std;

int main(){
    Matrix a(3,4);
    Matrix b(3,4);
    a.setElement(1, 2, 3);
    b.setElement(2, 3, 4);
    cout << "a is:\n";
    cout << a;
    cout << "b is:\n";
    cout << b;
    Matrix c = a + b;
   
    cout << "c is:\n";
    cout << c; 
    Matrix d = a;
    
    cout << "Before assignment, d is:\n";
    cout << d;
    d = b;
    cout << "After assignment, d is:\n";
    cout << d;
    return 0;
}
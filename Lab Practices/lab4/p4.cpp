#include <iostream>
using namespace std;

int main(){
    int *num = new int[5];
    for (int i = 0; i < 5; i++)
    {
        *(num+i) = rand();
        cout << *(num+i) << " " ;
    }
    cout << endl;
    int * p = num+5;
    for (int i = 0; i < 5; i++)
    {
        cout << *(p-1-i) << " ";
    }
    cout << endl;
    delete []num;
    return 0;
}
#include "mymatch.h"
#include <iostream>
using namespace std;
int main(){
    cout << "Please input a string:\n";
    char* str = new char[100];
    cin.getline(str, 100);
    cout << "Please input a character:\n";
    char c;
    cin >> c;
    char * res;
    if ((match(str, c)) != NULL)
        cout << match(str, c) << endl;
    else
        cout << "Not found!" << endl;
    delete []str;
}
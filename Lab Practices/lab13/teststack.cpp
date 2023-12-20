#include "stack.h"
#include <iostream>
using namespace std;

int main(){
    Stack st1; //st1: 1 2 3 4 5 6 7 8 9 10
    Item tmp;
    bool b2 = st1.push(11);
    cout << boolalpha << b2 << endl; //false
    st1.pop(tmp); //st1 after pop: 1 2 3 4 5 6 7 8 9
    st1.pop(tmp); //st1 after pop: 1 2 3 4 5 6 7 8
    cout << tmp << endl; //9
    Stack st2(st1); //st2: 1 2 3 4 5 6 7 8
    st2.pop(tmp); //st2 after pop: 1 2 3 4 5 6 7
    cout << tmp << endl; //8
    Stack st3 = st2; //st3: 1 2 3 4 5 6 7
    st3.push(10000);//st3 after push: 1 2 3 4 5 6 7 10000
    st2.pop(tmp);//st2 after pop: 1 2 3 4 5 6
    cout << tmp << endl; //7
    while (!st3.isempty())
    {
        st3.pop(tmp);
        cout << tmp << " ";
    } // 10000 7 6 5 4 3 2 1
    cout << endl;
    st3 = st1;//st3: 1 2 3 4 5 6 7 8
    while (!st3.isempty())
    {
        st3.pop(tmp);
        cout << tmp << " ";
    } //8 7 6 5 4 3 2 1
    cout << endl;
    bool b3 = st3.pop(tmp);
    cout << boolalpha << b3 << endl; //false
    return 0;
}
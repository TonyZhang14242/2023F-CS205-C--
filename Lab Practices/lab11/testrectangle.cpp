#include "ractangle.h"
#include <iostream>
using namespace std;

int main(){
    Rectangle r1;
    Rectangle r2(4, 35.2);
    cout << "       Rectangle 1" << endl;
    r1.display();
    cout << "\n       Rectangle 2" << endl;
    r2.display();
    cout << "The number of the rectangles are: " << Rectangle::getCount() << endl;

    return 0;
}
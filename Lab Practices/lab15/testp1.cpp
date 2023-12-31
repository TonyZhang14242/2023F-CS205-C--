#include "line.hpp"
using namespace std;
int main(){
    Point a(8, 9);
    cout << "test point a: x = 8, y = 9\n";
    Point b;
    cout << "test point a: x = 1, y = -1\n";
    Line l1(a, b);
    cout << "-----------------------------------\n";
    cout << "line 1: " << l1.getDistance() << endl;
    Line l2(l1);
    cout << "line 2: " << l2.getDistance() << endl;
    return 0;
}
#include <iostream>
#include <string.h>
using namespace std;
int main()
{
    int cards[4]{};
    int price[] = {3, 4, 5, 9, -1};
    char direction[4]{'L', 82, 'U', 68};
    char title[] = "ChartGPT is an awesome tool.";
    cout << "sizeof(cards) = " << sizeof(cards) << ",sizeof of cards[0] = " << sizeof(cards[0]) << endl;
    cout << "sizeof(price) = " << sizeof(price) << ",sizeof of price[0] = " << sizeof(price[0]) << endl;
    cout << "sizeof(direction) = " << sizeof(direction) << ",length of direction = " << strlen(direction) << endl;
    cout << "sizeof(title) = " << sizeof(title) << ",length of title = " << strlen(title) << endl;
    // Print the address of each array variable.
    cout << "Address of cards: " << cards << endl;
    cout << "Address of price: " << price << endl;
    cout << "Address of direction: " << &direction << endl;
    cout << "Address of title: " << &title << endl;
    return 0;
}
#include "functions.h"
#include <iostream>
using namespace std;

int main()
{
    string inp;
    int op = 0;
    do
    {
        cout << "Enter an index for operation (0 for add, 1 for substraction, 2 for multiplication, 3 for division, -1 to exit): ";
        cin >> inp;
        try
        {
            op = stoi(inp);
        }
        catch(const std::exception& e)
        {
            cout << "Invalid operation!\n";
            continue;
        }
        
        
        if (op == -1)
        {
            return 0;
        }
        int a = 0, b = 0;
        if (op == 0 || op == 1 || op == 2 || op == 3)
        {
            cout << "Enter two numbers (saparated by space): ";
            cin >> a >> b;
        }

        switch (op)
        {
        case 0:
            cout << "The result is " << add(a, b) << endl;
            break;
        case 1:
            cout << "The result is " << substraction(a, b) << endl;
            break;
        case 2:
            cout << "The result is " << multiply(a, b) << endl;
            break;
        case 3:
            cout << "The result is " << divide(a, b) << endl;
            break;
        case -1:
            break;
        default:
            cout << "Invalid operation!" << endl;
        }
    } while (op != -1);
    cout << "Done!\n";
}
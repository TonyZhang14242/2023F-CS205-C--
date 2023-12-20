#include <iostream>
using namespace std;
void Displaymenu()
{
    cout << "================================================================================\n";
    cout << "                                    MENU                                        \n";
    cout << "================================================================================\n";
    cout << "             1. Add\n";
    cout << "             2. Substract\n";
    cout << "             3. Multiply\n";
    cout << "             4. Divide\n";
    cout << "             5. Modulus\n";
}
int Add(int a, int b)
{
    return a + b;
}
int Substract(int a, int b)
{
    return a - b;
}
int Multiply(int a, int b)
{
    return a * b;
}
int Divide(int a, int b)
{
    return a / b;
}
int Modulus(int a, int b)
{
    return a % b;
}
int main()
{
    Displaymenu();
    int yourchoice;
    int a, b;
    char confirm;
    do
    {
        cout << "Enter your choice(1-5):";
        cin >> yourchoice;
        cout << "Enter your integer numbers:";
        cin >> a >> b;
        cout << endl;
        switch (yourchoice)
        {
        case 1:
            cout << "Result: " << Add(a, b) << endl;
            break;
        case 2:
            cout << "Result: " << Substract(a, b) << endl;
            break;
        case 3:
            cout << "Result: " << Multiply(a, b) << endl;
            break;
        case 4:
            cout << "Result: " << Divide(a, b) << endl;
            break;
        case 5:
            cout << "Result: " << Modulus(a, b) << endl;
            break;
        default:
            cout << "Invalid Instruction!" << endl;
            break;
        }
        cout << "Press y or Y to continue\n";
        cin >> confirm;
    } while (confirm == 'y' || confirm == 'Y');

    cout << "Done.\n";
}
#include "out_of_range_exception.hpp"
#include <iostream>
using namespace std;
int main()
{
    char s = 'y';
    do
    {
        if (s == 'y')
        {
            cout << "Please enter marks for 4 courses:";
            int *scores = new int[4];
            for (int i = 0; i < 4; i++)
            {
                cin >> scores[i];
            }
            try
            {
                float res = calculateAverage(scores[0], scores[1], scores[2], scores[3]);
                cout << "The average of 4 courses is " << res << endl;
            }
            catch (exception &e)
            {
                cout << e.what() << endl;
            }
            delete [] scores;
        }
        else
        {
            cout << "Bye, see you next time.\n";
            break;
        }
        cout << "Would you want to enter another marks for 4 courses(y/n)?";
        cin >> s;
    } while (true);
    return 0;
}
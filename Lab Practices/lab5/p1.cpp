#include <iostream>
#include <sstream>
using namespace std;

int main()
{
    long long cnt = 0;
    while (true)
    {
        string input;
        getline(cin, input);
        string str;
        stringstream sst(input);
        while (getline(sst, str, ' '))
        {
            if (str == "done")
            {
                if (cnt == 0){
                    cout << "no words entered.\n";
                }
                else
                cout << "You have entered " << cnt  << " words." << endl;
                return 0;
            }
            else
            {
                cnt++;
            }
        }
    }

}
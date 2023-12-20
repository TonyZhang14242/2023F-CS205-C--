#include <iostream>
#include <sstream>
using namespace std;

char vowels[] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
int main()
{
    long long vowel_cnt = 0;
    long long consonants_cnt = 0;
    long long non_letter = 0;
    while (true)
    {
        string input;
        getline(cin, input);
        string str;
        stringstream sst(input);
        while (getline(sst, str, ' '))
        {
            if (str == "q")
            {
                cout << vowel_cnt << " word(s) begin with vowel.\n";
                cout << consonants_cnt << " words(s) begin with consonants.\n";
                cout << non_letter << " others.\n";
                return 0;
            }
            else
            {
                if (!isalpha(str[0]))
                {
                    non_letter++;
                }
                else
                {
                    int flag = 0;
                    for (int i = 0; i < 10; i++)
                    {
                        if (str[0] == vowels[i])
                        {
                            vowel_cnt++;
                            flag = 1;
                            break;
                        }
                    }
                    if (!flag)
                    {
                        consonants_cnt++;
                    }
                }
            }
        }
    }
}
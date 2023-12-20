#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

int main(){
    string input;
    getline(cin, input);
    string output;
    for (int i = 0; i < input.size(); i++)
    {
        if ((input[i]<='Z' && input[i]>='A') || (input[i]<='z' && input[i] >= 'a') || input[i] == ' ')
            output += input[i];
    }
    //cout << output << endl;
    ofstream ost;
    ost.open("./f1.txt");
    if (ost.is_open())
    {
        ost << output;
        ost.close();
    }
    string out_upper = output;
    transform(output.begin(), output.end(), out_upper.begin(), ::toupper);

    ost.open("./f2.txt");
    if (ost.is_open())
    {
        ost << out_upper;
        ost.close();
    }

    ifstream ist;
    ist.open("./f1.txt");
    string res_f1;
    if (ist.is_open())
    {
        while (!ist.eof())
        {
            getline(ist, res_f1);
            cout << res_f1 << endl;
        }
        ist.close();
    }
    
    ist.open("./f2.txt");
    string res_f2;
    if (ist.is_open())
    {
        while (!ist.eof())
        {
            getline(ist, res_f2);
            cout << res_f2 << endl;
        }
        ist.close();
    }
}
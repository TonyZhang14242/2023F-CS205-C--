#include <iostream>
#include <cstring>
using namespace std;
struct stringy{
    char * str;
    int ct;
};

void set(stringy& sy, const char * chrs);

void show(const stringy& sy, const int num=1);
void show(const char *chr, const int num=1);

int main(){
    stringy beany;
    char testing[] = "Reality isn't what it used to be.";

    set(beany, testing);
    show(beany);
    show(beany,2);
    testing[0] = 'D';
    testing[1] = 'u';
    show(testing);
    show(testing, 3);
    show("Done!");
    delete []beany.str;
    return 0;
}

void set(stringy& sy, const char *chrs){
    sy.str = new char[strlen(chrs)+1];
    strcpy(sy.str, chrs);
    sy.ct = strlen(chrs);
}

void show(const stringy& sy,const int num){
    if (num == 0)
    {
        return;
    }
    cout << sy.str << endl;
    show(sy, num-1);
}

void show(const char *chr, const int num){
    if (num == 0)
    {
        return;
    }
    cout << chr << endl;
    show(chr, num-1);
}
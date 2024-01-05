#pragma once
#include <cstring>
#include <string>
using namespace std;

class OutOfRangeException: public exception
{
private:
    int idx;
    int val;
    char* info;
public:
    OutOfRangeException(int _idx, int _val) : idx(_idx), val(_val) {info = new char[100];}
    ~OutOfRangeException() {
        delete info;
    }
    virtual const char* what() const noexcept override{
        string s;
        s += "The parameter ";
        s += to_string(idx);
        s += " is ";
        s += to_string(val);
        s += " which is out of range (0-100).";
        memcpy(info, s.c_str(), s.size()+1);
        return info;
    }
    int getidx() { return idx; }
    int getval() { return val; }
};

float calculateAverage(int s1, int s2, int s3, int s4)
{
    float sum = 0;
    if (s1 > 100 || s1 < 0)
    {
        throw OutOfRangeException(1, s1);
    }
    else if (s2 > 100 || s2 < 0)
    {
        throw OutOfRangeException(2, s2);
    }
    else if (s3 > 100 || s3 < 0)
    {
        throw OutOfRangeException(3, s3);
    }
    else if (s4 > 100 || s4 < 0)
    {
        throw OutOfRangeException(4, s4);
    }
    sum += s1;
    sum += s2;
    sum += s3;
    sum += s4;
    return sum / 4;
}

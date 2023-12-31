#include <iostream>
#include <string>
using namespace std;
template <class T1, class T2>
class Pair
{
public:
    T1 key;
    T2 value;
    Pair(T1 k, T2 v) : key(k), value(v){};
    bool operator<(const Pair<T1, T2> &p) const;
    friend ostream &operator<<(ostream &os, Pair<T1, T2> p)
    {
        os << p.key << "\t" << p.value << endl;
        return os;
    }
};

template <class T1, class T2>
bool Pair<T1, T2>::operator<(const Pair<T1, T2> &p) const
{
    return this->key < p.key;
}


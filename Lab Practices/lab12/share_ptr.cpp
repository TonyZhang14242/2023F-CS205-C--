#include <iostream>
#include <memory>
using namespace std;
int main()
{
    double *p_reg = new double(5);
    cout << "address of p_reg: " << p_reg << endl;
    shared_ptr<double> pd = static_cast<shared_ptr<double>>(p_reg);
    cout << "pd points to: "<< pd.get() << endl;
    cout << pd.use_count() << endl;
    //pd = p_reg;
    cout << "*pd = " << *pd << endl;
    shared_ptr<double> pshared = pd; //origin: shared_ptr<double> pshared = p_reg
    /*
        Actually 2 problems here.

        The first is caused by isolation of pd and pshared.
        They do not share one control block, as pd.use_count() == pshared.use_count() == 1.
        When the program terminates at the end, they both free the content it points to, result in double free.

        We can skip this problem by using the statements above.
    */
    cout << "*pshred = " << *pshared << endl;
    cout << "pshared points to: "<< pshared.get() << endl;
    cout << pshared.use_count() << endl;

    string str("Hello World!"); //second problem: not using "new" to initialize.
    cout << &str << endl;
    shared_ptr<string> pstr(&str); //fails when program ends
    cout << "*pstr = " << *pstr << endl;
    return 0;
}
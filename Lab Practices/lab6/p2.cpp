#include <iostream>
using namespace std;

int fill_array(double arr[], int size)
{
    int i = 0;
    for (i = 0; i < size; i++)
    {
        bool isDouble = true;
        string s;
        cout << "Enter value #" << i << ": ";
        cin >> s;
        double d;
        try
        {
            d = stod(s);
        }
        catch (const std::exception &e)
        {
            isDouble = false;
        }
        if (isDouble)
        {
            arr[i] = d;
        }
        else
        {
            break;
        }
    }
    return i;
}

void show_array(double *arr, int size)
{

    for (int i = 0; i < size; i++)
    {
        cout << *(arr + i) << " ";
    }
    cout << endl;
}

void reverse_array(double *arr, int size)
{
    if (size <= 1)
    {
        return;
    }
    double tmp = arr[size - 1];
    arr[size - 1] = arr[0];
    arr[0] = tmp;
    reverse_array(arr + 1, size - 2);
}
int main()
{
    int num;
    cout << "Enter the size of array:";
    cin >> num;
    double *arr = new double[num];
    num = fill_array(arr, num);
    cout << "The origin array is: ";
    show_array(arr, num);
    cout << "The reversed array is: ";
    reverse_array(arr, num);
    show_array(arr, num);
    delete[] arr;
}
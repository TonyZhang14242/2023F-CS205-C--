#include <iostream>
#include <cstring>
using namespace std;

template <typename T>
T maxn(T arr[], int num){
    if (num <= 0)
    {
        cout << "Invalid input!\n";
        return -1;
    }
    
    T max_element = arr[0];
    for (int i = 0; i < num; i++)
    {
        max_element = max(max_element, arr[i]);
    }
    return max_element;
}

template<> char* maxn(char* arr[], int num){
    if (num <= 0)
    {
        cout << "Invalid input!\n";
        return nullptr;
    }
    char* max_element = arr[0];
    for (int i = 0; i < num; i++)
    {
        if (strlen(max_element) < strlen(arr[i]))
        {
            max_element = arr[i];
        }
    }
    return max_element;
}

int main(){
    int arr1[] = {1,2,3,4,5};
    double arr2[] = {1.1,2.7,-3.5,-2};
    char *arr3[] = {"this","no body","morning","birds","sky"};
    cout << "Max int is: " << maxn(arr1, 5) << endl;
    cout << "Max double is: " << maxn(arr2, 4) << endl;
    cout << "Longest string is: " << maxn(arr3, 5) << endl;
    return 0;
}




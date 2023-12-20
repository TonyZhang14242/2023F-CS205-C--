#include <iostream>

using namespace std;
struct CandyBar{
    char name[20];
    float weight;
    int calories;
}candies[3];

int main(){
    cout << "Please input three candybars' information:" << endl;
    for (int  i = 0; i < 3; i++)
    {
        cout << "Enter brand name of a Candybar: ";
        cin.getline(candies[i].name, 20);
        cout << "Enter weight of the Candybar: ";
        cin >> candies[i].weight;
        cout << "Enter calories (an integer value) of the Candybar: ";
        cin >> candies[i].calories;
        cin.get();
    }

    cout << "------------------------------------------------------------" << endl;
    cout << "Display the Candybar array contents\n";
    for (int i = 0; i < 3; i++)
    {
        cout << "Brand name: " << candies[i].name << "\nWeight: " << candies[i].weight << "\nCalories: " << candies[i].calories << endl;
    }

    float maxperweightcal = 0;
    int maxidx = 0;
    for (int i = 0; i < 3; i++)
    {
        if (candies[i].calories/candies[i].weight > maxperweightcal)
        {
            maxperweightcal = candies[i].calories/candies[i].weight;
            maxidx = i;
        }
    }
    cout << "------------------------------------------------------------\n";
    cout << "The greatest calories per weight is:\n";
    cout << "Brand name: " << candies[maxidx].name << endl;
    cout << "Calories per weight: " << maxperweightcal << endl;
    
    return 0;
    
}
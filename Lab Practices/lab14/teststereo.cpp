#include "stereo.hpp"
using namespace std;

int main(){
    CCube a_cube(4., 5., 6.);
    CSphere c_sphere(7.9);
    CStereoShape* p = &a_cube;
    p->show();
    p = &c_sphere;
    p->show();
    cout << CStereoShape::GetNumOfObject() << " objects are created.\n";
    return 0;
}
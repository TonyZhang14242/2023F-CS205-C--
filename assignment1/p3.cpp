#include <iostream>
#include <cmath>
#include <string.h>
#include <algorithm>

using namespace std;

const int MAX_TRIANGLES = 100;

struct Triangle {
    long double A,B,C;
};

struct TriangleDictionary {
    Triangle triangles[MAX_TRIANGLES];
    int triangle_count;
};

void addTriangle(TriangleDictionary* dict, double side1, double side2, double angle) {
        // To be completed
        if (side1 <=0 || side2 <= 0 || angle <= 0 || angle >= 180)
        {
            return;
        }
        
        long double A = angle;
        long double side3 = sqrtl(side1* side1 +side2 * side2-2*side1*side2*cosl(angle/180*M_PI));
        long double B = acosl(((side1*side1)+(side3*side3)-(side2*side2))/(2*side1*side3))/M_PI*180;
        long double C = acosl(((side2*side2)+(side3*side3)-(side1*side1))/(2*side2*side3))/M_PI*180;
        Triangle tri;
        tri.A = A;
        tri.B = B;
        tri.C = C;
        dict->triangles[dict->triangle_count] = tri;
        dict->triangle_count++;
}

bool isSimilar(const Triangle& triangle, double side1, double side2, double side3) {
        
        long double A = acosl(((side1*side1)+(side2*side2)-(side3*side3))/(2*side1*side2))/M_PI*180;
        long double B = acosl(((side1*side1)+(side3*side3)-(side2*side2))/(2*side1*side3))/M_PI*180;
        long double C = acosl(((side2*side2)+(side3*side3)-(side1*side1))/(2*side2*side3))/M_PI*180;
        long double arr[3];
        arr[0] = A;
        arr[1] = B;
        arr[2] = C;
        sort(arr,arr+3);
        
        long double cmp_arr[3];
        cmp_arr[0] = triangle.A;
        cmp_arr[1] = triangle.B;
        cmp_arr[2] = triangle.C;
        
        sort(cmp_arr,cmp_arr+3);
        
        if (fabsl(arr[0] - cmp_arr[0])<=1 && fabsl(arr[1] - cmp_arr[1])<=1 && fabs(arr[2] - cmp_arr[2])<=1)
        {
            return true;
        }
        
        return false;
}

bool searchSimilar(TriangleDictionary* dict, double side1, double side2, double angle) {
    double side3 = sqrt(side1 * side1 + side2 * side2 - 2 * side1 * side2 * cos(angle * M_PI / 180));
    for (int i = 0; i < dict->triangle_count; ++i) {
        if (isSimilar(dict->triangles[i], side1, side2, side3)) {
            return true;
        }
    }
    return false;
}

int main() {
    int n;
    // printf("Enter the number of operations (n): ");
    scanf("%d", &n);

    char** actions = (char**)malloc(n * sizeof(char*));
    double** parameters = (double**)malloc(n * sizeof(double*));

    for (int i = 0; i < n; ++i) {
        actions[i] = (char*)malloc(15 * sizeof(char));
        parameters[i] = (double*)malloc(3 * sizeof(double));
    }

    for (int i = 0; i < n; ++i) {
        // printf("Enter operation #%d: ", i + 1);
        scanf("%s", actions[i]);
        if (strcmp(actions[i], "addTriangle") == 0 || strcmp(actions[i], "searchSimilar") == 0) {
            scanf("%lf %lf %lf", &parameters[i][0], &parameters[i][1], &parameters[i][2]);
        }
    }

    TriangleDictionary triangleDictionary;
    triangleDictionary.triangle_count = 0;

    for (int i = 0; i < n; ++i) {
        if (strcmp(actions[i], "TriangleDictionary") == 0) {
            // Do nothing
        } else if (strcmp(actions[i], "addTriangle") == 0) {
            addTriangle(&triangleDictionary, parameters[i][0], parameters[i][1], parameters[i][2]);
        } else if (strcmp(actions[i], "searchSimilar") == 0) {
            int result = searchSimilar(&triangleDictionary, parameters[i][0], parameters[i][1], parameters[i][2]);
            printf(result ? "true\n" : "false\n");
        }
    }
}
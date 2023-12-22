#pragma once
#include <iostream>
#include <iomanip>
#define PI (double)3.1415926
class CStereoShape
{
private:
    static int numberOfObject;

public:
    CStereoShape() { numberOfObject++; }
    virtual ~CStereoShape() { numberOfObject--; }
    virtual double GetArea()
    {
        std::cout << "CStereoShape::GetArea()" << std::endl;
        return 0.0;
    }
    virtual double GetVolume()
    {
        std::cout << "CStereoShape::GetVolume()" << std::endl;
        return 0.0;
    }
    virtual void show()
    {
        std::cout << "CStereoShape::show()" << std::endl;
    }
    static int GetNumOfObject()
    {
        return numberOfObject;
    }
};

int CStereoShape::numberOfObject = 0;

class CCube : public CStereoShape
{
private:
    double length;
    double width;
    double height;

public:
    CCube(): length(1), width(1), height(1){}
    ~CCube() {}
    CCube(double l, double w, double h) : length(l), width(w), height(h) {}
    CCube(const CCube &c)
    {
        length = c.length;
        width = c.width;
        height = c.height;
    }
    double GetArea() override
    {
        return 2 * (length * width + length * height + width * height);
    }
    double GetVolume() override
    {
        return length * width * height;
    }
    void show() override
    {
        std::cout << "Cube:\n";
        std::cout << "length: " << length << std::setw(10) << "width: " << width << std::setw(10) << "height:" << height << "\n";
        std::cout << "area: " << GetArea() << std::setw(11) << "volume: " << GetVolume() << "\n";
    }
};

class CSphere : public CStereoShape
{
private:
    double radius;

public:
    CSphere(): radius(1){}
    ~CSphere() {}
    CSphere(double r) : radius(r) {}
    CSphere(const CSphere &c)
    {
        radius = c.radius;
    }
    double GetArea() override
    {
        return 4 * PI * radius * radius;
    }
    double GetVolume() override
    {
        return (4. / 3) * PI * radius * radius * radius;
    }
    void show() override
    {
        std::cout.setf(std::ios_base::fixed);
        std::cout << "Sphere:\n";
        std::cout << std::setprecision(1) << "radius: " << radius << "\n";
        std::cout << std::setprecision(2) << "area: " << GetArea() << std::setw(10) << "volume: " << GetVolume() << "\n";
    }
};
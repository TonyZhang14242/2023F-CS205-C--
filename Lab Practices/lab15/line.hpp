#pragma once
#include <iostream>
#include <cmath>
class Point
{
private:
    double x, y;

public:
    Point(double newX, double newY);
    double getX() const;
    double getY() const;
};

Point::Point(double newX = 1, double newY = -1) : x(newX), y(newY) {}
double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}

class Line
{
private:
    Point p1, p2;
    double distance;

public:
    Line(Point xp1, Point xp2);
    Line(Line &q);
    double getDistance() const;
};

Line::Line(Point xp1, Point xp2) : p1(xp1), p2(xp2) {}
Line::Line(Line &q)
{
    std::cout << "calling the copy constructor of Line\n";
    p1 = q.p1;
    p2 = q.p2;
    distance = q.getDistance();
}

double Line::getDistance() const
{
    return std::sqrt(std::pow(std::abs(p1.getX() - p2.getX()), 2) + std::pow(std::abs(p1.getY() - p2.getY()), 2));
}

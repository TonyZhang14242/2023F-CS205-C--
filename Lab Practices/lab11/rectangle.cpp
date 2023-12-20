#include "ractangle.h"
#include <iostream>
#include <iomanip>
#include <sstream>
int Rectangle::countOfObject = 0;
double Rectangle::getWidth(){
    return this->width;
}
double Rectangle::getHeight(){
    return this->height;
}

void Rectangle::setWidth(double w){
    this->width = w;
}
void Rectangle::setHeight(double h){
    this->height = h;
}
double Rectangle::getArea(){
    return this->width * this->height;
}
double Rectangle::getPerimeter(){
    return (this->width + this->height)*2;
}
void Rectangle::display(){
    std::cout << "-------------------------\n";
    std::cout << setiosflags (std::ios::right)<< std::setw(15) << "Width: " <<   width << std::endl;
    std::cout << setiosflags (std::ios::right) <<  std::setw(15) <<"Height: " << height << std::endl;
    std::cout << setiosflags (std::ios::right) << std::setw(15) <<"Perimeter: " <<   getPerimeter() << std::endl;
    std::cout <<setiosflags (std::ios::right) << std::setw(15) <<"Area: " <<   getArea() << std::endl;
}

int Rectangle::getCount(){
    return countOfObject;
}


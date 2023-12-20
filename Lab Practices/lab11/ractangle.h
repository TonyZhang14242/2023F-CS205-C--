#pragma once
class Rectangle{
    private:
        double width;
        double height;
        static int countOfObject;
    public:
        Rectangle():width(1),height(1){countOfObject++;}
        Rectangle(double w, double h):width(w),height(h){countOfObject++;}
        double getWidth();
        double getHeight();
        void setWidth(double w);
        void setHeight(double h);
        double getArea();
        double getPerimeter();
        void display();
        static int getCount();
        
};


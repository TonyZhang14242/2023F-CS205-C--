#include <iostream>
#pragma once
class Matrix
{
private:
    int row;
    int col;
    float *data;
    int* ref_cnt;
public:
    Matrix(int ro, int co) : row(ro), col(co) {data = new float[row * col]; ref_cnt = new int(1);}
    ~Matrix()
    {
        (*ref_cnt)--;
        if (*ref_cnt == 0)
        {
            delete[] data;
            delete ref_cnt;
        }
    }
    Matrix(const Matrix& mat);
    Matrix operator+(const Matrix &mat);
    Matrix &operator=(const Matrix &mat);
    void setElement(int row, int col, float value);
    int getRef(){
        return *ref_cnt;
    }
    friend std::ostream &operator<<(std::ostream &ost, const Matrix &mat);
};
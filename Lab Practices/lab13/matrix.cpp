#include "matrix.h"
//must using SOFT copy in this class
Matrix::Matrix(const Matrix &mat)
{
    (*mat.ref_cnt)++;
    ref_cnt = mat.ref_cnt;
    data = mat.data;
    row = mat.row;
    col = mat.col;
}
Matrix Matrix::operator+(const Matrix &mat)
{
    if (row != mat.row || col != mat.col)
    {
        std::abort();
    }
    Matrix tmp(mat.row, mat.col);
    for (int i = 0; i < mat.row; i++)
    {
        for (int j = 0; j < mat.col; j++)
        {
            tmp.data[i * mat.col + j] = data[i * mat.col + j] + mat.data[i * mat.col + j];
        }
    }
    return tmp;
}
Matrix &Matrix::operator=(const Matrix &mat)
{
    if (this == &mat)
    {
        return *this;
    }
    (*ref_cnt)--;
    if (*ref_cnt == 0)
    {
        delete data;
        delete ref_cnt;
    }
    (*mat.ref_cnt)++;
    ref_cnt = mat.ref_cnt;
    data = mat.data;
    row = mat.row;
    col = mat.col;
    return *this;
}
void Matrix::setElement(int row, int col, float value)
{
    data[row * this->col + col] = value;
}
std::ostream &operator<<(std::ostream &ost, const Matrix &mat)
{
    for (int i = 0; i < mat.row; i++)
    {
        for (int j = 0; j < mat.col; j++)
        {
            ost << mat.data[i * mat.col + j] << " ";
        }
        ost << "\n";
    }
    return ost;
}
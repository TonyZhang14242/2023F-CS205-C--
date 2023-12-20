// PREPEND BEGIN
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

struct Data
{
    int *entry;
    size_t row, col;
    size_t ref_cnt;

    Data(size_t row, size_t col) : row(row), col(col), ref_cnt(0)
    {
        entry = new int[row * col]{};
    }

    ~Data()
    {
        delete[] entry;
    }
};

struct Matrix
{
    Data *data;      // the ptr pointing to the entries
    size_t start;    // the starting index of ROI
    size_t row, col; // the shape of ROI

    Matrix() : data(nullptr), start(0), row(0), col(0) {}

    ~Matrix()
    {
        if (!data)
            return;
        if (!--data->ref_cnt)
            delete data;
    }
};

void print_matrix(Matrix &mat)
{
    for (size_t r = 0; r < mat.row; r++)
    {
        size_t head = mat.start + r * mat.data->col;
        for (size_t c = 0; c < mat.col; c++)
            cout << mat.data->entry[head + c] << ' ';
        cout << '\n';
    }
    cout << endl;
}
// PREPEND END

// TEMPLATE BEGIN
void unload_data(Matrix &mat)
{
    // TODO
    // Noted that `mat.data` could be `nullptr` here
    if (mat.data)
    {
        if (--mat.data->ref_cnt == 0)
        {
            delete mat.data;
        }
        mat.data = nullptr;
        mat.start = 0;
        mat.row = 0;
        mat.col = 0;
    }
}

void load_data(Matrix &mat, Data *data, size_t start, size_t row, size_t col)
{
    // TODO
    unload_data(mat);
    mat.data = data;
    mat.start = start;
    mat.row = row;
    mat.col = col;
    data->ref_cnt++;
}

void shallow_copy(Matrix &dest, Matrix &src)
{
    // TODO
    unload_data(dest);
    dest.data = src.data;
    dest.start = src.start;
    dest.row = src.row;
    dest.col = src.col;
    if (src.data)
        src.data->ref_cnt++;
}

void deep_copy(Matrix &dest, Matrix &src)
{
    // TODO
    unload_data(dest);
    dest.row = src.row;
    dest.col = src.col;
    dest.data = new Data(src.row, src.col);
    dest.data->ref_cnt = 1;
    size_t head = src.start;
    for (size_t r = 0; r < src.row; r++)
    {
        for (size_t c = 0; c < src.col; c++)
        {
            dest.data->entry[r * dest.col + c] = src.data->entry[head + c];
        }
        head += src.data->col;
    }
}

bool equal_matrix(Matrix &a, Matrix &b)
{
    // TODO
    if (a.row != b.row || a.col != b.col)
        return false;

    size_t headA = a.start;
    size_t headB = b.start;
    for (size_t r = 0; r < a.row; r++)
    {
        for (size_t c = 0; c < a.col; c++)
        {
            if (a.data->entry[headA + c] != b.data->entry[headB + c])
                return false;
        }
        headA += a.data->col;
        headB += b.data->col;
    }
    return true;
}

void add_matrix(Matrix &dest, Matrix &a, Matrix &b)
{
    // TODO
    unload_data(dest);
    if (a.row != b.row || a.col != b.col)
        return;

    dest.data = new Data(a.row, a.col);
    dest.data->ref_cnt = 1;
    dest.row = a.row;
    dest.col = a.col;

    size_t headA = a.start;
    size_t headB = b.start;
    for (size_t r = 0; r < a.row; r++)
    {
        for (size_t c = 0; c < a.col; c++)
        {
            dest.data->entry[r * dest.col + c] = a.data->entry[headA + c] + b.data->entry[headB + c];
        }
        headA += a.data->col;
        headB += b.data->col;
    }
}

void minus_matrix(Matrix &dest, Matrix &a, Matrix &b)
{
    // TODO
    unload_data(dest);
    if (a.row != b.row || a.col != b.col)
        return;

    dest.data = new Data(a.row, a.col);
    dest.data->ref_cnt = 1;
    dest.row = a.row;
    dest.col = a.col;

    size_t headA = a.start;
    size_t headB = b.start;
    for (size_t r = 0; r < a.row; r++)
    {
        for (size_t c = 0; c < a.col; c++)
        {
            dest.data->entry[r * dest.col + c] = a.data->entry[headA + c] - b.data->entry[headB + c];
        }
        headA += a.data->col;
        headB += b.data->col;
    }
}

void multiply_matrix(Matrix &dest, Matrix &a, Matrix &b)
{
    // TODO
    if (a.col != b.row)
        return;

    unload_data(dest);

    dest.data = new Data(a.row, b.col);
    dest.data->ref_cnt = 1;
    dest.row = a.row;
    dest.col = b.col;

    for (size_t r = 0; r < a.row; r++)
    {
        for (size_t c = 0; c < b.col; c++)
        {
            int sum = 0;
            for (size_t k = 0; k < a.col; k++)
            {
                sum += a.data->entry[a.start + r * a.data->col + k] * b.data->entry[b.start + k * b.data->col + c];
            }
            dest.data->entry[r * dest.col + c] = sum;
        }
    }
}
// TEMPLATE END

// APPEND BEGIN
void test()
{
    // Sample code on how to use your library
    Data *da = new Data(3, 2), *db = new Data(2, 3);
    for (size_t i = 0; i < 6; i++)
        da->entry[i] = db->entry[i] = i;

    Matrix a, b, c;
    load_data(a, da, 0, 3, 2); // the ROI is the whole matrix
    load_data(b, db, 0, 2, 3);
    print_matrix(a);
    /*
        0 1
        2 3
        4 5
    */
    print_matrix(b);
    /*
        0 1 2
        3 4 5
    */

    multiply_matrix(c, a, b);
    print_matrix(c);
    /*
        3 4 5
        9 14 19
        15 24 33
    */

    Matrix d, e, f;
    shallow_copy(d, c); // d, c -> (the same) data
    deep_copy(e, c);    // e->data have the exactly same content with c->ROI(data) with e.data.shape = c.ROI.shape
                        // but their addresses are different and ref_cnts possibly differ
    load_data(f, c.data, 1, 3, 2);
    print_matrix(f);
    /*
        4 5
        14 19
        24 33
    */
    add_matrix(b, a, f); // notice that the original b.data->ref_cnt becomes 0 and should be deleted
    print_matrix(b);
    /*
        4 6
        16 22
        28 38
    */

    cout << a.data->ref_cnt << ' ' << b.data->ref_cnt << ' '
         << c.data->ref_cnt << ' ' << d.data->ref_cnt << ' '
         << e.data->ref_cnt << ' ' << f.data->ref_cnt << endl;
    /*
        1 1 3 3 1 3
    */
}

int main()
{
    test();
    return 0;
}
// APPEND END
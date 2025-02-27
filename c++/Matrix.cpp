
#include <iostream>
#include <concepts>
#include <string>
using namespace std;

template<class type, int row, int column> 
class Matrix
{
    template<class t, int m, int n> 
    friend ostream& operator<<(ostream&, Matrix<t, m, n>);

    public:

    Matrix();
    Matrix(type);
    // Matrix(type[row][column]);
    Matrix(const Matrix&);
    ~Matrix();

    Matrix& operator=(Matrix);

    Matrix& operator+=(const Matrix&);
    Matrix& operator+=(int);
    Matrix operator+(Matrix);
    Matrix operator+(int);

    Matrix& operator-=(const Matrix&);
    Matrix& operator-=(int);
    Matrix operator-(Matrix);
    Matrix operator-(int);

    Matrix& operator*=(const Matrix&); // завтра днем потестить надо
    Matrix& operator*=(int);
    Matrix operator*(Matrix);
    Matrix operator*(int);

    Matrix& operator/=(int);
    Matrix operator/(int);

    Matrix& operator++();
    Matrix operator++(int);

    Matrix& operator--();
    Matrix operator--(int);

    Matrix<type, row-1, column-1> minor(int, int) const;
    int det() const; // дописать надо для матриц порядка выше 2
    Matrix transposition() const;
    void set(type, int, int);
    pair<type, type> get_size();

    type* operator[](int);
    type* operator[](int) const;
    type& at(int, int);

    class UniversalError;

    protected:
    const int m = row;
    const int n = column;
    type** matrix;
};

template<class type, int row, int column>
Matrix<type, row, column>::Matrix():
Matrix(0)
{}

template<class type, int row, int column>
Matrix<type, row, column>::Matrix(type value):
matrix(new type*[row])
{
    for (int i = 0; i<row; ++i)
    {
        matrix[i] = new type[column];
        for (int j = 0; j<column; ++j)
        { matrix[i][j] = (i == j) ? value : 0; }
    }
}

template<class type, int row, int column>
Matrix<type, row, column>::Matrix(const Matrix& another):
matrix(new type*[row])
{
    for (int i = 0; i<row; ++i)
    {
        matrix[i] = new type[column];
        for (int j = 0; j<column; ++j)
        { matrix[i][j] = another[i][j]; }
    }
}

template<class type, int row, int column>
Matrix<type, row, column>::~Matrix()
{
    for (int i = m-1; i >= 0; --i)
    { delete[] matrix[i]; }

    delete[] matrix;
}

template<class type, int row, int column>
Matrix<type, row, column>& Matrix<type, row, column>::operator=(Matrix another)
{
    for (int i = 0; i<row; ++i)
    {
        matrix[i] = new type[column];
        for (int j = 0; j<column; ++j)
        { matrix[i][j] = another[i][j]; }
    }

    return *this;
}

template<class type, int row, int column>
Matrix<type, row, column>& Matrix<type, row, column>::operator+=(const Matrix& another)
{
    for (int i = 0; i<row; ++i)
    {
        for (int j = 0; j<column; ++j)
        { matrix[i][j] += another[i][j]; }
    }

    return *this;
}

template<class type, int row, int column>
Matrix<type, row, column>& Matrix<type, row, column>::operator+=(int num)
{ return *this += Matrix<type, row, column>(num); }

template<class type, int row, int column>
Matrix<type, row, column> Matrix<type, row, column>::operator+(Matrix another)
{
    Matrix copy {*this};
    copy += another;
    return copy;
}

template<class type, int row, int column>
Matrix<type, row, column> Matrix<type, row, column>::operator+(int num)
{ return *this + Matrix<type, row, column>(num); }

template<class type, int row, int column>
Matrix<type, row, column>& Matrix<type, row, column>::operator-=(const Matrix& another)
{ return *this += -1 * another; }

template<class type, int row, int column>
Matrix<type, row, column>& Matrix<type, row, column>::operator-=(int num)
{ return *this -= Matrix<type, row, column>(num); }

template<class type, int row, int column>
Matrix<type, row, column> Matrix<type, row, column>::operator-(Matrix another)
{
    Matrix copy {*this};
    copy -= another;
    return copy;
}

template<class type, int row, int column>
Matrix<type, row, column> Matrix<type, row, column>::operator-(int num)
{ return *this - Matrix<type, row, column>(num); }

template<class type, int row, int column>
Matrix<type, row, column>& Matrix<type, row, column>::operator*=(const Matrix& another)
{
    Matrix<type, row, column> tmp;
    for (int i = 0; i<row; ++i)
    {
        for (int j = 0; j<column; ++j)
        {
            for (int k = 0; k<row; ++k)
            { tmp[i][j] += matrix[i][k]*another[k][j]; }
        }
    }

    return *this = tmp;   
}

template<class type, int row, int column>
Matrix<type, row, column>& Matrix<type, row, column>::operator*=(int num)
{ 
    for (int i = 0; i<row; ++i)
    {
        for (int j = 0; j<column; ++j)
        { matrix[i][j] *= num; }
    }

    return *this;
}

template<class type, int row, int column>
Matrix<type, row, column>& Matrix<type, row, column>::operator/=(int num)
{ 
    for (int i = 0; i<row; ++i)
    {
        for (int j = 0; j<column; ++j)
        { matrix[i][j] /= num; }
    }

    return *this;
}

template<class type, int row, int column>
Matrix<type, row, column> Matrix<type, row, column>::operator/(int num)
{
    Matrix tmp {*this};
    tmp /= num;
    return tmp;
}

template<class type, int row, int column>
Matrix<type, row, column> Matrix<type, row, column>::operator*(Matrix another)
{
    Matrix copy {*this};
    copy *= another;
    return copy;
}

template<class type, int row, int column>
Matrix<type, row, column> Matrix<type, row, column>::operator*(int num)
{
    Matrix copy {*this};
    copy *= num;
    return copy;
}

template<class type, int row, int column>
Matrix<type, row, column>& Matrix<type, row, column>::operator++()
{ return *this += 1; }

template<class type, int row, int column>
Matrix<type, row, column> Matrix<type, row, column>::operator++(int)
{
    Matrix copy {*this};
    *this += 1;
    return copy;
}

template<class type, int row, int column>
Matrix<type, row, column>& Matrix<type, row, column>::operator--()
{ return *this -= 1; }

template<class type, int row, int column>
Matrix<type, row, column> Matrix<type, row, column>::operator--(int)
{
    Matrix copy {*this};
    *this -= 1;
    return copy;
}

template<class type, int row, int column>
Matrix<type, row-1, column-1> Matrix<type, row, column>::minor(int in, int jn) const
{
    if (row == 1 | column == 1) throw UniversalError{"too small matrix"};

    Matrix<type, row-1, column-1> tmp;
    for (int i = 0; i<row; ++i)
    {
        for (int j = 0; j<column; ++j)
        {
            if ( i == in | j == jn ) continue;
            tmp[i-(i>in)][j-(j>jn)] = matrix[i][j];
        }
    }

    return tmp;
}

template<class type, int row, int column>
int Matrix<type, row, column>::det() const
{
    int i, j, d, k;

    j = 0; d = 0;
    k = 1; //(-1) в степени i

    if (row < 1) return d;
    if (row == 1) 
    {
        d = matrix[0][0];
        return(d);
    }
    if (row == 2) 
    {
        d = (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);
        return(d);
    }
    if (row > 2) {
        for (i = 0; i < m; i++) 
        {
            throw UniversalError{"мне лень прописывать пока что"};
            // d = d + k * matrix[i][0] * (minor(i, 0).det());
            // тут помогут концепты, если они заработают
            k = -k;
        }
    }

    return(d);
}

template<class type, int row, int column>
Matrix<type, row, column> Matrix<type, row, column>::transposition() const
{
    Matrix<type, column, row> tmp;
    for (int i = 0; i<row; ++i)
    {
        for (int j = 0; j<column; ++j)
        { tmp[j][i] = matrix[i][j]; }
    }

    return tmp;
}

template<class type, int row, int column>
void Matrix<type, row, column>::set(type value, int i, int j)
{ matrix[i][j] = value; }

template<class type, int row, int column>
pair<type, type> Matrix<type, row, column>::get_size()
{ return pair(m, n); }

template<class type, int row, int column>
type* Matrix<type, row, column>::operator[](int i)
{ return matrix[i]; }

template<class type, int row, int column>
type* Matrix<type, row, column>::operator[](int i) const
{ return matrix[i]; }

template<class type, int row, int column>
type& Matrix<type, row, column>::at(int i, int j)
{ return matrix[i][j]; }

template<class type, int row, int column>
class Matrix<type, row, column>::UniversalError
{
    // абалдеть понты
    // собственный класс для ошибок
    
    public:
    UniversalError(): message(nullptr) {}
    UniversalError(const char* message): message(message) {}

    string getMessage() const { return message; }

    protected:
    string message;
};

template<class type, int row, int column>
ostream& operator<<(ostream& out, Matrix<type, row, column> another)
{
    for (int i = 0; i<row; ++i)
    { 
        for (int j = 0; j<column; ++j)
        { out << another[i][j] << ' '; }

        out << endl;
    }

    return out;
}

template<class type, int row, int column>
istream& operator>>(istream& in, Matrix<type, row, column>& another)
{
    type tmp;
    for (int i = 0; i<row; ++i)
    {
        for (int j = 0; j<column; ++j)
        {
            in >> tmp;
            another[i][j] = tmp; 
        }
    }

    return in;
}
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Matrix
{
    friend ostream& operator<< (ostream&, Matrix);
    friend Matrix& operator++(Matrix&);
    friend Matrix& operator--(Matrix&);

    public:

    Matrix();
    Matrix(int, int, int);
    Matrix(vector<vector<int>>&);
    Matrix(Matrix&);
    ~Matrix();

    int det();
    Matrix minor(int, int);
    Matrix trans();
    Matrix adj();
    Matrix invert(int, int);
    int get_n();

    Matrix operator+ (Matrix&);
    Matrix operator- (Matrix&);
    Matrix operator+ (int);
    Matrix operator- (int);

    Matrix& operator+= (Matrix&);
    Matrix& operator-= (Matrix&);
    Matrix& operator+= (int);
    Matrix& operator-= (int);

    Matrix operator* (Matrix&);
    Matrix operator* (int);
    Matrix operator% (int);

    vector<int>& operator[] (int);

    protected:

    int m, n;
    vector<vector<int>> matr;
};

Matrix::Matrix():
m(0), n(0)
{}

Matrix::Matrix(int m, int n, int c = 0):
m(m), n(n)
{
    for (int i = 0; i<m; i++)
    {
        matr.push_back(vector<int>());
        for (int j = 0; j<n; j++)
        {
            if (i == j) matr[matr.size()-1].push_back(c);
            else matr[matr.size()-1].push_back(0);
        }
    } 
}

Matrix::Matrix(vector<vector<int>>& key):
matr(key) 
{
    m = matr.size();
    n = matr[0].size();
}

Matrix::Matrix(Matrix& second):
m(second.m), 
n(second.n),
matr(second.matr)
{}

Matrix::~Matrix()
{
    while (!matr.empty())
    { matr.pop_back(); }

    m = 0;
    n = 0;
}

int Matrix::det()
{
    int i, j, d, k;

    j = 0; d = 0;
    k = 1; //(-1) в степени i

    if (m < 1) return d;
    if (m == 1) 
    {
        d = matr[0][0];
        return(d);
    }
    if (m == 2) 
    {
        d = (matr[0][0] * matr[1][1]) - (matr[1][0] * matr[0][1]);
        return(d);
    }
    if (m > 2) {
        for (i = 0; i < m; i++) 
        {
            d = d + k * matr[i][0] * (*this).minor(i, 0).det();
            k = -k;
        }
    }

    return(d);
}

Matrix Matrix::minor(int i, int j)
{

    Matrix copy {(*this)};
    
    copy.matr.erase(copy.matr.cbegin()+i);
    copy.m--; copy.n--;

    for(int a = 0; a<this->m; a++)
    {
        copy[a].erase(copy[a].cbegin()+j);
    }

    return copy;
}

Matrix Matrix::trans()
{
    int fm = this->m;
    int fn = this->n;
    Matrix result {fm, fn};

    for (int i = 0; i<fm; i++)
    {
        for (int j = 0; j<fn; j++)
        {
            result[i][j] = (*this)[j][i];
        }
    }

    return result;
}

Matrix Matrix::adj()
{
    if (m != n) return Matrix (0, 0, 0);

    Matrix result {m, n};
    int k = 1;

    for (int i = 0; i<m; i++)
    {
        for (int j = 0; j<n; j++)
        {
            result[i][j] = k*(*this).minor(i, j).det();
            k = -k;
        }
    }

    return result;
}

Matrix Matrix::invert(int size, int rd)
{
    Matrix adj_key 
    {
        (
            (
                (
                    (*this).adj()%size
                )*rd
            )%size
        ).trans()
    };

    for (int i = 0; i<m; i++)
    {
        for (int j = 0; j<n; j++)
        {
            if (adj_key[i][j] < 0) 
            adj_key[i][j] += size; 
        }
    }

    return adj_key;
}

int Matrix::get_n()
{ return n; }

Matrix Matrix::operator+(Matrix& second)
{
    int fm = this->m, sm = second.m;
    int fn = this->n, sn = second.n;

    Matrix result {fm, fn};

    if ((fm != sm) | (fn != sn)) 
    return result;

    for (int i = 0; i<fm; i++)
    {
        for (int j = 0; j<fn; j++)
        {
            result[i][j] = (*this)[i][j]+second[i][j];
        }
    }

    return result; 
}

Matrix Matrix::operator-(Matrix& second)
{
    Matrix new_one {second*-1};
    return *this + new_one;
}

Matrix Matrix::operator+(int c)
{
    Matrix second {m, n, c};
    return *this + second;
}

Matrix Matrix::operator-(int c)
{ return *this + (-c); }

Matrix& Matrix::operator+=(Matrix& second)
{
    matr = (*this + second).matr;
    return *this;
}

Matrix& Matrix::operator-=(Matrix& second)
{
    matr = (*this - second).matr;
    return *this;
}

Matrix& Matrix::operator+=(int c)
{
    matr = (*this + c).matr;
    return *this;
}

Matrix& Matrix::operator-=(int c)
{
    matr = (*this - c).matr;
    return *this;
}

Matrix Matrix::operator*(Matrix& second)
{
    int fm = this->m, sm = second.m;
    int fn = this->n, sn = second.n;

    Matrix result {fm, sn, 0};

    if (fn != sm) return result;

    int a;
    for (int i = 0; i<fm; i++)
    {
        for (int j = 0; j<sn; j++)
        {
            a = 0;
            for(int z = 0; z<fn; z++)
            {
                a += (*this)[i][z] * second[z][j];
            }
            result[i][j] = a;
        }
    }

    return result; 
}

Matrix Matrix::operator*(int c)
{
    int fm = this->m;
    int fn = this->n;
    Matrix result {fm, fn};

    for (int i = 0; i<fm; i++)
    {
        for (int j = 0; j<fn; j++)
        {
            result[i][j] = (*this)[i][j]*c;
        }
    }

    return result;
}

Matrix Matrix::operator%(int c)
{
    int fm = this->m;
    int fn = this->n;
    Matrix result {fm, fn};

    for (int i = 0; i<fm; i++)
    {
        for (int j = 0; j<fn; j++)
        {
            result[i][j] = (*this)[i][j]%c;
        }
    }

    return result;
}

vector<int>& Matrix::operator[](int c)
{ return matr[c]; }


ostream& operator<< (ostream& out, Matrix pups)
{
    vector<vector<int>> key = pups.matr;
    for(int i = 0; i<key.size(); i++)
    {
        for (int j = 0; j<key[i].size(); j++)
        {
            out << key[i][j] << ' ';
        }
        out << endl;
    }

    return out;
}

Matrix& operator++(Matrix& second)
{ return second += 1; }

Matrix& operator--(Matrix& second)
{ return second -= 1; }


// int main()
// {
//     Matrix boobs {3, 3, 9};
//     int deter = boobs.det();
//     Matrix new_one {(boobs.adj())};

//     cout << boobs.det() << endl;
//     cout << new_one;

//     return 0;
// }
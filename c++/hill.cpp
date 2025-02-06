#include <iostream>
#include <fstream>
#include <locale>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Matrix
{
    friend Matrix run(
        int fm, int fn, int sm, int sn, 
        Matrix& first, Matrix& second,
        int (*func)(int, int)
    );
    friend void print_m(Matrix& wubba);

    public:

    Matrix(int m, int n, int c);
    Matrix(vector<vector<int>>& key);
    ~Matrix();

    int det();
    Matrix minor(int i, int j);
    Matrix trans();
    Matrix adj();
    Matrix invert(int size, int rd);
    int get_n();

    Matrix operator+ (Matrix& second);
    Matrix operator* (Matrix& second);
    Matrix operator* (int number);
    Matrix operator% (int number);

    vector<int>& operator[] (int c);

    protected:

    int m, n;
    vector<vector<int>> matr;
};

Matrix::Matrix(int m, int n, int c = 0):
m(m), n(n)
{
    for (int i = 0; i<m; i++)
    {
        matr.push_back(vector<int>());
        for (int j = 0; j<n; j++)
        {
            matr[matr.size()-1].push_back(c);
        }
    } 
}

Matrix::Matrix(vector<vector<int>>& key):
matr(key) 
{
    m = matr.size();
    n = matr[0].size();
}

Matrix::~Matrix()
{
    while (!matr.empty())
    {matr.pop_back();}

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
{
    return n;
}

Matrix Matrix::operator+(Matrix& second)
{
    int fm = this->m, sm = second.m;
    int fn = this->n, sn = second.n;

    Matrix result 
    {
        run(
            fm, fn, sm, sn, 
            (*this), second,
            [] (int a, int b) {return a+b;}
        )
    };

    return result; 
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
{return matr[c];}



Matrix run(
    int fm, int fn, int sm, int sn, 
    Matrix& first, Matrix& second,
    int (*func)(int, int)
)
{
    Matrix result {fm, fn};

    if ((fm != sm) | (fn != sn)) 
    return result;

    for (int i = 0; i<fm; i++)
    {
        for (int j = 0; j<fn; j++)
        {
            result[i][j] = func(first[i][j], second[i][j]);
        }
    }

    return result; 
}

void fill_a(map<wstring, int>& alphabet, const char* name = "alphabet.txt") 
{
    wifstream in(name);
    if (!in.is_open())
    {
        cerr << "File is not open" << endl;
        return;
    }
    in.imbue(locale("en_US.UTF-8"));

    wstring letter;
    int number;

    while (1)
    {
        in >> number >> letter;
        if (number == -1) break;
        alphabet[letter] = number;
    }
    alphabet[wstring(1, ' ')] = alphabet[letter]+1;
}

void fill_k(vector<vector<int>>& key, const char* name = "key.txt")
{
    ifstream in(name);

    int number;
    int m, n;

    in >> m >> n;
    for (int i = 0; i<m; i++)
    {
        key.push_back(vector<int>());
        for (int j = 0; j<n; j++)
        {
            in >> number;
            key[key.size()-1].push_back(number);
        }
    }
}

void print_a(map<wstring, int>& alphabet)
{
    for (auto [key, value]: alphabet)
    wcout << key << ' ' << value << endl;
}

void print_k(vector<vector<int>>& key)
{
    for(int i = 0; i<key.size(); i++)
    {
        for (int j = 0; j<key[i].size(); j++)
        {
            cout << key[i][j] << ' ';
        }
        cout << endl;
    }
}

void print_m(Matrix& wubba)
{print_k(wubba.matr);}

int div_up(int x, int y)
{
    if (y > x) return 1;
    return (x + y - 1) / y;
}

Matrix to_matrix(
    wstring phrase, 
    map<wstring, int>& alphabet,
    int n = 1
)
{
    int m = div_up(phrase.length(), n);
    vector<vector<int>> result;
    vector<int> zaloop;

    while (phrase.length() != m*n) phrase += wstring(1, ' ');

    for (int i = 0; i<phrase.length(); i += n)
    {
        for (auto letter: phrase.substr(i, n))
        {
            zaloop.push_back(alphabet[wstring(1, letter)]);
        }
        result.push_back(zaloop);
        zaloop.erase(zaloop.cbegin(), zaloop.cend());
    }

    return Matrix (result);
}

wstring to_wstring(
    Matrix& cipher,
    map<int, wstring> alphabet
)
{
    wstring result;

    for(int i = 0; i<cipher.get_n(); i++)
    {
        for (auto number: cipher[i])
        {
            result += alphabet[number];
        }
    }

    return result;
}

map<int, wstring> reverse_a(map<wstring, int>& alphabet)
{
    map<int, wstring> result;
    for (auto [key, value]: alphabet)
    {result[value] = key;}
    return result;
}


wstring encode(
    wstring phrase, 
    Matrix& key, 
    map<wstring, int>& alphabet
)
{    
    Matrix cipher {to_matrix(phrase, alphabet, key.get_n())*key};
    cipher = cipher % alphabet.size();

    return to_wstring(cipher, reverse_a(alphabet));
}

int e_gcd(int a, int b)
{
    if (b == 0) return a, 1, 0;
    int gcd, x1, y1 = e_gcd(b, a % b);
    int x = y1;
    int y = x1 - (a / b) * y1;
    return gcd, x, y;
}

wstring decode(
    wstring phrase, 
    Matrix& key, 
    map<wstring, int>& alphabet
)
{
    Matrix text {to_matrix(phrase, alphabet, key.get_n())};
    int d = key.det();
    int rd;
    int gcd, x, y = e_gcd(d, alphabet.size());
    
    if (x > 0)
    {
        rd = x;
    }
    else 
    {
        if (d > 0) rd = alphabet.size()+x;
        else rd = -x;
    }

    Matrix adj_key {key.invert(alphabet.size(), rd)};
    Matrix cipher {text*adj_key};

    return to_wstring(cipher, reverse_a(alphabet));
}

int main()
{
    ios_base::sync_with_stdio(false);
    wcin.imbue(locale("en_US.UTF-8"));
    wcout.imbue(locale("en_US.UTF-8"));

    map<wstring, int> alphabet;
    fill_a(alphabet);
    // // print_a(alphabet);

    vector<vector<int>> test_one;
    fill_k(test_one);
    // // print_k(test_one);

    Matrix wubba {test_one};
    // Matrix rev {wubba.adj()};
    // print_m(wubba);
    // print(' ');
    // print_m(rev);
    // test_one.clear();
    // int determ {wubba.det()};
    // print_m(wubba);
    // print(determ);

    wstring str;
    getline(wcin, str);
    wstring cipher = encode(str, wubba, alphabet);

    wcout << cipher << endl;
    // wcout << decode(cipher, wubba, alphabet) << endl;

    return 0;
}

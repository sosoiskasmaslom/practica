#include <iostream>
#include <vector>
using namespace std;

class BigInt
{
    friend ostream& operator<<(ostream&, BigInt);

    public:

    BigInt();
    BigInt(int);
    BigInt(const string&);
    template<class Type> BigInt(const vector<Type>&, bool);
    BigInt(const BigInt&);

    BigInt& operator=(BigInt);
    BigInt& operator=(const string);

    size_t size() const;
    void nozero();

    short& operator[](int);
    short operator[](int) const;

    bool operator>(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;


    BigInt subtractAbs(BigInt) const;

    BigInt& operator+=(const BigInt&);
    BigInt& operator+=(int);
    BigInt operator+(BigInt);
    BigInt operator+(int);

    BigInt operator-(BigInt);
    BigInt operator-(int);
    BigInt& operator-=(const BigInt&);
    BigInt& operator-=(int);

    BigInt multiplicationfigure(short) const;
    BigInt multiplication10(int) const;

    BigInt& operator*=(const BigInt&);
    BigInt& operator*=(int);
    BigInt operator*(BigInt);
    BigInt operator*(int); 

    BigInt& operator++(); // ++c
    BigInt operator++(int); // c++

    BigInt& operator--(); // --c
    BigInt operator--(int); // c--

    protected:

    bool negative;
    vector<short> number;
};

BigInt::BigInt():
negative(0)
{}

BigInt::BigInt(int num):
negative(num<0)
{
    num = abs(num);
    do
    {
        number.push_back(num%10);
        num /= 10;
    } while (num);
}

BigInt::BigInt(const string& line):
negative(line[0] == '-')
{ 
    for (int i = negative; i<line.size(); ++i) 
    number.insert(number.cbegin(), line[i]-'0'); 
}

template<class Type> 
BigInt::BigInt(const vector<Type>& vec, bool flag):
negative(flag)
{ for (auto v: vec) number.insert(number.cbegin(), v); }

BigInt::BigInt(const BigInt& another):
negative(another.negative),
number(another.number)
{}

BigInt& BigInt::operator=(BigInt another)
{
    negative = another.negative;
    number = another.number;

    return *this;
}

BigInt& BigInt::operator=(const string line)
{ return *this = BigInt(line); }

size_t BigInt::size() const
{ return number.size(); }

void BigInt::nozero()
{
    int i = size();
    while (i > 1)
    {
        if (number[i-1]) break;
        --i;
    }

    number.resize(i);
}

short& BigInt::operator[](int i)
{ return number[i]; }

short BigInt::operator[](int i) const
{ return number[i]; }

bool BigInt::operator>(const BigInt& another) const
{
    if (negative^another.negative) return !negative;

    if (size() == another.size())
    {
        for (int i = size()-1; i >= 0; --i)
        {
            if (number[i] == another[i]) continue;    
            return number[i] > another[i];
        }
    }

    return size()>another.size();
}

bool BigInt::operator<(const BigInt& another) const
{ return another > *this; }

bool BigInt::operator==(const BigInt& another) const
{
    if (negative != another.negative) return 0;
    if (size() != another.size()) return 0;

    for (int i = 0; i<size(); ++i)
    { if (number[i] != another[i]) return 0; }

    return 1;
}

bool BigInt::operator!=(const BigInt& another) const
{ return !(*this == another); }

BigInt BigInt::subtractAbs(BigInt another) const
{
    for (int i = 0; i<size(); ++i)
    {
        another[i] -= (i < size()) ? number[i] : 0;

        if (another[i] < 0)
        {
            another[i] += 10;
            --another[i];
        }
    }

    return another;
}

BigInt& BigInt::operator+=(const BigInt& another)
{
    if (negative == another.negative)
    {
        for (int i = 0; i<max(size(), another.size()); ++i)
        {
            if (i < size()) number[i] += (i < another.size()) ? another[i] : 0;
            else number.push_back((i < another.size()) ? another[i] : 0);

            if (number[i] > 9)
            {
                number[i] -= 10;
                ++number[i];
            }
        }

        return *this;
    }

    else
    {
        if (BigInt(number, 0) < BigInt(another.number, 0))
        { return *this = subtractAbs(another); }
        else { return *this = another.subtractAbs(*this); }
    }

    return *this;
}

BigInt& BigInt::operator+=(int num)
{ return *this += BigInt(num); }

BigInt BigInt::operator+(BigInt another)
{
    BigInt copy = *this;
    copy += another;
    return copy;
}

BigInt BigInt::operator+(int num)
{ return *this + BigInt(num); }

BigInt BigInt::operator-(BigInt another)
{
    another.negative ^= 1;
    return another += *this;
}

BigInt BigInt::operator-(int num)
{ return *this - BigInt(num); }

BigInt& BigInt::operator-=(const BigInt& another)
{ return *this = *this - another; }

BigInt& BigInt::operator-=(int num)
{ return *this = *this - BigInt(num); }

BigInt& BigInt::operator*=(const BigInt& another)
{
    BigInt result;
    result.number.resize(size() + another.size(), 0);
    result.negative = negative ^ another.negative;

    for (int i = 0; i < size(); ++i)
    {
        for (int j = 0; j < another.size(); ++j)
        {
            result.number[i + j] += number[i] * another[j];
            if (result.number[i + j] > 9)
            {
                result.number[i + j + 1] += result.number[i + j] / 10;
                result.number[i + j] %= 10;
            }
        }
    }

    return *this = result;
}

BigInt& BigInt::operator*=(int num)
{ return *this *= BigInt(num); }

BigInt BigInt::operator*(BigInt another)
{
    BigInt copy = *this;
    copy *= another;
    return copy;
}

BigInt BigInt::operator*(int num)
{ return *this * BigInt(num); }

BigInt& BigInt::operator++() // ++c
{ return *this += 1; }

BigInt BigInt::operator++(int) // c++
{
    BigInt copy = *this;
    *this += 1;
    return copy;
}

BigInt& BigInt::operator--() // --c
{ return *this -= 1; }

BigInt BigInt::operator--(int) // c--
{
    BigInt copy = *this;
    *this -= 1;
    return copy;
}

ostream& operator<<(ostream& out, BigInt another)
{
    another.nozero();
    if (another.negative) out << '-';
    for (int i = another.size(); i>0; --i)
    { out << another[i-1]; }

    return out;
}

istream& operator>>(istream& in, BigInt& another)
{
    string tmp;
    in >> tmp;
    another = BigInt(tmp);

    return in;
}

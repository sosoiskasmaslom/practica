
#include <iostream>
#include <vector>
using namespace std;

class BigInt
{
    friend ostream& operator<<(ostream&, BigInt);

    public:

    BigInt();
    BigInt(int);
    BigInt(const char*);
    BigInt(const vector<int>&, bool);
    BigInt(const BigInt&);

    int size() const;

    BigInt& operator=(const BigInt&);
    BigInt& operator=(const char*);

    bool operator>(const BigInt&) const;
    bool operator<(const BigInt&) const;

    int& operator[](int);
    int operator[](int) const;

    BigInt operator+(BigInt);
    BigInt subtractAbs(const BigInt&) const;
    BigInt operator+(int);
    BigInt& operator+=(const BigInt&);
    BigInt& operator+=(int);

    BigInt operator-(BigInt);
    BigInt operator-(int);
    BigInt& operator-=(const BigInt&);
    BigInt& operator-=(int);

    BigInt operator*(const BigInt&);
    BigInt operator*(int); 

    protected:

    bool negative;
    vector<int> number;
};

BigInt::BigInt():
negative(0),
number(vector<int>(0))
{}

BigInt::BigInt(int numb):
negative(numb<0),
number(vector<int>(0))
{
    numb = abs(numb);
    while (numb)
    {
        number.push_back(numb%10);
        numb /= 10;
    }
}


BigInt::BigInt(const char* line):
negative(line[0] == '-'),
number(vector<int>(0))
{
    for (int i = negative; line[i]; ++i)
    {
        if (line[i]-48 < 0 | line[i]-48 > 9) continue; 
        number.insert(number.cbegin(), line[i]-48); 
    }
}

BigInt::BigInt(const vector<int>& vec, bool neg = 0):
negative(neg),
number(vector<int>(vec.size()))
{
    for (int i = 0; i<size(); ++i)
    { number[i] = vec[size()-i-1]; }
}

BigInt::BigInt(const BigInt& other):
negative(other.negative),
number(other.number)
{}

int BigInt::size() const
{ return number.size(); }

BigInt& BigInt::operator=(const BigInt& other)
{
    negative = other.negative;
    number = other.number;

    return *this;
}

BigInt& BigInt::operator=(const char* line)
{
    *this = BigInt(line);
    return *this;
}

bool BigInt::operator<(const BigInt& other) const
{
    if (negative^other.negative)
    return negative;

    else if (number.size() != other.size())
    { return negative^(number.size() < other.size()); }

    else
    {
        for (int i = 0; i<size(); ++i)
        { if (number[i] != other[i]) return !negative^(number[i] < other[i]); }
    }

    return 0;
}

bool BigInt::operator>(const BigInt& other) const
{ return other < *this; }

int& BigInt::operator[](int index)
{ return number[index]; }

int BigInt::operator[](int index) const
{ return number[index]; }

BigInt BigInt::operator+(BigInt other)
{

    int tmp;
    if (negative == other.negative)
    {
        vector<int> result;
        for (int i = 0; i<size(); ++i)
        {
            tmp = number[i] + other[i];
            if (tmp > 9)
            {
                tmp -= 10;
                ++other[i+1];
            }

            result.push_back(tmp);
        }
        return BigInt(result, negative);
    }

    else
    {
        bool abs_is_first_greater = BigInt(number, 0) > BigInt(other.number, 0);

        if (!abs_is_first_greater)
        { return subtractAbs(other); }
        else
        {
            BigInt temp = other.subtractAbs(*this);
            temp.negative = other.negative;
            return temp;
        }
    }

    return BigInt();
}

BigInt BigInt::subtractAbs(const BigInt& other) const
{
    vector<int> result;
    int tmp = 0;

    for (int i = 0; i < size(); ++i)
    {
        tmp = number[i] - other[i] - tmp;

        if (tmp < 0)
        {
            tmp += 10;
            result.push_back(tmp);
            tmp = 1;
        }
        else
        {
            result.push_back(tmp);
            tmp = 0;
        }
    }

    return BigInt(result, negative);
}

BigInt BigInt::operator+(int num)
{ return *this + BigInt(num); }

BigInt& BigInt::operator+=(const BigInt& other)
{
    *this = *this + other;
    return *this;
}

BigInt& BigInt::operator+=(int num)
{
    *this = *this + num;
    return *this;
}

BigInt BigInt::operator-(BigInt other)
{ 
    other.negative ^= 1; 
    return *this + other;
}

BigInt BigInt::operator-(int num)
{ return *this + BigInt(-num); }

BigInt& BigInt::operator-=(const BigInt& other)
{
    *this = *this - other;
    return *this;
}

BigInt& BigInt::operator-=(int num)
{
    *this = *this - num;
    return *this;
}

ostream& operator<<(ostream& out, BigInt other)
{
    if (other.negative) out << '-';
    // for (auto it = other.number.rbegin(); it < other.number.rend(); ++it)
    // { out << *it; }

    // out << endl;

    for(auto it: other.number)
    { out << it; }

    // ААААААААААААААААА Я НЕ ПОНИМАЮ

    return out;
}

template<class Type>
Type abs(Type a)
{ return (a<0)? -a:a; }

int pow(int value, int degree)
{
    int tmp = 1;
    for (int i = 0; i<degree; ++i)
    { tmp *= value; }

    return tmp;
}


int main()
{
    BigInt test = 236;
    BigInt secs = -235;

    // cout << (test > secs) << endl;
    cout << (test - 235) << endl;

    return 0;
}
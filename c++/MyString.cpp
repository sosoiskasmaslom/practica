
#include <cstring>
#include <iostream>
using namespace std;

class MyString
{
    friend ostream& operator<<(ostream&, const MyString&);

    public:

    MyString();
    MyString(const char*);
    MyString(const MyString&);
    ~MyString();

    int size();

    MyString& operator=(MyString);
    MyString operator+(const MyString&);

    protected:
        int size_;
        char* str_;
};

MyString::MyString():
size_(0), str_(nullptr)
{}

MyString::MyString(const char* str):
size_(strlen(str)+1), str_(new char[size_])
{ strcpy(str_, str); }

MyString::MyString(const MyString& other):
MyString(other.str_)
{}

MyString::~MyString()
{ if (str_ != nullptr) delete[] str_; }

int MyString::size()
{ return size_; }

MyString& MyString::operator=(MyString tmp)
{
    swap(*this, tmp);
    return *this;
}

MyString MyString::operator+(const MyString& other)
{
    char* tmp = str_;
    strcat(tmp, other.str_);

    return MyString(tmp);
}

ostream& operator<<(ostream& out, const MyString& str)
{ return out << str.str_; }

int main()
{
    MyString s = "I love ";
    MyString t = "big black";
    cout << s << t << endl;
    cout << s+t << endl;

    return 0;
}
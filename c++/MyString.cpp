
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
    MyString& operator+=(const MyString&);
    MyString operator+(const char*);
    MyString& operator+=(const char*);

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

MyString& MyString::operator+=(const MyString& other)
{
    strcat(str_, other.str_);
    size_ = strlen(str_);

    return *this;
}

MyString MyString::operator+(const char* str)
{
    char* tmp = str_;
    strcat(tmp, str);

    return MyString(tmp);
}

MyString& MyString::operator+=(const char* str)
{
    strcat(str_, str);
    size_ = strlen(str_);

    return *this;
}


ostream& operator<<(ostream& out, const MyString& str)
{ return out << str.str_; }


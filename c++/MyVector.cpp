
#include <iostream>
#include <stdarg.h>
using namespace std;

class MyVector
{
    friend ostream& operator<< (ostream&, MyVector&);

    public:

    MyVector();
    MyVector(MyVector&);
    ~MyVector();

    void resize(int);
    void reserve(int);
    void shrink_to_fit();
    int& front();
    int& back();
    int size();
    bool empty();
    int capacity();
    void push_back(int);
    void insert(int, int);
    void erase(int);
    void erase(int, int);

    int& operator[] (int);
    MyVector& operator= (MyVector&);

    protected:

    int* data;
    size_t size_;
    size_t capacity_;
};

MyVector::MyVector():
data(nullptr), size_(0), capacity_(0)
{}

MyVector::MyVector(MyVector& another):
data(another.data), size_(another.size_), 
capacity_(another.capacity_) 
{}

MyVector::~MyVector()
{
    delete[] data;
    data = nullptr;
    size_ = 0;
    capacity_ = 0;
}

void MyVector::resize(int s)
{
    size_ = s;
    reserve(s);
}

void MyVector::reserve(int s)
{
    size_t new_capacity = (capacity_ == 0) ? 1 : 2 * capacity_;
    if (s != -1) new_capacity = s;
    int* new_data = new int[new_capacity]; 
        
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = (data[i]) ? data[i] : 0;
    }
        
    delete[] data;
    data = new_data;
    capacity_ = new_capacity;
}

void MyVector::shrink_to_fit()
{
    reserve(size_);
}

int& MyVector::front()
{return data[0];}

int& MyVector::back()
{return data[size_-1];}

int MyVector::size()
{return size_;}

bool MyVector::empty()
{return (size_<=0);}

int MyVector::capacity()
{return capacity_;}

void MyVector::push_back(int value)
{
    if (size_ == capacity_) reserve(-1);
    data[size_] = value;
    size_++;
}

void MyVector::insert(int value, int ind)
{
    push_back(back());
    for (int i = size_-1; i>ind-1; i--)
    {
        data[i] = data[i-1];
    }
    data[ind] = value;
}

void MyVector::erase(int ind)
{
    for (int i = ind; i<size_-1; i++)
    {
        data[i] = data[i+1];
    }
    resize(size_-1);
}

void MyVector::erase(int left, int right)
{
    int diff = right-left+1;
    for (int i = right+1; i<size_; i++)
    {
        data[i-diff] = data[i];
    }
    resize(size_-diff);
}

int& MyVector::operator[] (int i)
{return data[i];}

MyVector& MyVector::operator= (MyVector& another)
{
    data = another.data;
    size_ = another.size_;
    capacity_ = another.capacity_;

    return *this;
}

ostream& operator<< (ostream& out, MyVector& pups)
{
    out << '[';
    for (int i = 0; i<pups.size_; i++)
    {
        cout << pups.data[i];
        if (i!=pups.size_-1) out << ", ";
    }
    return out << "]";
}

int main()
{
    MyVector blya;
    blya.push_back(12);
    blya.push_back(45);
    blya.push_back(14);
    blya.push_back(62);
    blya.push_back(49);
    // blya.resize(3);
    // blya.insert(36, 0);

    cout << blya << endl;

    return 0;
}
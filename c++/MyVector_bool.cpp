
#include <iostream>
#include <bitset>
#include "MyVector.cpp"
using namespace std;

template<>
class MyVector<bool>
{
    template<class Fuck> friend ostream& operator<< (ostream&, MyVector<Fuck>);

    public:

    MyVector();
    template<size_t N> MyVector(bool(&array)[N]);
    template<size_t N> MyVector(bitset<N>);
    MyVector(MyVector&);
    ~MyVector();

    int size();
    int capacity();

    void resize(int);

    void push_back(bool);
    void insert(bool, int);
    void erase(int);

    MyVector swap();
    MyVector swap(int);
    MyVector set(int, int);

    bool front();
    bool back();
    bool at(int);
    bool operator[](int);

    protected:

    void reserve(int);

    bitset<8>* data;
    size_t size_;
    size_t capacity_;
};

MyVector<bool>::MyVector():
data(nullptr), size_(0), capacity_(0)
{}

template<size_t N>
MyVector<bool>::MyVector(bool(&array)[N]):
data(new bitset<8>[N/8 + 1]),
size_(N),
capacity_(N/8 + 1)
{
    for (int i = 0; i<N/8+1; i++)
    {
        for(int j = 0; j<8; j++)
        { data[i][j] = (array[i*8+j]) ? array[i*8+j] : 0; }
    }
}

template<size_t N> 
MyVector<bool>::MyVector(bitset<N> array):
data(new bitset<8>[N/8 + 1]),
size_(N),
capacity_(N/8 + 1)
{
    for (int i = 0; i<N/8+1; i++)
    {
        for(int j = 0; j<8; j++)
        { data[i][j] = (array[i*8+j]) ? array[i*8+j] : 0; }
    }
}

MyVector<bool>::MyVector(MyVector& other):
data(new bitset<8>[other.capacity_]),
size_(other.size_),
capacity_(other.capacity_)
{
    for (int i = 0; i<capacity_; i++)
    {
        for(int j = 0; j<8; j++)
        { data[i][j] = other.data[i][j]; }
    }
}

MyVector<bool>::~MyVector()
{ 
    delete[] data;
    size_ = 0;
    capacity_ = 0;
}

int MyVector<bool>::size()
{ return size_; }

int MyVector<bool>::capacity()
{ return capacity_; }

void MyVector<bool>::resize(int new_size)
{
    size_ = new_size;
    reserve((new_size/8)+1);
}

void MyVector<bool>::reserve(int new_capacity)
{
    bitset<8>* new_data = new bitset<8>[new_capacity]; 

    for (size_t i = 0; i < size_; ++i) {
        new_data[i/8][i%8] = ((*this)[i]) ? (*this)[i] : 0;
    }
        
    delete[] data;
    data = new_data;
    capacity_ = new_capacity;

}

void MyVector<bool>::push_back(bool value)
{
    if (size_ == capacity_*8) reserve(capacity_+1);
    set(value, size_);
    ++size_;
}

void MyVector<bool>::insert(bool value, int index)
{
    push_back(at(size_-1));
    for (int i = size_-1; i>index; --i)
    { set(at(i-1), i); }
    set(value, index);
}

void MyVector<bool>::erase(int index)
{
    for (int i = index+1; i<size_; ++i)
    { set(at(i), i-1); }
    set(0, size_-1);
    --size_;
}

MyVector<bool> MyVector<bool>::swap()
{ 
    for (int i = 0; i<size_; i++) swap(i); 
    return *this;
}

MyVector<bool> MyVector<bool>::swap(int index)
{
    set( ((*this)[index]) ? 0 : 1, index ); 
    return *this;
}

MyVector<bool> MyVector<bool>::set(int value, int index)
{
    data[index/8][index%8] = value;
    return *this;
}

bool MyVector<bool>::front()
{ return (*this)[0]; }

bool MyVector<bool>::back()
{ return (*this)[size_-1]; }

bool MyVector<bool>::at(int index)
{ return (*this)[index]; }

bool MyVector<bool>::operator[](int index)
{ return data[index/8][index%8]; }


template<> 
ostream& operator<< (ostream& out, MyVector<bool> other)
{
    out << '[';
    for (int i = 0; i<other.size_; ++i)
    { 
        out << other[i]; 
        if (i != other.size_-1) out << ", ";
    }
    return out << ']';
}
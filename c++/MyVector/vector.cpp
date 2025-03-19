
#include <iostream>
#include "MyVector.hpp"
using namespace own;


// class vector<T>

template<class T>
vector<T>::vector():
capacity_(0),
size_(0),
data(new T[0])
{}

template<class T>
template<size_t N> 
vector<T>::vector(T(&array)[N]):
capacity_(N),
size_(N),
data(new T[N])
{ for (int i = 0; i<N; ++i) data[i] = array[i]; }

template<class T>
vector<T>::vector(int value, int size):
capacity_(size),
size_(size),
data(new T[size])
{ for (int i = 0; i<size_; ++i) data[i] = value; }

template<class T>
vector<T>::vector(const vector& another):
capacity_(another.size_),
size_(another.size_),
data(new T[capacity_])
{ for (int i = 0; i<size(); ++i) data[i] = another[i]; }

template<class T>
vector<T>::~vector()
{ delete[] data; capacity_ = 0; size_ = 0; }

template<class T>
vector<T>& vector<T>::operator=(vector another)
{
    capacity_ = another.size_;
    size_ = another.size_;
    data = new T[capacity_];

    for (int i = 0; i<size_; ++i) 
    { data[i] = another[i]; }

    return *this;
}

template<class T>
T& vector<T>::operator[](int i)
{ return data[i]; }

template<class T>
T vector<T>::operator[](int i) const
{ return data[i]; }

template<class T>
vector<T>& vector<T>::operator+=(const vector& another)
{ 
    for (int i = 0; i<another.size(); ++i) 
    { push_back(another[i]); }

    return *this;
}

template<class T>
vector<T> vector<T>::operator+(const vector& another)
{ 
    vector tmp {*this};
    tmp += another;
    return tmp;
}

template<class T>
vector<T>& vector<T>::resize(size_t new_size)
{
    size_ = new_size;
    reserve(new_size);
    return *this;
}

template<class T>
vector<T>& vector<T>::reserve(size_t new_capacity)
{
    if (new_capacity == -1) 
    { new_capacity = (capacity_ == 0) ? 1 : 2 * capacity_; }
    
    T* new_data = new T[new_capacity];
    for (int i = 0; i<size(); ++i)
    { new_data[i] = (data[i]) ? data[i] : 0; }

    delete[] data;
    data = new_data;
    capacity_ = new_capacity;

    return *this;
}

template<class T>
vector<T>& vector<T>::shrink_to_fit()
{ return reserve(size()); }

template<class T>
T& vector<T>::front()
{ return data[0]; }

template<class T>
T& vector<T>::back()
{ return data[size()-1]; }

template<class T>
bool vector<T>::empty() const
{ return size() == 0; }

template<class T>
size_t vector<T>::size() const
{ return size_; }

template<class T>
size_t vector<T>::capacity() const
{ return capacity_; }

template<class T>
vector<T>& vector<T>::push_back(T value) 
{
    if (size()+1 == capacity()) reserve(-1);
    data[size()] = value;
    ++size_;

    return *this;
}

template<class T>
vector<T>& vector<T>::insert(T value, int ind)
{
    push_back(back());
    for (int i = size()-1; i>ind; --i)
    { data[i] = data[i-1]; }
    data[ind] = value;

    return *this;
}

template<class T>
vector<T>& vector<T>::erase(int l, int r)
{
    int jump = r-l+1;
    for (int i = r+1; i<size(); ++i)
    { data[i-jump] = data[i]; }
    resize(size()-jump);

    return *this;
}

template<class T>
vector<T>& vector<T>::erase(int ind)
{ return erase(ind, ind); }

template<class T>
typename vector<T>::iterator vector<T>::cbegin()
{ return iterator (this, 0); }

template<class T>
typename vector<T>::iterator vector<T>::cend()
{ return iterator (this, size()-1); }
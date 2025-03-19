
#include <iostream>
#include "MyVector.hpp"
using namespace own;

// class vector<T>::iterator

template<class T>   
vector<T>::iterator::iterator(vector<T>* ptr, size_t position):
ptr(ptr),
position(position)
{}

template<class T>
vector<T>::iterator::iterator(const iterator& iter):
ptr(iter.ptr),
position(iter.position)
{}

template<class T>
typename vector<T>::iterator& vector<T>::iterator::operator=(vector<T>* pointer)
{
    ptr = pointer;
    position = 0;

    return *this;
}

template<class T>
typename vector<T>::iterator& vector<T>::iterator::operator=(iterator iter)
{
    ptr = iter.ptr;
    position = iter.position;

    return *this;
}

template<class T>
T& vector<T>::iterator::operator*()
{ return (*ptr)[position]; }

template<class T>
typename vector<T>::iterator& vector<T>::iterator::operator+=(int num)
{
    position += num;
    return *this;
}

template<class T>
typename vector<T>::iterator& vector<T>::iterator::operator-=(int num)
{
    position -= num;
    return *this;
}

template<class T>
typename vector<T>::iterator vector<T>::iterator::operator+(int num)
{ return iterator (ptr, position+num); }

template<class T>
typename vector<T>::iterator vector<T>::iterator::operator-(int num)
{ return iterator (ptr, position-num); }

template<class T>
size_t vector<T>::iterator::operator-(vector<T>::iterator iter)
{ return abs(position - iter.position); }

template<class T>
typename vector<T>::iterator& vector<T>::iterator::operator++()
{
    position += 1;
    return *this;
}

template<class T>
typename vector<T>::iterator& vector<T>::iterator::operator--()
{
    position -= 1;
    return *this;
}

template<class T>
typename vector<T>::iterator vector<T>::iterator::operator++(int)
{ 
    iterator tmp {ptr, position};
    position += 1;
    return tmp;
}

template<class T>
typename vector<T>::iterator vector<T>::iterator::operator--(int)
{ 
    iterator tmp {ptr, position};
    position -= 1;
    return tmp;
}

template<class T>
bool vector<T>::iterator::operator==(vector<T>::iterator iter)
{ return position == iter.position; }

template<class T>
bool vector<T>::iterator::operator!=(vector<T>::iterator iter)
{ return position != iter.position; }

template<class T>
bool vector<T>::iterator::operator>(vector<T>::iterator iter)
{ return position > iter.position; }

template<class T>
bool vector<T>::iterator::operator>=(vector<T>::iterator iter)
{ return position >= iter.position; }

template<class T>
bool vector<T>::iterator::operator<(vector<T>::iterator iter)
{ return position < iter.position; }

template<class T>
bool vector<T>::iterator::operator<=(vector<T>::iterator iter)
{ return position <= iter.position; }

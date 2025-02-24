
#include <iostream>
using namespace std;

template<class Type>
class MyVector
{
    template<class Fuck> friend ostream& operator<< (ostream&, MyVector<Fuck>);

    public:

    MyVector();
    template<size_t N> MyVector(Type(&array)[N]);
    MyVector(MyVector&);
    ~MyVector();

    void resize(int);
    void reserve(int);
    void shrink_to_fit();
    Type& front();
    Type& back();
    int size();
    bool empty();
    int capacity();
    void push_back(Type);
    void insert(Type, int);
    void erase(int);
    void erase(int, int);

    Type& operator[] (int);
    MyVector& operator= (MyVector&);
    MyVector operator+ (MyVector&);

    protected:

    Type* data;
    size_t size_;
    size_t capacity_;
};

template<class Type>
MyVector<Type>::MyVector():
data(nullptr), size_(0), capacity_(0)
{}

template<class Type>
template<size_t N>
MyVector<Type>::MyVector(Type(&array)[N]):
data(new Type[N]), size_(N), capacity_(N)
{
    for (int i = 0; i<N; i++)
    data[i] = array[i];
}

template<class Type>
MyVector<Type>::MyVector(MyVector& another):
data(new Type[another.size_]),
size_(another.size_),
capacity_(another.size_)
{
    for (int i = 0; i<size_; i++)
    data[i] = another[i];
}

template<class Type>
MyVector<Type>::~MyVector()
{
    if (data != nullptr) delete[] data;
    size_ = 0;
    capacity_ = 0;
}

template<class Type>
void MyVector<Type>::resize(int s)
{
    size_ = s;
    reserve(s);
}

template<class Type>
void MyVector<Type>::reserve(int s)
{
    size_t new_capacity = (capacity_ == 0) ? 1 : 2 * capacity_;
    if (s != -1) new_capacity = s;
    Type* new_data = new Type[new_capacity]; 
        
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = (data[i]) ? data[i] : 0;
    }
        
    delete[] data;
    data = new_data;
    capacity_ = new_capacity;
}

template<class Type>
void MyVector<Type>::shrink_to_fit()
{ reserve(size_); }

template<class Type>
Type& MyVector<Type>::front()
{ return data[0]; }

template<class Type>
Type& MyVector<Type>::back()
{ return data[size_-1]; } 

template<class Type>
int MyVector<Type>::size()
{ return size_; }

template<class Type>
bool MyVector<Type>::empty()
{ return (size_<=0); }

template<class Type>
int MyVector<Type>::capacity()
{ return capacity_; }

template<class Type>
void MyVector<Type>::push_back(Type value)
{
    if (size_ == capacity_) reserve(-1);
    data[size_] = value;
    size_++;
}

template<class Type>
void MyVector<Type>::insert(Type value, int ind)
{
    push_back(back());
    for (int i = size_-1; i>ind-1; i--)
    {
        data[i] = data[i-1];
    }
    data[ind] = value;
}

template<class Type>
void MyVector<Type>::erase(int ind)
{
    for (int i = ind; i<size_-1; i++)
    {
        data[i] = data[i+1];
    }
    resize(size_-1);
}

template<class Type>
void MyVector<Type>::erase(int left, int right)
{
    int diff = right-left+1;
    for (int i = right+1; i<size_; i++)
    {
        data[i-diff] = data[i];
    }
    resize(size_-diff);
}

template<class Type>
Type& MyVector<Type>::operator[] (int i)
{ return data[i]; }

template<class Type>
MyVector<Type>& MyVector<Type>::operator= (MyVector& another)
{
    data = another.data;
    size_ = another.size_;
    capacity_ = another.capacity_;

    return *this;
}

template<class Type>
MyVector<Type> MyVector<Type>::operator+ (MyVector& another)
{
    MyVector tmp {*this};
    for (int i = 0; i<another.size_; i++)
    tmp.push_back(another[i]);

    return tmp;
}


template<class Type>
ostream& operator<< (ostream& out, MyVector<Type> pups)
{
    out << '[';
    for (int i = 0; i<pups.size_; i++)
    {
        cout << pups.data[i];
        if (i!=pups.size_-1) out << ", ";
    }
    return out << "]";
}

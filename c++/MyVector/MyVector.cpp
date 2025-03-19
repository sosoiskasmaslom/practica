
#include <iostream>

#include "vector.cpp"
#include "iterator.cpp"

using namespace own;

template<class T>
std::ostream& operator<<(std::ostream& out, vector<T> another)
{
    out << '[';
    for (int i = 0; i<another.size(); i++)
    { out << another[i] << ((i!=another.size()-1) ? ", " : ""); }
    return out << "]";
}

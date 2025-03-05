
#include <iostream>
#include "MyVector.hpp"
using namespace std;

int main()
{
    int array[] {1, 2, 3, 4, 5, 6, 7};
    MyVector::vector vec {array};
    
    cout << vec << endl;
    cout << vec[2] << endl;
    cout << vec + MyVector::vector<int> {2, 3} << endl;

    cout << vec.resize(5) << endl;
    cout << vec.insert(9, 1) << endl;
    cout << vec.erase(4) << endl;

    return 0;
}
/*
This file is to test C++11 feature:
1. Fixed width integer
2. Null ptr

*/


#include <iostream>
#include <cstdint>

using namespace std;

int main()
{
    int32_t width32;
    
    nullptr_t nullPtr;
    
    if (nullPtr == nullptr)
    {
        cout << "nullPtr has type: \"nullptr\"" << endl;
    }
    
    int i = 0;
    while (i++ <= 3)
    {
    }

    cout << "Size of width32: " << sizeof(width32) << endl;

    cout << "i = " << i << endl;

    return 0;
}


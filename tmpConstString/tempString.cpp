/*******************************************************
* This file to test life time of string's c_str() return value
*
*
******************************************************************/

#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

const char* testFunc1()
{
    string tmp;
    tmp = tmp + "test";
    
    return tmp.c_str();
}


const char* testFunc2()
{
    string tmp = "test";

    return tmp.c_str();
}




int main()
{

    const char* tmp = testFunc1();

    cout << tmp << endl;

    tmp = testFunc2();
    
    cout << tmp << endl;
    
    tmp = string(testFunc2()).c_str();

    cout << tmp << endl;

    return 0;
}



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

string testFunc3()
{
    string tmp = "test";
    return tmp;
}

const char* testFunc4()
{
    string tmp = "test";

    const char* xxx = tmp.c_str();
    return xxx;
}

const char* testFunc5()
{
    const char* tmp = "test";

    return tmp;
}

string& testFunc6()
{
    string tmp = "test";
    return tmp;
}

int main()
{

    const char* tmp = testFunc1();

    cout << tmp << endl;

    tmp = testFunc2();
    
    cout << tmp << endl;
    
    tmp = string(testFunc2()).c_str();

    cout << tmp << endl;

    tmp = testFunc3().c_str();
    cout << tmp << endl;

    tmp = testFunc4();
    cout << tmp << endl;

    tmp = testFunc5();
    cout << tmp << endl;

    tmp = testFunc6().c_str();
    cout << tmp << endl;
    return 0;
}



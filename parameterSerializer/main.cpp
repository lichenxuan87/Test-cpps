#include "KeyValueSerializer.h"
#include <iostream>

using namespace std;

int main()
{
    KeyValueSerializer s;
    s.openFile("tmp", KeyValueSerializer::WRITE);

    s.writeKeyValuePair("first", "1234");
    s.writeKeyValuePair("second", "other");

    s.closeFile();

    s.openFile("tmp", KeyValueSerializer::READ);

    string value;
    s.getValue("first", value);
    cout << "First: " << value << endl;

    s.getValue("second", value);
    cout << "Second: " << value << endl;

    s.closeFile();

    return 0;
}

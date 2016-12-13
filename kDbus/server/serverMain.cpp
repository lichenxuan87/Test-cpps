/*
 * serverMain.cpp
 *
 *  Created on: Nov 21, 2016
 *      Author: saic
 */

#include <dbus/DMessage.h>
#include <dbus/DAdaptor.h>
#include <iostream>

#include "DbusServerExample.h"

using namespace yunos;
using namespace std;


int main()
{
    DbusServerExample example;

    if (!example.init())
    {
        cout << "Initialization failed" << endl;
        return 1;
    }

    // Run a loop in DProxy
    example.run();

    return 0;

}

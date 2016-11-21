/*
 * CProxyExample.cpp
 *
 *  Created on: Nov 18, 2016
 *      Author: saic
 */

#include <dbus/DService.h>

#include "CProxyExample.h"
#include "kDbusName.h"

using namespace yunos;
using namespace std;

CProxyExample::CProxyExample( const SharedPtr< DService > & service,
                     const String &  path,
                     const String &  interface)
            :DProxy(service, path, interface)
{
    testCallback1 = new TestSignalCallback();
}

CProxyExample::~CProxyExample()
{
    if (testCallback1 != NULL)
        delete testCallback1;
}



void CProxyExample::onBirth(const DLifecycleListener::BirthInfo& birthInfo)
{
    // Put all methods that must wait until corresponding server appears on bus here
    cout << "On birth: " << birthInfo.mName << endl;
}

void CProxyExample::onDeath(const DLifecycleListener::DeathInfo& deathInfo)
{
    // Release resource upon death of dbus server
    cout << "On death: " << deathInfo.mName << endl;
}

void CProxyExample::addSignals()
{
    // Add callback
    this->addSignalRule(String("AwakeAndScream"), testCallback1);
}


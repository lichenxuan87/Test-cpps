/*
 * DbusClientExample.cpp
 *
 *  Created on: Nov 18, 2016
 *      Author: saic
 */



#include <dbus/DProxy.h>
#include <dbus/DServiceManager.h>
#include <dbus/DService.h>
#include <looper/Looper.h>
#include <iostream>

#include "kDbusName.h"
#include "DbusClientExample.h"

using namespace yunos;
using namespace std;



DbusClientExample::~DbusClientExample()
{
    if (m_serviceProxy != NULL)
    {
        delete m_serviceProxy;
    }

    if (m_looper != NULL)
    {
        delete m_looper;
    }
}

bool DbusClientExample::init()
{
    bool result = false;

    // You must create a loop first to make DServerManager::getInstance() success.
    m_looper = new IoLooper();

    // Get service name
    SharedPtr<DService> service = DServiceManager::getInstance()->getService(String(serviceName.c_str()));

    if(service.pointer() == NULL)
    {
        cout << "Failed to get service" << endl;
    }
    else
    {
        cout << "Get service successfully! " << endl;

        m_serviceProxy = new CProxyExample(service, String(objectPath.c_str()), String(serviceName.c_str()));
        m_serviceProxy->addSignals();

        result = true;
    }

    // Get server2 name

    return result;
}

void DbusClientExample::run()
{
    //TODO: is this necessary? will a sleep do?
    m_looper->run();
}


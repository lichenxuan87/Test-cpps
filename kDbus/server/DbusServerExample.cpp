/*
 * DbusServerExample.cpp
 *
 *  Created on: Nov 18, 2016
 *      Author: saic
 */


#include <dbus/DAdaptor.h>
#include <dbus/DServiceManager.h>
#include <dbus/DService.h>
#include <iostream>


#include "kDbusName.h"
#include "DbusServerExample.h"
#include "CAdaptorExample.h"

using namespace yunos;
using namespace std;

DbusServerExample::~DbusServerExample()
{
    if (m_exampleAdaptor != NULL)
    {
        delete m_exampleAdaptor;
    }

    if (m_looper != NULL)
    {
        delete m_looper;
    }
}


bool DbusServerExample::init()
{
    bool result = false;

    // You must create a loop first to make DServerManager::getInstance() success.
    m_looper = new IoLooper();

    // Register service
    SharedPtr<DService> service =
            DServiceManager::getInstance()->registerService(String(serviceName.c_str()));

    if(!service.pointer())
    {
        cout << "Failed to register service" << endl;
    }
    else
    {
        cout << "Register service successfully! " << endl;

        // Publish service
        m_exampleAdaptor = new CAdaptorExample(service, String(objectPath.c_str()), String(interfaceName.c_str()));
        m_exampleAdaptor->publish();

        // Send out signals
        SharedPtr<DMessage> msg = m_exampleAdaptor->obtainSignalMessage(String("AwakeAndScream"));
        msg->writeString("AAAAAAAAAOOOOOOOOOOUUUUUUUUUUUU");

        if (m_exampleAdaptor->sendMessage(msg))
        {
            cout << "Send out signal AwakeAndScream success" << endl;
        }
        else
        {
            cout << "Send out signal AwakeAndScream failed" << endl;
        }

        result = true;
    }
    return result;
}


void DbusServerExample::run()
{
    //TODO: is this necessary? will a sleep do?
    m_looper->run();
}

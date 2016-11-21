/*
 * CAdaptorExample.cpp
 *
 *  Created on: Nov 18, 2016
 *      Author: saic
 */


#include <dbus/DMessage.h>
#include <iostream>

#include "CAdaptorExample.h"

using namespace yunos;
using namespace std;


// Handle method call from proxies.
// Warning: you need to send back a reply message for all messages received
bool CAdaptorExample::handleMethodCall(const SharedPtr<DMessage>& msg)
{
    cout << "Received method call " << msg->methodName().c_str() << endl;
    if(msg->methodName() == "FireInTheHole")
    {
        int a = msg->readInt32();
        cout << "Parameter: " << a << endl;

        // Send back reply
        SharedPtr<DMessage> reply = obtainMethodReturnMessage(msg);
        reply->writeInt32(a+1);

        sendMessage(reply);

        return true;
    }
    else
    {
        cout << "This method call is not supported" << endl;

        SharedPtr<DMessage> reply = obtainErrorMessage(msg,
                            DError::BUS_ERROR_UNKNOWN_METHOD,
                            String("Method is not supported"));
        sendMessage(reply);
    }
    return false;
}


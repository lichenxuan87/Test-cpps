/*
 * aliDbus.cpp
 *
 *  Created on: Sep 29, 2016
 *      Author: saic
 */


#include <dbus/DServiceManager.h>
#include <dbus/DService.h>
#include <string>
#include <iostream>

using namespace yunos;
using namespace std;

const string serviceName = "com.saic.ivi.AudioManager";
const string objectPath = "/com/saic/ivi/AudioManager/Settings";
const string interfaceName = "com.saic.ivi.AudioManager.Settings";

int main()
{
    String serviceNameX(serviceName.c_str());
    SharedPtr<DService> service = DServiceManager::createServiceManager(serviceNameX, true);

    cerr << "xxx"<<endl;
    DProxy serviceProxy(service,
            String(objectPath.c_str()),
            String(interfaceName.c_str()));

    cerr << "xxx"<<endl;
    SharedPtr<DMessage> message = serviceProxy.obtainMethodCallMessage(String("VolumeDown"));

    cerr << "xxx"<<endl;
    message->writeString("Media");

    cerr << "xxx"<<endl;
    if (serviceProxy.sendMessage(message))
    {
        cout << "Send message success" << endl;
    }

    return 0;
}

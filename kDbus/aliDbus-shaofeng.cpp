/*
 * aliDbus.cpp
 *
 *  Created on: Sep 29, 2016
 *      Author: saic
 */


#include <dbus/DAdaptor.h>
#include <dbus/DServiceManager.h>
#include <dbus/DService.h>
#include <dbus/DConnection.h>
#include <looper/Looper.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

using namespace yunos;
using namespace std;


const string serviceName = "com.saic.ivi.testService";
const string objectPath = "/com/saic/ivi/testService";
const string interfaceName = "com.saic.ivi.testService";

class CAdaptorExample : public DAdaptor {
public:
    CAdaptorExample(const String& objectPath,
            const String& interface,
            const SharedPtr<DConnection>& conn)
            : DAdaptor(objectPath,interface,conn)
    {
    }

    CAdaptorExample(const SharedPtr<DService>& service,
            const String& objectPath,
            const String& interface)
            : DAdaptor(service, objectPath, interface),
              mPath(objectPath),
              mInterface(interface)
    {
    }

    virtual bool handleMethodCall(const SharedPtr<DMessage>& msg)
    {
        cout <<  msg->methodName().c_str() << "is invoked successfully" << endl;
        if(msg->methodName() == "FireInTheHole")
        {
            SharedPtr<DMessage> reply = msg->makeMethodReturn();
            int a = msg->readInt32();
            printf( "param a = %d\n",a);
            reply->writeInt32(a+1);

            sendMessage(reply);
            printf("fire in the hole  \n");
            return true;
        }
        return false;
    }

private:
    string mPath;
    string mInterface;
};

class DProxyExample : public DProxy {
public:
    DProxyExample(const SharedPtr<DService>& service, const String& objectPath, const String& interfaceName)
        : DProxy(service, objectPath,interfaceName) 
    {

    }


    virtual bool handleSignal(const SharedPtr<DMessage>& msg) 
    {
        cout <<  msg->signalName().c_str() << "is invoked successfully" << endl;
        if (msg->signalName() == "SigRadioSignalStrength")
        {
            int level = msg->readInt32();
            int usn = msg->readInt32();
            int wam = msg->readInt32();
            int fof = msg->readInt32();
            cout <<  "level-----" << level <<"  usn-----" <<  usn <<"  wam-----" << wam <<"fof-----" << fof << endl;
            return true;
        }
        else if(msg->signalName() == "testSignal")
        {
            int value = msg->readInt32();
           cout <<  "testsignal value-----" << value << endl;
            return true;
        }
        return false;
    }

};


static void testClient()
{
    sleep(5);
    IoLooper looper;
    SharedPtr<DServiceManager>  instance = DServiceManager::getInstance(true);
    SharedPtr<DService> service = instance->getService(String(serviceName.c_str()));
    if(!service.pointer())
    {
        cout << "Failed to get service" << endl;
        return;
    }
    cout << " Get service successfully! " << endl;

    DProxyExample serviceProxy(service, String(objectPath.c_str()), String(serviceName.c_str()));
    SharedPtr<DMessage> msg = serviceProxy.obtainMethodCallMessage(String("FireInTheHole"));
    msg->writeInt32(666);
    if (serviceProxy.sendMessage(msg))
    {
        cout << "Send message success" << endl;
    }
    serviceProxy.enableSignals();
    looper.run();
    return;
}

static void handleTimer(void* data) {

    SharedPtr<DService>* service = static_cast<SharedPtr<DService>*>(data);
    SharedPtr<DMessage> msg = (*service)->connection()->makeSignal(String(objectPath.c_str()),String(interfaceName.c_str()),String("testSignal"));
    if((*service)->connection()->sendMessage(msg))
    {
    cout << "Send signal message success" << endl;
    }
    Looper::current()->run();
}

static void testServer()
{
    IoLooper looper;
    SharedPtr<DServiceManager>  instance = DServiceManager::getInstance(true);
    SharedPtr<DService> service = instance->registerService(String(serviceName.c_str()), String(interfaceName.c_str()), String(objectPath.c_str()));
    if(!service.pointer())
    {
        cout << "Failed to register service" << endl;
        return;
    }
    cout << " Register service successfully! " << endl;

    CAdaptorExample adaptor(service, String(objectPath.c_str()), String(interfaceName.c_str()));
    adaptor.publish();
    looper.sendDelayedTask(Task(handleTimer, static_cast<void*>(&service)), 10000);
    looper.run();
    return;
}

static void *threadrun(void *data)
{
    testClient();
    return NULL;
}

int main(int argc, char *const argv[])
{
    pthread_t tid; 
    pthread_create(&tid, NULL, threadrun, NULL);
    
    testServer();

    return 0;
}



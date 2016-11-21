/*
 * CProxyExample.h
 *
 *  Created on: Nov 18, 2016
 *      Author: saic
 */

#ifndef KDBUS_CLIENT_CPROXYEXAMPLE_H_
#define KDBUS_CLIENT_CPROXYEXAMPLE_H_

#include <dbus/DProxy.h>
#include <iostream>

using std::cout;
using std::operator<<;
using std::endl;

namespace yunos
{

class TestSignalCallback;

class CProxyExample : public DProxy
{
public:
    CProxyExample( const SharedPtr< DService > & service,
                     const String &  path,
                     const String &  interface);

    ~CProxyExample();

    void onBirth(const DLifecycleListener::BirthInfo &  birthInfo);
    void onDeath(const DLifecycleListener::DeathInfo& deathInfo);

    void addSignals();

private:
    TestSignalCallback* testCallback1;

};


class TestSignalCallback : public dbus::DSignalCallback
{
public:
    bool handleSignal(const SharedPtr<DMessage>& msg)
    {
        cout <<  "Received signal: " << msg->signalName() << ", value: " << msg->readString() << endl;
        return true;
    }
};


} // namespace yunos

#endif /* KDBUS_CLIENT_CPROXYEXAMPLE_H_ */

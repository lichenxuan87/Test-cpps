/*
 * DbusServerExample.h
 *
 *  Created on: Nov 18, 2016
 *      Author: saic
 */

#ifndef KDBUS_DBUSSERVEREXAMPLE_H_
#define KDBUS_DBUSSERVEREXAMPLE_H_

#include <dbus/DAdaptor.h>
#include <looper/Looper.h>

using yunos::DAdaptor;
using std::list;
using yunos::IoLooper;

class DbusServerExample
{
public:
    DbusServerExample() :
        m_exampleAdaptor(),
        m_looper()
        {}

    ~DbusServerExample();

    bool init();

    void run();

private:

    DAdaptor* m_exampleAdaptor;
    IoLooper* m_looper;
};





#endif /* KDBUS_DBUSSERVEREXAMPLE_H_ */

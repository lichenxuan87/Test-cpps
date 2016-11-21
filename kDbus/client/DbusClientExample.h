/*
 * DbusClientExample.h
 *
 *  Created on: Nov 18, 2016
 *      Author: saic
 */

#ifndef KDBUS_DBUSCLIENTEXAMPLE_H_
#define KDBUS_DBUSCLIENTEXAMPLE_H_


#include <looper/Looper.h>
#include <dbus/DService.h>
#include "CProxyExample.h"

using yunos::IoLooper;

namespace yunos
{

class DbusClientExample
{
public:
    DbusClientExample()
        : m_serviceProxy(),
          m_looper()
    {}

    ~DbusClientExample();

    bool init();

    void run();

    DProxy* getProxy() { return m_serviceProxy;}

private:
    DbusClientExample(DbusClientExample&);
    DbusClientExample& operator=(DbusClientExample&);

    // Proxies
    CProxyExample* m_serviceProxy;
    // CProxyExample2* m_serviceProxy2;
    // CProxyExample3* m_serviceProxy3;

    // Loop
    IoLooper* m_looper;
};


}


#endif /* KDBUS_DBUSCLIENTEXAMPLE_H_ */

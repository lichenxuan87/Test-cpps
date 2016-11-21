/*
 * CAdaptorExample.h
 *
 *  Created on: Nov 18, 2016
 *      Author: saic
 */

#ifndef KDBUS_CADAPTOREXAMPLE_H_
#define KDBUS_CADAPTOREXAMPLE_H_

#include <dbus/DAdaptor.h>

namespace yunos{

class CAdaptorExample : public DAdaptor
{
public:
    CAdaptorExample(const SharedPtr<DService>& service,
            const String& objectPath,
            const String& interface)
        : DAdaptor(service, objectPath, interface)
    {
    }

    virtual bool handleMethodCall(const SharedPtr<DMessage>& msg);

    void broadcastSignals();
};

} //namespace yunos


#endif /* KDBUS_CADAPTOREXAMPLE_H_ */

/*
 * test.cpp
 *
 *  Created on: Dec 12, 2016
 *      Author: saic
 */

#include "stdio.h"
#include "glib.h"
#include "gio/gio.h"

void onNameAcquired(GDBusConnection *conn, const char *name, void *ud)
{
    printf("On Name acquired\n");
}

void onBusAcquired(GDBusConnection *conn, const char *name, void *ud)
{
    printf("On Bus acquired\n");
}

void onNameLost(GDBusConnection *conn, const char *name, void *ud)
{
    printf("On Name lost\n");
}


int main()
{
    printf("Entering CDbusProcessor::%s\n", __FUNCTION__);
    GMainLoop* mpMainLoop = g_main_loop_new(nullptr, false);
    int mBusId = g_bus_own_name(G_BUS_TYPE_SYSTEM, "com.saic.ivi.test",
                            G_BUS_NAME_OWNER_FLAGS_REPLACE,
                            onBusAcquired, onNameAcquired,
                            onNameLost, nullptr, nullptr);
    if (mBusId == 0)
    {
        throw "system service g_bus_own_name failed.";
        printf("system service g_bus_own_name failed.\n");
    }
    if (mpMainLoop == nullptr)
    {
        throw "g_main_loop_new failed.";
        printf("g_main_loop_new failed.\n");
    }
    printf("Leaving CDbusProcessor::%s\n", __FUNCTION__);

    g_main_loop_run(mpMainLoop);

    return 0;

}





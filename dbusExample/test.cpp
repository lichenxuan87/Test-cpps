/*****************************************************************************
    Project:        ZXQ

    Copyright ©     2014-2017 BanMa Info-Tech Co.,Ltd
                    All rights reserved.

    This software is supplied only under the terms of a license agreement,
    nondisclosure agreement or other written agreement with BanMa Info-Tech
    Co.,Ltd. Use, redistribution or other disclosure of any parts of this
    software is prohibited except in accordance with the terms of such written
    agreement with BanMa Info-Tech Co.,Ltd. This software is confidential
    and proprietary information of BanMa Info-Tech Co.,Ltd.

*****************************************************************************/


#include "stdio.h"
#include "glib.h"
#include "gio/gio.h"
#include "com.saic.ivi.test.xml.h"

ComSaicIviTest * gSkeleton = NULL;


gboolean handleSetFrequency (
		ComSaicIviTest *object,
		GDBusMethodInvocation *invocation)
{
	printf("Recieved method call handleSetFrequency\n");
	com_saic_ivi_test_complete_set_frequency(gSkeleton, invocation);

	return TRUE;
}




void onNameAcquired(GDBusConnection *conn, const char *name, void *ud)
{
    printf("On Name acquired\n");

}

void onBusAcquired(GDBusConnection *conn, const char *name, void *ud)
{

    printf("On Bus acquired\n");

    gSkeleton = com_saic_ivi_test_skeleton_new();

	GError* error = NULL;

	if (!g_dbus_interface_skeleton_export (G_DBUS_INTERFACE_SKELETON (gSkeleton),
											conn,
										   "/com/saic/ivi/test",
										   &error))
	{
		/* handle error */
		printf("Export interface error\n");
	}

	g_signal_connect (gSkeleton, "handle-set-frequency", G_CALLBACK (handleSetFrequency), NULL); /* user_data */
}

void onNameLost(GDBusConnection *conn, const char *name, void *ud)
{
    printf("On Name lost\n");
}


int main()
{
    printf("Entering CDbusProcessor::%s\n", __FUNCTION__);

    GMainLoop* mpMainLoop = g_main_loop_new(nullptr, false);
    int mBusId = g_bus_own_name(G_BUS_TYPE_SESSION, "com.saic.ivi.test",
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





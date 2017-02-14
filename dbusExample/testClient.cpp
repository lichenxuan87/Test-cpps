#include "com.saic.ivi.test.xml.h"
#include <time.h>
#include <cstdio>
#include <errno.h>
#include <string.h>
#include <cstdlib>
#include <unistd.h>


GMainLoop* gMainLoop = NULL;

void onbusNameAppear(GDBusConnection *conn, const gchar *name, const gchar *name_owner, gpointer user_data)
{
	timespec kernelTp = {0};

	// Get current kernel time
	clock_gettime(CLOCK_MONOTONIC_RAW, &kernelTp); // Kernel time

	// Print kernel time
	printf("Kernel time: %ld.%.6ld, bus name appears\n", kernelTp.tv_sec, kernelTp.tv_nsec/1000);

}

void* run(void*)
{
	g_main_loop_run(gMainLoop);

	return (void*)0;
}

GAsyncResult *gRes = NULL;

void
AsyncReadyCallback (GObject *source_object,
                        GAsyncResult *res,
                        gpointer user_data)
{
	GError *error = NULL;

	int output = 0;
	com_saic_ivi_test_call_fire_in_the_hole_finish (
			(ComSaicIviTest*)source_object,
			&output,
			res,
			&error);

	if (error == NULL)
	{
		printf(" Call method: Success, return result:%d\n", output);
	}
	else
	{
		printf(" Call method: Failed, %s\n", error->message);
		g_error_free(error);
	}
}


int main()
{
	GError *error = NULL;

	//g_bus_watch_name(G_BUS_TYPE_SESSION, "com.saic.ivi.test", G_BUS_NAME_WATCHER_FLAGS_NONE, onbusNameAppear, NULL, NULL, NULL);

	gMainLoop = g_main_loop_new(nullptr, false);

	pthread_t tid = 0;
	pthread_create(&tid, NULL, run,  NULL);

	while(true)
	{
		if(g_main_loop_is_running (gMainLoop))
		{
			printf("Gmainloop is running now\n");
			break;

		}

		sleep(1);
	}

	timespec kernelTp = {0};

	// Get current kernel time
	clock_gettime(CLOCK_MONOTONIC_RAW, &kernelTp); // Kernel time

	// Print kernel time
	printf("Kernel time: %ld.%.6ld, start to create proxy\n", kernelTp.tv_sec, kernelTp.tv_nsec/1000);


	ComSaicIviTest * testProxy = com_saic_ivi_test_proxy_new_for_bus_sync(
			G_BUS_TYPE_SYSTEM,
			G_DBUS_PROXY_FLAGS_DO_NOT_AUTO_START_AT_CONSTRUCTION,
			"com.saic.ivi.test",
			"/com/saic/ivi/test",
			NULL,
			NULL);


	// Get current kernel time
	clock_gettime(CLOCK_MONOTONIC_RAW, &kernelTp); // Kernel time
	printf("Kernel time: %ld.%.6ld, create proxy success, call method\n", kernelTp.tv_sec, kernelTp.tv_nsec/1000);

	//com_saic_ivi_test_call_set_frequency(testProxy, NULL, AsyncReadyCallback, NULL);


	clock_gettime(CLOCK_MONOTONIC_RAW, &kernelTp); // Kernel time
	printf("Kernel time: %ld.%.6ld, synchronized call\n", kernelTp.tv_sec, kernelTp.tv_nsec/1000);

	int output = 0;
	com_saic_ivi_test_call_fire_in_the_hole_sync(testProxy, 33, &output, NULL, &error);

	// Get current kernel time
	clock_gettime(CLOCK_MONOTONIC_RAW, &kernelTp); // Kernel time

	// Print kernel time
	printf("Kernel time: %ld.%.6ld", kernelTp.tv_sec, kernelTp.tv_nsec/1000);

	if (error == NULL)
	{
		printf(" Call method: Success, return result %d\n", output);
	}
	else
	{
		printf(" Call method: Failed, %s\n", error->message);
		g_error_free(error);
	}


	sleep(10);

	return 0;

}

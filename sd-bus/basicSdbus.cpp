// This cpp file is from 0pointer.net
// This cpp file must be used with an Ubuntu that supports systemd, which is Ubuntu 15.04.


#include <stdio.h>
#include <stdlib.h>
#include <systemd/sd-bus.h>

int main(int argc, char *argv[]) {
    sd_bus_error error = SD_BUS_ERROR_NULL;
    sd_bus_message *m = NULL;
    sd_bus *bus = NULL;
    int result;
    int r;

    /* Connect to the system bus */
    r = sd_bus_open_user(&bus);
    if (r < 0) {
            fprintf(stderr, "Failed to connect to system bus: %s\n", strerror(-r));
            goto finish;
    }

    /* Issue the method call and store the respons message in m */
    r = sd_bus_call_method(bus,
                           "com.saic.ivi.test",           /* service to contact */
                           "/com/saic/ivi/test",          /* object path */
                           "com.saic.ivi.test",   /* interface name */
                           "Fire",                          /* method name */
                           &error,                               /* object to return error in */
                           &m,                                   /* return message on success */
                           "i",                                 /* input signature */
                           3									/* first argument */
                           );
    if (r < 0) {
            fprintf(stderr, "Failed to issue method call: %s\n", error.message);
            goto finish;
    }
    else
    {
    	printf("Call method success!\n");
    }

    /* Parse the response message */
    r = sd_bus_message_read(m, "i", &result);
    if (r < 0) {
            fprintf(stderr, "Failed to parse response message: %s\n", strerror(-r));
            goto finish;
    }

    printf("Return result is %d.\n", result);

finish:
    sd_bus_error_free(&error);
    sd_bus_message_unref(m);
    sd_bus_unref(bus);

    return r < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}

ifndef ARCH 
CC=/home/saic/gcc-linaro-arm-linux-gnueabihf-4.7-2013.03-20130313_linux/bin/arm-linux-gnueabihf-gcc
LDDIR=/home/saic/targetfs/usr/lib/
INCDIR=/home/saic/targetfs/usr/include/
else
CC=gcc
LDDIR= /usr/lib/x86_64-linux-gnu/ -L/usr/lib/x86_64-linux-gnu/
INCDIR=/usr/include/gstreamer-1.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/
endif
wayland_client:waylandClient.c
	$(CC) $^  -g -o $@ -I$(INCDIR) -L$(LDDIR) -lwayland-client -lffi

clean:
	rm -rf wayland_client

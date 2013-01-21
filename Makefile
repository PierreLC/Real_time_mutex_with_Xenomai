# Filename: Makefile
#
# Purpose:  Makefile for rt_mutex_xenomai.c
#
# Author:   Pierre LE COZ


XENOCONFIG=/home/petersmooth/XenoPi/xenomai-2.6.1/rpi/usr/xenomai/bin/xeno-config
CC=        $(shell $(XENOCONFIG) --cc)
CFLAGS=    $(shell $(XENOCONFIG) --skin=native --cflags)
LDFLAGS=   $(shell $(XENOCONFIG) --skin=native --ldflags)
LDFLAGS+=-lnative
LDLIBS=-lnative -lxenomai
  
 
all:: rt_mutex_xenomai
clean:: 
	rm -f rt_mutex_xenomai *.o






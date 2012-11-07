# Makefile for building CQueue
# By: Roneil Rumburg

CC = gcc

# use -g and -O0 here when using a debugger like gdb
CFLAGS = -Wall -pedantic -O2 -std=gnu99

# Project files
HEADERS = cqueue.h
SOURCES = cqueue.c cqueue-test.c
TARGETS = cqueue-test

default: $(TARGETS)

cqueue-test : cqueue.o cqueue-test.o
	$(CC) $(CFLAGS) -o $@  $^

# Add additional dependencies for header files (so changes to header
# files cause files including them to be recompiled
Makefile.dependencies:: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -MM $(SOURCES) > Makefile.dependencies

-include Makefile.dependencies

# Phony means not a "real" target, it doesn't build anything
# The phony target "clean" that is used to remove all compiled object files.

.PHONY: clean

clean:
	@rm -f $(TARGETS) *.o Makefile.dependencies

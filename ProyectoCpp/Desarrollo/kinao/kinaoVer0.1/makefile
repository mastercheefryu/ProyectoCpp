include ../Build/Common/CommonDefs.mak
INC_DIRS = ../../Include = /usr/include/ni
BIN_DIR = ../Bin
SRC_FILES = ./*.cpp
EXE_NAME = Test
OBJS = main.cpp 



CC = g++
DEBUG = -g
CFLAGS = -Wall $(DEBUG) --pedantic -c
LFLAGS = -Wall --pedantic $(DEBUG)
TARGET = main
$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)
Test.o: joint.h cpp_global.h 
	$(CC) $(CFLAGS) joint.cpp
clean:
	rm -f *.o $(TARGET)


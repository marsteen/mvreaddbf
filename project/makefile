#**********************************************************************
#
# Standard makefile
#
# written 2013 by Martin Steen
#
#**********************************************************************
#
# C++ : Name of C++ Compiler
#
C++       = g++
#
#
#

#
#
#
.SUFFIXES : .cpp .o
#
#
#
CPPFILES = main.cpp \
           lib/DatabaseDbf/Database.cpp
CFILES = 

#
CCFLAGS = -O2 -I./include
#
TARGET   = readdbf
#
default : $(TARGET)
#
clean:
	rm -rf *.o
#
#
.cpp.o:
	$(C++) -c $(CCFLAGS) -o$@ $<

.c.o:
	gcc -c $(CCFLAGS) -o$@ $<

#
OBJECTS1 = $(CPPFILES:.cpp=.o)
OBJECTS2 = $(CFILES:.c=.o)
#
LDFLAGS = 
#
$(TARGET) : $(OBJECTS1) $(OBJECTS2)
	$(C++) -s -o $(TARGET) $(OBJECTS1) $(OBJECTS2) $(LDFLAGS)
#


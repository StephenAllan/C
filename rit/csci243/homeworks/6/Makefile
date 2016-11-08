#
# Created by gmakemake (Ubuntu Jul 25 2014) on Sun Oct 26 18:51:29 2014
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

CFLAGS = -std=c99 -ggdb -Wall -Wextra

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	queueADT.c queueTest1.c queueTest2.c queueTest3.c queueTest4.c
PS_FILES =	
S_FILES =	
H_FILES =	queueADT.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	queueADT.o myTest.o queueTest1.o queueTest2.o queueTest3.o queueTest4.o
ADTFILE =	queueADT.o

#
# Main targets
#

all:	myTest queueTest1 queueTest2 queueTest3 queueTest4 clean

#queueADT:	queueADT.o $(OBJFILES)
#	$(CC) $(CFLAGS) -o queueADT queueADT.o $(CLIBFLAGS)

myTest:	myTest.o $(ADTFILE)
	$(CC) $(CFLAGS) -o myTest myTest.o $(ADTFILE) $(CLIBFLAGS)

queueTest1:	queueTest1.o $(ADTFILE)
	$(CC) $(CFLAGS) -o queueTest1 queueTest1.o $(ADTFILE) $(CLIBFLAGS)

queueTest2:	queueTest2.o $(ADTFILE)
	$(CC) $(CFLAGS) -o queueTest2 queueTest2.o $(ADTFILE) $(CLIBFLAGS)

queueTest3:	queueTest3.o $(ADTFILE)
	$(CC) $(CFLAGS) -o queueTest3 queueTest3.o $(ADTFILE) $(CLIBFLAGS)

queueTest4:	queueTest4.o $(ADTFILE)
	$(CC) $(CFLAGS) -o queueTest4 queueTest4.o $(ADTFILE) $(CLIBFLAGS)

#
# Dependencies
#

queueADT.o:	queueADT.h
myTest.o:	queueADT.h
queueTest1.o:	queueADT.h
queueTest2.o:	queueADT.h
queueTest3.o:	queueADT.h
queueTest4.o:	queueADT.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:	$(OBJFILES)
	-/bin/rm -f $(OBJFILES) core

realclean:        clean
	-/bin/rm -f queueADT queueTest1 queueTest2 queueTest3 queueTest4 

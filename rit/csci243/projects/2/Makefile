#
# Created by gmakemake (Ubuntu Jul 25 2014) on Sun Nov  2 15:25:00 2014
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

CFLAGS = -Wall -Wextra -pedantic -std=c99 -ggdb
LFLAGS = -ggdb
LDFLAGS =

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	amigonet.c amigosim.c mytest.c
PS_FILES =	
S_FILES =	
H_FILES =	amigonet.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	amigonet.o

#
# Main targets
#

all:	amigosim mytest clean

amigosim:	amigosim.o $(OBJFILES)
	$(CC) $(CFLAGS) -o amigosim amigosim.o $(OBJFILES) $(CLIBFLAGS)

mytest:	mytest.o $(OBJFILES)
	$(CC) $(CFLAGS) -o mytest mytest.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

amigonet.o:	amigonet.h
amigosim.o:	amigonet.h 
mytest.o:	amigonet.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean: $(OBJFILES)
	-/bin/rm -f $(OBJFILES) amigosim.o mytest.o core

realclean:        clean
	-/bin/rm -f amigosim mytest 

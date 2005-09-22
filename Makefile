# $Source$
# $Revision$
# $Date$

# -O0 disables all optimization for debugging purposes; switch from
# $(DEBUGFLAGS) to $(MYCFLAGS) when desired

DEBUGFLAGS	= -g -O0

MYCFLAGS	=  -Wall -O2

CC		= gcc -std=gnu99

CFLAGS		= $(MYCFLAGS) #$(DEBUGFLAGS)

SWFLAGS	= -I/usr/include/python2.3

LINT		= $(CC) $(LINTFLAGS)
LINTFLAGS	= -fsyntax-only -Wall -Wno-unused -Wunreachable-code

MKLIB		= $(CC) -fpic -c medians_1D.c

MKSWIGPY		= swig -python medians_1D.i

DEST		= $HOME/bin

EXTHDRS		= 

HDRS		= 

INSTALL		= /usr/bin/install

LD		= cc

LDFLAGS		= -g 

LOADLIBES	=

LDLIBS		= 

# other system libs; I don't need them yet...
# -lm -lz

MAKEFILE	= Makefile

OBJS		= medians_1D.o \
		demo.o

SWOBJS		= medians_1D.o \
		medians_1D_wrap.o

TEST_OBJS	=

PRINT		= pr

PROGRAM	= demo

SHARED		= libmedians_1D.so

SWIGLIB		= medians_1Dmodule.so

SRCS		= medians_1D.c \
		demo.c

SWSRCS	= medians_1D.c \
		medians_1D_wrap.c

.c.o:
		$(CC) -c $(CFLAGS) $<

all:		$(PROGRAM)

$(PROGRAM):     $(OBJS) $(LOADLIBES)
		@echo "Linking $(PROGRAM) ..."
		$(LD) $(LDFLAGS) $(OBJS) $(LOADLIBES) $(LDLIBS) -o $(PROGRAM)
		@echo "done"

lib:;			@$(MKLIB)
			@echo "Making shared lib $(SHARED) ..."
			$(LD) -shared medians_1D.o -o $(SHARED)
			@echo "done"

swig:;		@$(MKSWIGPY)
			@echo "Making shared lib $(SWIGLIB) ..."
			$(CC) -c $(SWSRCS) $(SWFLAGS)
			$(LD) -shared $(SWOBJS) -o $(SWIGLIB)
			@echo "done"

clean:;		@rm -f $(OBJS) $(SWOBJS) core

clobber:;	@rm -f $(OBJS) $(SWOBJS) $(PROGRAM) $(SHARED) $(SWIGLIB) core tags

depend:;	@makedepend -Y $(CFLAGS) $(HDRS) $(SRCS)

echo:;		@echo $(HDRS) $(SRCS)

index:;		@ctags -wx $(HDRS) $(SRCS)

install:	$(PROGRAM)
		@echo Installing $(PROGRAM) in $(DEST)
		@if [ $(DEST) != . ]; then \
		(rm -f $(DEST)/$(PROGRAM); $(INSTALL) $(PROGRAM) $(DEST)); fi

lint:;		@$(LINT) $(LINTFLAGS) $(SRCS)

new:;		@rm -f $(PROGRAM)

print:;		@$(PRINT) $(HDRS) $(SRCS)

TAGS:           $(EXTHDRS) $(HDRS) $(SRCS); @etags $(SYSHDRS) $(EXTHDRS) $(HDRS) $(SRCS)

update:		$(DEST)/$(PROGRAM)

$(DEST)/$(PROGRAM): $(SRCS) $(LOADLIBES) $(HDRS) $(EXTHDRS)
		@$(MAKE) -f $(MAKEFILE) ROOT=$(ROOT) DEST=$(DEST) install

# End Makefile

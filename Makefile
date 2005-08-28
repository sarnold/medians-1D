# $Source$
# $Revision$
# $Date$

# -O0 disables all optimization for debugging purposes; switch from
# $(DEBUGFLAGS) to $(MYCFLAGS) when desired

DEBUGFLAGS	= -g -O0

MYCFLAGS	=  -Wall -O2

CC		= gcc -std=gnu99

CFLAGS		= $(MYCFLAGS) #$(DEBUGFLAGS)

LINT		= $(CC) $(LINTFLAGS)
LINTFLAGS	= -fsyntax-only -Wall -Wno-unused -Wunreachable-code

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

TEST_OBJS	=

PRINT		= pr

PROGRAM		= demo


SRCS		= medians_1D.c \
		demo.c


.c.o:
		$(CC) -c $(CFLAGS) $<

all:		$(PROGRAM)

$(PROGRAM):     $(OBJS) $(LOADLIBES)
		@echo "Linking $(PROGRAM) ..."
		$(LD) $(LDFLAGS) $(OBJS) $(LOADLIBES) $(LDLIBS) -o $(PROGRAM)
		@echo "done"

clean:;		@rm -f $(OBJS) core

clobber:;	@rm -f $(OBJS) $(PROGRAM) core tags

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

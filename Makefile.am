DOT	= dot
DOX	= doxygen

# output directories for auto-generated non-source files
DOCS	= doxygen

AUTOMAKE_OPTIONS = foreign

AM_CFLAGS = -g -Wall \
            -DANSI \
            -fstrength-reduce -fpcc-struct-return \
            -Wstrict-prototypes \
            -I$(top_srcdir)

AM_LDFLAGS = -lm

bin_PROGRAMS = demo

demo_SOURCES = demo.c

noinst_LIBRARIES = libmedians_1d.a
libmedians_1d_a_SOURCES = \
            medians_1D.c

LDADD = $(top_srcdir)/libmedians_1d.a

SUFFIXES = .c .o .obj .i

#EXTRA_DIST = doxygen ccccout

include sources.mk

MY_SRCS	= $(FULL_SOURCES)
MY_INCS	= -I$(top_srcdir)

$(DOCS)/.keep_dir :
	mkdir -p $(dir $@)
	touch $@

docs :	Doxyfile $(DOCS)/.keep_dir
	rm -rf $(DOCS)/html
	$(DOX) Doxyfile
	@echo "API docs now in $(DOCS)/html"


clean-docs :
	rm -rf $(DOCS)

clean-local:
	rm -rf Makefile.in aclocal.m4 ar-lib autom4te.cache/ compile \
		config.h.in configure depcomp install-sh missing

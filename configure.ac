AC_INIT([medians_1D], [0.9], [stephen.arnold42@gmail.com])

AM_INIT_AUTOMAKE([foreign -Wall])
AM_PROG_AR
LT_INIT()

dnl Check for programs
AC_PROG_CC
AC_PROG_INSTALL

dnl Check for header files
AC_HEADER_STDC
AC_CHECK_HEADERS(stdio.h stdlib.h unistd.h math.h)

AC_CONFIG_HEADERS(config.h)

dnl Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

AC_MSG_CHECKING([whether -lm is needed])
AC_LINK_IFELSE([AC_LANG_PROGRAM([[
#ifndef __NO_MATH_INLINES
# define __NO_MATH_INLINES 1 /* for glibc */
#endif
#include <math.h>

double a,b;
]],[[
a=sqrt(b);
]])],[
    AC_MSG_RESULT([no])
  ],[
    AC_MSG_RESULT([yes])
    AC_CHECK_LIB([m],[sqrt])
  ])


AC_CONFIG_FILES(Makefile)

AC_OUTPUT()


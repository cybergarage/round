##################################################################
#
# Round SDK for C
#
# Copyright (C) Satoshi Konno 2015
#
# This is licensed under BSD-style license, see file COPYING.
#
##################################################################

AC_CONFIG_AUX_DIR(config)
AM_CONFIG_HEADER(config.h)

AC_INIT([round-sdk], [0.1])
AC_CONFIG_SRCDIR([include/round/client.h])
AM_INIT_AUTOMAKE([subdir-objects])

##############################
# Checks for programs.
##############################

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_AWK
#AC_PROG_LIBTOOL
AC_PROG_RANLIB

##############################
# Checks for header files.
##############################

AC_CHECK_HEADERS([stdbool.h])

##############################
# Testing
##############################

AC_ARG_ENABLE([tests], AC_HELP_STRING([--enable-tests], [ build tests (default = no) ]), [build_tests="yes"], [])
AM_CONDITIONAL(UNITTESTS,test "$build_tests" = yes)
if [ test "$build_tests" = yes ]; then
	AC_CHECK_LIB([boost_unit_test_framework-mt],[main],,
		[AC_CHECK_LIB([boost_unit_test_framework],[main],,[AC_MSG_ERROR(Round for C++ needs boost::unit_test_framework)])])
	AC_CHECK_LIB([boost_system-mt],[main],,
		[AC_CHECK_LIB([boost_system],[main],,[AC_MSG_ERROR(Round for C++ needs boost::system)])])
	AC_CHECK_LIB([boost_thread-mt],[main],,
		[AC_CHECK_LIB([boost_thread],[main],,[AC_MSG_ERROR(Round for C++ needs boost::thread)])])
fi

##############################
# Makefiles
##############################

AC_OUTPUT([
Makefile
include/Makefile
lib/Makefile
lib/unix/Makefile
tests/Makefile
tests/unix/Makefile
])

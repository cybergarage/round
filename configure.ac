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
# Constants
##############################

LIBCURL_VERSION=7.13.0
JANSSON_VERSION=2.2.1
EXPAT_VERSION=1.95
LIBXML2_VERSION=2.6.0
MUPNP_VERSION=3.0.0

##############################
# Checks compiler
##############################

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_AWK
#AC_PROG_LIBTOOL
AC_PROG_RANLIB

##############################
# Check standard header files
##############################

AC_CHECK_HEADERS([stdbool.h])

##############################
# Check libcurl
##############################

AC_CHECK_LIB(curl, curl_easy_perform,
[
	AC_DEFINE([CG_HTTP_CURL],1,[LIBCURL])

	HTTP_CFLAGS=`curl-config --cflags`
	AC_SUBST(HTTP_CFLAGS)

	HTTP_LIBS=`curl-config --libs`
	AC_SUBST(HTTP_LIBS)
],[
	AC_MSG_ERROR(Round needs libcurl-dev >= $LIBCURL_VERSION)
])

##############################
# Check jansson
##############################

AC_CHECK_LIB([jansson],[main],,[AC_MSG_ERROR(Round needs Jansson $JANSSON_VERSION later)])

AC_MSG_CHECKING(json_object_foreach)
  AC_TRY_COMPILE([
    #include <jansson.h>
    void func()
    {
      json_t *jsonTDict;
      const char *jsonKey;
      json_t *jsonTObj;
      json_object_foreach(jsonTDict, jsonKey, jsonTObj) {
      }
    }
  ],
  [],
  [AC_MSG_RESULT(yes)
  AC_DEFINE([ROUND_USE_JANSSON_JSON_OBJECT_FOREACH],1,[json_object_foreach])],
  [AC_MSG_RESULT(no)]
)

AC_MSG_CHECKING(json_array_foreach)
  AC_TRY_COMPILE([
    #include <jansson.h>
    void func()
    {
      json_t *jsonTArray;
      size_t jsonIdx;
      json_t *jsonTObj;
      json_array_foreach(jsonTArray, jsonIdx, jsonTObj) {
      }
    }
  ],
  [],
  [AC_MSG_RESULT(yes)
  AC_DEFINE([ROUND_USE_JANSSON_JSON_ARRAY_FOREACH],1,[json_array_foreach])],
  [AC_MSG_RESULT(no)]
)

##############################
# Check XML parsers
##############################

AC_CHECK_HEADERS([expat/expat.h])
AC_CHECK_HEADERS([expat.h])
AC_CHECK_LIB([expat],[main],
[
  FOUND_EXPAT=yes
	XML_LIBS+="-lexpat"
],
[]
)

AC_CHECK_LIB(xml2, xmlSAXUserParseMemory,
[
  FOUND_LIBXML2=yes
	XML_CFLAGS+=`pkg-config libxml-2.0 --cflags`
	XML_LIBS+=`pkg-config libxml-2.0 --libs`
],
[]
)

if [ test $FOUND_EXPAT != yes ]; then
  if [ test $FOUND_LIBXML2 != yes ]; then
  	AC_MSG_ERROR(Round needs Expat >= $EXPAT_VERSION or libxml2-dev >= $LIBXML2_VERSION)
  fi
fi

AC_SUBST(XML_CFLAGS)
AC_SUBST(XML_LIBS)

##############################
# Check mUPnP
##############################

AC_CHECK_LIB([mupnp],[main],,[AC_MSG_ERROR(Round needs mUPnP $MUPNP_VERSION later)])

##############################
# Testing
##############################

AC_ARG_ENABLE(
  [tests],
	AC_HELP_STRING([--enable-tests], [ build tests (default = no) ]),
	[case "${enableval}" in
    yes | no ) build_tests="${enableval}" ;;
  esac],
	[]
)
AM_CONDITIONAL(ROUND_ENABLE_TESTS,test "$build_tests" = yes)
if [ test "$build_tests" = yes ]; then
  AC_CHECK_LIB([boost_unit_test_framework-mt],[main],,[AC_MSG_ERROR(mUPnP unittests need boost::unit_test_framework)])
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

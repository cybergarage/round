##################################################################
#
# Round SDK for C
#
# Copyright (C) Satoshi Konno 2015
#
# This is licensed under BSD-style license, see file COPYING.
#
##################################################################

noinst_PROGRAMS = roundclienttest

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src -I../



roundclienttest_SOURCES = \
	..//ClientTest.cpp \
	..//FinderTest.cpp \
	..//RoundSdkTest.cpp
#if HAVE_LIBTOOL
#roundclienttest_LDADD = ../../lib/unix/libroundclient.la
#else
roundclienttest_LDADD = ../../lib/unix/libroundclient.a
#endif

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
	..//ClusterListTest.cpp \
	..//ClusterTest.cpp \
	..//FinderTest.cpp \
	..//NodeListTest.cpp \
	..//NodeTest.cpp \
	..//RoundSdkTest.cpp \
	..//script/JsEngineTest.cpp \
	..//script/LuaEngineTest.cpp \
	..//script/RubyEngineTest.cpp
#if HAVE_LIBTOOL
#roundclienttest_LDADD = @CURL_LIBS@ @XML_LIBS@ ../../lib/unix/libroundclient.la
#else
roundclienttest_LDADD = @CURL_LIBS@ @XML_LIBS@ ../../lib/unix/libroundclient.a
#endif

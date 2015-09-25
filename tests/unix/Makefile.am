##################################################################
#
# Round SDK for C
#
# Copyright (C) Satoshi Konno 2015
#
# This is licensed under BSD-style license, see file COPYING.
#
##################################################################

noinst_PROGRAMS = roundtest

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src -I../

	..//RoundTest.h

roundtest_SOURCES = \
	..//Base64Test.cpp \
	..//ClientTest.cpp \
	..//ClockTest.cpp \
	..//ClusterListTest.cpp \
	..//ClusterTest.cpp \
	..//ErrorTest.cpp \
	..//FinderTest.cpp \
	..//JSONTest.cpp \
	..//LocalNodeTest.cpp \
	..//MapTest.cpp \
	..//MessageTest.cpp \
	..//MethodManagerTest.cpp \
	..//MethodMapTest.cpp \
	..//MethodTest.cpp \
	..//NodeListTest.cpp \
	..//NodeTest.cpp \
	..//QueueTest.cpp \
	..//RegistryTest.cpp \
	..//RemoteNodeTest.cpp \
	..//RoundTest.cpp \
	..//script/JsEngineTest.cpp \
	..//script/LuaEngineTest.cpp \
	..//script/RubyEngineTest.cpp \
	..//ScriptEngineMapTest.cpp \
	..//ScriptEngineTest.cpp \
	..//SemaphoreTest.cpp \
	..//ServerTest.cpp \
	..//StringTest.cpp \
	..//util/mutex_test.cpp \
	..//util/string_test.cpp
#if HAVE_LIBTOOL
#roundtest_LDADD = @HTTP_LIBS@ @XML_LIBS@ ../../lib/unix/libround.la
#else
roundtest_LDADD = @HTTP_LIBS@ @XML_LIBS@ ../../lib/unix/libround.a
#endif

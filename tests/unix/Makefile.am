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

	..//RoundTest.h \
	..//ScriptTestController.h

roundtest_SOURCES = \
	..//ClientTest.cpp \
	..//ClockTest.cpp \
	..//ClusterListTest.cpp \
	..//ClusterTest.cpp \
	..//ErrorTest.cpp \
	..//FinderTest.cpp \
	..//json/JSONArrayTest.cpp \
	..//json/JSONMapTest.cpp \
	..//json/JSONObjectTest.cpp \
	..//json/JSONParseTest.cpp \
	..//LocalNodeMessageTest.cpp \
	..//LocalNodeTest.cpp \
	..//MessageTest.cpp \
	..//MethodManagerTest.cpp \
	..//MethodMapTest.cpp \
	..//MethodTest.cpp \
	..//NodeListTest.cpp \
	..//NodeTest.cpp \
	..//RegistryTest.cpp \
	..//RemoteNodeTest.cpp \
	..//RoundTest.cpp \
	..//script/JsEngineTest.cpp \
	..//script/LuaEngineTest.cpp \
	..//script/RubyEngineTest.cpp \
	..//ScriptEngineMapTest.cpp \
	..//ScriptEngineTest.cpp \
	..//ScriptTestController.cpp \
	..//ServerTest.cpp \
	..//util/Base64Test.cpp \
	..//util/ListOrderedTest.cpp \
	..//util/ListTest.cpp \
	..//util/MapTest.cpp \
	..//util/QueueTest.cpp \
	..//util/SemaphoreTest.cpp \
	..//util/StringTest.cpp
#if HAVE_LIBTOOL
#roundtest_LDADD = @HTTP_LIBS@ @XML_LIBS@ ../../lib/unix/libround.la
#else
roundtest_LDADD = @HTTP_LIBS@ @XML_LIBS@ ../../lib/unix/libround.a
#endif

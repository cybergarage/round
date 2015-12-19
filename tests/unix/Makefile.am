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

	../RoundTest.h \
	../NodeTestController.h \
	../ScriptTestController.h

roundtest_SOURCES = \
	../RpcServerTest.cpp \
	../DigestTest.cpp \
	../ErrorTest.cpp \
	../MethodMapTest.cpp \
	../json/JSONParseTest.cpp \
	../json/JSONArrayTest.cpp \
	../json/JSONRpcTest.cpp \
	../json/JSONMapTest.cpp \
	../json/JSONObjectTest.cpp \
	../util/ListTest.cpp \
	../util/QueueTest.cpp \
	../util/ConsistentHashingRingTest.cpp \
	../util/MutexTest.cpp \
	../util/OptionTest.cpp \
	../util/Base64Test.cpp \
	../util/MapTest.cpp \
	../util/StatusTest.cpp \
	../util/StringTest.cpp \
	../util/SemaphoreTest.cpp \
	../util/ListOrderedTest.cpp \
	../NodeRingTest.cpp \
	../ScriptTestController.cpp \
	../MessageTest.cpp \
	../ClockTest.cpp \
	../ClusterManagerTest.cpp \
	../RegistryTest.cpp \
	../ClusterTest.cpp \
	../ClientTest.cpp \
	../MethodManagerTest.cpp \
	../ScriptEngineTest.cpp \
	../FinderTest.cpp \
	../MethodTest.cpp \
	../RemoteNodeTest.cpp \
	../NodeTestController.cpp \
	../script/JsEngineTest.cpp \
	../script/LuaEngineTest.cpp \
	../script/RubyEngineTest.cpp \
	../NodeTest.cpp \
	../LocalNodeTest.cpp \
	../ScriptEngineMapTest.cpp \
	../LocalNodeMessageTest.cpp \
	../RoundTest.cpp \
	../ServerTest.cpp
#if HAVE_LIBTOOL
#roundtest_LDADD = @HTTP_LIBS@ @XML_LIBS@ ../../lib/unix/libround.la
#else
roundtest_LDADD = @HTTP_LIBS@ @XML_LIBS@ ../../lib/unix/libround.a
#endif

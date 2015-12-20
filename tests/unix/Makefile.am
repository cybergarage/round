##################################################################
#
# Round for C
#
# Copyright (C) Satoshi Konno 2015
#
# This is licensed under BSD-style license, see file COPYING.
#
##################################################################

noinst_PROGRAMS = roundtest

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src -I../

	../NodeTestController.h \
	../ScriptTestController.h \
	../RoundTest.h

roundtest_SOURCES = \
	../ClockTest.cpp \
	../RegistryTest.cpp \
	../ClusterManagerTest.cpp \
	../MethodManagerTest.cpp \
	../ErrorTest.cpp \
	../LocalNodeMessageTest.cpp \
	../MethodTest.cpp \
	../RoundTest.cpp \
	../DigestTest.cpp \
	../util/ListTest.cpp \
	../util/Base64Test.cpp \
	../util/QueueTest.cpp \
	../util/SemaphoreTest.cpp \
	../util/ConsistentHashingRingTest.cpp \
	../util/StatusTest.cpp \
	../util/MapTest.cpp \
	../util/StringTest.cpp \
	../util/MutexTest.cpp \
	../util/OptionTest.cpp \
	../util/ListOrderedTest.cpp \
	../ScriptTestController.cpp \
	../RemoteNodeTest.cpp \
	../ScriptEngineTest.cpp \
	../LocalNodeTest.cpp \
	../NodeRingTest.cpp \
	../FinderTest.cpp \
	../ClientTest.cpp \
	../NodeTest.cpp \
	../MessageTest.cpp \
	../ScriptEngineMapTest.cpp \
	../json/JSONMapTest.cpp \
	../json/JSONArrayTest.cpp \
	../json/JSONRpcTest.cpp \
	../json/JSONObjectTest.cpp \
	../json/JSONParseTest.cpp \
	../MethodMapTest.cpp \
	../RpcServerTest.cpp \
	../script/RubyEngineTest.cpp \
	../script/LuaEngineTest.cpp \
	../script/JsEngineTest.cpp \
	../NodeTestController.cpp \
	../ClusterTest.cpp \
	../ServerTest.cpp
#if HAVE_LIBTOOL
#roundtest_LDADD = @HTTP_LIBS@ @XML_LIBS@ ../../lib/unix/libround.la
#else
roundtest_LDADD = @HTTP_LIBS@ @XML_LIBS@ ../../lib/unix/libround.a
#endif

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
TESTS = roundtest

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src -I../

	../ScriptTestController.h \
	../NodeTestController.h \
	../RoundTest.h

roundtest_SOURCES = \
	../ClusterManagerTest.cpp \
	../LocalNodeMessageTest.cpp \
	../RoundTest.cpp \
	../MethodTest.cpp \
	../MethodManagerTest.cpp \
	../ClockTest.cpp \
	../ServerTest.cpp \
	../MessageTest.cpp \
	../DigestTest.cpp \
	../LocalNodeTest.cpp \
	../util/StatusTest.cpp \
	../util/ListTest.cpp \
	../util/StringTest.cpp \
	../util/MutexTest.cpp \
	../util/OptionTest.cpp \
	../util/SemaphoreTest.cpp \
	../util/ListOrderedTest.cpp \
	../util/QueueTest.cpp \
	../util/MapTest.cpp \
	../util/Base64Test.cpp \
	../util/ConsistentHashingRingTest.cpp \
	../MethodMapTest.cpp \
	../RpcServerTest.cpp \
	../RegistryTest.cpp \
	../ScriptEngineTest.cpp \
	../ScriptTestController.cpp \
	../ClusterTest.cpp \
	../NodeTestController.cpp \
	../ErrorTest.cpp \
	../RemoteNodeTest.cpp \
	../FinderTest.cpp \
	../ScriptEngineMapTest.cpp \
	../ClientTest.cpp \
	../json/JSONArrayTest.cpp \
	../json/JSONParseTest.cpp \
	../json/JSONRpcTest.cpp \
	../json/JSONMapTest.cpp \
	../json/JSONObjectTest.cpp \
	../NodeRingTest.cpp \
	../NodeTest.cpp \
	../script/RubyEngineTest.cpp \
	../script/LuaEngineTest.cpp \
	../script/JsEngineTest.cpp \
	../script/PythonEngineTest.cpp
#if HAVE_LIBTOOL
#roundtest_LDADD = @HTTP_LIBS@ @XML_LIBS@ ../../lib/unix/libround.la
#else
roundtest_LDADD = @HTTP_LIBS@ @XML_LIBS@ ../../lib/unix/libround.a
#endif

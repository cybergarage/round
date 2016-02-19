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

	../RoundTest.h \
	../NodeTestController.h \
	../ScriptTestController.h

roundtest_SOURCES = \
	../json/JSONObjectTest.cpp \
	../json/JSONParseTest.cpp \
	../json/JSONRpcTest.cpp \
	../json/JSONMapTest.cpp \
	../json/JSONArrayTest.cpp \
	../script/JsEngineTest.cpp \
	../script/RubyEngineTest.cpp \
	../script/LuaEngineTest.cpp \
	../script/PythonEngineTest.cpp \
	../util/StatusTest.cpp \
	../util/Base64Test.cpp \
	../util/SemaphoreTest.cpp \
	../util/QueueTest.cpp \
	../util/StringTest.cpp \
	../util/MutexTest.cpp \
	../util/MapTest.cpp \
	../util/ConsistentHashingRingTest.cpp \
	../util/ListOrderedTest.cpp \
	../util/OptionTest.cpp \
	../util/ListTest.cpp \
	../RegistryTest.cpp \
	../RpcServerTest.cpp \
	../ClusterManagerTest.cpp \
	../ScriptTestController.cpp \
	../ScriptEngineTest.cpp \
	../ServerTest.cpp \
	../NodeRingTest.cpp \
	../LocalNodeMessageTest.cpp \
	../RoundTest.cpp \
	../ScriptEngineMapTest.cpp \
	../FinderTest.cpp \
	../MethodManagerTest.cpp \
	../MethodTest.cpp \
	../NodeTest.cpp \
	../ClockTest.cpp \
	../NodeTestController.cpp \
	../LocalNodeTest.cpp \
	../ErrorTest.cpp \
	../DigestTest.cpp \
	../ClusterTest.cpp \
	../ClientTest.cpp \
	../MessageTest.cpp \
	../MethodMapTest.cpp \
	../RemoteNodeTest.cpp

roundtest_LDADD = @XML_LIBS@ ../../lib/unix/libround.a

##################################################################
#
# Round for C
#
# Copyright (C) Satoshi Konno 2015
#
# This is licensed under BSD-style license, see file COPYING.
#
##################################################################

TESTS = roundtest
check_PROGRAMS = roundtest

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src -I../

	../NodeTestController.h \
	../RoundTest.h \
	../ScriptTestController.h

roundtest_SOURCES = \
	../ClusterTest.cpp \
	../DigestTest.cpp \
	../ScriptEngineMapTest.cpp \
	../ClockTest.cpp \
	../ScriptEngineTest.cpp \
	../TriggerTest.cpp \
	../RemoteNodeTest.cpp \
	../LocalNodeTest.cpp \
	../RoundTest.cpp \
	../ServerTest.cpp \
	../ErrorTest.cpp \
	../NodeTest.cpp \
	../MethodTest.cpp \
	../json/JSONArrayTest.cpp \
	../json/JSONRpcTest.cpp \
	../json/JSONObjectTest.cpp \
	../json/JSONMapTest.cpp \
	../json/JSONParseTest.cpp \
	../FinderTest.cpp \
	../LocalNodeMessageTest.cpp \
	../RpcServerTest.cpp \
	../MessageTest.cpp \
	../script/JsEngineTest.cpp \
	../script/RubyEngineTest.cpp \
	../script/LuaEngineTest.cpp \
	../script/PythonEngineTest.cpp \
	../NodeRingTest.cpp \
	../ClientTest.cpp \
	../RouteTest.cpp \
	../ClusterManagerTest.cpp \
	../ScriptTestController.cpp \
	../util/ConsistentHashingRingTest.cpp \
	../util/ThreadTest.cpp \
	../util/MapTest.cpp \
	../util/MutexTest.cpp \
	../util/ListOrderedTest.cpp \
	../util/SemaphoreTest.cpp \
	../util/OptionTest.cpp \
	../util/ListTest.cpp \
	../util/ObjectTest.cpp \
	../util/QueueTest.cpp \
	../util/Base64Test.cpp \
	../util/StatusTest.cpp \
	../util/TimeTest.cpp \
	../util/StringTest.cpp \
	../RegistryTest.cpp \
	../NodeTestController.cpp \
	../MethodMapTest.cpp \
	../MethodManagerTest.cpp

roundtest_LDADD = @XML_LIBS@ ../../lib/unix/libround.a

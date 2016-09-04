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

	..//NodeTestController.h \
	..//RoundTest.h \
	..//ScriptTestController.h

roundtest_SOURCES = \
	..//ClientTest.cpp \
	..//ClockTest.cpp \
	..//ClusterManagerTest.cpp \
	..//ClusterTest.cpp \
	..//DigestTest.cpp \
	..//ErrorTest.cpp \
	..//FinderTest.cpp \
	..//json/JSONArrayTest.cpp \
	..//json/JSONMapTest.cpp \
	..//json/JSONObjectTest.cpp \
	..//json/JSONParseTest.cpp \
	..//json/JSONRpcTest.cpp \
	..//LocalNodeMessageTest.cpp \
	..//LocalNodeTest.cpp \
	..//MessageTest.cpp \
	..//MethodManagerTest.cpp \
	..//MethodMapTest.cpp \
	..//MethodTest.cpp \
	..//NodeRingTest.cpp \
	..//NodeTest.cpp \
	..//NodeTestController.cpp \
	..//RegistryTest.cpp \
	..//RemoteNodeTest.cpp \
	..//RoundTest.cpp \
	..//RouteTest.cpp \
	..//RpcServerTest.cpp \
	..//script/JsEngineTest.cpp \
	..//script/LuaEngineTest.cpp \
	..//script/PythonEngineTest.cpp \
	..//script/RubyEngineTest.cpp \
	..//ScriptEngineMapTest.cpp \
	..//ScriptEngineTest.cpp \
	..//ScriptTestController.cpp \
	..//ServerTest.cpp \
	..//TriggerTest.cpp \
	..//util/Base64Test.cpp \
	..//util/ConsistentHashingRingTest.cpp \
	..//util/ListOrderedTest.cpp \
	..//util/ListTest.cpp \
	..//util/MapTest.cpp \
	..//util/MutexTest.cpp \
	..//util/ObjectTest.cpp \
	..//util/OptionTest.cpp \
	..//util/QueueTest.cpp \
	..//util/SemaphoreTest.cpp \
	..//util/StatusTest.cpp \
	..//util/StringTest.cpp \
	..//util/ThreadTest.cpp \
	..//util/TimeTest.cpp

roundtest_LDADD = @XML_LIBS@ ../../lib/unix/libround.a

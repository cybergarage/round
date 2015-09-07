##################################################################
#
# Round SDK for C
#
# Copyright (C) Satoshi Konno 2015
#
# This is licensed under BSD-style license, see file COPYING.
#
##################################################################

#if HAVE_LIBTOOL
#lib_LTLIBRARIES = libround.la
#else
lib_LIBRARIES = libround.a
#endif

AM_CFLAGS = -I$(top_builddir)/include -I$(top_builddir)/src

round_mpi_sources = \
	../../src/round/client.c \
	../../src/round/cluster.c \
	../../src/round/cluster_list.c \
	../../src/round/finder.c \
	../../src/round/node.c \
	../../src/round/node_list.c \
	../../src/round/script/js_engine.c \
	../../src/round/script/js_sm_engine.c \
	../../src/round/script/lua_engine.c \
	../../src/round/script/ruby_engine.c \
	../../src/round/script.c \
	../../src/round/script_engine.c \
	../../src/round/script_engine_map.c \
	../../src/round/script_manager.c \
	../../src/round/script_map.c \
	../../src/round/util/list.c \
	../../src/round/util/map.c \
	../../src/round/util/map_object.c \
	../../src/round/util/map_object_list.c \
	../../src/round/util/mutex.c \
	../../src/round/util/strings.c \
	../../src/round/util/thread.c \
	../../src/round/util/thread_list.c

#if HAVE_LIBTOOL
#libround_la_SOURCES = \
#        $(uecho_source)
#libround_la_CFLAGS = $(AM_CFLAGS)
#else
libround_a_SOURCES = \
        $(round_mpi_sources)
libround_a_CFLAGS = $(AM_CFLAGS)
#endif

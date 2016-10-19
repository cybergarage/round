##################################################################
#
# Round for C
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
	../../src/round/impl/upnp_server.c \
	../../src/round/impl/upnp_finder.c \
	../../src/round/impl/upnp_remote_node.c \
	../../src/round/node_ring.c \
	../../src/round/server_finder.c \
	../../src/round/node.c \
	../../src/round/method_map.c \
	../../src/round/registry_map.c \
	../../src/round/cluster_manager.c \
	../../src/round/script_engine.c \
	../../src/round/remote_node.c \
	../../src/round/local_node.c \
	../../src/round/error_rpc.c \
	../../src/round/registry_manager.c \
	../../src/round/script_engine_map.c \
	../../src/round/cluster.c \
	../../src/round/method/remove_registry.c \
	../../src/round/method/get_registry.c \
	../../src/round/method/remove_method.c \
	../../src/round/method/set_registry.c \
	../../src/round/method/set_method.c \
	../../src/round/method/system_method.c \
	../../src/round/client_finder.c \
	../../src/round/message_manager.c \
	../../src/round/message.c \
	../../src/round/local_node_thread.c \
	../../src/round/clock.c \
	../../src/round/trigger.c \
	../../src/round/server.c \
	../../src/round/route_object.c \
	../../src/round/method_manager.c \
	../../src/round/client.c \
	../../src/round/server_list.c \
	../../src/round/method.c \
	../../src/round/script/script_functions.c \
	../../src/round/script/python_engine.c \
	../../src/round/script/lua_engine.c \
	../../src/round/script/native_engine.c \
	../../src/round/script/lua/lua_functions.c \
	../../src/round/script/ruby_engine.c \
	../../src/round/script/js_sm_engine.c \
	../../src/round/script/js_engine.c \
	../../src/round/script/python/python_functions.c \
	../../src/round/script/js/js_sm_functions.c \
	../../src/round/registry.c \
	../../src/round/local_node_message.c \
	../../src/round/error.c \
	../../src/round/trigger_manager.c \
	../../src/round/util/thread.c \
	../../src/round/util/json_array.c \
	../../src/round/util/json_path_get.c \
	../../src/round/util/json_rpc.c \
	../../src/round/util/json_map.c \
	../../src/round/util/queue_object.c \
	../../src/round/util/json.c \
	../../src/round/util/mutex.c \
	../../src/round/util/list.c \
	../../src/round/util/base64.c \
	../../src/round/util/string_func.c \
	../../src/round/util/json_path_set.c \
	../../src/round/util/queue.c \
	../../src/round/util/consistent_hashing_ring.c \
	../../src/round/util/map.c \
	../../src/round/util/object.c \
	../../src/round/util/timer.c \
	../../src/round/util/list_ordered.c \
	../../src/round/util/map_object.c \
	../../src/round/util/consistent_hashing_node.c \
	../../src/round/util/map_hash.c \
	../../src/round/util/semaphore.c \
	../../src/round/util/thread_manager.c \
	../../src/round/util/map_object_list.c \
	../../src/round/util/json_object.c \
	../../src/round/util/string.c \
	../../src/round/util/digest.c \
	../../src/round/route_manager.c \
	../../src/round/node_methods.c \
	../../src/round/route.c \
	../../src/round/rpc_server.c

#if HAVE_LIBTOOL
#libround_la_SOURCES = \
#        $(uecho_source)
#libround_la_CFLAGS = $(AM_CFLAGS)
#else
libround_a_SOURCES = \
        $(round_mpi_sources)
libround_a_CFLAGS = $(AM_CFLAGS)
#endif

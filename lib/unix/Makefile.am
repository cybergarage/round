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
#lib_LTLIBRARIES = libroundclient.la
#else
lib_LIBRARIES = libroundclient.a
#endif

AM_CFLAGS = -I$(top_builddir)/include -I$(top_builddir)/src

round_mpi_sources = \
	../../src/round/client.c \
	../../src/round/finder.c

#if HAVE_LIBTOOL
#libroundclient_la_SOURCES = \
#        $(uecho_source)
#libroundclient_la_CFLAGS = $(AM_CFLAGS)
#else
libroundclient_a_SOURCES = \
        $(round_mpi_sources)
libroundclient_a_CFLAGS = $(AM_CFLAGS)
#endif

##################################################################
#
# Round for C
#
# Copyright (C) Satoshi Konno 2015
#
# This is licensed under BSD-style license, see file COPYING.
#
##################################################################

bin_PROGRAMS = roundd

AM_CPPFLAGS = \
	../ \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/src \
	@XML_CFLAGS@

AUTOMAKE_OPTIONS = \
        subdir-objects

roundd_SOURCES = \
	../roundd.cpp

roundd_LDADD = \
	../../../lib/unix/libround.a \
	-lmupnp \
	@LUA_LIBS@ \
	@XML_LIBS@

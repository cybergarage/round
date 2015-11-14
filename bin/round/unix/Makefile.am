##################################################################
#
# Round SDK for C
#
# Copyright (C) Satoshi Konno 2015
#
# This is licensed under BSD-style license, see file COPYING.
#
##################################################################

bin_PROGRAMS = round

AM_CPPFLAGS = \
	../ \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/src \
	@XML_CFLAGS@

AUTOMAKE_OPTIONS = \
        subdir-objects

round_SOURCES = \
	../round.cpp

round_LDADD = \
	../../../lib/unix/libround.a \
	-lmupnp \
	@LUA_LIBS@ \
	@XML_LIBS@

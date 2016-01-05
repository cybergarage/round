##################################################################
#
# Round for C
#
# Copyright (C) Satoshi Konno 2015
#
# This is licensed under BSD-style license, see file COPYING.
#
##################################################################

noinst_PROGRAMS = round

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src -I../
	..//cli.h \
	..//command.h \
	..//const.h

round_SOURCES = \
	..//cli.cpp \
	..//command/list.cpp \
	..//command.cpp \
	..//round.cpp

round_LDADD = @HTTP_LIBS@ @XML_LIBS@ ../../lib/unix/libround.a

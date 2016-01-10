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
	../command.h \
	../const.h \
	../cli.h

round_SOURCES = \
	../command/list.cpp \
	../cli.cpp \
	../round.cpp \
	../command.cpp

round_LDADD = @XML_LIBS@ ../../lib/unix/libround.a

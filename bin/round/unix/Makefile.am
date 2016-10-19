##################################################################
#
# Round for C
#
# Copyright (C) Satoshi Konno 2015
#
# This is licensed under BSD-style license, see file COPYING.
#
##################################################################

bin_PROGRAMS = round

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src -I../
	../cli.h \
	../const.h \
	../command.h

round_SOURCES = \
	../command.cpp \
	../cli.cpp \
	../round.cpp \
	../command/list.cpp

round_LDADD = ../../../lib/unix/libround.a @XML_LIBS@

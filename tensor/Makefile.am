lib_LTLIBRARIES = libtensor.la

AM_CPPFLAGS = -I$(top_srcdir)

pkginclude_HEADERS = tensor.h tensor_char.h tensor_complex_double.h	\
tensor_complex_float.h tensor_complex_long_double.h tensor_double.h	\
tensor_float.h tensor_int.h tensor_long_double.h tensor_long.h			\
tensor_short.h tensor_uchar.h tensor_uint.h tensor_ulong.h					\
tensor_ushort.h range.h

noinst_HEADERS = init_source.c access_source.c prop_source.c						\
file_source.c test_complex_source.c test_source.c view_source.c view.h	\
oper.h oper_source.c arithmetic_source.c arithmetic_complex_source.c		\
trig_source.c trig_complex_source.c explog_source.c											\
explog_complex_source.c stat_source.c sort_source.c sort_index_source.c	\
round_source.c round_complex_source.c logical_source.c dist_source.c

libtensor_la_SOURCES = init.c access.c prop.c file.c view.c oper.c	\
arithmetic.c trig.c explog.c stat.c sort.c sort_index.c round.c			\
logical.c dist.c tensor.c

# tests

check_PROGRAMS = test test_static

TESTS = $(check_PROGRAMS)

test_LDADD = $(builddir)/libtensor.la
test_static_LDADD = $(builddir)/libtensor.la

test_SOURCES = test.c

test_static_SOURCES = test_static.c

CLEANFILES = $(builddir)/test.dat $(builddir)/test_static.dat	\
$(builddir)/test.txt $(builddir)/test_static.txt

# Maintainer section

MAINTAINERCLEANFILES = $(top_srcdir)/tensor/Makefile.in

## Process this file with automake to produce Makefile.in

check_PROGRAMS = tensor_alloc tensor_io tensor_views tensor_sum

examples_src = tensor_alloc.c tensor_io.c tensor_views.c tensor_sum.c

examples_txt = tensor_alloc.txt tensor_io.txt tensor_views.txt tensor_sum.txt

dist_noinst_DATA = $(examples_src) $(examples_txt)

LDADD = $(top_builddir)/tensor/libtensor.la

AM_CPPFLAGS = -I$(top_srcdir)

AM_DEFAULT_SOURCE_EXT = .c

CLEANFILES = $(builddir)/test.dat

# Maintainer section

MAINTAINERCLEANFILES = $(top_srcdir)/doc/examples/Makefile.in

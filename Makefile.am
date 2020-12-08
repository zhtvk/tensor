## Process this file with automake to produce Makefile.in

SUBDIRS = tensor doc .

ACLOCAL_AMFLAGS = -I m4

noinst_HEADERS = templates_on.h templates_off.h build.h

# Maintainer section

MAINTAINERCLEANFILES = $(top_srcdir)/Makefile.in					\
$(top_srcdir)/aclocal.m4 $(top_srcdir)/config.h.in				\
$(top_srcdir)/configure


maintainer-clean-local:
	-rm -rf $(top_srcdir)/autom4te.cache/ $(top_srcdir)/build/*	\
$(top_srcdir)/config/ $(top_srcdir)/m4/

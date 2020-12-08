#!/bin/sh

# libtoolize \
#     && aclocal \
#     && autoheader \
#     && autoconf \
#     && automake --gnu --add-missing --force-missing

autoreconf -i -f -v

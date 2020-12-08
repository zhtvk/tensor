## Tensor

Tensor is a library for multidimensional array representation and
processing. It is an extension of
[GSL](https://www.gnu.org/software/gsl/) - the GNU Scientific Library,
which is a collection of numerical routines for scientific computing.

### Prerequisites

You would need the GSL library in order to use this extension. A copy
can be downloaded from a nearby GNU mirror
http://ftpmirror.gnu.org/gsl/.

Detailed installation instructions can be found in the included README
and INSTALL files in the downloaded package, however, the shell command

    ./configure && make && make install

should suffice to configure, build, and install GSL on most systems.

### Installation

The Tensor library can be installed in a similar fashion. Run the
following shell commands in its top-level directory:

    mkdir build
    cd build
    ../configure
    make -j
    make -j check
    make install

Have a look at the included INSTALL file for customised build
instructions.

### Documentation

A reference manual is included in GNU Texinfo format. It should be
available for reading on your system using the *info tensor* command
once the library is installed.

### Licensing

Tensor is free software, you can redistribute it and/or modify it under
the terms of the [GNU General Public
License](https://www.gnu.org/licenses/gpl.html) (GPL).

The GNU General Public License does not permit this software to be
redistributed in proprietary programs.

This library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

dnl Process this file with autoconf to produce a configure script.

AC_INIT([tensor], [0.1])

dnl store intermediate files in a separate directory
AC_CONFIG_AUX_DIR([config])

dnl separate directory for m4 macros
AC_CONFIG_MACRO_DIRS([m4])

AM_INIT_AUTOMAKE([gnu])
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE

AC_PROG_MKDIR_P

dnl things required by automake
dnl AC_ARG_PROGRAM
AC_PROG_MAKE_SET

dnl Check for which system.
AC_CANONICAL_HOST

dnl Checks for programs.
AC_LANG([C])
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL

dnl Check compiler features
AC_C_INLINE

if test "$ac_cv_c_inline" != no
then 
    dnl Check for "extern inline", using a modified version of the test
    dnl for AC_C_INLINE from acspecific.mt
    dnl
    AC_CACHE_CHECK([for GNU-style extern inline], ac_cv_c_extern_inline,
                   [ac_cv_c_extern_inline=no
                    AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[extern $ac_cv_c_inline double foo(double x);
                                                         extern $ac_cv_c_inline double foo(double x) { return x + 1.0 ; } ;
                                                         double foo (double x) { return x + 1.0 ; };]],
                                                       [[ foo(1.0) ]])],
                                      [ac_cv_c_extern_inline="yes"],
                                      [])])

    if test "$ac_cv_c_extern_inline" != no
    then
        AC_DEFINE(HAVE_INLINE,[1],[Define if you have inline])
    else
        AC_CACHE_CHECK([for C99-style inline], ac_cv_c_c99inline,
                       [ac_cv_c_c99inline=no
                        dnl next line is a necessary condition
                        AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[extern inline void* foo() { foo(); return &foo ; };]],
                                                           [[ return foo() != 0 ]])],
                                          [ac_cv_c_c99inline="yes"],[])
                        dnl but not sufficient, extern must work but inline on its own should not
                        if test "$ac_cv_c_c99inline" != no
                        then
                            AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[inline void* foo() { foo(); return &foo ; };]], 
                                                               [[ return foo() != 0 ]])],
                                              [], ac_cv_c_c99inline="no")
                        fi])
        if test "$ac_cv_c_c99inline" != no
        then
            AC_DEFINE(HAVE_INLINE,[1],[Define if you have inline])
            AC_DEFINE(HAVE_C99_INLINE,[1],[Define if you have inline with C99 behavior])
        fi
    fi
fi

dnl check if printf supports long double

AC_CACHE_CHECK([for long double stdio],
               ac_cv_func_printf_longdouble,
               [AC_RUN_IFELSE(
                    [AC_LANG_SOURCE([[
                                        #include <stdlib.h>
                                        #include <stdio.h>
                                        int main (void) 
                                        { 
                                            const char * s = "5678.25";
                                            long double x = 1.234; 
                                            fprintf(stderr,"%Lg\n",x);
                                            sscanf(s, "%Lg", &x);
                                            if (x == 5678.25)
                                               {exit (0);} else {exit(1);};
                                        }
                                    ]])],
                    [ac_cv_func_printf_longdouble="yes"],
                    [ac_cv_func_printf_longdouble="no"],
                    [ac_cv_func_printf_longdouble="no"])])

if test "$ac_cv_func_printf_longdouble" != no
then
    AC_DEFINE(HAVE_PRINTF_LONGDOUBLE,1,
              [Define to 1 if printf can handle %Lf for long double])
fi

dnl Add support for the `--enable-shared' and `--disable-shared' configure flags
AC_PROG_LIBTOOL

dnl Checks for library functions.
AC_CHECK_LIB(m, cos, [],
             [AC_MSG_ERROR([could not find libm.])])
             
dnl AC_CHECK_LIB(gslcblas, cblas_dgemm, [],
dnl              [AC_MSG_ERROR([could not find libgslcblas.])])

dnl Search for libcblas first, and then for libgslcblas
AC_SEARCH_LIBS(cblas_dgemm, cblas gslcblas,
               [AS_IF([test "x$ac_cv_search_cblas_dgemm" = x-lcblas],
                      [AC_DEFINE([HAVE_LIBCBLAS], [1],
                                 [Define to 1 if you have the `cblas' library (-lcblas).])]
                      [test "x$ac_cv_search_cblas_dgemm" = x-lgslcblas],
                      [AC_DEFINE([HAVE_LIBGSLCBLAS], [1],
                                 [Define to 1 if you have the `gslcblas' library (-lgslcblas).])])],
               [AC_MSG_ERROR([could not find libcblas or libgslcblas.])])
AC_CHECK_LIB(gsl, gsl_block_alloc, [],
             [AC_MSG_ERROR([could not find libgsl.])])             

dnl appended at the bottom of config.h
AH_BOTTOM([#define RETURN_IF_NULL(x) if (!x) { return ; }])

dnl
AC_CONFIG_FILES([            \
Makefile                     \
tensor/Makefile              \
doc/Makefile                 \
doc/examples/Makefile        \
])

AC_OUTPUT

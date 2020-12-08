
/* tensor/test.c
 * 
 * Copyright (C) 2020 Viktor Slavkovikj
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <config.h>

#if defined( _MSC_VER ) && defined( GSL_DLL )
#undef inline
#define inline __forceinline 
#endif
#if (!GSL_RANGE_CHECK) && defined(HAVE_INLINE)
#undef GSL_RANGE_CHECK
#define GSL_RANGE_CHECK 1
#endif

#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_machine.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_minmax.h>
#include <gsl/gsl_sys.h>
#include <time.h>
#include <tensor/tensor.h>

int status = 0;

#ifndef DESC
#define DESC ""
#endif

#define BASE_GSL_COMPLEX_LONG
#include "templates_on.h"
#include "test_complex_source.c"
#include "templates_off.h"
#undef  BASE_GSL_COMPLEX_LONG

#define BASE_GSL_COMPLEX
#include "templates_on.h"
#include "test_complex_source.c"
#include "templates_off.h"
#undef  BASE_GSL_COMPLEX

#define BASE_GSL_COMPLEX_FLOAT
#include "templates_on.h"
#include "test_complex_source.c"
#include "templates_off.h"
#undef  BASE_GSL_COMPLEX_FLOAT

#define BASE_LONG_DOUBLE
#include "templates_on.h"
#include "test_source.c"
#include "templates_off.h"
#undef  BASE_LONG_DOUBLE

#define BASE_DOUBLE
#include "templates_on.h"
#include "test_source.c"
#include "templates_off.h"
#undef  BASE_DOUBLE

#define BASE_FLOAT
#include "templates_on.h"
#include "test_source.c"
#include "templates_off.h"
#undef  BASE_FLOAT

#define BASE_ULONG
#include "templates_on.h"
#include "test_source.c"
#include "templates_off.h"
#undef  BASE_ULONG

#define BASE_LONG
#include "templates_on.h"
#include "test_source.c"
#include "templates_off.h"
#undef  BASE_LONG

#define BASE_UINT
#include "templates_on.h"
#include "test_source.c"
#include "templates_off.h"
#undef  BASE_UINT

#define BASE_INT
#include "templates_on.h"
#include "test_source.c"
#include "templates_off.h"
#undef  BASE_INT

#define BASE_USHORT
#include "templates_on.h"
#include "test_source.c"
#include "templates_off.h"
#undef  BASE_USHORT

#define BASE_SHORT
#include "templates_on.h"
#include "test_source.c"
#include "templates_off.h"
#undef  BASE_SHORT

#define BASE_UCHAR
#include "templates_on.h"
#include "test_source.c"
#include "templates_off.h"
#undef  BASE_UCHAR

#define BASE_CHAR
#include "templates_on.h"
#include "test_source.c"
#include "templates_off.h"
#undef  BASE_CHAR

void my_error_handler (const char *reason, const char *file,
                       int line, int err);

int
main (void)
{
  /* Verbose tests */
  gsl_test_verbose (1);
  
  gsl_rng * rng = gsl_rng_alloc (gsl_rng_default);
  
  time_t current_time = time (0);

  /* Use random seed each run */
  gsl_rng_set (rng, (unsigned long int) current_time);

  gsl_ieee_env_setup ();

  const size_t MAX_DIM = 6;
  const size_t MAX_SIZE = 10;   /* 1..10 */

  size_t i, dim[MAX_DIM], size[MAX_DIM];

  printf ("Tesiting with tensor dim: ");
  for (i = 0; i < MAX_DIM; ++i)
    {
      dim[i] = i;
      printf ("%zu, ", dim[i]);
      
      size[i] = (size_t) gsl_rng_uniform_int (rng, MAX_SIZE) + 1;
    }
  printf ("\n");
  
  printf ("Tesiting with tensor sizes: ");
  for (i = 1; i < MAX_DIM; ++i)
    {
      printf ("%zu, ", size[i]);
    }
  printf ("\n");
    
  /* Zero dim */

  test_alloc (dim[0]);
  test_float_alloc (dim[0]);
  test_long_double_alloc (dim[0]);
  test_ulong_alloc (dim[0]);
  test_long_alloc (dim[0]);
  test_uint_alloc (dim[0]);
  test_int_alloc (dim[0]);
  test_ushort_alloc (dim[0]);
  test_short_alloc (dim[0]);
  test_uchar_alloc (dim[0]);
  test_char_alloc (dim[0]);
  test_complex_alloc (dim[0]);
  test_complex_float_alloc (dim[0]);
  test_complex_long_double_alloc (dim[0]);

  /* One dim */
    
  test_alloc (dim[1], size[1]);
  test_float_alloc (dim[1], size[1]);
  test_long_double_alloc (dim[1], size[1]);
  test_ulong_alloc (dim[1], size[1]);
  test_long_alloc (dim[1], size[1]);
  test_uint_alloc (dim[1], size[1]);
  test_int_alloc (dim[1], size[1]);
  test_ushort_alloc (dim[1], size[1]);
  test_short_alloc (dim[1], size[1]);
  test_uchar_alloc (dim[1], size[1]);
  test_char_alloc (dim[1], size[1]);
  test_complex_alloc (dim[1], size[1]);
  test_complex_float_alloc (dim[1], size[1]);
  test_complex_long_double_alloc (dim[1], size[1]);

  /* Two dim */
    
  test_alloc (dim[2], size[1], size[2]);
  test_float_alloc (dim[2], size[1], size[2]);
  test_long_double_alloc (dim[2], size[1], size[2]);
  test_ulong_alloc (dim[2], size[1], size[2]);
  test_long_alloc (dim[2], size[1], size[2]);
  test_uint_alloc (dim[2], size[1], size[2]);
  test_int_alloc (dim[2], size[1], size[2]);
  test_ushort_alloc (dim[2], size[1], size[2]);
  test_short_alloc (dim[2], size[1], size[2]);
  test_uchar_alloc (dim[2], size[1], size[2]);
  test_char_alloc (dim[2], size[1], size[2]);
  test_complex_alloc (dim[2], size[1], size[2]);
  test_complex_float_alloc (dim[2], size[1], size[2]);
  test_complex_long_double_alloc (dim[2], size[1], size[2]);

  /* Three dim */
    
  test_alloc (dim[3], size[1], size[2], size[3]);
  test_float_alloc (dim[3], size[1], size[2], size[3]);
  test_long_double_alloc (dim[3], size[1], size[2], size[3]);
  test_ulong_alloc (dim[3], size[1], size[2], size[3]);
  test_long_alloc (dim[3], size[1], size[2], size[3]);
  test_uint_alloc (dim[3], size[1], size[2], size[3]);
  test_int_alloc (dim[3], size[1], size[2], size[3]);
  test_ushort_alloc (dim[3], size[1], size[2], size[3]);
  test_short_alloc (dim[3], size[1], size[2], size[3]);
  test_uchar_alloc (dim[3], size[1], size[2], size[3]);
  test_char_alloc (dim[3], size[1], size[2], size[3]);
  test_complex_alloc (dim[3], size[1], size[2], size[3]);
  test_complex_float_alloc (dim[3], size[1], size[2], size[3]);
  test_complex_long_double_alloc (dim[3], size[1], size[2], size[3]);

  /* Four dim */
  
  test_alloc (dim[4], size[1], size[2], size[3], size[4]);
  test_float_alloc (dim[4], size[1], size[2], size[3], size[4]);
  test_long_double_alloc (dim[4], size[1], size[2], size[3], size[4]);
  test_ulong_alloc (dim[4], size[1], size[2], size[3], size[4]);
  test_long_alloc (dim[4], size[1], size[2], size[3], size[4]);
  test_uint_alloc (dim[4], size[1], size[2], size[3], size[4]);
  test_int_alloc (dim[4], size[1], size[2], size[3], size[4]);
  test_ushort_alloc (dim[4], size[1], size[2], size[3], size[4]);
  test_short_alloc (dim[4], size[1], size[2], size[3], size[4]);
  test_uchar_alloc (dim[4], size[1], size[2], size[3], size[4]);
  test_char_alloc (dim[4], size[1], size[2], size[3], size[4]);
  test_complex_alloc (dim[4], size[1], size[2], size[3], size[4]);
  test_complex_float_alloc (dim[4], size[1], size[2], size[3], size[4]);
  test_complex_long_double_alloc (dim[4], size[1], size[2], size[3], size[4]);

  /* Five dim */
    
  test_alloc (dim[5], size[1], size[2], size[3], size[4], size[5]);
  test_float_alloc (dim[5], size[1], size[2], size[3], size[4], size[5]);
  test_long_double_alloc (dim[5], size[1], size[2], size[3], size[4], size[5]);
  test_ulong_alloc (dim[5], size[1], size[2], size[3], size[4], size[5]);
  test_long_alloc (dim[5], size[1], size[2], size[3], size[4], size[5]);
  test_uint_alloc (dim[5], size[1], size[2], size[3], size[4], size[5]);
  test_int_alloc (dim[5], size[1], size[2], size[3], size[4], size[5]);
  test_ushort_alloc (dim[5], size[1], size[2], size[3], size[4], size[5]);
  test_short_alloc (dim[5], size[1], size[2], size[3], size[4], size[5]);
  test_uchar_alloc (dim[5], size[1], size[2], size[3], size[4], size[5]);
  test_char_alloc (dim[5], size[1], size[2], size[3], size[4], size[5]);
  test_complex_alloc (dim[5], size[1], size[2], size[3], size[4], size[5]);
  test_complex_float_alloc (dim[5], size[1], size[2], size[3], size[4], size[5]);
  test_complex_long_double_alloc (dim[5], size[1], size[2], size[3], size[4], size[5]);

  /* aalloc */
  
  test_aalloc (dim[3], size[1], size[2], size[3]);
  test_float_aalloc (dim[3], size[1], size[2], size[3]);
  test_long_double_aalloc (dim[3], size[1], size[2], size[3]);
  test_ulong_aalloc (dim[3], size[1], size[2], size[3]);
  test_long_aalloc (dim[3], size[1], size[2], size[3]);
  test_uint_aalloc (dim[3], size[1], size[2], size[3]);
  test_int_aalloc (dim[3], size[1], size[2], size[3]);
  test_ushort_aalloc (dim[3], size[1], size[2], size[3]);
  test_short_aalloc (dim[3], size[1], size[2], size[3]);
  test_uchar_aalloc (dim[3], size[1], size[2], size[3]);
  test_char_aalloc (dim[3], size[1], size[2], size[3]);
  test_complex_aalloc (dim[3], size[1], size[2], size[3]);
  test_complex_float_aalloc (dim[3], size[1], size[2], size[3]);
  test_complex_long_double_aalloc (dim[3], size[1], size[2], size[3]);

  /* calloc */
  
  test_calloc (dim[3], size[1], size[2], size[3]);
  test_float_calloc (dim[3], size[1], size[2], size[3]);
  test_long_double_calloc (dim[3], size[1], size[2], size[3]);
  test_ulong_calloc (dim[3], size[1], size[2], size[3]);
  test_long_calloc (dim[3], size[1], size[2], size[3]);
  test_uint_calloc (dim[3], size[1], size[2], size[3]);
  test_int_calloc (dim[3], size[1], size[2], size[3]);
  test_ushort_calloc (dim[3], size[1], size[2], size[3]);
  test_short_calloc (dim[3], size[1], size[2], size[3]);
  test_uchar_calloc (dim[3], size[1], size[2], size[3]);
  test_char_calloc (dim[3], size[1], size[2], size[3]);
  test_complex_calloc (dim[3], size[1], size[2], size[3]);
  test_complex_float_calloc (dim[3], size[1], size[2], size[3]);
  test_complex_long_double_calloc (dim[3], size[1], size[2], size[3]);

  /* copy */

  test_copy (dim[3], size[1], size[2], size[3]);
  test_float_copy (dim[3], size[1], size[2], size[3]);
  test_long_double_copy (dim[3], size[1], size[2], size[3]);
  test_ulong_copy (dim[3], size[1], size[2], size[3]);
  test_long_copy (dim[3], size[1], size[2], size[3]);
  test_uint_copy (dim[3], size[1], size[2], size[3]);
  test_int_copy (dim[3], size[1], size[2], size[3]);
  test_ushort_copy (dim[3], size[1], size[2], size[3]);
  test_short_copy (dim[3], size[1], size[2], size[3]);
  test_uchar_copy (dim[3], size[1], size[2], size[3]);
  test_char_copy (dim[3], size[1], size[2], size[3]);
  test_complex_copy (dim[3], size[1], size[2], size[3]);
  test_complex_float_copy (dim[3], size[1], size[2], size[3]);
  test_complex_long_double_copy (dim[3], size[1], size[2], size[3]);

  /* copy non-contiguous */

  test_copy_nctg (dim[3], size[1], size[2], size[3]);
  test_float_copy_nctg (dim[3], size[1], size[2], size[3]);
  test_long_double_copy_nctg (dim[3], size[1], size[2], size[3]);
  test_ulong_copy_nctg (dim[3], size[1], size[2], size[3]);
  test_long_copy_nctg (dim[3], size[1], size[2], size[3]);
  test_uint_copy_nctg (dim[3], size[1], size[2], size[3]);
  test_int_copy_nctg (dim[3], size[1], size[2], size[3]);
  test_ushort_copy_nctg (dim[3], size[1], size[2], size[3]);
  test_short_copy_nctg (dim[3], size[1], size[2], size[3]);
  test_uchar_copy_nctg (dim[3], size[1], size[2], size[3]);
  test_char_copy_nctg (dim[3], size[1], size[2], size[3]);
  test_complex_copy_nctg (dim[3], size[1], size[2], size[3]);
  test_complex_float_copy_nctg (dim[3], size[1], size[2], size[3]);
  test_complex_long_double_copy_nctg (dim[3], size[1], size[2], size[3]);

  /* access */

  test_access (dim[3], size[1], size[2], size[3]);
  test_float_access (dim[3], size[1], size[2], size[3]);
  test_long_double_access (dim[3], size[1], size[2], size[3]);
  test_ulong_access (dim[3], size[1], size[2], size[3]);
  test_long_access (dim[3], size[1], size[2], size[3]);
  test_uint_access (dim[3], size[1], size[2], size[3]);
  test_int_access (dim[3], size[1], size[2], size[3]);
  test_ushort_access (dim[3], size[1], size[2], size[3]);
  test_short_access (dim[3], size[1], size[2], size[3]);
  test_uchar_access (dim[3], size[1], size[2], size[3]);
  test_char_access (dim[3], size[1], size[2], size[3]);
  test_complex_access (dim[3], size[1], size[2], size[3]);
  test_complex_float_access (dim[3], size[1], size[2], size[3]);
  test_complex_long_double_access (dim[3], size[1], size[2], size[3]);

  /* file */

  test_file_bin (dim[3], size[1], size[2], size[3]);
  test_float_file_bin (dim[3], size[1], size[2], size[3]);
  test_long_double_file_bin (dim[3], size[1], size[2], size[3]);
  test_ulong_file_bin (dim[3], size[1], size[2], size[3]);
  test_long_file_bin (dim[3], size[1], size[2], size[3]);
  test_uint_file_bin (dim[3], size[1], size[2], size[3]);
  test_int_file_bin (dim[3], size[1], size[2], size[3]);
  test_ushort_file_bin (dim[3], size[1], size[2], size[3]);
  test_short_file_bin (dim[3], size[1], size[2], size[3]);
  test_uchar_file_bin (dim[3], size[1], size[2], size[3]);
  test_char_file_bin (dim[3], size[1], size[2], size[3]);
  test_complex_file_bin (dim[3], size[1], size[2], size[3]);
  test_complex_float_file_bin (dim[3], size[1], size[2], size[3]);
  test_complex_long_double_file_bin (dim[3], size[1], size[2], size[3]);  

  test_file_txt (dim[3], size[1], size[2], size[3]);
  test_float_file_txt (dim[3], size[1], size[2], size[3]);
  test_long_double_file_txt (dim[3], size[1], size[2], size[3]);
  test_ulong_file_txt (dim[3], size[1], size[2], size[3]);
  test_long_file_txt (dim[3], size[1], size[2], size[3]);
  test_uint_file_txt (dim[3], size[1], size[2], size[3]);
  test_int_file_txt (dim[3], size[1], size[2], size[3]);
  test_ushort_file_txt (dim[3], size[1], size[2], size[3]);
  test_short_file_txt (dim[3], size[1], size[2], size[3]);
  test_uchar_file_txt (dim[3], size[1], size[2], size[3]);
  test_char_file_txt (dim[3], size[1], size[2], size[3]);
  test_complex_file_txt (dim[3], size[1], size[2], size[3]);
  test_complex_float_file_txt (dim[3], size[1], size[2], size[3]);
  test_complex_long_double_file_txt (dim[3], size[1], size[2], size[3]);

  /* Properties */
  
  gsl_error_handler_t * old_handler;
  old_handler = gsl_set_error_handler (&my_error_handler);
  
  test_prop (dim[3], size[1], size[2], size[3]);
  test_float_prop (dim[3], size[1], size[2], size[3]);
  test_long_double_prop (dim[3], size[1], size[2], size[3]);
  test_ulong_prop (dim[3], size[1], size[2], size[3]);
  test_long_prop (dim[3], size[1], size[2], size[3]);
  test_uint_prop (dim[3], size[1], size[2], size[3]);
  test_int_prop (dim[3], size[1], size[2], size[3]);
  test_ushort_prop (dim[3], size[1], size[2], size[3]);
  test_short_prop (dim[3], size[1], size[2], size[3]);
  test_uchar_prop (dim[3], size[1], size[2], size[3]);
  test_char_prop (dim[3], size[1], size[2], size[3]);
  test_complex_prop (dim[3], size[1], size[2], size[3]);
  test_complex_float_prop (dim[3], size[1], size[2], size[3]);
  test_complex_long_double_prop (dim[3], size[1], size[2], size[3]);

  gsl_set_error_handler (old_handler);

  /* Views */

  test_view (dim[3], size[1], size[2], size[3]);
  test_float_view (dim[3], size[1], size[2], size[3]);
  test_long_double_view (dim[3], size[1], size[2], size[3]);
  test_ulong_view (dim[3], size[1], size[2], size[3]);
  test_long_view (dim[3], size[1], size[2], size[3]);
  test_uint_view (dim[3], size[1], size[2], size[3]);
  test_int_view (dim[3], size[1], size[2], size[3]);
  test_ushort_view (dim[3], size[1], size[2], size[3]);
  test_short_view (dim[3], size[1], size[2], size[3]);
  test_uchar_view (dim[3], size[1], size[2], size[3]);
  test_char_view (dim[3], size[1], size[2], size[3]);
  test_complex_view (dim[3], size[1], size[2], size[3]);
  test_complex_float_view (dim[3], size[1], size[2], size[3]);
  test_complex_long_double_view (dim[3], size[1], size[2], size[3]);

  test_view_array (dim[3], size[1], size[2], size[3]);
  test_float_view_array (dim[3], size[1], size[2], size[3]);
  test_long_double_view_array (dim[3], size[1], size[2], size[3]);
  test_ulong_view_array (dim[3], size[1], size[2], size[3]);
  test_long_view_array (dim[3], size[1], size[2], size[3]);
  test_uint_view_array (dim[3], size[1], size[2], size[3]);
  test_int_view_array (dim[3], size[1], size[2], size[3]);
  test_ushort_view_array (dim[3], size[1], size[2], size[3]);
  test_short_view_array (dim[3], size[1], size[2], size[3]);
  test_uchar_view_array (dim[3], size[1], size[2], size[3]);
  test_char_view_array (dim[3], size[1], size[2], size[3]);
  test_complex_view_array (dim[3], size[1], size[2], size[3]);
  test_complex_float_view_array (dim[3], size[1], size[2], size[3]);
  test_complex_long_double_view_array (dim[3], size[1], size[2], size[3]);

  test_view_from (size[1], size[2]);
  test_float_view_from (size[1], size[2]);
  test_long_double_view_from (size[1], size[2]);
  test_ulong_view_from (size[1], size[2]);
  test_long_view_from (size[1], size[2]);
  test_uint_view_from (size[1], size[2]);
  test_int_view_from (size[1], size[2]);
  test_ushort_view_from (size[1], size[2]);
  test_short_view_from (size[1], size[2]);
  test_uchar_view_from (size[1], size[2]);
  test_char_view_from (size[1], size[2]);
  test_complex_view_from (size[1], size[2]);
  test_complex_float_view_from (size[1], size[2]);
  test_complex_long_double_view_from (size[1], size[2]);

  test_view_to (size[1], size[2]);
  test_float_view_to (size[1], size[2]);
  test_long_double_view_to (size[1], size[2]);
  test_ulong_view_to (size[1], size[2]);
  test_long_view_to (size[1], size[2]);
  test_uint_view_to (size[1], size[2]);
  test_int_view_to (size[1], size[2]);
  test_ushort_view_to (size[1], size[2]);
  test_short_view_to (size[1], size[2]);
  test_uchar_view_to (size[1], size[2]);
  test_char_view_to (size[1], size[2]);
  test_complex_view_to (size[1], size[2]);
  test_complex_float_view_to (size[1], size[2]);
  test_complex_long_double_view_to (size[1], size[2]);

  /* Operators */

  test_oper (dim[3], size[1], size[2], size[3]);
  test_float_oper (dim[3], size[1], size[2], size[3]);
  test_long_double_oper (dim[3], size[1], size[2], size[3]);
  test_ulong_oper (dim[3], size[1], size[2], size[3]);
  test_long_oper (dim[3], size[1], size[2], size[3]);
  test_uint_oper (dim[3], size[1], size[2], size[3]);
  test_int_oper (dim[3], size[1], size[2], size[3]);
  test_ushort_oper (dim[3], size[1], size[2], size[3]);
  test_short_oper (dim[3], size[1], size[2], size[3]);
  test_uchar_oper (dim[3], size[1], size[2], size[3]);
  test_char_oper (dim[3], size[1], size[2], size[3]);
  test_complex_oper (dim[3], size[1], size[2], size[3]);
  test_complex_float_oper (dim[3], size[1], size[2], size[3]);
  test_complex_long_double_oper (dim[3], size[1], size[2], size[3]);

  /* Arithmetic operators */

  test_oper_arithmetic (dim[3], size[1], size[2], size[3]);
  test_float_oper_arithmetic (dim[3], size[1], size[2], size[3]);
  test_long_double_oper_arithmetic (dim[3], size[1], size[2], size[3]);
  test_ulong_oper_arithmetic (dim[3], size[1], size[2], size[3]);
  test_long_oper_arithmetic (dim[3], size[1], size[2], size[3]);
  test_uint_oper_arithmetic (dim[3], size[1], size[2], size[3]);
  test_int_oper_arithmetic (dim[3], size[1], size[2], size[3]);
  test_ushort_oper_arithmetic (dim[3], size[1], size[2], size[3]);
  test_short_oper_arithmetic (dim[3], size[1], size[2], size[3]);
  test_uchar_oper_arithmetic (dim[3], size[1], size[2], size[3]);
  test_char_oper_arithmetic (dim[3], size[1], size[2], size[3]);
  test_complex_oper_arithmetic (dim[3], size[1], size[2], size[3]);
  test_complex_float_oper_arithmetic (dim[3], size[1], size[2], size[3]);
  test_complex_long_double_oper_arithmetic (dim[3], size[1], size[2], size[3]);

  /* Logical operators */

  test_oper_logical (dim[3], size[1], size[2], size[3]);
  test_float_oper_logical (dim[3], size[1], size[2], size[3]);
  test_long_double_oper_logical (dim[3], size[1], size[2], size[3]);
  test_ulong_oper_logical (dim[3], size[1], size[2], size[3]);
  test_long_oper_logical (dim[3], size[1], size[2], size[3]);
  test_uint_oper_logical (dim[3], size[1], size[2], size[3]);
  test_int_oper_logical (dim[3], size[1], size[2], size[3]);
  test_ushort_oper_logical (dim[3], size[1], size[2], size[3]);
  test_short_oper_logical (dim[3], size[1], size[2], size[3]);
  test_uchar_oper_logical (dim[3], size[1], size[2], size[3]);
  test_char_oper_logical (dim[3], size[1], size[2], size[3]);

  /* Trigonometric operators */

  test_oper_trig (dim[3], size[1], size[2], size[3]);
  test_float_oper_trig (dim[3], size[1], size[2], size[3]);
  test_long_double_oper_trig (dim[3], size[1], size[2], size[3]);
  test_ulong_oper_trig (dim[3], size[1], size[2], size[3]);
  test_long_oper_trig (dim[3], size[1], size[2], size[3]);
  test_uint_oper_trig (dim[3], size[1], size[2], size[3]);
  test_int_oper_trig (dim[3], size[1], size[2], size[3]);
  test_ushort_oper_trig (dim[3], size[1], size[2], size[3]);
  test_short_oper_trig (dim[3], size[1], size[2], size[3]);
  test_uchar_oper_trig (dim[3], size[1], size[2], size[3]);
  test_char_oper_trig (dim[3], size[1], size[2], size[3]);
  test_complex_oper_trig (dim[3], size[1], size[2], size[3]);

  /* Exponential and logarithmic operators */

  test_oper_explog (dim[3], size[1], size[2], size[3]);
  test_float_oper_explog (dim[3], size[1], size[2], size[3]);
  test_long_double_oper_explog (dim[3], size[1], size[2], size[3]);
  test_ulong_oper_explog (dim[3], size[1], size[2], size[3]);
  test_long_oper_explog (dim[3], size[1], size[2], size[3]);
  test_uint_oper_explog (dim[3], size[1], size[2], size[3]);
  test_int_oper_explog (dim[3], size[1], size[2], size[3]);
  test_ushort_oper_explog (dim[3], size[1], size[2], size[3]);
  test_short_oper_explog (dim[3], size[1], size[2], size[3]);
  test_uchar_oper_explog (dim[3], size[1], size[2], size[3]);
  test_char_oper_explog (dim[3], size[1], size[2], size[3]);
  test_complex_oper_explog (dim[3], size[1], size[2], size[3]);

  /* Rounding and truncation operators */
  
  test_oper_round (dim[3], size[1], size[2], size[3]);
  test_float_oper_round (dim[3], size[1], size[2], size[3]);
  test_long_double_oper_round (dim[3], size[1], size[2], size[3]);
  test_ulong_oper_round (dim[3], size[1], size[2], size[3]);
  test_long_oper_round (dim[3], size[1], size[2], size[3]);
  test_uint_oper_round (dim[3], size[1], size[2], size[3]);
  test_int_oper_round (dim[3], size[1], size[2], size[3]);
  test_ushort_oper_round (dim[3], size[1], size[2], size[3]);
  test_short_oper_round (dim[3], size[1], size[2], size[3]);
  test_uchar_oper_round (dim[3], size[1], size[2], size[3]);
  test_char_oper_round (dim[3], size[1], size[2], size[3]);
  test_complex_oper_round (dim[3], size[1], size[2], size[3]);
  test_complex_float_oper_round (dim[3], size[1], size[2], size[3]);
  test_complex_long_double_oper_round (dim[3], size[1], size[2], size[3]);

  /* Statistics */
  
  test_oper_stat (dim[3], size[1], size[2], size[3]);
  test_float_oper_stat (dim[3], size[1], size[2], size[3]);
  test_long_double_oper_stat (dim[3], size[1], size[2], size[3]);
  test_ulong_oper_stat (dim[3], size[1], size[2], size[3]);
  test_long_oper_stat (dim[3], size[1], size[2], size[3]);
  test_uint_oper_stat (dim[3], size[1], size[2], size[3]);
  test_int_oper_stat (dim[3], size[1], size[2], size[3]);
  test_ushort_oper_stat (dim[3], size[1], size[2], size[3]);
  test_short_oper_stat (dim[3], size[1], size[2], size[3]);
  test_uchar_oper_stat (dim[3], size[1], size[2], size[3]);
  test_char_oper_stat (dim[3], size[1], size[2], size[3]);

  /* Sorting */
  
  test_oper_sort (dim[3], size[1], size[2], size[3]);
  test_float_oper_sort (dim[3], size[1], size[2], size[3]);
  test_long_double_oper_sort (dim[3], size[1], size[2], size[3]);
  test_ulong_oper_sort (dim[3], size[1], size[2], size[3]);
  test_long_oper_sort (dim[3], size[1], size[2], size[3]);
  test_uint_oper_sort (dim[3], size[1], size[2], size[3]);
  test_int_oper_sort (dim[3], size[1], size[2], size[3]);
  test_ushort_oper_sort (dim[3], size[1], size[2], size[3]);
  test_short_oper_sort (dim[3], size[1], size[2], size[3]);
  test_uchar_oper_sort (dim[3], size[1], size[2], size[3]);
  test_char_oper_sort (dim[3], size[1], size[2], size[3]);

  test_oper_sort_index (dim[3], size[1], size[2], size[3]);
  test_float_oper_sort_index (dim[3], size[1], size[2], size[3]);
  test_long_double_oper_sort_index (dim[3], size[1], size[2], size[3]);
  test_ulong_oper_sort_index (dim[3], size[1], size[2], size[3]);
  test_long_oper_sort_index (dim[3], size[1], size[2], size[3]);
  test_uint_oper_sort_index (dim[3], size[1], size[2], size[3]);
  test_int_oper_sort_index (dim[3], size[1], size[2], size[3]);
  test_ushort_oper_sort_index (dim[3], size[1], size[2], size[3]);
  test_short_oper_sort_index (dim[3], size[1], size[2], size[3]);
  test_uchar_oper_sort_index (dim[3], size[1], size[2], size[3]);
  test_char_oper_sort_index (dim[3], size[1], size[2], size[3]);


  gsl_rng_free (rng);

  exit (gsl_test_summary ());
}

void
my_error_handler (const char *reason, const char *file, int line, int err)
{
  if (0)
    printf ("(caught [%s:%d: %s (%d)])\n", file, line, reason, err);
  status = 1;
}

/* tensor/test_complex_source.c
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

/* Allocation */

void
FUNCTION (test, alloc) (const size_t dim, ...);

void
FUNCTION (test, aalloc) (const size_t dim,
                         const size_t size0,
                         const size_t size1,
                         const size_t size2);

void
FUNCTION (test, calloc) (const size_t dim,
                         const size_t size0,
                         const size_t size1,
                         const size_t size2);

void
FUNCTION (test, copy) (const size_t dim,
                       const size_t size0,
                       const size_t size1,
                       const size_t size2);

void
FUNCTION (test, copy_nctg) (const size_t dim,
                            const size_t size0,
                            const size_t size1,
                            const size_t size2);

/* Tensor element access */

void
FUNCTION (test, access) (const size_t dim,
                         const size_t size0,
                         const size_t size1,
                         const size_t size2);

/* Tensor file io */

void
FUNCTION (test, file_bin) (const size_t dim,
                           const size_t size0,
                           const size_t size1,
                           const size_t size2);

void
FUNCTION (test, file_txt) (const size_t dim,
                           const size_t size0,
                           const size_t size1,
                           const size_t size2);

/* Tensor properties */

void
FUNCTION (test, prop) (const size_t dim,
                       const size_t size0,
                       const size_t size1,
                       const size_t size2);

/* Tensor views */

void
FUNCTION (test, view) (const size_t dim,
                       const size_t size0,
                       const size_t size1,
                       const size_t size2);

void
FUNCTION (test, view_array) (const size_t dim,
                             const size_t size0,
                             const size_t size1,
                             const size_t size2);

void
FUNCTION (test, view_from) (const size_t size0,
                            const size_t size1);

void
FUNCTION (test, view_to) (const size_t size0,
                          const size_t size1);

/* Tensor operators */

void
FUNCTION (test, oper) (const size_t dim,
                       const size_t size0,
                       const size_t size1,
                       const size_t size2);

/* Arithmetic operators */

void
FUNCTION (test, oper_arithmetic) (const size_t dim,
                                  const size_t size0,
                                  const size_t size1,
                                  const size_t size2);

/* Trigonometric operators */

void
FUNCTION (test, oper_trig) (const size_t dim,
                            const size_t size0,
                            const size_t size1,
                            const size_t size2);

/* Exponential and logarithmic operators */

void
FUNCTION (test, oper_explog) (const size_t dim,
                              const size_t size0,
                              const size_t size1,
                              const size_t size2);

/* Rounding and truncation operators */

void
FUNCTION (test, oper_round) (const size_t dim,
                             const size_t size0,
                             const size_t size1,
                             const size_t size2);

void
FUNCTION (test, alloc) (const size_t dim, ...)
{
  va_list argp1, argp2;

#ifdef va_copy
  va_copy (argp2, argp1);
#else
  argp2 = argp1;
#endif  /* va_copy */

  va_start (argp1, dim);

  TYPE (tensor) * t;

  t = FUNCTION (tensor, valloc) (dim, argp1);

  va_end (argp1);

  gsl_test (t->data == 0, NAME (tensor)
            "_valloc returns valid pointer");

  gsl_test (t->dim != dim, NAME (tensor)
            "_valloc returns correct dim");

  va_start (argp2, dim);

  size_t d;
  for (d = 0; d < dim; ++d)
    {
      gsl_test (t->size[d] != va_arg(argp2, size_t), NAME (tensor)
                "_valloc returns correct size %zu for dim %zu",
                t->size[d], d);
    }

  va_end (argp2);

  FUNCTION (tensor, free) (t);
}

void
FUNCTION (test, aalloc) (const size_t dim,
                         const size_t size0,
                         const size_t size1,
                         const size_t size2)
{
  const size_t size[] = {size0, size1, size2};

  TYPE (tensor) * t;

  t = FUNCTION (tensor, aalloc) (dim, size);

  gsl_test (t->data == 0, NAME (tensor)
            "_aalloc returns valid pointer");

  gsl_test (t->dim != dim, NAME (tensor)
            "_aalloc returns correct dim");

  size_t d;
  for (d = 0; d < dim; ++d)
    {
      gsl_test (t->size[d] != size[d], NAME (tensor)
                "_aalloc returns correct size %zu for dim %zu",
                t->size[d], d);
    }

  FUNCTION (tensor, free) (t);
}

void
FUNCTION (test, calloc) (const size_t dim,
                         const size_t size0,
                         const size_t size1,
                         const size_t size2)
{
  TYPE (tensor) * t;

  t = FUNCTION (tensor, calloc) (dim, size0, size1, size2);

  const BASE zero = ZERO;
  int status = 0;

  size_t i, j, k;
  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          const BASE element = FUNCTION (tensor, get) (t, i, j, k);
          if (GSL_REAL (element) != GSL_REAL (zero) ||
              GSL_IMAG (element) != GSL_IMAG (zero))
            {
              status = 1;
              break;
            }
        }

  gsl_test (status, NAME (tensor)
            "_calloc all tensor elements are zero");

  FUNCTION (tensor, free) (t);
}

void
FUNCTION (test, copy) (const size_t dim,
                       const size_t size0,
                       const size_t size1,
                       const size_t size2)
{
  TYPE (tensor) * t_in;
  TYPE (tensor) * t_out;

  t_in = FUNCTION (tensor, alloc) (dim, size0, size1, size2);

  BASE x, y;
  int status = 0;

  size_t i, j, k;
  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          GSL_REAL (x) = i * size0 + j * size1 + k;
          GSL_IMAG (x) = i * size0 + j * size1 + 2 * k;
          FUNCTION (tensor, set) (t_in, x, i, j, k);
        }

  t_out = FUNCTION (tensor, copy) (t_in);

  gsl_test (FUNCTION (tensor, tsize) (t_in) !=
            FUNCTION (tensor, tsize) (t_out),
            NAME (tensor)
            "_copy tensor and its copy have same number of elements");
  gsl_test (FUNCTION (tensor, is_view) (t_out),
            NAME (tensor)
            "_copy copied tensor is not a view");

  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          x = FUNCTION (tensor, get) (t_in, i, j, k);
          y = FUNCTION (tensor, get) (t_out, i, j, k);

          if (GSL_REAL (x) != GSL_REAL (y) ||
              GSL_IMAG (x) != GSL_IMAG (y))
            {
              status = 1;
              break;
            }
        }

  gsl_test (status,
            NAME (tensor)
            "_copy tensor and its copy have equal elements");

  FUNCTION (tensor, free) (t_in);
  FUNCTION (tensor, free) (t_out);
}

void
FUNCTION (test, copy_nctg) (const size_t dim,
                            const size_t size0,
                            const size_t size1,
                            const size_t size2)
{
  TYPE (tensor) * t_in;
  TYPE (tensor) * t_out;

  t_in = FUNCTION (tensor, alloc) (dim, size0, size1, size2);

  /* Emulate non-contiguous tensor */
  size_t d;
  for (d = 0; d < dim; ++d)
    {
      t_in->stride[d] = t_in->size[d] / 2 + 1;

      if (t_in->size[d] > 1)
        t_in->size[d] = t_in->size[d] / t_in->stride[d];
    }

  BASE x, y;
  int status = 0;

  size_t i, j, k;
  for (i = 0; i < t_in->size[0]; ++i)
    for (j = 0; j < t_in->size[1]; ++j)
      for (k = 0; k < t_in->size[2]; ++k)
        {
          GSL_REAL (x) = i * size0 + j * size1 + k;
          GSL_IMAG (x) = i * size0 + j * size1 + 2 * k;
          FUNCTION (tensor, set) (t_in, x, i, j, k);
        }

  t_out = FUNCTION (tensor, copy) (t_in);

  gsl_test (FUNCTION (tensor, tsize) (t_in) !=
            FUNCTION (tensor, tsize) (t_out),
            NAME (tensor)
            "_copy (non-contiguous) tensor and its copy "
            "have same number of elements");

  gsl_test (FUNCTION (tensor, is_view) (t_out),
            NAME (tensor)
            "_copy copied tensor is not a view");

  gsl_test (!FUNCTION (tensor, is_contiguous) (t_out),
            NAME (tensor)
            "_copy copied tensor is contiguous");

  for (i = 0; i < t_in->size[0]; ++i)
    for (j = 0; j < t_in->size[1]; ++j)
      for (k = 0; k < t_in->size[2]; ++k)
        {
          x = FUNCTION (tensor, get) (t_in, i, j, k);
          y = FUNCTION (tensor, get) (t_out, i, j, k);

          if (GSL_REAL (x) != GSL_REAL (y) ||
              GSL_IMAG (x) != GSL_IMAG (y))
            {
              status = 1;
              break;
            }
        }

  gsl_test (status,
            NAME (tensor)
            "_copy (non-contiguous) tensor and its "
            "copy have equal elements");

  FUNCTION (tensor, free) (t_in);
  FUNCTION (tensor, free) (t_out);
}

void
FUNCTION (test, access) (const size_t dim,
                         const size_t size0,
                         const size_t size1,
                         const size_t size2)
{
  TYPE (tensor) * t;

  t = FUNCTION (tensor, alloc) (dim, size0, size1, size2);

  /* set */

  BASE x, y;
  BASE * pdata;
  const BASE * cpdata;
  int status = 0;

  size_t i, j, k;
  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          GSL_REAL (x) = i * size0 + j * size1 + k;
          GSL_IMAG (x) = GSL_REAL (x) + 1;
          FUNCTION (tensor, set) (t, x, i, j, k);
        }

  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          GSL_REAL (x) = i * size0 + j * size1 + k;
          GSL_IMAG (x) = GSL_REAL (x) + 1;

          cpdata = FUNCTION (tensor, const_ptr) (t, i, j, k);

          if (GSL_REAL (*cpdata) != GSL_REAL (x) ||
              GSL_IMAG (*cpdata) != GSL_IMAG (x))
            {
              status = 1;
              break;
            }
        }

  gsl_test (status, NAME (tensor)
            "_set writes into tensor");

  /* get */

  GSL_REAL (x) = size0 * size1 * size2;
  GSL_IMAG (x) = GSL_REAL (x) - 1;

  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          pdata = FUNCTION (tensor, ptr) (t, i, j, k);

          GSL_REAL (*pdata) = GSL_REAL (x);
          GSL_IMAG (*pdata) = GSL_IMAG (x);

          GSL_REAL (x) = GSL_REAL (x) - 1;
          GSL_IMAG (x) = GSL_IMAG (x) - 1;
        }

  GSL_REAL (x) = size0 * size1 * size2;
  GSL_IMAG (x) = GSL_REAL (x) - 1;

  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          y = FUNCTION (tensor, get) (t, i, j, k);
          if (GSL_REAL (y) != GSL_REAL (x) ||
              GSL_IMAG (y) != GSL_IMAG (x))
            {
              status = 1;
              break;
            }

          GSL_REAL (x) = GSL_REAL (x) - 1;
          GSL_IMAG (x) = GSL_IMAG (x) - 1;
        }

  gsl_test (status, NAME (tensor)
            "_get reads from tensor");

  /* set_all */

  GSL_REAL (x) = 42;
  GSL_IMAG (x) = 42;

  FUNCTION (tensor, set_all) (t, x);

  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          y = FUNCTION (tensor, get) (t, i, j, k);
          if (GSL_REAL (y) != GSL_REAL (x) ||
              GSL_IMAG (y) != GSL_IMAG (x))
            {
              status = 1;
              break;
            }
        }

  gsl_test (status, NAME (tensor)
            "_set_all writes into tensor");

  FUNCTION (tensor, free) (t);
}

void
FUNCTION (test, file_bin) (const size_t dim,
                           const size_t size0,
                           const size_t size1,
                           const size_t size2)
{
  TYPE (tensor) * t, * u;

  t = FUNCTION (tensor, alloc) (dim, size0, size1, size2);
  u = FUNCTION (tensor, alloc) (dim, size0, size1, size2);

  BASE x, y;
  GSL_REAL (x) = 0;
  GSL_IMAG (x) = 1;
  int status = 0;

  size_t i, j, k;
  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          FUNCTION (tensor, set) (t, x, i, j, k);
          GSL_REAL (x) = GSL_REAL (x) + 1;
          GSL_IMAG (x) = GSL_IMAG (x) + 1;
        }

#ifdef NO_INLINE
  char filename[] = "test_static.dat";
#else
  char filename[] = "test.dat";
#endif

  FILE * f;

  /* Write and read binary */

  f = fopen (filename, "wb");

  FUNCTION (tensor, fwrite) (f, t);

  fclose (f);

  f = fopen (filename, "rb");

  FUNCTION (tensor, fread) (f, u);

  fclose (f);

  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          x = FUNCTION (tensor, get) (u, i, j, k);
          y = FUNCTION (tensor, get) (t, i, j, k);
          if (GSL_REAL (x) != GSL_REAL (y) ||
              GSL_IMAG (x) != GSL_IMAG (y))
            {
              status = 1;
              break;
            }
        }

  gsl_test (status, NAME (tensor)
            "_fwrite/fread file io");

  FUNCTION (tensor, free) (t);
  FUNCTION (tensor, free) (u);
}

#if !(USES_LONGDOUBLE && !HAVE_PRINTF_LONGDOUBLE)

void
FUNCTION (test, file_txt) (const size_t dim,
                           const size_t size0,
                           const size_t size1,
                           const size_t size2)
{
  TYPE (tensor) * t, * u;

  t = FUNCTION (tensor, alloc) (dim, size0, size1, size2);
  u = FUNCTION (tensor, alloc) (dim, size0, size1, size2);

  BASE x, y;
  GSL_REAL (x) = 0;
  GSL_IMAG (x) = 1;
  int status = 0;

  size_t i, j, k;
  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          FUNCTION (tensor, set) (t, x, i, j, k);
          GSL_REAL (x) = GSL_REAL (x) + 1;
          GSL_IMAG (x) = GSL_IMAG (x) + 1;
        }

#ifdef NO_INLINE
  char filename[] = "test_static.txt";
#else
  char filename[] = "test.txt";
#endif

  FILE * f;

  /* Write and read binary */

  f = fopen (filename, "w");

  FUNCTION (tensor, fprintf) (f, t, OUT_FORMAT);

  fclose (f);

  f = fopen (filename, "r");

  FUNCTION (tensor, fscanf) (f, u);

  fclose (f);

  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          x = FUNCTION (tensor, get) (u, i, j, k);
          y = FUNCTION (tensor, get) (t, i, j, k);
          if (GSL_REAL (x) != GSL_REAL (y) ||
              GSL_IMAG (x) != GSL_IMAG (y))
            {
              status = 1;
              break;
            }
        }

  gsl_test (status, NAME (tensor)
            "_fprintf/fscanf file io");

  FUNCTION (tensor, free) (t);
  FUNCTION (tensor, free) (u);
}

#endif  /* #if !(USES_LONGDOUBLE && !HAVE_PRINTF_LONGDOUBLE) */

void
FUNCTION (test, prop) (const size_t dim,
                       const size_t size0,
                       const size_t size1,
                       const size_t size2)
{
  TYPE (tensor) * t;

  t = FUNCTION (tensor, alloc) (dim, size0, size1, size2);

  /* tsize */

  gsl_test (FUNCTION (tensor, tsize) (t) != size0 * size1 * size2,
            NAME (tensor) "_tsize" DESC
            " returns correct total number of elements");

#if GSL_RANGE_CHECK

  /* fits_size */

  size_t d, i;
  for (d = 0; d < dim; ++d)
    {
      for (i = 0; i < 2; ++i)
        {
          int size[] = {-1, -1, -1};
          size[d] = i;
          status = 0;

          FUNCTION (tensor, fits_size)
            (t, t->size[0] + size[0],
             t->size[1] + size[1],
             t->size[2] + size[2]);

          if (i == 0)
            {
              gsl_test (!status, NAME (tensor)
                        "_fits_size catches index %zu"
                        " at upper bound", d);
            }
          else                  /* i == 1 */
            {
              gsl_test (!status, NAME (tensor)
                        "_fits_size catches index %zu"
                        " above upper bound", d);
            }
        }
    }

  /* match size */

  gsl_test (!FUNCTION (tensor, match_size) (t, t),
            NAME (tensor) "_match_size returns "
            "correct value for identity");

  /* match total size */

  gsl_test (!FUNCTION (tensor, match_tsize) (t, t),
            NAME (tensor) "_match_tsize returns "
            "correct value for identity");

#endif  /* GSL_RANGE_CHECK */

  /* is null pos neg nonneg nonpos */

  BASE x;
  GSL_REAL (x) = 0;
  GSL_IMAG (x) = 0;

  FUNCTION (tensor, set_all) (t, x);

  gsl_test (!FUNCTION (tensor, is_null) (t),
            NAME (tensor) "_is_null on zero tensor");

  gsl_test (FUNCTION (tensor, is_pos) (t),
            NAME (tensor) "_is_pos on zero tensor");

  gsl_test (FUNCTION (tensor, is_neg) (t),
            NAME (tensor) "_is_neg on zero tensor");

  gsl_test (!FUNCTION (tensor, is_nonneg) (t),
            NAME (tensor) "_is_nonneg on zero tensor");

  gsl_test (!FUNCTION (tensor, is_nonpos) (t),
            NAME (tensor) "_is_nonpos on zero tensor");

  GSL_REAL (x) = 1;
  GSL_IMAG (x) = 1;

  FUNCTION (tensor, set_all) (t, x);

  gsl_test (FUNCTION (tensor, is_null) (t),
            NAME (tensor) "_is_null on one tensor");

  gsl_test (!FUNCTION (tensor, is_pos) (t),
            NAME (tensor) "_is_pos on one tensor");

  gsl_test (FUNCTION (tensor, is_neg) (t),
            NAME (tensor) "_is_neg on one tensor");

  gsl_test (!FUNCTION (tensor, is_nonneg) (t),
            NAME (tensor) "_is_nonneg on one tensor");

  gsl_test (FUNCTION (tensor, is_nonpos) (t),
            NAME (tensor) "_is_nonpos on one tensor");

  GSL_REAL (x) = -1;
  GSL_IMAG (x) = -1;

  FUNCTION (tensor, set_all) (t, x);

  gsl_test (FUNCTION (tensor, is_null) (t),
            NAME (tensor) "_is_null on negative tensor");

  gsl_test (FUNCTION (tensor, is_pos) (t),
            NAME (tensor) "_is_pos on negative tensor");

  gsl_test (!FUNCTION (tensor, is_neg) (t),
            NAME (tensor) "_is_neg on negative tensor");

  gsl_test (FUNCTION (tensor, is_nonneg) (t),
            NAME (tensor) "_is_nonneg on negative tensor");

  gsl_test (!FUNCTION (tensor, is_nonpos) (t),
            NAME (tensor) "_is_nonpos on negative tensor");

  FUNCTION (tensor, set_zero) (t);
  GSL_REAL (x) = 1;
  GSL_IMAG (x) = 1;

  FUNCTION (tensor, set) (t, x, 0, 0, 0);

  gsl_test (FUNCTION (tensor, is_null) (t),
            NAME (tensor) "_is_null on non-negative tensor");

  gsl_test (FUNCTION (tensor, is_pos) (t),
            NAME (tensor) "_is_pos on non-negative tensor");

  gsl_test (FUNCTION (tensor, is_neg) (t),
            NAME (tensor) "_is_neg on non-negative tensor");

  gsl_test (!FUNCTION (tensor, is_nonneg) (t),
            NAME (tensor) "_is_nonneg on non-negative tensor");

  gsl_test (FUNCTION (tensor, is_nonpos) (t),
            NAME (tensor) "_is_nonpos on non-negative tensor");

  /* equal */

  GSL_REAL (x) = 42;
  GSL_IMAG (x) = 42;

  FUNCTION (tensor, set_all) (t, x);

  gsl_test (!FUNCTION (tensor, equal) (t, t),
            NAME (tensor) "_equal on identity tensor");

  /* is same */

  gsl_test (!FUNCTION (tensor, is_same) (t),
            NAME (tensor) "_is_same on identity tensor");

  GSL_REAL (x) = 1;
  GSL_IMAG (x) = 1;

  FUNCTION (tensor, set) (t, x, 0, 0, 0);

  gsl_test (FUNCTION (tensor, is_same) (t),
            NAME (tensor) "_is_same on mixed tensor");

  /* is const */

  gsl_test (FUNCTION (tensor, is_const) (t, x),
            NAME (tensor) "_is_const on mixed tensor");

  GSL_REAL (x) = 42;
  GSL_IMAG (x) = 42;

  FUNCTION (tensor, set) (t, x, 0, 0, 0);

  gsl_test (!FUNCTION (tensor, is_const) (t, x),
            NAME (tensor) "_is_const on identity tensor");

  FUNCTION (tensor, free) (t);
}

void
FUNCTION (test, view) (const size_t dim,
                       const size_t size0,
                       const size_t size1,
                       const size_t size2)
{
  TYPE (tensor) * t;
  TYPE (tensor) * v;

  t = FUNCTION (tensor, alloc) (dim, size0, size1, size2);

  BASE x, y;
  int status = 0;

  size_t i, j, k;
  for (i = 0; i < t->size[0]; ++i)
    for (j = 0; j < t->size[1]; ++j)
      for (k = 0; k < t->size[2]; ++k)
        {
          GSL_REAL (x) = i * t->size[0] + j * t->size[1] + k;
          GSL_IMAG (x) = i * t->size[0] + j * t->size[1] + k + 2;
          FUNCTION (tensor, set) (t, x, i, j, k);
        }

  v = FUNCTION (tensor, view) (t, RANGE (0, t->size[0], 1),
                               RANGE (0, t->size[1], 2),
                               RANGE (0, t->size[2], 3));

  gsl_test (!FUNCTION (tensor, is_view) (v),
            NAME (tensor)
            "_view" DESC " successfully created view");

  gsl_test (FUNCTION (tensor, is_contiguous) (v),
            NAME (tensor)
            "_view" DESC " view is non-contiguous");

  size_t vi, vj, vk;
  for (i = 0, vi = 0; i < t->size[0]; i += 1, ++vi)
    for (j = 0, vj = 0; j < t->size[1]; j += 2, ++vj)
      for (k = 0, vk = 0; k < t->size[2]; k += 3, ++vk)
        {
          x = FUNCTION (tensor, get) (t, i, j, k);
          y = FUNCTION (tensor, get) (v, vi, vj, vk);

          if (GSL_REAL (x) != GSL_REAL (y) ||
              GSL_IMAG (x) != GSL_IMAG (y))
            {
              status = 1;
              break;
            }
        }

  gsl_test (status,
            NAME (tensor)
            "_view original tensor and "
            "view have equal elements");

  FUNCTION (tensor, free) (t);
  FUNCTION (tensor, free) (v);
}

void
FUNCTION (test, view_array) (const size_t dim,
                             const size_t size0,
                             const size_t size1,
                             const size_t size2)
{
  ATOMIC array[size0 * size1 * size2 * MULTIPLICITY];

  size_t x = 0;

  size_t i, j, k, m;
  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        for (m = 0; m < MULTIPLICITY; ++m)
          {
            array[x] = (ATOMIC) x++;
          }

  TYPE (tensor) * v;

  v = FUNCTION (tensor, view_array) (array, dim, size0,
                                     size1, size2);

  gsl_test (v->data == 0, NAME (tensor)
            "_view_array returns valid pointer");

  FUNCTION (tensor, free) (v);
}

void
FUNCTION (test, view_from) (const size_t size0,
                            const size_t size1)
{
  TYPE (tensor) * t;
  TYPE (gsl_vector) * v;
  TYPE (gsl_matrix) * m;

  BASE x, y;
  GSL_REAL (x) = 0;
  GSL_IMAG (x) = 1;

  int status = 0;

  /* vector */

  v = FUNCTION (gsl_vector, alloc) (size0);

  size_t i;
  for (i = 0; i < size0; ++i)
    {
      FUNCTION (gsl_vector, set) (v, i, x);
      GSL_REAL (x) = GSL_REAL (x) + 1;
      GSL_IMAG (x) = GSL_IMAG (x) + 1;
    }

  t = FUNCTION (tensor, view_vector) (v);

  gsl_test (t->dim != 1, NAME (tensor)
            "_view_vector tensor view dimension is 1");

  gsl_test (t->size[0] != v->size, NAME (tensor)
            "_view_vector vector and tensor view have same size");

  gsl_test (t->stride[0] != v->stride, NAME (tensor)
            "_view_vector vector and tensor view have same stride");

  for (i = 0; i < t->size[0]; ++i)
    {
      x = FUNCTION (gsl_vector, get) (v, i);
      y = FUNCTION (tensor, get) (t, i);

      if (GSL_REAL (x) != GSL_REAL (y) ||
          GSL_IMAG (x) != GSL_IMAG (y))
        {
          status = 1;
          break;
        }
    }

  gsl_test (status, NAME (tensor)
            "_view_vector vector and "
            "tensor view have equal elements");

  FUNCTION (tensor, free) (t);
  FUNCTION (gsl_vector, free) (v);

  /* matrix */

  m = FUNCTION (gsl_matrix, alloc) (size0, size1);

  GSL_REAL (x) = 0;
  GSL_IMAG (x) = 1;

  size_t j;
  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      {
        FUNCTION (gsl_matrix, set) (m, i, j, x);
        GSL_REAL (x) = GSL_REAL (x) + 1;
        GSL_IMAG (x) = GSL_IMAG (x) + 1;
      }

  t = FUNCTION (tensor, view_matrix) (m);

  gsl_test (t->dim != 2, NAME (tensor)
            "_view_matrix tensor view dimension is 2");

  gsl_test (t->size[0] != m->size1 ||
            t->size[1] != m->size2,
            NAME (tensor)
            "_view_matrix matrix and "
            "tensor view have same sizes");

  gsl_test (t->stride[0] != m->tda, NAME (tensor)
            "_view_matrix matrix and "
            "tensor view have same stride");

  for (i = 0; i < t->size[0]; ++i)
    for (j = 0; j < t->size[1]; ++j)
      {
        x = FUNCTION (gsl_matrix, get) (m, i, j);
        y = FUNCTION (tensor, get) (t, i, j);

        if (GSL_REAL (x) != GSL_REAL (y) ||
            GSL_IMAG (x) != GSL_IMAG (y))
          {
            status = 1;
            break;
          }
      }

  gsl_test (status, NAME (tensor)
            "_view_matrix matrix and "
            "tensor view have equal elements");

  FUNCTION (tensor, free) (t);
  FUNCTION (gsl_matrix, free) (m);
}

void
FUNCTION (test, view_to) (const size_t size0,
                          const size_t size1)
{
  TYPE (tensor) * t;
  VIEW (gsl_vector, view) vv;
  VIEW (gsl_matrix, view) mv;

  BASE x, y;
  GSL_REAL (x) = 0;
  GSL_IMAG (x) = 1;

  int status = 0;

  /* vector */

  t = FUNCTION (tensor, alloc) (1, size0);

  size_t i;
  for (i = 0; i < t->size[0]; ++i)
    {
      FUNCTION (tensor, set) (t, x, i);
      GSL_REAL (x) = GSL_REAL (x) + 1;
      GSL_IMAG (x) = GSL_IMAG (x) + 1;
    }

  vv = FUNCTION (gsl_vector, view_tensor) (t);

  gsl_test (t->size[0] != vv.vector.size, NAME (gsl_vector)
            "_view_tensor tensor and vector view have same size");

  gsl_test (t->stride[0] != vv.vector.stride, NAME (gsl_vector)
            "_view_tensor tensor and vector view have same stride");

  for (i = 0; i < t->size[0]; ++i)
    {
      x = FUNCTION (gsl_vector, get) (&vv.vector, i);
      y = FUNCTION (tensor, get) (t, i);
      if (GSL_REAL (x) != GSL_REAL (y) ||
          GSL_IMAG (x) != GSL_IMAG (y))
        {
          status = 1;
          break;
        }
    }

  gsl_test (status, NAME (gsl_vector)
            "_view_tensor tensor and "
            "vector view have equal elements");

  FUNCTION (tensor, free) (t);

  /* matrix */

  GSL_REAL (x) = 0;
  GSL_IMAG (x) = 1;

  t = FUNCTION (tensor, alloc) (2, size0, size1);

  size_t j;
  for (i = 0; i < t->size[0]; ++i)
    for (j = 0; j < t->size[1]; ++j)
      {
        FUNCTION (tensor, set) (t, x, i, j);
        GSL_REAL (x) = GSL_REAL (x) + 1;
        GSL_IMAG (x) = GSL_IMAG (x) + 1;
      }

  mv = FUNCTION (gsl_matrix, view_tensor) (t);

  gsl_test (t->size[0] != mv.matrix.size1 ||
            t->size[1] != mv.matrix.size2,
            NAME (gsl_matrix)
            "_view_tensor tensor and matrix view have same sizes");

  gsl_test (t->stride[0] != mv.matrix.tda, NAME (gsl_matrix)
            "_view_tensor tensor and matrix view have same stride");

  for (i = 0; i < t->size[0]; ++i)
    for (j = 0; j < t->size[1]; ++j)
      {
        x = FUNCTION (gsl_matrix, get) (&mv.matrix, i, j);
        y = FUNCTION (tensor, get) (t, i, j);

        if (GSL_REAL (x) != GSL_REAL (y) ||
            GSL_IMAG (x) != GSL_IMAG (y))
          {
            status = 1;
            break;
          }
      }

  gsl_test (status, NAME (gsl_matrix)
            "_view_tensor tensor and "
            "matrix view have equal elements");

  FUNCTION (tensor, free) (t);
}

void
FUNCTION (test, oper) (const size_t dim,
                       const size_t size0,
                       const size_t size1,
                       const size_t size2)
{
  TYPE (tensor) * t1, * t2, * t3;

  t1 = FUNCTION (tensor, calloc) (dim, size0, size1, size2);
  t2 = FUNCTION (tensor, alloc) (dim, size0, size1, size2);
  t3 = FUNCTION (tensor, alloc) (dim, size0, size1, size2);

  /* assign */

  BASE x;
  GSL_REAL (x) = 3;
  GSL_IMAG (x) = 4;

  FUNCTION (tensor, set_all) (t2, x);

  FUNCTION (tensor, assign) (t1, t2);

  gsl_test (!FUNCTION (tensor, equal) (t1, t2),
            NAME (tensor) "_assign original and "
            "assigned to tensor have equal elements");

  /* swap */

  int status = 0;

  GSL_REAL (x) = 3;
  GSL_IMAG (x) = 4;
  FUNCTION (tensor, set_all) (t1, x);

  GSL_REAL (x) = 5;
  GSL_IMAG (x) = 6;
  FUNCTION (tensor, set_all) (t2, x);

  FUNCTION (tensor, swap) (t1, t2);

  FUNCTION (tensor, set_all) (t3, x);
  if (!FUNCTION (tensor, equal) (t1, t3))
    status = 1;

  GSL_REAL (x) = 3;
  GSL_IMAG (x) = 4;
  FUNCTION (tensor, set_all) (t3, x);
  if (!FUNCTION (tensor, equal) (t2, t3))
    status = 1;

  gsl_test (status, NAME (tensor)
            "_swap tensors' elements have been exchanged");

  FUNCTION (tensor, free) (t1);
  FUNCTION (tensor, free) (t2);
  FUNCTION (tensor, free) (t3);

  /* morph */

  t1 = FUNCTION (tensor, alloc) (dim, size0, size1, size2);

  GSL_REAL (x) = 0;
  GSL_IMAG (x) = 1;

  size_t i, j, k;
  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          FUNCTION (tensor, set) (t1, x, i, j, k);
          GSL_REAL (x) = GSL_REAL (x) + 1;
          GSL_IMAG (x) = GSL_IMAG (x) + 1;
        }

  t2 = FUNCTION (tensor, view) (t1,
                                RANGE (0, t1->size[0], 2),
                                RANGE (0, t1->size[1], 2),
                                RANGE (0, t1->size[2], 2));

  t3 = FUNCTION (tensor, view) (t1,
                                RANGE (0, t1->size[0], 2),
                                RANGE (0, t1->size[1], 2),
                                RANGE (0, t1->size[2], 2));

  FUNCTION (tensor, morph) (t3,
                            t3->size[2],
                            t3->size[1],
                            t3->size[0]);

  gsl_test (FUNCTION (tensor, tsize) (t2) !=
            FUNCTION (tensor, tsize) (t3),
            NAME (tensor)
            "_morph original and morphed tensor total size is equal");

  BASE y;
  status = 0;
  for (i = 0; i < FUNCTION (tensor, tsize) (t3); ++i)
    {
      x = *(BASE *) (t2->data + FUNCTION (tensor, index) (t2, i));
      y = *(BASE *) (t3->data + FUNCTION (tensor, index) (t3, i));

      if (GSL_REAL (x) != GSL_REAL (y) ||
          GSL_IMAG (x) != GSL_IMAG (y))
        {
          status = 1;
          break;
        }
    }

  gsl_test (status, NAME (tensor)
            "_morph original and morphed tensor have equal elements");

  FUNCTION (tensor, free) (t1);
  FUNCTION (tensor, free) (t2);
  FUNCTION (tensor, free) (t3);

  /* deflate */

  t1 = FUNCTION (tensor, alloc) (dim,
                                 (size0 == 1) ? size0 + 1 : size0,
                                 (size1 == 1) ? size1 + 1 : size1,
                                 (size2 == 1) ? size2 + 1 : size2);

  GSL_REAL (x) = 0;
  GSL_IMAG (x) = 1;
  for (i = 0; i < t1->size[0]; ++i)
    for (j = 0; j < t1->size[1]; ++j)
      for (k = 0; k < t1->size[2]; ++k)
        {
          FUNCTION (tensor, set) (t1, x, i, j, k);
          GSL_REAL (x) = GSL_REAL (x) + 1;
          GSL_IMAG (x) = GSL_IMAG (x) + 1;
        }

  t2 = FUNCTION (tensor, view) (t1,
                                RANGE (0, t1->size[0], 1),
                                RANGE (0, 1, 1),
                                RANGE (0, t1->size[2], 1));

  t3 = FUNCTION (tensor, view) (t1,
                                RANGE (0, t1->size[0], 1),
                                RANGE (0, 1, 1),
                                RANGE (0, t1->size[2], 1));

  FUNCTION (tensor, deflate) (t2);

  gsl_test (t2->dim != 2 ||
            t2->size[0] != t1->size[0] ||
            t2->size[1] != t1->size[2],
            NAME (tensor)
            "_deflate tensor dim of size 1 have been removed");

  status = 0;
  for (i = 0; i < FUNCTION (tensor, tsize) (t2); ++i)
    {
      x = *(BASE *) (t2->data + FUNCTION (tensor, index) (t2, i));
      y = *(BASE *) (t3->data + FUNCTION (tensor, index) (t3, i));

      if (GSL_REAL (x) != GSL_REAL (y) ||
          GSL_IMAG (x) != GSL_IMAG (y))
        {
          status = 1;
          break;
        }
    }

  gsl_test (status, NAME (tensor)
            "_deflate tensor elements are unaltered");

  FUNCTION (tensor, free) (t1);
  FUNCTION (tensor, free) (t2);
  FUNCTION (tensor, free) (t3);

  /* inflate */

  t1 = FUNCTION (tensor, alloc) (dim, size0, size1, size2);

  GSL_REAL (x) = 0;
  GSL_IMAG (x) = 1;
  for (i = 0; i < t1->size[0]; ++i)
    for (j = 0; j < t1->size[1]; ++j)
      for (k = 0; k < t1->size[2]; ++k)
        {
          FUNCTION (tensor, set) (t1, x, i, j, k);
          GSL_REAL (x) = GSL_REAL (x) + 1;
          GSL_IMAG (x) = GSL_IMAG (x) + 1;
        }

  /* First dim */

  t2 = FUNCTION (tensor, view) (t1,
                                RANGE (0, t1->size[0], 2),
                                RANGE (0, t1->size[1], 2),
                                RANGE (0, t1->size[2], 2));

  t3 = FUNCTION (tensor, view) (t1,
                                RANGE (0, t1->size[0], 2),
                                RANGE (0, t1->size[1], 2),
                                RANGE (0, t1->size[2], 2));

  FUNCTION (tensor, inflate) (t2, 0);

  gsl_test (t2->dim != 4 ||
            t2->size[0] != 1 ||
            t2->size[1] != t3->size[0] ||
            t2->size[2] != t3->size[1] ||
            t2->size[3] != t3->size[2],
            NAME (tensor)
            "_inflate tensor dim of size 1 has been "
            "added as first dimension");

  status = 0;
  for (i = 0; i < FUNCTION (tensor, tsize) (t2); ++i)
    {
      x = *(BASE *) (t2->data + FUNCTION (tensor, index) (t2, i));
      y = *(BASE *) (t3->data + FUNCTION (tensor, index) (t3, i));

      if (GSL_REAL (x) != GSL_REAL (y) ||
          GSL_IMAG (x) != GSL_IMAG (y))
        {
          status = 1;
          break;
        }
    }

  gsl_test (status, NAME (tensor)
            "_inflate (first dim) tensor elements are unaltered");

  FUNCTION (tensor, free) (t2);
  FUNCTION (tensor, free) (t3);

  /* Middle dim */

  t2 = FUNCTION (tensor, view) (t1,
                                RANGE (0, t1->size[0], 2),
                                RANGE (0, t1->size[1], 2),
                                RANGE (0, t1->size[2], 2));

  t3 = FUNCTION (tensor, view) (t1,
                                RANGE (0, t1->size[0], 2),
                                RANGE (0, t1->size[1], 2),
                                RANGE (0, t1->size[2], 2));

  FUNCTION (tensor, inflate) (t2, 1);

  gsl_test (t2->dim != 4 ||
            t2->size[0] != t3->size[0] ||
            t2->size[1] != 1 ||
            t2->size[2] != t3->size[1] ||
            t2->size[3] != t3->size[2],
            NAME (tensor)
            "_inflate tensor dim of size 1 has been "
            "added as middle dimension");

  status = 0;
  for (i = 0; i < FUNCTION (tensor, tsize) (t2); ++i)
    {
      x = *(BASE *) (t2->data + FUNCTION (tensor, index) (t2, i));
      y = *(BASE *) (t3->data + FUNCTION (tensor, index) (t3, i));

      if (GSL_REAL (x) != GSL_REAL (y) ||
          GSL_IMAG (x) != GSL_IMAG (y))
        {
          status = 1;
          break;
        }
    }

  gsl_test (status, NAME (tensor)
            "_inflate (middle dim) tensor elements are unaltered");

  FUNCTION (tensor, free) (t2);
  FUNCTION (tensor, free) (t3);

  /* Last dim */

  t2 = FUNCTION (tensor, view) (t1,
                                RANGE (0, t1->size[0], 2),
                                RANGE (0, t1->size[1], 2),
                                RANGE (0, t1->size[2], 2));

  t3 = FUNCTION (tensor, view) (t1,
                                RANGE (0, t1->size[0], 2),
                                RANGE (0, t1->size[1], 2),
                                RANGE (0, t1->size[2], 2));

  FUNCTION (tensor, inflate) (t2, 3);

  gsl_test (t2->dim != 4 ||
            t2->size[0] != t3->size[0] ||
            t2->size[1] != t3->size[1] ||
            t2->size[2] != t3->size[2] ||
            t2->size[3] != 1,
            NAME (tensor)
            "_inflate tensor dim of size 1 has been "
            "added as last dimension");

  status = 0;
  for (i = 0; i < FUNCTION (tensor, tsize) (t2); ++i)
    {
      x = *(BASE *) (t2->data + FUNCTION (tensor, index) (t2, i));
      y = *(BASE *) (t3->data + FUNCTION (tensor, index) (t3, i));

      if (GSL_REAL (x) != GSL_REAL (y) ||
          GSL_IMAG (x) != GSL_IMAG (y))
        {
          status = 1;
          break;
        }
    }

  gsl_test (status, NAME (tensor)
            "_inflate (last dim) tensor elements are unaltered");

  FUNCTION (tensor, free) (t1);
  FUNCTION (tensor, free) (t2);
  FUNCTION (tensor, free) (t3);

  /* concat */

  t1 = FUNCTION (tensor, alloc) (dim, size0, size1, size2);
  t2 = FUNCTION (tensor, alloc) (dim, size0, size1, size2);

  GSL_REAL (x) = 0;
  GSL_IMAG (x) = 1;
  for (i = 0; i < t1->size[0]; ++i)
    for (j = 0; j < t1->size[1]; ++j)
      for (k = 0; k < t1->size[2]; ++k)
        {
          FUNCTION (tensor, set) (t1, x, i, j, k);
          GSL_REAL (x) = GSL_REAL (x) + 1;
          GSL_IMAG (x) = GSL_IMAG (x) + 1;

          FUNCTION (tensor, set) (t2, x, i, j, k);
          GSL_REAL (x) = GSL_REAL (x) + 1;
          GSL_IMAG (x) = GSL_IMAG (x) + 1;
        }

  /* First dim */

  t3 = FUNCTION (tensor, concat) (0, 2, t1, t2);

  gsl_test (t3->size[0] != t1->size[0] + t2->size[0] ||
            t3->size[1] != t1->size[1] ||
            t3->size[2] != t1->size[2],
            NAME (tensor)
            "_concat (first dim) has correct sizes");

  TYPE (tensor) * v;

  v = FUNCTION (tensor, view) (t3,
                               RANGE (0, t1->size[0], 1),
                               RANGE (0, t1->size[1], 1),
                               RANGE (0, t1->size[2], 1));

  gsl_test (!FUNCTION (tensor, equal) (v, t1),
            NAME (tensor)
            "_concat (first dim) resulting tensor has "
            "matching elements with first operand");

  FUNCTION (tensor, free) (v);

  v = FUNCTION (tensor, view)
    (t3,
     RANGE (t1->size[0], t3->size[0], 1),
     RANGE (0, t2->size[1], 1),
     RANGE (0, t2->size[2], 1));

  gsl_test (!FUNCTION (tensor, equal) (v, t2),
            NAME (tensor)
            "_concat (first dim) resulting tensor has "
            "matching elements with second operand");

  FUNCTION (tensor, free) (t3);
  FUNCTION (tensor, free) (v);

  /* Middle dim */

  t3 = FUNCTION (tensor, concat) (1, 2, t1, t2);

  gsl_test (t3->size[0] != t1->size[0] ||
            t3->size[1] != t1->size[1] + t2->size[1] ||
            t3->size[2] != t1->size[2],
            NAME (tensor)
            "_concat (middle dim) has correct sizes");

  v = FUNCTION (tensor, view) (t3,
                               RANGE (0, t1->size[0], 1),
                               RANGE (0, t1->size[1], 1),
                               RANGE (0, t1->size[2], 1));

  gsl_test (!FUNCTION (tensor, equal) (v, t1),
            NAME (tensor)
            "_concat (middle dim) resulting tensor has "
            "matching elements with first operand");

  FUNCTION (tensor, free) (v);

  v = FUNCTION (tensor, view)
    (t3,
     RANGE (0, t2->size[0], 1),
     RANGE (t1->size[1], t3->size[1], 1),
     RANGE (0, t2->size[2], 1));

  gsl_test (!FUNCTION (tensor, equal) (v, t2),
            NAME (tensor)
            "_concat (middle dim) resulting tensor has "
            "matching elements with second operand");

  FUNCTION (tensor, free) (t3);
  FUNCTION (tensor, free) (v);

  /* Last dim */

  t3 = FUNCTION (tensor, concat) (2, 2, t1, t2);

  gsl_test (t3->size[0] != t1->size[0] ||
            t3->size[1] != t1->size[1] ||
            t3->size[2] != t1->size[2] + t2->size[2],
            NAME (tensor)
            "_concat (last dim) has correct sizes");

  v = FUNCTION (tensor, view) (t3,
                               RANGE (0, t1->size[0], 1),
                               RANGE (0, t1->size[1], 1),
                               RANGE (0, t1->size[2], 1));

  gsl_test (!FUNCTION (tensor, equal) (v, t1),
            NAME (tensor)
            "_concat (last dim) resulting tensor has "
            "matching elements with first operand");

  FUNCTION (tensor, free) (v);

  v = FUNCTION (tensor, view)
    (t3,
     RANGE (0, t2->size[0], 1),
     RANGE (0, t2->size[1], 1),
     RANGE (t1->size[2], t3->size[2], 1));

  gsl_test (!FUNCTION (tensor, equal) (v, t2),
            NAME (tensor)
            "_concat (last dim) resulting tensor has "
            "matching elements with second operand");

  FUNCTION (tensor, free) (t1);
  FUNCTION (tensor, free) (t2);
  FUNCTION (tensor, free) (t3);
  FUNCTION (tensor, free) (v);
}

void
FUNCTION (test, oper_arithmetic) (const size_t dim,
                                  const size_t size0,
                                  const size_t size1,
                                  const size_t size2)
{
  TYPE (tensor) * t, * u;
  t = FUNCTION (tensor, alloc) (dim, size0, size1, size2);
  u = FUNCTION (tensor, alloc) (dim, size0, size1, size2);

  BASE x, y, z;
  int status = 0;

  /* abs (magnitude) */

  GSL_REAL (x) = 0;
  GSL_IMAG (x) = 1;

  size_t i, j, k;
  for (i = 0; i < t->size[0]; ++i)
    for (j = 0; j < t->size[1]; ++j)
      for (k = 0; k < t->size[2]; ++k)
        {
          FUNCTION (tensor, set) (t, x, i, j, k);

          GSL_REAL (x) += 1;
          GSL_IMAG (x) += 1;
        }

  FUNCTION (tensor, abs) (t);

  GSL_REAL (y) = 0;
  GSL_IMAG (y) = 1;

  ATOMIC mag;
  for (i = 0; i < t->size[0]; ++i)
    for (j = 0; j < t->size[1]; ++j)
      for (k = 0; k < t->size[2]; ++k)
        {
          x = FUNCTION (tensor, get) (t, i, j, k);

          mag = SQRT (GSL_REAL (y) * GSL_REAL (y) +
                      GSL_IMAG (y) * GSL_IMAG (y));

          if (GSL_IMAG (x) != 0 ||
              GSL_REAL (x) != mag)
            {
              status = 1;
              break;
            }

          GSL_REAL (y) += 1;
          GSL_IMAG (y) += 1;
        }

  gsl_test (status, NAME (tensor)
            "_abs return correct magnitude");

  /* negative */

  GSL_REAL (x) = 1;
  GSL_IMAG (x) = 1;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, neg) (t);

  gsl_test (!FUNCTION (tensor, is_neg) (t),
            NAME (tensor) "_neg on positive tensor");

  FUNCTION (tensor, set_zero) (t);

  FUNCTION (tensor, neg) (t);

  gsl_test (!FUNCTION (tensor, is_null) (t),
            NAME (tensor) "_neg on zero tensor");

  GSL_REAL (x) = -1;
  GSL_IMAG (x) = -1;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, neg) (t);

  gsl_test (!FUNCTION (tensor, is_pos) (t),
            NAME (tensor) "_neg on negative tensor");

  GSL_REAL (x) = 1;
  GSL_IMAG (x) = -1;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, neg) (t);

  GSL_REAL (y) = -1;
  GSL_IMAG (y) = 1;

  gsl_test (!FUNCTION (tensor, is_const) (t, y),
            NAME (tensor) "_neg on mixed tensor");

  /* inv */

  GSL_REAL (x) = 1;
  GSL_IMAG (x) = 1;

  FUNCTION (tensor, set_all) (t, x);
  FUNCTION (tensor, inv) (t);

  GSL_REAL (y) = (1 / SQRT (2)) * (1 / SQRT (2));
  GSL_IMAG (y) = -(1 / SQRT (2)) * (1 / SQRT (2));

  gsl_test (!FUNCTION (tensor, is_const) (t, y),
            NAME (tensor)
            "_inv returns correct "
            "value in first quadrant");

  GSL_REAL (x) = -1;
  GSL_IMAG (x) = 1;

  FUNCTION (tensor, set_all) (t, x);
  FUNCTION (tensor, inv) (t);

  GSL_REAL (y) = -(1 / SQRT (2)) * (1 / SQRT (2));
  GSL_IMAG (y) = -(1 / SQRT (2)) * (1 / SQRT (2));

  gsl_test (!FUNCTION (tensor, is_const) (t, y),
            NAME (tensor)
            "_inv returns correct "
            "value in second quadrant");

  GSL_REAL (x) = -1;
  GSL_IMAG (x) = -1;

  FUNCTION (tensor, set_all) (t, x);
  FUNCTION (tensor, inv) (t);

  GSL_REAL (y) = -(1 / SQRT (2)) * (1 / SQRT (2));
  GSL_IMAG (y) = (1 / SQRT (2)) * (1 / SQRT (2));

  gsl_test (!FUNCTION (tensor, is_const) (t, y),
            NAME (tensor)
            "_inv returns correct "
            "value in third quadrant");

  GSL_REAL (x) = 1;
  GSL_IMAG (x) = -1;

  FUNCTION (tensor, set_all) (t, x);
  FUNCTION (tensor, inv) (t);

  GSL_REAL (y) = (1 / SQRT (2)) * (1 / SQRT (2));
  GSL_IMAG (y) = (1 / SQRT (2)) * (1 / SQRT (2));

  gsl_test (!FUNCTION (tensor, is_const) (t, y),
            NAME (tensor)
            "_inv returns correct "
            "value in fourth quadrant");

  /* add */
  GSL_SET_COMPLEX (&x, 1, 2);
  GSL_SET_COMPLEX (&y, 3, 4);
  GSL_SET_COMPLEX (&z, 4, 6);

  FUNCTION (tensor, set_all) (t, x);
  FUNCTION (tensor, set_all) (u, y);

  FUNCTION (tensor, add) (t, u);

  gsl_test (!FUNCTION (tensor, is_const) (t, z),
            NAME (tensor)
            "_add (" OUT_FORMAT ", " OUT_FORMAT "j)" " + "
            "(" OUT_FORMAT ", " OUT_FORMAT "j) = "
            "(" OUT_FORMAT ", " OUT_FORMAT "j)",
            GSL_REAL (x), GSL_IMAG (x),
            GSL_REAL (y), GSL_IMAG (y),
            GSL_REAL (z), GSL_IMAG (z));

  /* sub */
  GSL_SET_COMPLEX (&x, 1, 2);
  GSL_SET_COMPLEX (&y, 3, 4);
  GSL_SET_COMPLEX (&z, -2, -2);

  FUNCTION (tensor, set_all) (t, x);
  FUNCTION (tensor, set_all) (u, y);

  FUNCTION (tensor, sub) (t, u);

  gsl_test (!FUNCTION (tensor, is_const) (t, z),
            NAME (tensor)
            "_sub (" OUT_FORMAT ", " OUT_FORMAT "j)" " - "
            "(" OUT_FORMAT ", " OUT_FORMAT "j) = "
            "(" OUT_FORMAT ", " OUT_FORMAT "j)",
            GSL_REAL (x), GSL_IMAG (x),
            GSL_REAL (y), GSL_IMAG (y),
            GSL_REAL (z), GSL_IMAG (z));

  /* mul */
  GSL_SET_COMPLEX (&x, 1, 2);
  GSL_SET_COMPLEX (&y, 3, 4);
  GSL_SET_COMPLEX (&z, -5, 10);

  FUNCTION (tensor, set_all) (t, x);
  FUNCTION (tensor, set_all) (u, y);

  FUNCTION (tensor, mul) (t, u);

  gsl_test (!FUNCTION (tensor, is_const) (t, z),
            NAME (tensor)
            "_mul (" OUT_FORMAT ", " OUT_FORMAT "j)" " * "
            "(" OUT_FORMAT ", " OUT_FORMAT "j) = "
            "(" OUT_FORMAT ", " OUT_FORMAT "j)",
            GSL_REAL (x), GSL_IMAG (x),
            GSL_REAL (y), GSL_IMAG (y),
            GSL_REAL (z), GSL_IMAG (z));

  /* div */
  GSL_SET_COMPLEX (&x, 1, 1);
  GSL_SET_COMPLEX (&y, 1, -1);
  GSL_SET_COMPLEX (&z, 0, 1);

  FUNCTION (tensor, set_all) (t, x);
  FUNCTION (tensor, set_all) (u, y);

  FUNCTION (tensor, div) (t, u);

  status = 0;

  if (!FUNCTION (tensor, is_same) (t))
    {
      status = 1;
    }

  if (gsl_fcmp ((double) GSL_REAL (FUNCTION (tensor, get) (t, 0, 0, 0)),
                (double) GSL_REAL (z), (double) GSL_FLT_EPSILON))
    {
      status = 1;
    }

  if (gsl_fcmp ((double) GSL_IMAG (FUNCTION (tensor, get) (t, 0, 0, 0)),
                (double) GSL_IMAG (z), (double) GSL_FLT_EPSILON))
    {
      status = 1;
    }

  gsl_test (status, NAME (tensor)
            "_div (" OUT_FORMAT ", " OUT_FORMAT "j)" " / "
            "(" OUT_FORMAT ", " OUT_FORMAT "j) = "
            "(" OUT_FORMAT ", " OUT_FORMAT "j)",
            GSL_REAL (x), GSL_IMAG (x),
            GSL_REAL (y), GSL_IMAG (y),
            GSL_REAL (z), GSL_IMAG (z));

  /* conj */

  GSL_REAL (x) = 1;
  GSL_IMAG (x) = -1;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, conj) (t);

  GSL_REAL (y) = 1;
  GSL_IMAG (y) = 1;

  gsl_test (!FUNCTION (tensor, is_const) (t, y),
            NAME (tensor)
            "_conj returns (" OUT_FORMAT ", " OUT_FORMAT "j) "
            "for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
            GSL_REAL (y), GSL_IMAG (y), GSL_REAL (x), GSL_IMAG (x));

  GSL_REAL (x) = -1;
  GSL_IMAG (x) = 1;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, conj) (t);

  GSL_REAL (y) = -1;
  GSL_IMAG (y) = -1;

  gsl_test (!FUNCTION (tensor, is_const) (t, y),
            NAME (tensor)
            "_conj returns (" OUT_FORMAT ", " OUT_FORMAT "j) "
            "for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
            GSL_REAL (y), GSL_IMAG (y), GSL_REAL (x), GSL_IMAG (x));

  /* arg */
  
  GSL_REAL (x) = 2;
  GSL_IMAG (x) = 1;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, arg) (t);

  GSL_REAL (y) = ATAN2 (GSL_IMAG (x), GSL_REAL (x));
  GSL_IMAG (y) = 0;

  gsl_test (!FUNCTION (tensor, is_const) (t, y),
            NAME (tensor)
            "_arg returns (" OUT_FORMAT ", " OUT_FORMAT "j) "
            "for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
            GSL_REAL (y), GSL_IMAG (y), GSL_REAL (x), GSL_IMAG (x));

  FUNCTION (tensor, free) (t);
  FUNCTION (tensor, free) (u);
}

void
FUNCTION (test, oper_trig) (const size_t dim,
                            const size_t size0,
                            const size_t size1,
                            const size_t size2)
{
#if defined(BASE_GSL_COMPLEX)

  TYPE (tensor) * t;
  t = FUNCTION (tensor, alloc) (dim, size0, size1, size2);

  size_t i;
  const size_t N = 4;
  gsl_complex x[N], res;
  const int real[] = {1, -1, -1, 1};
  const int imag[] = {1, 1, -1, -1};

  for (i = 0; i < N; ++i)
    {
      GSL_REAL (x[i]) = real[i];
      GSL_IMAG (x[i]) = imag[i];

      /* sin, arcsin, csc, arccsc, sinh, arcsinh, csch, arcsch */

      /* sin */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, sin) (t);

      res = gsl_complex_sin (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_sin returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* arcsin */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, arcsin) (t);

      res = gsl_complex_arcsin (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_arcsin returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* csc */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, csc) (t);

      res = gsl_complex_csc (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_csc returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* arccsc */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, arccsc) (t);

      res = gsl_complex_arccsc (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_arccsc returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* sinh */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, sinh) (t);

      res = gsl_complex_sinh (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_sinh returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* arcsinh */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, arcsinh) (t);

      res = gsl_complex_arcsinh (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_arcsinh returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* csch */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, csch) (t);

      res = gsl_complex_csch (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_csch returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* arccsch */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, arccsch) (t);

      res = gsl_complex_arccsch (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_arccsch returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* cos, arccos, sec, arcsec, cosh, arccosh, sech, arcsech */

      /* cos */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, cos) (t);

      res = gsl_complex_cos (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_cos returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* arccos */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, arccos) (t);

      res = gsl_complex_arccos (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_arccos returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* sec */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, sec) (t);

      res = gsl_complex_sec (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_sec returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* arcsec */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, arcsec) (t);

      res = gsl_complex_arcsec (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_arcsec returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* cosh */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, cosh) (t);

      res = gsl_complex_cosh (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_cosh returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* arccosh */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, arccosh) (t);

      res = gsl_complex_arccosh (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_arccosh returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* sech */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, sech) (t);

      res = gsl_complex_sech (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_sech returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* arcsech */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, arcsech) (t);

      res = gsl_complex_arcsech (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_arcsech returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* tan, arctan, cot, arccot, tanh, arctanh, coth, arccoth */

      /* tan */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, tan) (t);

      res = gsl_complex_tan (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_tan returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* arctan */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, arctan) (t);

      res = gsl_complex_arctan (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_arctan returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* cot */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, cot) (t);

      res = gsl_complex_cot (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_cot returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* arccot */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, arccot) (t);

      res = gsl_complex_arccot (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_arccot returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* tanh */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, tanh) (t);

      res = gsl_complex_tanh (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_tanh returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* arctanh */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, arctanh) (t);

      res = gsl_complex_arctanh (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_arctanh returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* coth */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, coth) (t);

      res = gsl_complex_coth (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_coth returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));

      /* arccoth */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, arccoth) (t);

      res = gsl_complex_arccoth (x[i]);

      gsl_test (!FUNCTION (tensor, is_const) (t, res),
                NAME (tensor)
                "_arccoth returns (" OUT_FORMAT ", " OUT_FORMAT "j)"
                " for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (res), GSL_IMAG (res),
                GSL_REAL (x[i]), GSL_IMAG (x[i]));
    }

  FUNCTION (tensor, free) (t);

#endif  /* defined(BASE_GSL_COMPLEX) */
}

void
FUNCTION (test, oper_explog) (const size_t dim,
                              const size_t size0,
                              const size_t size1,
                              const size_t size2)
{
#if defined(BASE_GSL_COMPLEX)
  
  TYPE (tensor) * t;
  t = FUNCTION (tensor, alloc) (dim, size0, size1, size2);

  BASE x, y, res;
  ATOMIC z;
  gsl_complex b;

  /* pow */
  GSL_REAL (x) = 2.2;
  GSL_IMAG (x) = -3.4;

  GSL_REAL (y) = 1.8;
  GSL_IMAG (y) = 2.7;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, pow) (t, y);

  res = gsl_complex_pow (x, y);

  gsl_test (!FUNCTION (tensor, is_const) (t, res),
            NAME (tensor)
            "_pow returns (" OUT_FORMAT ", " OUT_FORMAT "j) for base "
            "(" OUT_FORMAT ", " OUT_FORMAT "j) "
            " and power (" OUT_FORMAT ", " OUT_FORMAT "j)",
            res, x, y);

  /* pow real */
  z = 2;
  
  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, pow_real) (t, z);

  res = gsl_complex_pow_real (x, z);

  gsl_test (!FUNCTION (tensor, is_const) (t, res),
            NAME (tensor)
            "_pow_real returns (" OUT_FORMAT ", " OUT_FORMAT "j) "
            "for base (" OUT_FORMAT ", " OUT_FORMAT "j) "
            " and power (" OUT_FORMAT ")",
            res, x, z);

  /* sqrt */
  GSL_REAL (x) = -2;
  GSL_IMAG (x) = 0;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, sqrt) (t);

  res = gsl_complex_sqrt (x);

  gsl_test (!FUNCTION (tensor, is_const) (t, res),
            NAME (tensor)
            "_sqrt returns (" OUT_FORMAT ", " OUT_FORMAT "j) "
            "for argument (" OUT_FORMAT ", " OUT_FORMAT "j) ",
            res, x);

  /* cbrt */
  GSL_REAL (x) = 2.2;
  GSL_IMAG (x) = -3.4;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, cbrt) (t);

  res = gsl_complex_pow_real (x, 1. / 3);

  gsl_test (!FUNCTION (tensor, is_const) (t, res),
            NAME (tensor)
            "_cbrt returns (" OUT_FORMAT ", " OUT_FORMAT "j) "
            "for argument (" OUT_FORMAT ", " OUT_FORMAT "j) ",
            res, x);

  /* exp */
  GSL_REAL (x) = 2.2;
  GSL_IMAG (x) = -3.4;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, exp) (t);

  res = gsl_complex_exp (x);

  gsl_test (!FUNCTION (tensor, is_const) (t, res),
            NAME (tensor)
            "_exp returns (" OUT_FORMAT ", " OUT_FORMAT "j) "
            "for argument (" OUT_FORMAT ", " OUT_FORMAT "j) ",
            res, x);

  /* exp2 */
  GSL_REAL (x) = 2.2;
  GSL_IMAG (x) = -3.4;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, exp2) (t);

  GSL_REAL (b) = 2;
  GSL_IMAG (b) = 0;
  
  res = gsl_complex_pow (b, x);

  gsl_test (!FUNCTION (tensor, is_const) (t, res),
            NAME (tensor)
            "_exp2 returns (" OUT_FORMAT ", " OUT_FORMAT "j) "
            "for argument (" OUT_FORMAT ", " OUT_FORMAT "j) ",
            res, x);

  /* exp10 */
  GSL_REAL (x) = 2.2;
  GSL_IMAG (x) = -3.4;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, exp10) (t);

  GSL_REAL (b) = 10;
  GSL_IMAG (b) = 0;
  
  res = gsl_complex_pow (b, x);

  gsl_test (!FUNCTION (tensor, is_const) (t, res),
            NAME (tensor)
            "_exp10 returns (" OUT_FORMAT ", " OUT_FORMAT "j) "
            "for argument (" OUT_FORMAT ", " OUT_FORMAT "j) ",
            res, x);

  /* log */
  GSL_REAL (x) = 2.2;
  GSL_IMAG (x) = -3.4;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, log) (t);

  res = gsl_complex_log (x);

  gsl_test (!FUNCTION (tensor, is_const) (t, res),
            NAME (tensor)
            "_log returns (" OUT_FORMAT ", " OUT_FORMAT "j) "
            "for argument (" OUT_FORMAT ", " OUT_FORMAT "j) ",
            res, x);

  /* log2 */
  GSL_REAL (x) = 2.2;
  GSL_IMAG (x) = -3.4;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, log2) (t);

  res = gsl_complex_mul_real (gsl_complex_log (x), 1 / LOG (2));

  gsl_test (!FUNCTION (tensor, is_const) (t, res),
            NAME (tensor)
            "_log2 returns (" OUT_FORMAT ", " OUT_FORMAT "j) "
            "for argument (" OUT_FORMAT ", " OUT_FORMAT "j) ",
            res, x);

  /* log10 */
  GSL_REAL (x) = 2.2;
  GSL_IMAG (x) = -3.4;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, log10) (t);

  res = gsl_complex_log10 (x);

  gsl_test (!FUNCTION (tensor, is_const) (t, res),
            NAME (tensor)
            "_log10 returns (" OUT_FORMAT ", " OUT_FORMAT "j) "
            "for argument (" OUT_FORMAT ", " OUT_FORMAT "j) ",
            res, x);

  FUNCTION (tensor, free) (t);

#endif  /* defined(BASE_GSL_COMPLEX) */  
}

void
FUNCTION (test, oper_round) (const size_t dim,
                             const size_t size0,
                             const size_t size1,
                             const size_t size2)
{
  TYPE (tensor) * t;
  t = FUNCTION (tensor, alloc) (dim, size0, size1, size2);
  
  const size_t M = 5;

  BASE y[M];

  ATOMIC x = 0;
  
  size_t j;
  for (j = 0; j < M; ++j)
    {
      GSL_REAL (y[j]) = x;
      
      GSL_IMAG (y[j]) = -(x + 1);

      ++x;
    }
  
  BASE clip_min, clip_max;
  
  GSL_REAL (clip_min) = 1;
  
  GSL_IMAG (clip_min) = -4;

  GSL_REAL (clip_max) = 3;
  
  GSL_IMAG (clip_max) = -2;
  
  ATOMIC real_clip[] = {1, 1, 2, 3, 3};
  
  ATOMIC imag_clip[] = {-2, -2, -3, -4, -4};
  
  BASE clip[M];

  for (j = 0; j < M; ++j)
    {
      GSL_REAL (clip[j]) = real_clip[j];
      
      GSL_IMAG (clip[j]) = imag_clip[j];
    }  

  for (j = 0; j < M; ++j)
    {
      /* clip */
      FUNCTION (tensor, set_all) (t, y[j]);
      
      FUNCTION (tensor, clip) (t, clip_min, clip_max);
      
      gsl_test (!FUNCTION (tensor, is_const) (t, clip[j]),
                NAME (tensor)
                "_clip [(" OUT_FORMAT ", " OUT_FORMAT "j), "
                "(" OUT_FORMAT ", " OUT_FORMAT "j)] "
                "returns (" OUT_FORMAT ", " OUT_FORMAT "j) "
                "for argument (" OUT_FORMAT ", " OUT_FORMAT "j)",
                GSL_REAL (clip_min), GSL_IMAG (clip_min),
                GSL_REAL (clip_max), GSL_IMAG (clip_max),
                GSL_REAL (clip[j]), GSL_IMAG (clip[j]),
                GSL_REAL (y[j]), GSL_IMAG (y[j]));
    }
  
  FUNCTION (tensor, free) (t);  
}

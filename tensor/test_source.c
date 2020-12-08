/* tensor/test_source.c
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

void
FUNCTION (test, oper_logical) (const size_t dim,
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

/* Statistics */

void
FUNCTION (test, oper_stat) (const size_t dim,
                            const size_t size0,
                            const size_t size1,
                            const size_t size2);

/* Sorting */

void
FUNCTION (test, oper_sort) (const size_t dim,
                            const size_t size0,
                            const size_t size1,
                            const size_t size2);

void
FUNCTION (test, oper_sort_index) (const size_t dim,
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
          if (FUNCTION (tensor, get) (t, i, j, k) != zero)
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
          x = i * size0 + j * size1 + k;
          FUNCTION (tensor, set) (t_in, x, i, j, k);
        }

  t_out = FUNCTION (tensor, copy) (t_in);

  gsl_test (FUNCTION (tensor, tsize) (t_in) !=
            FUNCTION (tensor, tsize) (t_out),
            NAME (tensor)
            "_copy tensor and its copy have same number of elements");
  gsl_test (FUNCTION (tensor, is_view) (t_out),
            NAME (tensor)
            "_copy" DESC " copied tensor is not a view");

  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          x = FUNCTION (tensor, get) (t_in, i, j, k);
          y = FUNCTION (tensor, get) (t_out, i, j, k);

          if (x != y)
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
          x = i * t_in->size[0] + j * t_in->size[1] + k;
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
            "_copy" DESC " copied tensor is not a view");

  gsl_test (!FUNCTION (tensor, is_contiguous) (t_out),
            NAME (tensor)
            "_copy" DESC " copied tensor is contiguous");

  for (i = 0; i < t_in->size[0]; ++i)
    for (j = 0; j < t_in->size[1]; ++j)
      for (k = 0; k < t_in->size[2]; ++k)
        {
          x = FUNCTION (tensor, get) (t_in, i, j, k);
          y = FUNCTION (tensor, get) (t_out, i, j, k);

          if (x != y)
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

  BASE x;
  int status = 0;

  size_t i, j, k;
  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          x = i * size0 + j * size1 + k;
          FUNCTION (tensor, set) (t, x, i, j, k);
        }

  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          x = i * size0 + j * size1 + k;

          if (* FUNCTION (tensor, const_ptr) (t, i, j, k) != x)
            {
              status = 1;
              break;
            }
        }

  gsl_test (status, NAME (tensor)
            "_set writes into tensor");

  /* get */

  x = size0 * size1 * size2;

  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          * FUNCTION (tensor, ptr) (t, i, j, k) = x--;
        }

  x = size0 * size1 * size2;

  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          if (FUNCTION (tensor, get) (t, i, j, k) != x--)
            {
              status = 1;
              break;
            }
        }

  gsl_test (status, NAME (tensor)
            "_get reads from tensor");

  /* set_all */

  x = 42;

  FUNCTION (tensor, set_all) (t, x);

  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          if (FUNCTION (tensor, get) (t, i, j, k) != x)
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

  BASE x = 0;
  int status = 0;

  size_t i, j, k;
  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          FUNCTION (tensor, set) (t, x++, i, j, k);
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
          if (FUNCTION (tensor, get) (u, i, j, k) !=
              FUNCTION (tensor, get) (t, i, j, k))
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

  BASE x = 0;
  int status = 0;

  size_t i, j, k;
  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          FUNCTION (tensor, set) (t, x++, i, j, k);
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
          if (FUNCTION (tensor, get) (u, i, j, k) !=
              FUNCTION (tensor, get) (t, i, j, k))
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

  FUNCTION (tensor, set_zero) (t);

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

  FUNCTION (tensor, set_one) (t);

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

#if (!defined(UNSIGNED) && !defined(BASE_CHAR))

  FUNCTION (tensor, set_all) (t, -1);

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

#endif  /* (!defined(UNSIGNED) && !defined(BASE_CHAR)) */

  FUNCTION (tensor, set_zero) (t);
  FUNCTION (tensor, set) (t, 1, 0, 0, 0);

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

  FUNCTION (tensor, set_all) (t, 42);

  gsl_test (!FUNCTION (tensor, equal) (t, t),
            NAME (tensor) "_equal on identity tensor");

  /* is same */

  gsl_test (!FUNCTION (tensor, is_same) (t),
            NAME (tensor) "_is_same on identity tensor");

  FUNCTION (tensor, set) (t, 1, 0, 0, 0);

  gsl_test (FUNCTION (tensor, is_same) (t),
            NAME (tensor) "_is_same on mixed tensor");

  /* is const */

  gsl_test (FUNCTION (tensor, is_const) (t, 42),
            NAME (tensor) "_is_const on mixed tensor");

  FUNCTION (tensor, set) (t, 42, 0, 0, 0);

  gsl_test (!FUNCTION (tensor, is_const) (t, 42),
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
          x = i * t->size[0] + j * t->size[1] + k;
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

          if (x != y)
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
  ATOMIC array[size0 * size1 * size2];

  size_t x = 0;

  size_t i, j, k;
  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
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

  BASE x = 0;
  int status = 0;

  /* vector */

  v = FUNCTION (gsl_vector, alloc) (size0);

  size_t i;
  for (i = 0; i < size0; ++i)
    FUNCTION (gsl_vector, set) (v, i, x++);

  t = FUNCTION (tensor, view_vector) (v);

  gsl_test (t->dim != 1, NAME (tensor)
            "_view_vector tensor view dimension is 1");

  gsl_test (t->size[0] != v->size, NAME (tensor)
            "_view_vector vector and tensor view have same size");

  gsl_test (t->stride[0] != v->stride, NAME (tensor)
            "_view_vector vector and tensor view have same stride");

  for (i = 0; i < t->size[0]; ++i)
    {
      if (FUNCTION (gsl_vector, get) (v, i) !=
          FUNCTION (tensor, get) (t, i))
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

  x = 0;

  size_t j;
  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      {
        FUNCTION (gsl_matrix, set) (m, i, j, x++);
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
        if (FUNCTION (gsl_matrix, get) (m, i, j) !=
            FUNCTION (tensor, get) (t, i, j))
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

  BASE x = 0;
  int status = 0;

  /* vector */

  t = FUNCTION (tensor, alloc) (1, size0);

  size_t i;
  for (i = 0; i < t->size[0]; ++i)
    {
      FUNCTION (tensor, set) (t, x++, i);
    }

  vv = FUNCTION (gsl_vector, view_tensor) (t);

  gsl_test (t->size[0] != vv.vector.size, NAME (gsl_vector)
            "_view_tensor tensor and vector view have same size");

  gsl_test (t->stride[0] != vv.vector.stride, NAME (gsl_vector)
            "_view_tensor tensor and vector view have same stride");

  for (i = 0; i < t->size[0]; ++i)
    {
      if (FUNCTION (gsl_vector, get) (&vv.vector, i) !=
          FUNCTION (tensor, get) (t, i))
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

  x = 0;

  t = FUNCTION (tensor, alloc) (2, size0, size1);

  size_t j;
  for (i = 0; i < t->size[0]; ++i)
    for (j = 0; j < t->size[1]; ++j)
      {
        FUNCTION (tensor, set) (t, x++, i, j);
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
        if (FUNCTION (gsl_matrix, get) (&mv.matrix, i, j) !=
            FUNCTION (tensor, get) (t, i, j))
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

  BASE x = 3;

  FUNCTION (tensor, set_all) (t2, x);

  FUNCTION (tensor, assign) (t1, t2);

  gsl_test (!FUNCTION (tensor, equal) (t1, t2),
            NAME (tensor) "_assign original and "
            "assigned to tensor have equal elements");

  /* swap */

  int status = 0;

  x = 1;
  FUNCTION (tensor, set_all) (t1, x);

  x = 2;
  FUNCTION (tensor, set_all) (t2, x);

  FUNCTION (tensor, swap) (t1, t2);

  FUNCTION (tensor, set_all) (t3, x);
  if (!FUNCTION (tensor, equal) (t1, t3))
    status = 1;

  x = 1;
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

  x = 0;

  size_t i, j, k;
  for (i = 0; i < size0; ++i)
    for (j = 0; j < size1; ++j)
      for (k = 0; k < size2; ++k)
        {
          FUNCTION (tensor, set) (t1, x++, i, j, k);
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

      if (x != y)
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

  x = 0;
  for (i = 0; i < t1->size[0]; ++i)
    for (j = 0; j < t1->size[1]; ++j)
      for (k = 0; k < t1->size[2]; ++k)
        {
          FUNCTION (tensor, set) (t1, x++, i, j, k);
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

      if (x != y)
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

  x = 0;
  for (i = 0; i < t1->size[0]; ++i)
    for (j = 0; j < t1->size[1]; ++j)
      for (k = 0; k < t1->size[2]; ++k)
        {
          FUNCTION (tensor, set) (t1, x++, i, j, k);
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

      if (x != y)
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

      if (x != y)
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

      if (x != y)
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

  x = 0;
  for (i = 0; i < t1->size[0]; ++i)
    for (j = 0; j < t1->size[1]; ++j)
      for (k = 0; k < t1->size[2]; ++k)
        {
          FUNCTION (tensor, set) (t1, x++, i, j, k);
          FUNCTION (tensor, set) (t2, x++, i, j, k);
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
  ATOMIC scale, add;

#if !defined(UNSIGNED)

  /* abs */

  x = 42;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, abs) (t);

  gsl_test (!FUNCTION (tensor, is_pos) (t),
            NAME (tensor) "_abs on positive tensor");

  x = -42;

  FUNCTION (tensor, set) (t, x, 0, 0, 0);

  FUNCTION (tensor, abs) (t);

  gsl_test (!FUNCTION (tensor, is_pos) (t),
            NAME (tensor) "_abs on mixed tensor");

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, abs) (t);

  gsl_test (!FUNCTION (tensor, is_pos) (t),
            NAME (tensor) "_abs on negative tensor");

  /* negative */

  x = 42;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, neg) (t);

  gsl_test (!FUNCTION (tensor, is_neg) (t),
            NAME (tensor) "_neg on positive tensor");

  FUNCTION (tensor, set_zero) (t);

  FUNCTION (tensor, neg) (t);

  gsl_test (!FUNCTION (tensor, is_null) (t),
            NAME (tensor) "_neg on null tensor");

  x = -42;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, neg) (t);

  gsl_test (!FUNCTION (tensor, is_pos) (t),
            NAME (tensor) "_neg on negative tensor");

#endif  /* !defined(UNSIGNED) */

  /* inv */

#if FP

  x = 42;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, inv) (t);

  gsl_test (!FUNCTION (tensor, is_const) (t, 1 / x),
            NAME (tensor)
            "_inv returns correct "
            "value for positive tensor");

  x = -42;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, inv) (t);

  gsl_test (!FUNCTION (tensor, is_const) (t, 1 / x),
            NAME (tensor)
            "_inv returns correct "
            "value for negative tensor");

  FUNCTION (tensor, set_zero) (t);

  FUNCTION (tensor, inv) (t);

  gsl_test (!FUNCTION (tensor, is_const) (t, 1 / 0.),
            NAME (tensor)
            "_inv returns correct "
            "value for null tensor");

#endif  /* FP */

  /* add */
  x = 3;
  y = 2;
  z = x + y;

  FUNCTION (tensor, set_all) (t, x);
  FUNCTION (tensor, set_all) (u, y);

  FUNCTION (tensor, add) (t, u);

  gsl_test (!FUNCTION (tensor, is_const) (t, z), NAME (tensor)
            "_add " OUT_FORMAT " + " OUT_FORMAT " = " OUT_FORMAT,
            x, y, z);

  /* sub */
  x = 5;
  y = 3;
  z = x - y;

  FUNCTION (tensor, set_all) (t, x);
  FUNCTION (tensor, set_all) (u, y);

  FUNCTION (tensor, sub) (t, u);

  gsl_test (!FUNCTION (tensor, is_const) (t, z), NAME (tensor)
            "_sub " OUT_FORMAT " - " OUT_FORMAT " = " OUT_FORMAT,
            x, y, z);

  /* mul */
  x = 3;
  y = 4;
  z = x * y;

  FUNCTION (tensor, set_all) (t, x);
  FUNCTION (tensor, set_all) (u, y);

  FUNCTION (tensor, mul) (t, u);

  gsl_test (!FUNCTION (tensor, is_const) (t, z), NAME (tensor)
            "_mul " OUT_FORMAT " * " OUT_FORMAT " = " OUT_FORMAT,
            x, y, z);

  /* div */
  x = 6;
  y = 3;
  z = x / y;

  FUNCTION (tensor, set_all) (t, x);
  FUNCTION (tensor, set_all) (u, y);

  FUNCTION (tensor, div) (t, u);

  gsl_test (!FUNCTION (tensor, is_const) (t, z), NAME (tensor)
            "_div " OUT_FORMAT " / " OUT_FORMAT " = " OUT_FORMAT,
            x, y, z);

#if !FP
  
  /* mod */
  x = 7;
  y = 4;
  z = x % y;

  FUNCTION (tensor, set_all) (t, x);
  FUNCTION (tensor, set_all) (u, y);

  FUNCTION (tensor, mod) (t, u);

  gsl_test (!FUNCTION (tensor, is_const) (t, z), NAME (tensor)
            "_mod " OUT_FORMAT " %% " OUT_FORMAT " = " OUT_FORMAT,
            x, y, z);
  
#endif  /* !FP */

  /* scale_add */
  x = 3;
  scale = 2;
  add = 4;
  z = x * scale + add;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, scale_add) (t, scale, add);

  gsl_test (!FUNCTION (tensor, is_const) (t, z), NAME (tensor)
            "_scale_add " OUT_FORMAT " * " OUT_FORMAT " + " OUT_FORMAT
            " = " OUT_FORMAT, x, scale, add, z);

  FUNCTION (tensor, free) (t);
  FUNCTION (tensor, free) (u);
}

void
FUNCTION (test, oper_logical) (const size_t dim,
                               const size_t size0,
                               const size_t size1,
                               const size_t size2)
{
  TYPE (tensor) * t, * u;
  t = FUNCTION (tensor, alloc) (dim, size0, size1, size2);
  u = FUNCTION (tensor, alloc) (dim, size0, size1, size2);

  /* Logical not */

  ATOMIC x = 42;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, not) (t);

  gsl_test (!FUNCTION (tensor, is_null) (t),
            NAME (tensor) "_not on \"true\" tensor");

  x = 0;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, not) (t);

  gsl_test (!FUNCTION (tensor, is_const) (t, 1),
            NAME (tensor) "_not on \"false\" tensor");

#if FP

  /* fcmpc */

  FUNCTION (tensor, set_one) (t);

  const size_t M = 4;
  /* Base epsilon multiplier */
  ATOMIC m[] = {-4, -0.5, 0.5, 4};
  /* Expected result const */
  int rcst[] = {1, 0, 0, -1};

  size_t i;
  for (i = 0; i < M; ++i)
    {
      tensor_int * res;

      res = FUNCTION (tensor, fcmpc)
        (t, 1 + m[i] * BASE_EPSILON, BASE_EPSILON);

      gsl_test (!tensor_int_is_const (res, rcst[i]),
                NAME (tensor)
                "_fcmpc returns correct value on %g * eps", m[i]);

      tensor_int_free (res);
    }

  /* fcmp */

  for (i = 0; i < M; ++i)
    {
      tensor_int * res;

      FUNCTION (tensor, set_all) (u, 1 + m[i] * BASE_EPSILON);

      res = FUNCTION (tensor, fcmp)
        (t, u, BASE_EPSILON);

      gsl_test (!tensor_int_is_const (res, rcst[i]),
                NAME (tensor)
                "_fcmp returns correct value on %g * eps", m[i]);

      tensor_int_free (res);
    }

#endif  /* FP */

  tensor_int * res;

  /* cmpc */

  x = 3;

  FUNCTION (tensor, set_all) (t, x);

  res = FUNCTION (tensor, cmpc) (t, x);

  gsl_test (!tensor_int_is_null (res), NAME (tensor)
            "_cmpc with identity value constant");

  tensor_int_free (res);

  res = FUNCTION (tensor, cmpc) (t, x - 1);

  gsl_test (!tensor_int_is_const (res, 1), NAME (tensor)
            "_cmpc with lesser value constant");

  tensor_int_free (res);

  res = FUNCTION (tensor, cmpc) (t, x + 1);

  gsl_test (!tensor_int_is_const (res, -1), NAME (tensor)
            "_cmpc with larger value constant");

  tensor_int_free (res);

  /* cmp */

  x = 5;

  FUNCTION (tensor, set_all) (t, x);

  res = FUNCTION (tensor, cmp) (t, t);

  gsl_test (!tensor_int_is_null (res), NAME (tensor)
            "_cmp with identity tensor");

  tensor_int_free (res);

  FUNCTION (tensor, set_all) (t, x);
  FUNCTION (tensor, set_all) (u, x - 1);

  res = FUNCTION (tensor, cmp) (t, u);

  gsl_test (!tensor_int_is_const (res, 1), NAME (tensor)
            "_cmp with lesser values tensor");

  tensor_int_free (res);

  FUNCTION (tensor, set_all) (t, x);
  FUNCTION (tensor, set_all) (u, x + 1);

  res = FUNCTION (tensor, cmp) (t, u);

  gsl_test (!tensor_int_is_const (res, -1), NAME (tensor)
            "_cmp with larger values tensor");

  tensor_int_free (res);

  /* and, or, xor */

  /* 0 0 */
  x = 0;
  FUNCTION (tensor, set_all) (t, x);
  FUNCTION (tensor, set_all) (u, x);

  res = FUNCTION (tensor, and) (t, u);
  
  gsl_test (!tensor_int_is_null (res), NAME (tensor)
            "_and on \"false\" and \"false\" tensors");
  
  tensor_int_free (res);

  res = FUNCTION (tensor, or) (t, u);
  
  gsl_test (!tensor_int_is_null (res), NAME (tensor)
            "_or on \"false\" and \"false\" tensors");
  
  tensor_int_free (res);

  res = FUNCTION (tensor, xor) (t, u);
  
  gsl_test (!tensor_int_is_null (res), NAME (tensor)
            "_xor on \"false\" and \"false\" tensors");
  
  tensor_int_free (res);

  /* 0 1 */
  x = 0;
  FUNCTION (tensor, set_all) (t, x);
  
  x = 1;
  FUNCTION (tensor, set_all) (u, x);

  res = FUNCTION (tensor, and) (t, u);
  
  gsl_test (!tensor_int_is_null (res), NAME (tensor)
            "_and on \"false\" and \"true\" tensors");
  
  tensor_int_free (res);

  res = FUNCTION (tensor, or) (t, u);
  
  gsl_test (!tensor_int_is_const (res, 1), NAME (tensor)
            "_or on \"false\" and \"true\" tensors");
  
  tensor_int_free (res);

  res = FUNCTION (tensor, xor) (t, u);
  
  gsl_test (!tensor_int_is_const (res, 1), NAME (tensor)
            "_xor on \"false\" and \"true\" tensors");
  
  tensor_int_free (res);

  /* 1 0 */
  x = 1;
  FUNCTION (tensor, set_all) (t, x);
  
  x = 0;
  FUNCTION (tensor, set_all) (u, x);

  res = FUNCTION (tensor, and) (t, u);

  gsl_test (!tensor_int_is_null (res), NAME (tensor)
            "_and on \"true\" and \"false\" tensors");

  tensor_int_free (res);

  res = FUNCTION (tensor, or) (t, u);

  gsl_test (!tensor_int_is_const (res, 1), NAME (tensor)
            "_or on \"true\" and \"false\" tensors");

  tensor_int_free (res);

  res = FUNCTION (tensor, xor) (t, u);

  gsl_test (!tensor_int_is_const (res, 1), NAME (tensor)
            "_xor on \"true\" and \"false\" tensors");

  tensor_int_free (res);

  /* 1 1 */
  x = 1;
  FUNCTION (tensor, set_all) (t, x);
  FUNCTION (tensor, set_all) (u, x);

  res = FUNCTION (tensor, and) (t, u);

  gsl_test (!tensor_int_is_const (res, 1), NAME (tensor)
            "_and on \"true\" and \"true\" tensors");

  tensor_int_free (res);

  res = FUNCTION (tensor, or) (t, u);

  gsl_test (!tensor_int_is_const (res, 1), NAME (tensor)
            "_or on \"true\" and \"true\" tensors");

  tensor_int_free (res);

  res = FUNCTION (tensor, xor) (t, u);

  gsl_test (!tensor_int_is_null (res), NAME (tensor)
            "_xor on \"true\" and \"true\" tensors");

  tensor_int_free (res);  

  FUNCTION (tensor, free) (t);
  FUNCTION (tensor, free) (u);
}
void
FUNCTION (test, oper_trig) (const size_t dim,
                            const size_t size0,
                            const size_t size1,
                            const size_t size2)
{
#if FP

  TYPE (tensor) * t, * u, * v;
  t = FUNCTION (tensor, alloc) (dim, size0, size1, size2);
  u = FUNCTION (tensor, alloc) (dim, size0, size1, size2);

  size_t i;
  const size_t N = 9;
  const ATOMIC x[] = {0, M_PI_4, M_PI_2, 3 * M_PI_4, M_PI,
                      5 * M_PI_4, 3 * M_PI_2, 7 * M_PI_4, 2 * M_PI};
  const ATOMIC y[] = {-M_PI, -M_PI_4, -M_PI_2, -3 * M_PI_4, 0,
                      5 * M_PI_4, 3 * M_PI_2, 7 * M_PI_4, 2 * M_PI};

  tensor_int * res;

  for (i = 0; i < N; ++i)
    {
      /* sin, arcsin, csc, arccsc, sinh, arcsinh, csch, arcsch */

      /* sin */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, sin) (t);

      gsl_test (!FUNCTION (tensor, is_const) (t, SIN (x[i])),
                NAME (tensor)
                "_sin returns " OUT_FORMAT " for argument "
                OUT_FORMAT, SIN (x[i]), x[i]);

      /* arcsin */
      FUNCTION (tensor, arcsin) (t);

      res = FUNCTION (tensor, fcmpc)
        (t, ASIN (SIN (x[i])), BASE_EPSILON);

      gsl_test (!tensor_int_is_null (res),
                NAME (tensor)
                "_arcsin returns ~" OUT_FORMAT " for argument "
                OUT_FORMAT, ASIN (SIN (x[i])), SIN (x[i]));

      tensor_int_free (res);

      /* csc */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, csc) (t);

      res = FUNCTION (tensor, fcmpc)
        (t, 1 / SIN (x[i]), BASE_EPSILON);

      gsl_test (!tensor_int_is_null (res),
                NAME (tensor)
                "_csc returns ~" OUT_FORMAT " for argument "
                OUT_FORMAT, 1 / SIN (x[i]), x[i]);

      tensor_int_free (res);

      /* arccsc */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, arccsc) (t);

      res = FUNCTION (tensor, fcmpc)
        (t, ASIN (1 / x[i]), BASE_EPSILON);

      gsl_test (!tensor_int_is_null (res),
                NAME (tensor)
                "_arccsc returns ~" OUT_FORMAT " for argument "
                OUT_FORMAT, ASIN (1 / x[i]), x[i]);

      tensor_int_free (res);

      /* sinh */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, sinh) (t);

      gsl_test (!FUNCTION (tensor, is_const) (t, SINH (x[i])),
                NAME (tensor)
                "_sinh returns " OUT_FORMAT " for argument "
                OUT_FORMAT, SINH (x[i]), x[i]);

      /* arcsinh */
      FUNCTION (tensor, arcsinh) (t);

      res = FUNCTION (tensor, fcmpc)
        (t, ASINH (SINH (x[i])), BASE_EPSILON);

      gsl_test (!tensor_int_is_null (res),
                NAME (tensor)
                "_arcsinh returns ~" OUT_FORMAT " for argument "
                OUT_FORMAT, ASINH (SINH (x[i])), SINH (x[i]));

      tensor_int_free (res);

      /* csch */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, csch) (t);

      res = FUNCTION (tensor, fcmpc)
        (t, 1 / SINH (x[i]), BASE_EPSILON);

      gsl_test (!tensor_int_is_null (res),
                NAME (tensor)
                "_csch returns ~" OUT_FORMAT " for argument "
                OUT_FORMAT, 1 / SINH (x[i]), x[i]);

      tensor_int_free (res);

      /* arccsch */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, arccsch) (t);

      res = FUNCTION (tensor, fcmpc)
        (t, ASINH (1 / x[i]), BASE_EPSILON);

      gsl_test (!tensor_int_is_null (res),
                NAME (tensor)
                "_arccsch returns ~" OUT_FORMAT " for argument "
                OUT_FORMAT, ASINH (1 / x[i]), x[i]);

      tensor_int_free (res);

      /* cos, arccos, sec, arcsec, cosh, arccosh, sech, arcsech */

      /* cos */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, cos) (t);

      gsl_test (!FUNCTION (tensor, is_const) (t, COS (x[i])),
                NAME (tensor)
                "_cos returns " OUT_FORMAT " for argument "
                OUT_FORMAT, COS (x[i]), x[i]);

      /* arccos */
      FUNCTION (tensor, arccos) (t);

      res = FUNCTION (tensor, fcmpc)
        (t, ACOS (COS (x[i])), BASE_EPSILON);

      gsl_test (!tensor_int_is_null (res),
                NAME (tensor)
                "_arccos returns ~" OUT_FORMAT " for argument "
                OUT_FORMAT, ACOS (COS (x[i])), COS (x[i]));

      tensor_int_free (res);

      /* sec */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, sec) (t);

      res = FUNCTION (tensor, fcmpc)
        (t, 1 / COS (x[i]), BASE_EPSILON);

      gsl_test (!tensor_int_is_null (res),
                NAME (tensor)
                "_sec returns ~" OUT_FORMAT " for argument "
                OUT_FORMAT, 1 / COS (x[i]), x[i]);

      tensor_int_free (res);

      /* arcsec */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, arcsec) (t);

      res = FUNCTION (tensor, fcmpc)
        (t, ACOS (1 / x[i]), BASE_EPSILON);

      gsl_test (!tensor_int_is_null (res),
                NAME (tensor)
                "_arcsec returns ~" OUT_FORMAT " for argument "
                OUT_FORMAT, ACOS (1 / x[i]), x[i]);

      tensor_int_free (res);

      /* cosh */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, cosh) (t);

      gsl_test (!FUNCTION (tensor, is_const) (t, COSH (x[i])),
                NAME (tensor)
                "_cosh returns " OUT_FORMAT " for argument "
                OUT_FORMAT, COSH (x[i]), x[i]);

      /* arccosh */
      FUNCTION (tensor, arccosh) (t);

      res = FUNCTION (tensor, fcmpc)
        (t, ACOSH (COSH (x[i])), BASE_EPSILON);

      gsl_test (!tensor_int_is_null (res),
                NAME (tensor)
                "_arccosh returns ~" OUT_FORMAT " for argument "
                OUT_FORMAT, ACOSH (COSH (x[i])), COSH (x[i]));

      tensor_int_free (res);

      /* sech */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, sech) (t);

      res = FUNCTION (tensor, fcmpc)
        (t, 1 / COSH (x[i]), BASE_EPSILON);

      gsl_test (!tensor_int_is_null (res),
                NAME (tensor)
                "_sech returns ~" OUT_FORMAT " for argument "
                OUT_FORMAT, 1 / COSH (x[i]), x[i]);

      tensor_int_free (res);

      /* arcsech */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, arcsech) (t);

      res = FUNCTION (tensor, fcmpc)
        (t, ACOSH (1 / x[i]), BASE_EPSILON);

      gsl_test (!tensor_int_is_null (res),
                NAME (tensor)
                "_arcsech returns ~" OUT_FORMAT " for argument "
                OUT_FORMAT, ACOSH (1 / x[i]), x[i]);

      tensor_int_free (res);

      /* tan, arctan, arctan2, cot, arccot, tanh, arctanh, coth, arccoth */

      /* tan */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, tan) (t);

      gsl_test (!FUNCTION (tensor, is_const) (t, TAN (x[i])),
                NAME (tensor)
                "_tan returns " OUT_FORMAT " for argument "
                OUT_FORMAT, TAN (x[i]), x[i]);

      /* arctan */
      FUNCTION (tensor, arctan) (t);

      res = FUNCTION (tensor, fcmpc)
        (t, ATAN (TAN (x[i])), BASE_EPSILON);

      gsl_test (!tensor_int_is_null (res),
                NAME (tensor)
                "_arctan returns ~" OUT_FORMAT " for argument "
                OUT_FORMAT, ATAN (TAN (x[i])), TAN (x[i]));

      tensor_int_free (res);


      

      /* arctan2 */
      FUNCTION (tensor, set_all) (t, y[i]);
      FUNCTION (tensor, set_all) (u, x[i]);
      
      v = FUNCTION (tensor, arctan2) (t, u);

      res = FUNCTION (tensor, fcmpc)
        (v, ATAN2 (y[i], x[i]), BASE_EPSILON);

      gsl_test (!tensor_int_is_null (res),
                NAME (tensor)
                "_arctan2 returns ~" OUT_FORMAT " for arguments "
                OUT_FORMAT " " OUT_FORMAT,
                ATAN2 (y[i], x[i]), y[i], x[i]);

      FUNCTION (tensor, free) (v);
      tensor_int_free (res);

      /* cot */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, cot) (t);

      res = FUNCTION (tensor, fcmpc)
        (t, 1 / TAN (x[i]), BASE_EPSILON);

      gsl_test (!tensor_int_is_null (res),
                NAME (tensor)
                "_cot returns ~" OUT_FORMAT " for argument "
                OUT_FORMAT, 1 / TAN (x[i]), x[i]);

      tensor_int_free (res);

      /* arccot */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, arccot) (t);

      res = FUNCTION (tensor, fcmpc)
        (t, ATAN (1 / x[i]), BASE_EPSILON);

      gsl_test (!tensor_int_is_null (res),
                NAME (tensor)
                "_arccot returns ~" OUT_FORMAT " for argument "
                OUT_FORMAT, ATAN (1 / x[i]), x[i]);

      tensor_int_free (res);

      /* tanh */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, tanh) (t);

      gsl_test (!FUNCTION (tensor, is_const) (t, TANH (x[i])),
                NAME (tensor)
                "_tanh returns " OUT_FORMAT " for argument "
                OUT_FORMAT, TANH (x[i]), x[i]);

      /* arctanh */
      FUNCTION (tensor, arctanh) (t);

      res = FUNCTION (tensor, fcmpc)
        (t, ATANH (TANH (x[i])), BASE_EPSILON);

      gsl_test (!tensor_int_is_null (res),
                NAME (tensor)
                "_arctanh returns ~" OUT_FORMAT " for argument "
                OUT_FORMAT, ATANH (TANH (x[i])), TANH (x[i]));

      tensor_int_free (res);

      /* coth */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, coth) (t);

      res = FUNCTION (tensor, fcmpc)
        (t, 1 / TANH (x[i]), BASE_EPSILON);

      gsl_test (!tensor_int_is_null (res),
                NAME (tensor)
                "_coth returns ~" OUT_FORMAT " for argument "
                OUT_FORMAT, 1 / TANH (x[i]), x[i]);

      tensor_int_free (res);

      /* arccoth */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, arccoth) (t);

      res = FUNCTION (tensor, fcmpc)
        (t, ATANH (1 / x[i]), BASE_EPSILON);

      gsl_test (!tensor_int_is_null (res),
                NAME (tensor)
                "_arccoth returns ~" OUT_FORMAT " for argument "
                OUT_FORMAT, ATANH (1 / x[i]), x[i]);

      tensor_int_free (res);
    }

  FUNCTION (tensor, free) (u);
  FUNCTION (tensor, free) (t);

#endif  /* FP */
}

void
FUNCTION (test, oper_explog) (const size_t dim,
                              const size_t size0,
                              const size_t size1,
                              const size_t size2)
{
#if FP

  TYPE (tensor) * t;
  t = FUNCTION (tensor, alloc) (dim, size0, size1, size2);

  tensor_int * res;

  BASE x, y;

  /* pow */
  x = 2.2;

  y = 2;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, pow) (t, y);

  gsl_test (!FUNCTION (tensor, is_const) (t, POW (x, y)),
            NAME (tensor)
            "_pow returns " OUT_FORMAT " for base "
            OUT_FORMAT " and power " OUT_FORMAT,
            POW (x, y), x, y);

  /* sqrt */
  x = 2;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, sqrt) (t);

  gsl_test (!FUNCTION (tensor, is_const) (t, SQRT (x)),
            NAME (tensor)
            "_sqrt returns " OUT_FORMAT " for argument " OUT_FORMAT,
            SQRT (x), x);

  /* cbrt */
  x = 8;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, cbrt) (t);

  gsl_test (!FUNCTION (tensor, is_const) (t, CBRT (x)),
            NAME (tensor)
            "_cbrt returns " OUT_FORMAT " for argument " OUT_FORMAT,
            CBRT (x), x);

  /* exp */
  x = 1;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, exp) (t);

  gsl_test (!FUNCTION (tensor, is_const) (t, EXP (x)),
            NAME (tensor)
            "_exp returns " OUT_FORMAT " for argument " OUT_FORMAT,
            EXP (x), x);

  /* exp2 */
  x = 2;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, exp2) (t);

  gsl_test (!FUNCTION (tensor, is_const) (t, EXP2 (x)),
            NAME (tensor)
            "_exp2 returns " OUT_FORMAT " for argument " OUT_FORMAT,
            EXP2 (x), x);

  /* exp10 */
  x = 2;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, exp10) (t);

  gsl_test (!FUNCTION (tensor, is_const) (t, POW (10, x)),
            NAME (tensor)
            "_exp10 returns " OUT_FORMAT " for argument " OUT_FORMAT,
            POW (10, x), x);

  /* expm1 */
  x = BASE_EPSILON;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, expm1) (t);

  res = FUNCTION (tensor, fcmpc) (t, EXPM1 (x), BASE_EPSILON);

  gsl_test (!tensor_int_is_null (res),
            NAME (tensor)
            "_expm1 returns " OUT_FORMAT " for argument " OUT_FORMAT,
            EXPM1 (x), x);

  tensor_int_free (res);

  /* log */
  x = M_PI;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, log) (t);

  gsl_test (!FUNCTION (tensor, is_const) (t, LOG (x)),
            NAME (tensor)
            "_log returns " OUT_FORMAT " for argument " OUT_FORMAT,
            LOG (x), x);

  /* log2 */
  x = M_PI;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, log2) (t);

  res = FUNCTION (tensor, fcmpc) (t, LOG2 (x), BASE_EPSILON);

  gsl_test (!tensor_int_is_null (res),
            NAME (tensor)
            "_log2 returns " OUT_FORMAT " for argument " OUT_FORMAT,
            LOG2 (x), x);

  tensor_int_free (res);

  /* log10 */
  x = M_PI;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, log10) (t);

  res = FUNCTION (tensor, fcmpc) (t, LOG10 (x), BASE_EPSILON);

  gsl_test (!tensor_int_is_null (res),
            NAME (tensor)
            "_log10 returns " OUT_FORMAT " for argument " OUT_FORMAT,
            LOG10 (x), x);

  tensor_int_free (res);

  /* log1p */
  x = BASE_EPSILON;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, log1p) (t);

  res = FUNCTION (tensor, fcmpc) (t, LOG1P (x), BASE_EPSILON);

  gsl_test (!tensor_int_is_null (res),
            NAME (tensor)
            "_log1p returns " OUT_FORMAT " for argument " OUT_FORMAT,
            LOG1P (x), x);

  tensor_int_free (res);

  /* logb */
  x = 8;

  FUNCTION (tensor, set_all) (t, x);

  FUNCTION (tensor, logb) (t);

  res = FUNCTION (tensor, fcmpc) (t, LOGB (x), BASE_EPSILON);

  gsl_test (!tensor_int_is_null (res),
            NAME (tensor)
            "_logb returns " OUT_FORMAT " for argument " OUT_FORMAT,
            LOGB (x), x);

  tensor_int_free (res);

  FUNCTION (tensor, free) (t);

#endif  /* FP */
}

void
FUNCTION (test, oper_round) (const size_t dim,
                             const size_t size0,
                             const size_t size1,
                             const size_t size2)
{
  TYPE (tensor) * t;
  t = FUNCTION (tensor, alloc) (dim, size0, size1, size2);

#if FP
  
  const size_t N = 9;    
  BASE x[] = {-4, -3.75, -3.5, -3.25, 0, 3.25, 3.5, 3.75, 4};

  size_t i;
  for (i = 0; i < N; ++i)
    {
      /* ceil */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, ceil) (t);
      
      gsl_test (!FUNCTION (tensor, is_const) (t, CEIL (x[i])),
                NAME (tensor)
                "_ceil returns " OUT_FORMAT
                " for argument " OUT_FORMAT,
                CEIL (x[i]), x[i]);

      /* floor */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, floor) (t);
      
      gsl_test (!FUNCTION (tensor, is_const) (t, FLOOR (x[i])),
                NAME (tensor)
                "_floor returns " OUT_FORMAT
                " for argument " OUT_FORMAT,
                FLOOR (x[i]), x[i]);

      /* round */
      FUNCTION (tensor, set_all) (t, x[i]);

      FUNCTION (tensor, round) (t);
      
      gsl_test (!FUNCTION (tensor, is_const) (t, ROUND (x[i])),
                NAME (tensor)
                "_round returns " OUT_FORMAT
                " for argument " OUT_FORMAT,
                ROUND (x[i]), x[i]);
    }

#endif  /* FP */

  const size_t M = 5;
  BASE y[] = {0, 1, 2, 3, 4};
  BASE clip_min = 1;
  BASE clip_max = 2;
  BASE clip[] = {1, 1, 2, 2, 2};

  size_t j;
  for (j = 0; j < M; ++j)
    {
      /* clip */
      FUNCTION (tensor, set_all) (t, y[j]);
      
      FUNCTION (tensor, clip) (t, clip_min, clip_max);
      
      gsl_test (!FUNCTION (tensor, is_const) (t, clip[j]),
                NAME (tensor)
                "_clip [" OUT_FORMAT ", " OUT_FORMAT "] "
                "returns " OUT_FORMAT
                " for argument " OUT_FORMAT,
                clip_min, clip_max, clip[j], y[j]);
    }
  
  FUNCTION (tensor, free) (t);
}

void
FUNCTION (test, oper_stat) (const size_t dim,
                            const size_t size0,
                            const size_t size1,
                            const size_t size2)
{
  TYPE (tensor) * t, * u;
  
#if defined(BASE_CHAR) || defined(BASE_UCHAR)
  
  t = FUNCTION (tensor, alloc) (dim,
                                GSL_MIN (size0, 5),
                                GSL_MIN (size1, 5),
                                GSL_MIN (size2, 5));

  printf ("Tesiting with modified tensor sizes: %zu, %zu, %zu\n",
          GSL_MIN (size0, 5), GSL_MIN (size1, 5), GSL_MIN (size2, 5));

#else

  t = FUNCTION (tensor, alloc) (dim, size0, size1, size2);
  
#endif /* defined(BASE_CHAR) || defined(BASE_UCHAR)   */
  
  u = FUNCTION (tensor, alloc) (1, dim);

  ATOMIC x = 1;
  
  /* Expected values */
  ATOMIC exp_min, exp_max;
  size_t exp_min_idx, exp_max_idx;
  double exp_sum, exp_prod, exp_mean, exp_var, exp_std;

  /* Returned values */
  ATOMIC min, max;
  size_t min_idx, max_idx;
  double sum, prod, mean, var, std;

  size_t i, j, k;
  for (i = 0; i < t->size[0]; ++i)
    for (j = 0; j < t->size[1]; ++j)
      for (k = 0; k < t->size[2]; ++k)
        {
          FUNCTION (tensor, set) (t, x, i, j, k);
          ++x;
        }  

  /* Tensor u for testing product */
  FUNCTION (tensor, set) (u, size0, 0);
  FUNCTION (tensor, set) (u, size1, 1);
  FUNCTION (tensor, set) (u, size2, 2);

  size_t n = FUNCTION (tensor, tsize) (t);
  size_t last_idx = FUNCTION (tensor, index) (t, n - 1);

  exp_min = 1;
  exp_min_idx = FUNCTION (tensor, index) (t, 0);
  
  exp_max = t->data[last_idx];
  exp_max_idx = last_idx;

  /* min */
  gsl_test (exp_min != FUNCTION (tensor, min) (t),
            NAME (tensor) "_min returns correct value");
  /* max */
  gsl_test (exp_max != FUNCTION (tensor, max) (t),
            NAME (tensor) "_max returns correct value");

  /* minmax */
  FUNCTION (tensor, minmax) (t, &min, &max);

  gsl_test (min != exp_min || max != exp_max,
            NAME (tensor) "_minmax returns correct values");

  /* min_index */
  gsl_test (exp_min_idx != FUNCTION (tensor, min_index) (t),
            NAME (tensor) "_min_index returns correct index");

  /* max_index */
  gsl_test (exp_max_idx != FUNCTION (tensor, max_index) (t),
            NAME (tensor) "_max_index returns correct index");

  /* minmax_index */
  FUNCTION (tensor, minmax_index) (t, &min_idx, &max_idx);

  gsl_test (min_idx != exp_min_idx || max_idx != exp_max_idx,
            NAME (tensor) "_minmax_index returns correct indices");

  /* sum */
  exp_sum = n / 2. * (n + 1);

  sum = FUNCTION (tensor, sum) (t);

  gsl_test (sum != exp_sum,
            NAME (tensor) "_sum returns correct value");

  /* prod */
  exp_prod = size0 * size1 * size2;

  prod = FUNCTION (tensor, prod) (u);
  
  gsl_test (prod != exp_prod,
            NAME (tensor) "_prod returns correct value");

  /* mean */
  exp_mean = exp_sum / n;

  mean = FUNCTION (tensor, mean) (t);

  gsl_test (mean != exp_mean,
            NAME (tensor) "_mean returns correct value");

  /* var */
  exp_var = 0;
  for (i = 0; i < t->size[0]; ++i)
    for (j = 0; j < t->size[1]; ++j)
      for (k = 0; k < t->size[2]; ++k)
        {
          exp_var += (FUNCTION (tensor, get) (t, i, j, k) - exp_mean) *
            (FUNCTION (tensor, get) (t, i, j, k) - exp_mean);
        }
  
  exp_var /= n;

  var = FUNCTION (tensor, var) (t);

  gsl_test (var != exp_var,
            NAME (tensor) "_var returns correct value");

  /* std */
  exp_std = sqrt (exp_var);

  std = FUNCTION (tensor, std) (t);
  
  gsl_test (std != exp_std,
            NAME (tensor) "_std returns correct value");
  
  FUNCTION (tensor, free) (t);
  FUNCTION (tensor, free) (u);
}

void
FUNCTION (test, oper_sort) (const size_t dim,
                            const size_t size0,
                            const size_t size1,
                            const size_t size2)
{
  TYPE (tensor) * t;
  
#if defined(BASE_CHAR) || defined(BASE_UCHAR)
  
  t = FUNCTION (tensor, alloc) (dim,
                                GSL_MIN (size0, 5),
                                GSL_MIN (size1, 5),
                                GSL_MIN (size2, 5));

  printf ("Tesiting with modified tensor sizes: %zu, %zu, %zu\n",
          GSL_MIN (size0, 5), GSL_MIN (size1, 5), GSL_MIN (size2, 5));

#else

  t = FUNCTION (tensor, alloc) (dim, size0, size1, size2);
  
#endif /* defined(BASE_CHAR) || defined(BASE_UCHAR)   */

  BASE x = t->size[0] * t->size[1] * t->size[2];
  BASE y;

  int status = 0;

  size_t i, j, k;
  for (i = 0; i < t->size[0]; ++i)
    for (j = 0; j < t->size[1]; ++j)
      for (k = 0; k < t->size[2]; ++k)
        {
          FUNCTION (tensor, set) (t, x--, i, j, k);
        }

  FUNCTION (tensor, sort) (t);

  y = FUNCTION (tensor, get) (t, 0, 0, 0);

  for (i = 0; i < t->size[0]; ++i)
    for (j = 0; j < t->size[1]; ++j)
      for (k = 0; k < t->size[2]; ++k)
        {
          x = FUNCTION (tensor, get) (t, i, j, k);

          if (x < y)
            {
              status = 1;
              break;
            }

          y = x;
        }

  gsl_test (status, NAME (tensor)
            "_sort tensor elements are in non-decreasing order");

  FUNCTION (tensor, free) (t);
}

void
FUNCTION (test, oper_sort_index) (const size_t dim,
                                  const size_t size0,
                                  const size_t size1,
                                  const size_t size2)
{
  TYPE (tensor) * t;
  
#if defined(BASE_CHAR) || defined(BASE_UCHAR)
  
  t = FUNCTION (tensor, alloc) (dim,
                                GSL_MIN (size0, 5),
                                GSL_MIN (size1, 5),
                                GSL_MIN (size2, 5));

  size_t p[5 * 5 * 5];

  printf ("Tesiting with modified tensor sizes: %zu, %zu, %zu\n",
          GSL_MIN (size0, 5), GSL_MIN (size1, 5), GSL_MIN (size2, 5));

#else

  t = FUNCTION (tensor, alloc) (dim, size0, size1, size2);

  size_t p[size0 * size1 * size2];
  
#endif /* defined(BASE_CHAR) || defined(BASE_UCHAR)   */

  BASE x = t->size[0] * t->size[1] * t->size[2];
  BASE y;

  int status = 0;

  size_t i, j, k;
  for (i = 0; i < t->size[0]; ++i)
    for (j = 0; j < t->size[1]; ++j)
      for (k = 0; k < t->size[2]; ++k)
        {
          FUNCTION (tensor, set) (t, x--, i, j, k);
        }

  FUNCTION (tensor, sort_index) (p, t);

  y = *FUNCTION (tensor, ptr_idx) (t, p[0]);

  int idx = 0;
  for (i = 0; i < t->size[0]; ++i)
    for (j = 0; j < t->size[1]; ++j)
      for (k = 0; k < t->size[2]; ++k)
        {
          x = *FUNCTION (tensor, ptr_idx) (t, p[idx]);

          if (x < y)
            {
              status = 1;
              break;
            }

          y = x;
          ++idx;
        }

  gsl_test (status, NAME (tensor)
            "_sort_index tensor elements at sorted indices "
            "are in non-decreasing order");

  FUNCTION (tensor, free) (t);
}

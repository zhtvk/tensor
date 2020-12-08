/* tensor/tensor_long.h
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

#ifndef __TENSOR_LONG_H__
#define __TENSOR_LONG_H__

#include <stdlib.h>
#include <stdarg.h>

#include <gsl/gsl_types.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_inline.h>
#include <gsl/gsl_check_range.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector_long.h>
#include <gsl/gsl_matrix_long.h>

#include <tensor/tensor_int.h>
#include <tensor/range.h>


#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif


__BEGIN_DECLS

typedef struct
{
  size_t dim;
  size_t * size;
  size_t * stride;
  long * data;
  gsl_block_long * block;
  int owner;
} tensor_long;

/* Allocation */

tensor_long *
tensor_long_valloc (const size_t dim, va_list argp);

tensor_long *
tensor_long_alloc (const size_t dim, ...);

tensor_long *
tensor_long_aalloc (const size_t dim, const size_t * size);

tensor_long *
tensor_long_calloc (const size_t dim, ...);

void
tensor_long_free (tensor_long * t);

/* Tensor element access */

long
tensor_long_get (const tensor_long * t, ...);

long *
tensor_long_ptr (tensor_long * t, ...);

const long *
tensor_long_const_ptr (const tensor_long * t, ...);

size_t
tensor_long_index (const tensor_long * t, const size_t i);

INLINE_DECL
long *
tensor_long_ptr_idx (tensor_long * t,
                           const size_t idx);

INLINE_DECL
const long *
tensor_long_const_ptr_idx (const tensor_long * t,
                                 const size_t idx);

void
tensor_long_set (tensor_long * t, const long x, ...);

void
tensor_long_set_zero (tensor_long * t);

void
tensor_long_set_one (tensor_long * t);

void
tensor_long_set_all (tensor_long * t, const long x);

/* Tensor properties */

int
tensor_long_vfits_size (const tensor_long * t, va_list argp);

int
tensor_long_fits_size (const tensor_long * t, ...);

int
tensor_long_match_size (const tensor_long * t1,
                              const tensor_long * t2);

int
tensor_long_match_tsize (const tensor_long * t1,
                               const tensor_long * t2);

int
tensor_long_is_null (const tensor_long * t);

int
tensor_long_is_pos (const tensor_long * t);

int
tensor_long_is_neg (const tensor_long * t);

int
tensor_long_is_nonneg (const tensor_long * t);

int
tensor_long_is_nonpos (const tensor_long * t);

int
tensor_long_equal (const tensor_long * t1,
                         const tensor_long * t2);
int
tensor_long_is_same (const tensor_long * t);

int
tensor_long_is_const (const tensor_long * t,
                            const long c);

INLINE_DECL
size_t
tensor_long_tsize (const tensor_long * t);

INLINE_DECL
int
tensor_long_is_view (const tensor_long * t);

INLINE_DECL
int
tensor_long_is_contiguous (const tensor_long * t);

/* Tensor file io */

int
tensor_long_fread (FILE * stream, tensor_long * t);

int
tensor_long_fwrite (FILE * stream, const tensor_long * t);

int
tensor_long_fscanf (FILE * stream, tensor_long * t);

int
tensor_long_fprintf (FILE * stream, const tensor_long * t, const char * format);

/* Tensor views */

tensor_long *
tensor_long_view (tensor_long * t, ...);

const tensor_long *
tensor_long_const_view (const tensor_long * t, ...);

tensor_long *
tensor_long_aview (tensor_long * t, const size_t * range);

const tensor_long *
tensor_long_const_aview (const tensor_long * t, const size_t * range);

tensor_long *
tensor_long_view_array (long * array, const size_t dim, ...);

const tensor_long *
tensor_long_const_view_array (const long * array, const size_t dim, ...);

tensor_long *
tensor_long_view_vector (gsl_vector_long * vector);

const tensor_long *
tensor_long_const_view_vector (const gsl_vector_long * vector);

_gsl_vector_long_view
gsl_vector_long_view_tensor (tensor_long * t);

_gsl_vector_long_const_view
gsl_vector_long_const_view_tensor (const tensor_long * t);

tensor_long *
tensor_long_view_matrix (gsl_matrix_long * matrix);

const tensor_long *
tensor_long_const_view_matrix (const gsl_matrix_long * matrix);

_gsl_matrix_long_view
gsl_matrix_long_view_tensor (tensor_long * t);

_gsl_matrix_long_const_view
gsl_matrix_long_const_view_tensor (const tensor_long * t);

/* Tensor operators */

tensor_long *
tensor_long_copy (const tensor_long * t_in);

int
tensor_long_assign (tensor_long * t1, const tensor_long * t2);

int
tensor_long_swap (tensor_long * t1, tensor_long * t2);

void
tensor_long_adjoin (tensor_long * t);

int
tensor_long_morph (tensor_long * t, ...);

void
tensor_long_deflate (tensor_long * t);

int
tensor_long_inflate (tensor_long * t, const size_t didx);

tensor_long *
tensor_long_concat (const size_t didx, const size_t n, ...);

/* Arithmetic operators */

void
tensor_long_abs (tensor_long * t);

void
tensor_long_neg (tensor_long * t);

void
tensor_long_inv (tensor_long * t);

int
tensor_long_add (tensor_long * t1,
                       const tensor_long * t2);

int
tensor_long_sub (tensor_long * t1,
                       const tensor_long * t2);

int
tensor_long_mul (tensor_long * t1,
                       const tensor_long * t2);

int
tensor_long_div (tensor_long * t1,
                       const tensor_long * t2);

int
tensor_long_mod (tensor_long * t1,
                       const tensor_long * t2);

void
tensor_long_scale_add (tensor_long * t,
                                 const long s,
                                 const long a);

/* Arithmetic complex only operators */

void
tensor_long_conj (tensor_long * t);

void
tensor_long_arg (tensor_long * t);

/* Trigonometric operators */

void
tensor_long_sin (tensor_long * t);

void
tensor_long_cos (tensor_long * t);

void
tensor_long_tan (tensor_long * t);

/* Reciprocal trigonometric operators */

void
tensor_long_sec (tensor_long * t);

void
tensor_long_csc (tensor_long * t);

void
tensor_long_cot (tensor_long * t);

/* Inverse trigonometric operators */

void
tensor_long_arcsin (tensor_long * t);

void
tensor_long_arccos (tensor_long * t);

void
tensor_long_arctan (tensor_long * t);

tensor_long *
tensor_long_arctan2 (const tensor_long * y,
                           const tensor_long * x);

/* Reciprocal inverse trigonometric operators */

void
tensor_long_arcsec (tensor_long * t);

void
tensor_long_arccsc (tensor_long * t);

void
tensor_long_arccot (tensor_long * t);

/* Hyperbolic operators */

void
tensor_long_sinh (tensor_long * t);

void
tensor_long_cosh (tensor_long * t);

void
tensor_long_tanh (tensor_long * t);

/* Reciprocal hyperbolic operators */

void
tensor_long_sech (tensor_long * t);

void
tensor_long_csch (tensor_long * t);

void
tensor_long_coth (tensor_long * t);

/* Inverse hyperbolic operators */

void
tensor_long_arcsinh (tensor_long * t);

void
tensor_long_arccosh (tensor_long * t);

void
tensor_long_arctanh (tensor_long * t);

/* Reciprocal inverse hyperbolic operators */

void
tensor_long_arcsech (tensor_long * t);

void
tensor_long_arccsch (tensor_long * t);

void
tensor_long_arccoth (tensor_long * t);

/* Exponential operators */

void
tensor_long_pow (tensor_long * t, long p);

void
tensor_long_pow_real (tensor_long * t, long p);

void
tensor_long_sqrt (tensor_long * t);

void
tensor_long_cbrt (tensor_long * t);

void
tensor_long_exp (tensor_long * t);

void
tensor_long_exp2 (tensor_long * t);

void
tensor_long_exp10 (tensor_long * t);

void
tensor_long_expm1 (tensor_long * t);

/* Logarithmic operators */
 
void
tensor_long_log (tensor_long * t);

void
tensor_long_log2 (tensor_long * t);

void
tensor_long_log10 (tensor_long * t);

void
tensor_long_log1p (tensor_long * t);

void
tensor_long_logb (tensor_long * t);

/* Tensor statistics */

long
tensor_long_max (const tensor_long * t);

long
tensor_long_min (const tensor_long * t);

void
tensor_long_minmax (const tensor_long * t,
                          long * min, long * max);

size_t
tensor_long_max_index (const tensor_long * t);

size_t
tensor_long_min_index (const tensor_long * t);

void
tensor_long_minmax_index (const tensor_long * t,
                                size_t * min_index,
                                size_t * max_index);

double
tensor_long_sum (const tensor_long * t);

double
tensor_long_prod (const tensor_long * t);

double
tensor_long_mean (const tensor_long * t);

double
tensor_long_var (const tensor_long * t);

double
tensor_long_std (const tensor_long * t);

/* Rounding and truncation operators */

void
tensor_long_ceil (tensor_long * t);

void
tensor_long_floor (tensor_long * t);

void
tensor_long_round (tensor_long * t);

void
tensor_long_clip (tensor_long * t,
                        const long min, const long max);

/* Logical operators */

void
tensor_long_not (tensor_long * t);

tensor_int *
tensor_long_fcmp (const tensor_long * t1,
                        const tensor_long * t2,
                        const long eps);

tensor_int *
tensor_long_fcmpc (const tensor_long * t,
                         const long x, const long eps);

tensor_int *
tensor_long_cmp (const tensor_long * t1,
                       const tensor_long * t2);

tensor_int *
tensor_long_cmpc (const tensor_long * t,
                        const long x);

tensor_int *
tensor_long_and (const tensor_long * t1,
                       const tensor_long * t2);

tensor_int *
tensor_long_or (const tensor_long * t1,
                      const tensor_long * t2);

tensor_int *
tensor_long_xor (const tensor_long * t1,
                       const tensor_long * t2);

/* Tensor distributions */

void
tensor_long_set_uniform (tensor_long * t, const gsl_rng * rng);

void
tensor_long_set_normal (tensor_long * t, const gsl_rng * rng,
                              double mu, double sigma);

void
tensor_long_set_std_normal (tensor_long * t,
                                  const gsl_rng * rng);

void
tensor_long_set_uniform_int (tensor_long * t,
                                   const gsl_rng * rng,
                                   unsigned long int max);

/* Tensor sorting */

void
tensor_long_sort (tensor_long * t);

void
tensor_long_sort_index (size_t * p, const tensor_long * t);


#ifdef HAVE_INLINE

INLINE_FUN
long *
tensor_long_ptr_idx (tensor_long * t,
                           const size_t idx)
{
  return (long *) (t->data + idx);
}

INLINE_FUN
const long *
tensor_long_const_ptr_idx (const tensor_long * t,
                                 const size_t idx)
{
  return (const long *) (t->data + idx);
}

INLINE_FUN
size_t
tensor_long_tsize (const tensor_long * t)
{
  if (t->dim == 0)
    return 0;
  
  size_t i, total_size;
  for (i = 0, total_size = 1; i < t->dim; ++i)
    {
      total_size *= t->size[i];
    }
  
  return total_size;
}

INLINE_FUN
int
tensor_long_is_view (const tensor_long * t)
{
  return (t->owner) ? 0 : 1;
}

INLINE_FUN
int
tensor_long_is_contiguous (const tensor_long * t)
{
  if (t->dim == 0)
    {
      return 1;
    }
  else
    {
      size_t i, stride = 1;
      for (i = 0; i < t->dim; ++i)
        {
          if (t->stride[t->dim - i - 1] != stride)
            {
              return 0;
            }

          stride *= t->size[t->dim - i - 1];
        }

      return 1;
    }
}

#endif  /* HAVE_INLINE */

__END_DECLS

#endif /* __TENSOR_LONG_H__ */

/* tensor/tensor_ulong.h
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

#ifndef __TENSOR_ULONG_H__
#define __TENSOR_ULONG_H__

#include <stdlib.h>
#include <stdarg.h>

#include <gsl/gsl_types.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_inline.h>
#include <gsl/gsl_check_range.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector_ulong.h>
#include <gsl/gsl_matrix_ulong.h>

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
  unsigned long * data;
  gsl_block_ulong * block;
  int owner;
} tensor_ulong;

/* Allocation */

tensor_ulong *
tensor_ulong_valloc (const size_t dim, va_list argp);

tensor_ulong *
tensor_ulong_alloc (const size_t dim, ...);

tensor_ulong *
tensor_ulong_aalloc (const size_t dim, const size_t * size);

tensor_ulong *
tensor_ulong_calloc (const size_t dim, ...);

void
tensor_ulong_free (tensor_ulong * t);

/* Tensor element access */

unsigned long
tensor_ulong_get (const tensor_ulong * t, ...);

unsigned long *
tensor_ulong_ptr (tensor_ulong * t, ...);

const unsigned long *
tensor_ulong_const_ptr (const tensor_ulong * t, ...);

size_t
tensor_ulong_index (const tensor_ulong * t, const size_t i);

INLINE_DECL
unsigned long *
tensor_ulong_ptr_idx (tensor_ulong * t,
                           const size_t idx);

INLINE_DECL
const unsigned long *
tensor_ulong_const_ptr_idx (const tensor_ulong * t,
                                 const size_t idx);

void
tensor_ulong_set (tensor_ulong * t, const unsigned long x, ...);

void
tensor_ulong_set_zero (tensor_ulong * t);

void
tensor_ulong_set_one (tensor_ulong * t);

void
tensor_ulong_set_all (tensor_ulong * t, const unsigned long x);

/* Tensor properties */

int
tensor_ulong_vfits_size (const tensor_ulong * t, va_list argp);

int
tensor_ulong_fits_size (const tensor_ulong * t, ...);

int
tensor_ulong_match_size (const tensor_ulong * t1,
                              const tensor_ulong * t2);

int
tensor_ulong_match_tsize (const tensor_ulong * t1,
                               const tensor_ulong * t2);

int
tensor_ulong_is_null (const tensor_ulong * t);

int
tensor_ulong_is_pos (const tensor_ulong * t);

int
tensor_ulong_is_neg (const tensor_ulong * t);

int
tensor_ulong_is_nonneg (const tensor_ulong * t);

int
tensor_ulong_is_nonpos (const tensor_ulong * t);

int
tensor_ulong_equal (const tensor_ulong * t1,
                         const tensor_ulong * t2);
int
tensor_ulong_is_same (const tensor_ulong * t);

int
tensor_ulong_is_const (const tensor_ulong * t,
                            const unsigned long c);

INLINE_DECL
size_t
tensor_ulong_tsize (const tensor_ulong * t);

INLINE_DECL
int
tensor_ulong_is_view (const tensor_ulong * t);

INLINE_DECL
int
tensor_ulong_is_contiguous (const tensor_ulong * t);

/* Tensor file io */

int
tensor_ulong_fread (FILE * stream, tensor_ulong * t);

int
tensor_ulong_fwrite (FILE * stream, const tensor_ulong * t);

int
tensor_ulong_fscanf (FILE * stream, tensor_ulong * t);

int
tensor_ulong_fprintf (FILE * stream, const tensor_ulong * t, const char * format);

/* Tensor views */

tensor_ulong *
tensor_ulong_view (tensor_ulong * t, ...);

const tensor_ulong *
tensor_ulong_const_view (const tensor_ulong * t, ...);

tensor_ulong *
tensor_ulong_aview (tensor_ulong * t, const size_t * range);

const tensor_ulong *
tensor_ulong_const_aview (const tensor_ulong * t, const size_t * range);

tensor_ulong *
tensor_ulong_view_array (unsigned long * array, const size_t dim, ...);

const tensor_ulong *
tensor_ulong_const_view_array (const unsigned long * array, const size_t dim, ...);

tensor_ulong *
tensor_ulong_view_vector (gsl_vector_ulong * vector);

const tensor_ulong *
tensor_ulong_const_view_vector (const gsl_vector_ulong * vector);

_gsl_vector_ulong_view
gsl_vector_ulong_view_tensor (tensor_ulong * t);

_gsl_vector_ulong_const_view
gsl_vector_ulong_const_view_tensor (const tensor_ulong * t);

tensor_ulong *
tensor_ulong_view_matrix (gsl_matrix_ulong * matrix);

const tensor_ulong *
tensor_ulong_const_view_matrix (const gsl_matrix_ulong * matrix);

_gsl_matrix_ulong_view
gsl_matrix_ulong_view_tensor (tensor_ulong * t);

_gsl_matrix_ulong_const_view
gsl_matrix_ulong_const_view_tensor (const tensor_ulong * t);

/* Tensor operators */

tensor_ulong *
tensor_ulong_copy (const tensor_ulong * t_in);

int
tensor_ulong_assign (tensor_ulong * t1, const tensor_ulong * t2);

int
tensor_ulong_swap (tensor_ulong * t1, tensor_ulong * t2);

void
tensor_ulong_adjoin (tensor_ulong * t);

int
tensor_ulong_morph (tensor_ulong * t, ...);

void
tensor_ulong_deflate (tensor_ulong * t);

int
tensor_ulong_inflate (tensor_ulong * t, const size_t didx);

tensor_ulong *
tensor_ulong_concat (const size_t didx, const size_t n, ...);

/* Arithmetic operators */

void
tensor_ulong_abs (tensor_ulong * t);

void
tensor_ulong_neg (tensor_ulong * t);

void
tensor_ulong_inv (tensor_ulong * t);

int
tensor_ulong_add (tensor_ulong * t1,
                       const tensor_ulong * t2);

int
tensor_ulong_sub (tensor_ulong * t1,
                       const tensor_ulong * t2);

int
tensor_ulong_mul (tensor_ulong * t1,
                       const tensor_ulong * t2);

int
tensor_ulong_div (tensor_ulong * t1,
                       const tensor_ulong * t2);

int
tensor_ulong_mod (tensor_ulong * t1,
                       const tensor_ulong * t2);

void
tensor_ulong_scale_add (tensor_ulong * t,
                                 const unsigned long s,
                                 const unsigned long a);

/* Arithmetic complex only operators */

void
tensor_ulong_conj (tensor_ulong * t);

void
tensor_ulong_arg (tensor_ulong * t);

/* Trigonometric operators */

void
tensor_ulong_sin (tensor_ulong * t);

void
tensor_ulong_cos (tensor_ulong * t);

void
tensor_ulong_tan (tensor_ulong * t);

/* Reciprocal trigonometric operators */

void
tensor_ulong_sec (tensor_ulong * t);

void
tensor_ulong_csc (tensor_ulong * t);

void
tensor_ulong_cot (tensor_ulong * t);

/* Inverse trigonometric operators */

void
tensor_ulong_arcsin (tensor_ulong * t);

void
tensor_ulong_arccos (tensor_ulong * t);

void
tensor_ulong_arctan (tensor_ulong * t);

tensor_ulong *
tensor_ulong_arctan2 (const tensor_ulong * y,
                           const tensor_ulong * x);

/* Reciprocal inverse trigonometric operators */

void
tensor_ulong_arcsec (tensor_ulong * t);

void
tensor_ulong_arccsc (tensor_ulong * t);

void
tensor_ulong_arccot (tensor_ulong * t);

/* Hyperbolic operators */

void
tensor_ulong_sinh (tensor_ulong * t);

void
tensor_ulong_cosh (tensor_ulong * t);

void
tensor_ulong_tanh (tensor_ulong * t);

/* Reciprocal hyperbolic operators */

void
tensor_ulong_sech (tensor_ulong * t);

void
tensor_ulong_csch (tensor_ulong * t);

void
tensor_ulong_coth (tensor_ulong * t);

/* Inverse hyperbolic operators */

void
tensor_ulong_arcsinh (tensor_ulong * t);

void
tensor_ulong_arccosh (tensor_ulong * t);

void
tensor_ulong_arctanh (tensor_ulong * t);

/* Reciprocal inverse hyperbolic operators */

void
tensor_ulong_arcsech (tensor_ulong * t);

void
tensor_ulong_arccsch (tensor_ulong * t);

void
tensor_ulong_arccoth (tensor_ulong * t);

/* Exponential operators */

void
tensor_ulong_pow (tensor_ulong * t, unsigned long p);

void
tensor_ulong_pow_real (tensor_ulong * t, unsigned long p);

void
tensor_ulong_sqrt (tensor_ulong * t);

void
tensor_ulong_cbrt (tensor_ulong * t);

void
tensor_ulong_exp (tensor_ulong * t);

void
tensor_ulong_exp2 (tensor_ulong * t);

void
tensor_ulong_exp10 (tensor_ulong * t);

void
tensor_ulong_expm1 (tensor_ulong * t);

/* Logarithmic operators */
 
void
tensor_ulong_log (tensor_ulong * t);

void
tensor_ulong_log2 (tensor_ulong * t);

void
tensor_ulong_log10 (tensor_ulong * t);

void
tensor_ulong_log1p (tensor_ulong * t);

void
tensor_ulong_logb (tensor_ulong * t);

/* Tensor statistics */

unsigned long
tensor_ulong_max (const tensor_ulong * t);

unsigned long
tensor_ulong_min (const tensor_ulong * t);

void
tensor_ulong_minmax (const tensor_ulong * t,
                          unsigned long * min, unsigned long * max);

size_t
tensor_ulong_max_index (const tensor_ulong * t);

size_t
tensor_ulong_min_index (const tensor_ulong * t);

void
tensor_ulong_minmax_index (const tensor_ulong * t,
                                size_t * min_index,
                                size_t * max_index);

double
tensor_ulong_sum (const tensor_ulong * t);

double
tensor_ulong_prod (const tensor_ulong * t);

double
tensor_ulong_mean (const tensor_ulong * t);

double
tensor_ulong_var (const tensor_ulong * t);

double
tensor_ulong_std (const tensor_ulong * t);

/* Rounding and truncation operators */

void
tensor_ulong_ceil (tensor_ulong * t);

void
tensor_ulong_floor (tensor_ulong * t);

void
tensor_ulong_round (tensor_ulong * t);

void
tensor_ulong_clip (tensor_ulong * t,
                        const unsigned long min, const unsigned long max);

/* Logical operators */

void
tensor_ulong_not (tensor_ulong * t);

tensor_int *
tensor_ulong_fcmp (const tensor_ulong * t1,
                        const tensor_ulong * t2,
                        const unsigned long eps);

tensor_int *
tensor_ulong_fcmpc (const tensor_ulong * t,
                         const unsigned long x, const unsigned long eps);

tensor_int *
tensor_ulong_cmp (const tensor_ulong * t1,
                       const tensor_ulong * t2);

tensor_int *
tensor_ulong_cmpc (const tensor_ulong * t,
                        const unsigned long x);

tensor_int *
tensor_ulong_and (const tensor_ulong * t1,
                       const tensor_ulong * t2);

tensor_int *
tensor_ulong_or (const tensor_ulong * t1,
                      const tensor_ulong * t2);

tensor_int *
tensor_ulong_xor (const tensor_ulong * t1,
                       const tensor_ulong * t2);

/* Tensor distributions */

void
tensor_ulong_set_uniform (tensor_ulong * t, const gsl_rng * rng);

void
tensor_ulong_set_normal (tensor_ulong * t, const gsl_rng * rng,
                              double mu, double sigma);

void
tensor_ulong_set_std_normal (tensor_ulong * t,
                                  const gsl_rng * rng);

void
tensor_ulong_set_uniform_int (tensor_ulong * t,
                                   const gsl_rng * rng,
                                   unsigned long int max);

/* Tensor sorting */

void
tensor_ulong_sort (tensor_ulong * t);

void
tensor_ulong_sort_index (size_t * p, const tensor_ulong * t);


#ifdef HAVE_INLINE

INLINE_FUN
unsigned long *
tensor_ulong_ptr_idx (tensor_ulong * t,
                           const size_t idx)
{
  return (unsigned long *) (t->data + idx);
}

INLINE_FUN
const unsigned long *
tensor_ulong_const_ptr_idx (const tensor_ulong * t,
                                 const size_t idx)
{
  return (const unsigned long *) (t->data + idx);
}

INLINE_FUN
size_t
tensor_ulong_tsize (const tensor_ulong * t)
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
tensor_ulong_is_view (const tensor_ulong * t)
{
  return (t->owner) ? 0 : 1;
}

INLINE_FUN
int
tensor_ulong_is_contiguous (const tensor_ulong * t)
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

#endif /* __TENSOR_ULONG_H__ */

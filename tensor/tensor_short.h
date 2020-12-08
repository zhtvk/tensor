/* tensor/tensor_short.h
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

#ifndef __TENSOR_SHORT_H__
#define __TENSOR_SHORT_H__

#include <stdlib.h>
#include <stdarg.h>

#include <gsl/gsl_types.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_inline.h>
#include <gsl/gsl_check_range.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector_short.h>
#include <gsl/gsl_matrix_short.h>

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
  short * data;
  gsl_block_short * block;
  int owner;
} tensor_short;

/* Allocation */

tensor_short *
tensor_short_valloc (const size_t dim, va_list argp);

tensor_short *
tensor_short_alloc (const size_t dim, ...);

tensor_short *
tensor_short_aalloc (const size_t dim, const size_t * size);

tensor_short *
tensor_short_calloc (const size_t dim, ...);

void
tensor_short_free (tensor_short * t);

/* Tensor element access */

short
tensor_short_get (const tensor_short * t, ...);

short *
tensor_short_ptr (tensor_short * t, ...);

const short *
tensor_short_const_ptr (const tensor_short * t, ...);

size_t
tensor_short_index (const tensor_short * t, const size_t i);

INLINE_DECL
short *
tensor_short_ptr_idx (tensor_short * t,
                           const size_t idx);

INLINE_DECL
const short *
tensor_short_const_ptr_idx (const tensor_short * t,
                                 const size_t idx);

void
tensor_short_set (tensor_short * t, const short x, ...);

void
tensor_short_set_zero (tensor_short * t);

void
tensor_short_set_one (tensor_short * t);

void
tensor_short_set_all (tensor_short * t, const short x);

/* Tensor properties */

int
tensor_short_vfits_size (const tensor_short * t, va_list argp);

int
tensor_short_fits_size (const tensor_short * t, ...);

int
tensor_short_match_size (const tensor_short * t1,
                              const tensor_short * t2);

int
tensor_short_match_tsize (const tensor_short * t1,
                               const tensor_short * t2);

int
tensor_short_is_null (const tensor_short * t);

int
tensor_short_is_pos (const tensor_short * t);

int
tensor_short_is_neg (const tensor_short * t);

int
tensor_short_is_nonneg (const tensor_short * t);

int
tensor_short_is_nonpos (const tensor_short * t);

int
tensor_short_equal (const tensor_short * t1,
                         const tensor_short * t2);
int
tensor_short_is_same (const tensor_short * t);

int
tensor_short_is_const (const tensor_short * t,
                            const short c);

INLINE_DECL
size_t
tensor_short_tsize (const tensor_short * t);

INLINE_DECL
int
tensor_short_is_view (const tensor_short * t);

INLINE_DECL
int
tensor_short_is_contiguous (const tensor_short * t);

/* Tensor file io */

int
tensor_short_fread (FILE * stream, tensor_short * t);

int
tensor_short_fwrite (FILE * stream, const tensor_short * t);

int
tensor_short_fscanf (FILE * stream, tensor_short * t);

int
tensor_short_fprintf (FILE * stream, const tensor_short * t, const char * format);

/* Tensor views */

tensor_short *
tensor_short_view (tensor_short * t, ...);

const tensor_short *
tensor_short_const_view (const tensor_short * t, ...);

tensor_short *
tensor_short_aview (tensor_short * t, const size_t * range);

const tensor_short *
tensor_short_const_aview (const tensor_short * t, const size_t * range);

tensor_short *
tensor_short_view_array (short * array, const size_t dim, ...);

const tensor_short *
tensor_short_const_view_array (const short * array, const size_t dim, ...);

tensor_short *
tensor_short_view_vector (gsl_vector_short * vector);

const tensor_short *
tensor_short_const_view_vector (const gsl_vector_short * vector);

_gsl_vector_short_view
gsl_vector_short_view_tensor (tensor_short * t);

_gsl_vector_short_const_view
gsl_vector_short_const_view_tensor (const tensor_short * t);

tensor_short *
tensor_short_view_matrix (gsl_matrix_short * matrix);

const tensor_short *
tensor_short_const_view_matrix (const gsl_matrix_short * matrix);

_gsl_matrix_short_view
gsl_matrix_short_view_tensor (tensor_short * t);

_gsl_matrix_short_const_view
gsl_matrix_short_const_view_tensor (const tensor_short * t);

/* Tensor operators */

tensor_short *
tensor_short_copy (const tensor_short * t_in);

int
tensor_short_assign (tensor_short * t1, const tensor_short * t2);

int
tensor_short_swap (tensor_short * t1, tensor_short * t2);

void
tensor_short_adjoin (tensor_short * t);

int
tensor_short_morph (tensor_short * t, ...);

void
tensor_short_deflate (tensor_short * t);

int
tensor_short_inflate (tensor_short * t, const size_t didx);

tensor_short *
tensor_short_concat (const size_t didx, const size_t n, ...);

/* Arithmetic operators */

void
tensor_short_abs (tensor_short * t);

void
tensor_short_neg (tensor_short * t);

void
tensor_short_inv (tensor_short * t);

int
tensor_short_add (tensor_short * t1,
                       const tensor_short * t2);

int
tensor_short_sub (tensor_short * t1,
                       const tensor_short * t2);

int
tensor_short_mul (tensor_short * t1,
                       const tensor_short * t2);

int
tensor_short_div (tensor_short * t1,
                       const tensor_short * t2);

int
tensor_short_mod (tensor_short * t1,
                       const tensor_short * t2);

void
tensor_short_scale_add (tensor_short * t,
                                 const short s,
                                 const short a);

/* Arithmetic complex only operators */

void
tensor_short_conj (tensor_short * t);

void
tensor_short_arg (tensor_short * t);

/* Trigonometric operators */

void
tensor_short_sin (tensor_short * t);

void
tensor_short_cos (tensor_short * t);

void
tensor_short_tan (tensor_short * t);

/* Reciprocal trigonometric operators */

void
tensor_short_sec (tensor_short * t);

void
tensor_short_csc (tensor_short * t);

void
tensor_short_cot (tensor_short * t);

/* Inverse trigonometric operators */

void
tensor_short_arcsin (tensor_short * t);

void
tensor_short_arccos (tensor_short * t);

void
tensor_short_arctan (tensor_short * t);

tensor_short *
tensor_short_arctan2 (const tensor_short * y,
                           const tensor_short * x);

/* Reciprocal inverse trigonometric operators */

void
tensor_short_arcsec (tensor_short * t);

void
tensor_short_arccsc (tensor_short * t);

void
tensor_short_arccot (tensor_short * t);

/* Hyperbolic operators */

void
tensor_short_sinh (tensor_short * t);

void
tensor_short_cosh (tensor_short * t);

void
tensor_short_tanh (tensor_short * t);

/* Reciprocal hyperbolic operators */

void
tensor_short_sech (tensor_short * t);

void
tensor_short_csch (tensor_short * t);

void
tensor_short_coth (tensor_short * t);

/* Inverse hyperbolic operators */

void
tensor_short_arcsinh (tensor_short * t);

void
tensor_short_arccosh (tensor_short * t);

void
tensor_short_arctanh (tensor_short * t);

/* Reciprocal inverse hyperbolic operators */

void
tensor_short_arcsech (tensor_short * t);

void
tensor_short_arccsch (tensor_short * t);

void
tensor_short_arccoth (tensor_short * t);

/* Exponential operators */

void
tensor_short_pow (tensor_short * t, short p);

void
tensor_short_pow_real (tensor_short * t, short p);

void
tensor_short_sqrt (tensor_short * t);

void
tensor_short_cbrt (tensor_short * t);

void
tensor_short_exp (tensor_short * t);

void
tensor_short_exp2 (tensor_short * t);

void
tensor_short_exp10 (tensor_short * t);

void
tensor_short_expm1 (tensor_short * t);

/* Logarithmic operators */
 
void
tensor_short_log (tensor_short * t);

void
tensor_short_log2 (tensor_short * t);

void
tensor_short_log10 (tensor_short * t);

void
tensor_short_log1p (tensor_short * t);

void
tensor_short_logb (tensor_short * t);

/* Tensor statistics */

short
tensor_short_max (const tensor_short * t);

short
tensor_short_min (const tensor_short * t);

void
tensor_short_minmax (const tensor_short * t,
                          short * min, short * max);

size_t
tensor_short_max_index (const tensor_short * t);

size_t
tensor_short_min_index (const tensor_short * t);

void
tensor_short_minmax_index (const tensor_short * t,
                                size_t * min_index,
                                size_t * max_index);

double
tensor_short_sum (const tensor_short * t);

double
tensor_short_prod (const tensor_short * t);

double
tensor_short_mean (const tensor_short * t);

double
tensor_short_var (const tensor_short * t);

double
tensor_short_std (const tensor_short * t);

/* Rounding and truncation operators */

void
tensor_short_ceil (tensor_short * t);

void
tensor_short_floor (tensor_short * t);

void
tensor_short_round (tensor_short * t);

void
tensor_short_clip (tensor_short * t,
                        const short min, const short max);

/* Logical operators */

void
tensor_short_not (tensor_short * t);

tensor_int *
tensor_short_fcmp (const tensor_short * t1,
                        const tensor_short * t2,
                        const short eps);

tensor_int *
tensor_short_fcmpc (const tensor_short * t,
                         const short x, const short eps);

tensor_int *
tensor_short_cmp (const tensor_short * t1,
                       const tensor_short * t2);

tensor_int *
tensor_short_cmpc (const tensor_short * t,
                        const short x);

tensor_int *
tensor_short_and (const tensor_short * t1,
                       const tensor_short * t2);

tensor_int *
tensor_short_or (const tensor_short * t1,
                      const tensor_short * t2);

tensor_int *
tensor_short_xor (const tensor_short * t1,
                       const tensor_short * t2);

/* Tensor distributions */

void
tensor_short_set_uniform (tensor_short * t, const gsl_rng * rng);

void
tensor_short_set_normal (tensor_short * t, const gsl_rng * rng,
                              double mu, double sigma);

void
tensor_short_set_std_normal (tensor_short * t,
                                  const gsl_rng * rng);

void
tensor_short_set_uniform_int (tensor_short * t,
                                   const gsl_rng * rng,
                                   unsigned long int max);

/* Tensor sorting */

void
tensor_short_sort (tensor_short * t);

void
tensor_short_sort_index (size_t * p, const tensor_short * t);


#ifdef HAVE_INLINE

INLINE_FUN
short *
tensor_short_ptr_idx (tensor_short * t,
                           const size_t idx)
{
  return (short *) (t->data + idx);
}

INLINE_FUN
const short *
tensor_short_const_ptr_idx (const tensor_short * t,
                                 const size_t idx)
{
  return (const short *) (t->data + idx);
}

INLINE_FUN
size_t
tensor_short_tsize (const tensor_short * t)
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
tensor_short_is_view (const tensor_short * t)
{
  return (t->owner) ? 0 : 1;
}

INLINE_FUN
int
tensor_short_is_contiguous (const tensor_short * t)
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

#endif /* __TENSOR_SHORT_H__ */

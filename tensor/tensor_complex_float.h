/* tensor/tensor_complex_float.h
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

#ifndef __TENSOR_COMPLEX_FLOAT_H__
#define __TENSOR_COMPLEX_FLOAT_H__

#include <stdlib.h>
#include <stdarg.h>

#include <gsl/gsl_types.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_inline.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_check_range.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector_complex_float.h>
#include <gsl/gsl_matrix_complex_float.h>

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
  float * data;
  gsl_block_complex_float * block;
  int owner;
} tensor_complex_float;

/* Allocation */

tensor_complex_float *
tensor_complex_float_valloc (const size_t dim, va_list argp);

tensor_complex_float *
tensor_complex_float_alloc (const size_t dim, ...);

tensor_complex_float *
tensor_complex_float_aalloc (const size_t dim, const size_t * size);

tensor_complex_float *
tensor_complex_float_calloc (const size_t dim, ...);

void
tensor_complex_float_free (tensor_complex_float * t);

/* Tensor element access */

gsl_complex_float
tensor_complex_float_get (const tensor_complex_float * t, ...);

gsl_complex_float *
tensor_complex_float_ptr (tensor_complex_float * t, ...);

const gsl_complex_float *
tensor_complex_float_const_ptr (const tensor_complex_float * t, ...);

size_t
tensor_complex_float_index (const tensor_complex_float * t, const size_t i);

INLINE_DECL
gsl_complex_float *
tensor_complex_float_ptr_idx (tensor_complex_float * t,
                           const size_t idx);

INLINE_DECL
const gsl_complex_float *
tensor_complex_float_const_ptr_idx (const tensor_complex_float * t,
                                 const size_t idx);

void
tensor_complex_float_set (tensor_complex_float * t, const gsl_complex_float x, ...);

void
tensor_complex_float_set_zero (tensor_complex_float * t);

void
tensor_complex_float_set_one (tensor_complex_float * t);

void
tensor_complex_float_set_all (tensor_complex_float * t, const gsl_complex_float x);

/* Tensor properties */

int
tensor_complex_float_vfits_size (const tensor_complex_float * t, va_list argp);

int
tensor_complex_float_fits_size (const tensor_complex_float * t, ...);

int
tensor_complex_float_match_size (const tensor_complex_float * t1,
                              const tensor_complex_float * t2);

int
tensor_complex_float_match_tsize (const tensor_complex_float * t1,
                               const tensor_complex_float * t2);

int
tensor_complex_float_is_null (const tensor_complex_float * t);

int
tensor_complex_float_is_pos (const tensor_complex_float * t);

int
tensor_complex_float_is_neg (const tensor_complex_float * t);

int
tensor_complex_float_is_nonneg (const tensor_complex_float * t);

int
tensor_complex_float_is_nonpos (const tensor_complex_float * t);

int
tensor_complex_float_equal (const tensor_complex_float * t1,
                         const tensor_complex_float * t2);
int
tensor_complex_float_is_same (const tensor_complex_float * t);

int
tensor_complex_float_is_const (const tensor_complex_float * t,
                            const gsl_complex_float c);

INLINE_DECL
size_t
tensor_complex_float_tsize (const tensor_complex_float * t);

INLINE_DECL
int
tensor_complex_float_is_view (const tensor_complex_float * t);

INLINE_DECL
int
tensor_complex_float_is_contiguous (const tensor_complex_float * t);

/* Tensor file io */

int
tensor_complex_float_fread (FILE * stream, tensor_complex_float * t);

int
tensor_complex_float_fwrite (FILE * stream, const tensor_complex_float * t);

int
tensor_complex_float_fscanf (FILE * stream, tensor_complex_float * t);

int
tensor_complex_float_fprintf (FILE * stream, const tensor_complex_float * t, const char * format);

/* Tensor views */

tensor_complex_float *
tensor_complex_float_view (tensor_complex_float * t, ...);

const tensor_complex_float *
tensor_complex_float_const_view (const tensor_complex_float * t, ...);

tensor_complex_float *
tensor_complex_float_aview (tensor_complex_float * t, const size_t * range);

const tensor_complex_float *
tensor_complex_float_const_aview (const tensor_complex_float * t, const size_t * range);

tensor_complex_float *
tensor_complex_float_view_array (float * array, const size_t dim, ...);

const tensor_complex_float *
tensor_complex_float_const_view_array (const float * array, const size_t dim, ...);

tensor_complex_float *
tensor_complex_float_view_vector (gsl_vector_complex_float * vector);

const tensor_complex_float *
tensor_complex_float_const_view_vector (const gsl_vector_complex_float * vector);

_gsl_vector_complex_float_view
gsl_vector_complex_float_view_tensor (tensor_complex_float * t);

_gsl_vector_complex_float_const_view
gsl_vector_complex_float_const_view_tensor (const tensor_complex_float * t);

tensor_complex_float *
tensor_complex_float_view_matrix (gsl_matrix_complex_float * matrix);

const tensor_complex_float *
tensor_complex_float_const_view_matrix (const gsl_matrix_complex_float * matrix);

_gsl_matrix_complex_float_view
gsl_matrix_complex_float_view_tensor (tensor_complex_float * t);

_gsl_matrix_complex_float_const_view
gsl_matrix_complex_float_const_view_tensor (const tensor_complex_float * t);

/* Tensor operators */

tensor_complex_float *
tensor_complex_float_copy (const tensor_complex_float * t_in);

int
tensor_complex_float_assign (tensor_complex_float * t1, const tensor_complex_float * t2);

int
tensor_complex_float_swap (tensor_complex_float * t1, tensor_complex_float * t2);

void
tensor_complex_float_adjoin (tensor_complex_float * t);

int
tensor_complex_float_morph (tensor_complex_float * t, ...);

void
tensor_complex_float_deflate (tensor_complex_float * t);

int
tensor_complex_float_inflate (tensor_complex_float * t, const size_t didx);

tensor_complex_float *
tensor_complex_float_concat (const size_t didx, const size_t n, ...);

/* Arithmetic operators */

void
tensor_complex_float_abs (tensor_complex_float * t);

void
tensor_complex_float_neg (tensor_complex_float * t);

void
tensor_complex_float_inv (tensor_complex_float * t);

int
tensor_complex_float_add (tensor_complex_float * t1,
                       const tensor_complex_float * t2);

int
tensor_complex_float_sub (tensor_complex_float * t1,
                       const tensor_complex_float * t2);

int
tensor_complex_float_mul (tensor_complex_float * t1,
                       const tensor_complex_float * t2);

int
tensor_complex_float_div (tensor_complex_float * t1,
                       const tensor_complex_float * t2);

int
tensor_complex_float_mod (tensor_complex_float * t1,
                       const tensor_complex_float * t2);

void
tensor_complex_float_scale_add (tensor_complex_float * t,
                                 const float s,
                                 const float a);

/* Arithmetic complex only operators */

void
tensor_complex_float_conj (tensor_complex_float * t);

void
tensor_complex_float_arg (tensor_complex_float * t);

/* Trigonometric operators */

void
tensor_complex_float_sin (tensor_complex_float * t);

void
tensor_complex_float_cos (tensor_complex_float * t);

void
tensor_complex_float_tan (tensor_complex_float * t);

/* Reciprocal trigonometric operators */

void
tensor_complex_float_sec (tensor_complex_float * t);

void
tensor_complex_float_csc (tensor_complex_float * t);

void
tensor_complex_float_cot (tensor_complex_float * t);

/* Inverse trigonometric operators */

void
tensor_complex_float_arcsin (tensor_complex_float * t);

void
tensor_complex_float_arccos (tensor_complex_float * t);

void
tensor_complex_float_arctan (tensor_complex_float * t);

tensor_complex_float *
tensor_complex_float_arctan2 (const tensor_complex_float * y,
                           const tensor_complex_float * x);

/* Reciprocal inverse trigonometric operators */

void
tensor_complex_float_arcsec (tensor_complex_float * t);

void
tensor_complex_float_arccsc (tensor_complex_float * t);

void
tensor_complex_float_arccot (tensor_complex_float * t);

/* Hyperbolic operators */

void
tensor_complex_float_sinh (tensor_complex_float * t);

void
tensor_complex_float_cosh (tensor_complex_float * t);

void
tensor_complex_float_tanh (tensor_complex_float * t);

/* Reciprocal hyperbolic operators */

void
tensor_complex_float_sech (tensor_complex_float * t);

void
tensor_complex_float_csch (tensor_complex_float * t);

void
tensor_complex_float_coth (tensor_complex_float * t);

/* Inverse hyperbolic operators */

void
tensor_complex_float_arcsinh (tensor_complex_float * t);

void
tensor_complex_float_arccosh (tensor_complex_float * t);

void
tensor_complex_float_arctanh (tensor_complex_float * t);

/* Reciprocal inverse hyperbolic operators */

void
tensor_complex_float_arcsech (tensor_complex_float * t);

void
tensor_complex_float_arccsch (tensor_complex_float * t);

void
tensor_complex_float_arccoth (tensor_complex_float * t);

/* Exponential operators */

void
tensor_complex_float_pow (tensor_complex_float * t, gsl_complex_float p);

void
tensor_complex_float_pow_real (tensor_complex_float * t, float p);

void
tensor_complex_float_sqrt (tensor_complex_float * t);

void
tensor_complex_float_cbrt (tensor_complex_float * t);

void
tensor_complex_float_exp (tensor_complex_float * t);

void
tensor_complex_float_exp2 (tensor_complex_float * t);

void
tensor_complex_float_exp10 (tensor_complex_float * t);

void
tensor_complex_float_expm1 (tensor_complex_float * t);

/* Logarithmic operators */
 
void
tensor_complex_float_log (tensor_complex_float * t);

void
tensor_complex_float_log2 (tensor_complex_float * t);

void
tensor_complex_float_log10 (tensor_complex_float * t);

void
tensor_complex_float_log1p (tensor_complex_float * t);

void
tensor_complex_float_logb (tensor_complex_float * t);

/* Tensor statistics */

float
tensor_complex_float_max (const tensor_complex_float * t);

float
tensor_complex_float_min (const tensor_complex_float * t);

void
tensor_complex_float_minmax (const tensor_complex_float * t,
                          float * min, float * max);

size_t
tensor_complex_float_max_index (const tensor_complex_float * t);

size_t
tensor_complex_float_min_index (const tensor_complex_float * t);

void
tensor_complex_float_minmax_index (const tensor_complex_float * t,
                                size_t * min_index,
                                size_t * max_index);

double
tensor_complex_float_sum (const tensor_complex_float * t);

double
tensor_complex_float_prod (const tensor_complex_float * t);

double
tensor_complex_float_mean (const tensor_complex_float * t);

double
tensor_complex_float_var (const tensor_complex_float * t);

double
tensor_complex_float_std (const tensor_complex_float * t);

/* Rounding and truncation operators */

void
tensor_complex_float_ceil (tensor_complex_float * t);

void
tensor_complex_float_floor (tensor_complex_float * t);

void
tensor_complex_float_round (tensor_complex_float * t);

void
tensor_complex_float_clip (tensor_complex_float * t,
                        const gsl_complex_float min, const gsl_complex_float max);

/* Logical operators */

void
tensor_complex_float_not (tensor_complex_float * t);

tensor_int *
tensor_complex_float_fcmp (const tensor_complex_float * t1,
                        const tensor_complex_float * t2,
                        const float eps);

tensor_int *
tensor_complex_float_fcmpc (const tensor_complex_float * t,
                         const float x, const float eps);

tensor_int *
tensor_complex_float_cmp (const tensor_complex_float * t1,
                       const tensor_complex_float * t2);

tensor_int *
tensor_complex_float_cmpc (const tensor_complex_float * t,
                        const float x);

tensor_int *
tensor_complex_float_and (const tensor_complex_float * t1,
                       const tensor_complex_float * t2);

tensor_int *
tensor_complex_float_or (const tensor_complex_float * t1,
                      const tensor_complex_float * t2);

tensor_int *
tensor_complex_float_xor (const tensor_complex_float * t1,
                       const tensor_complex_float * t2);

/* Tensor distributions */

void
tensor_complex_float_set_uniform (tensor_complex_float * t, const gsl_rng * rng);

void
tensor_complex_float_set_normal (tensor_complex_float * t, const gsl_rng * rng,
                              double mu, double sigma);

void
tensor_complex_float_set_std_normal (tensor_complex_float * t,
                                  const gsl_rng * rng);

void
tensor_complex_float_set_uniform_int (tensor_complex_float * t,
                                   const gsl_rng * rng,
                                   unsigned long int max);

/* Tensor sorting */

void
tensor_complex_float_sort (tensor_complex_float * t);

void
tensor_complex_float_sort_index (size_t * p, const tensor_complex_float * t);


#ifdef HAVE_INLINE

INLINE_FUN
gsl_complex_float *
tensor_complex_float_ptr_idx (tensor_complex_float * t,
                           const size_t idx)
{
  return (gsl_complex_float *) (t->data + idx);
}

INLINE_FUN
const gsl_complex_float *
tensor_complex_float_const_ptr_idx (const tensor_complex_float * t,
                                 const size_t idx)
{
  return (const gsl_complex_float *) (t->data + idx);
}

INLINE_FUN
size_t
tensor_complex_float_tsize (const tensor_complex_float * t)
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
tensor_complex_float_is_view (const tensor_complex_float * t)
{
  return (t->owner) ? 0 : 1;
}

INLINE_FUN
int
tensor_complex_float_is_contiguous (const tensor_complex_float * t)
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

#endif /* __TENSOR_COMPLEX_FLOAT_H__ */

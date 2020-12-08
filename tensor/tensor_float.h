/* tensor/tensor_float.h
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

#ifndef __TENSOR_FLOAT_H__
#define __TENSOR_FLOAT_H__

#include <stdlib.h>
#include <stdarg.h>

#include <gsl/gsl_types.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_inline.h>
#include <gsl/gsl_check_range.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector_float.h>
#include <gsl/gsl_matrix_float.h>

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
  gsl_block_float * block;
  int owner;
} tensor_float;

/* Allocation */

tensor_float *
tensor_float_valloc (const size_t dim, va_list argp);

tensor_float *
tensor_float_alloc (const size_t dim, ...);

tensor_float *
tensor_float_aalloc (const size_t dim, const size_t * size);

tensor_float *
tensor_float_calloc (const size_t dim, ...);

void
tensor_float_free (tensor_float * t);

/* Tensor element access */

float
tensor_float_get (const tensor_float * t, ...);

float *
tensor_float_ptr (tensor_float * t, ...);

const float *
tensor_float_const_ptr (const tensor_float * t, ...);

size_t
tensor_float_index (const tensor_float * t, const size_t i);

INLINE_DECL
float *
tensor_float_ptr_idx (tensor_float * t,
                           const size_t idx);

INLINE_DECL
const float *
tensor_float_const_ptr_idx (const tensor_float * t,
                                 const size_t idx);

void
tensor_float_set (tensor_float * t, const float x, ...);

void
tensor_float_set_zero (tensor_float * t);

void
tensor_float_set_one (tensor_float * t);

void
tensor_float_set_all (tensor_float * t, const float x);

/* Tensor properties */

int
tensor_float_vfits_size (const tensor_float * t, va_list argp);

int
tensor_float_fits_size (const tensor_float * t, ...);

int
tensor_float_match_size (const tensor_float * t1,
                              const tensor_float * t2);

int
tensor_float_match_tsize (const tensor_float * t1,
                               const tensor_float * t2);

int
tensor_float_is_null (const tensor_float * t);

int
tensor_float_is_pos (const tensor_float * t);

int
tensor_float_is_neg (const tensor_float * t);

int
tensor_float_is_nonneg (const tensor_float * t);

int
tensor_float_is_nonpos (const tensor_float * t);

int
tensor_float_equal (const tensor_float * t1,
                         const tensor_float * t2);
int
tensor_float_is_same (const tensor_float * t);

int
tensor_float_is_const (const tensor_float * t,
                            const float c);

INLINE_DECL
size_t
tensor_float_tsize (const tensor_float * t);

INLINE_DECL
int
tensor_float_is_view (const tensor_float * t);

INLINE_DECL
int
tensor_float_is_contiguous (const tensor_float * t);

/* Tensor file io */

int
tensor_float_fread (FILE * stream, tensor_float * t);

int
tensor_float_fwrite (FILE * stream, const tensor_float * t);

int
tensor_float_fscanf (FILE * stream, tensor_float * t);

int
tensor_float_fprintf (FILE * stream, const tensor_float * t, const char * format);

/* Tensor views */

tensor_float *
tensor_float_view (tensor_float * t, ...);

const tensor_float *
tensor_float_const_view (const tensor_float * t, ...);

tensor_float *
tensor_float_aview (tensor_float * t, const size_t * range);

const tensor_float *
tensor_float_const_aview (const tensor_float * t, const size_t * range);

tensor_float *
tensor_float_view_array (float * array, const size_t dim, ...);

const tensor_float *
tensor_float_const_view_array (const float * array, const size_t dim, ...);

tensor_float *
tensor_float_view_vector (gsl_vector_float * vector);

const tensor_float *
tensor_float_const_view_vector (const gsl_vector_float * vector);

_gsl_vector_float_view
gsl_vector_float_view_tensor (tensor_float * t);

_gsl_vector_float_const_view
gsl_vector_float_const_view_tensor (const tensor_float * t);

tensor_float *
tensor_float_view_matrix (gsl_matrix_float * matrix);

const tensor_float *
tensor_float_const_view_matrix (const gsl_matrix_float * matrix);

_gsl_matrix_float_view
gsl_matrix_float_view_tensor (tensor_float * t);

_gsl_matrix_float_const_view
gsl_matrix_float_const_view_tensor (const tensor_float * t);

/* Tensor operators */

tensor_float *
tensor_float_copy (const tensor_float * t_in);

int
tensor_float_assign (tensor_float * t1, const tensor_float * t2);

int
tensor_float_swap (tensor_float * t1, tensor_float * t2);

void
tensor_float_adjoin (tensor_float * t);

int
tensor_float_morph (tensor_float * t, ...);

void
tensor_float_deflate (tensor_float * t);

int
tensor_float_inflate (tensor_float * t, const size_t didx);

tensor_float *
tensor_float_concat (const size_t didx, const size_t n, ...);

/* Arithmetic operators */

void
tensor_float_abs (tensor_float * t);

void
tensor_float_neg (tensor_float * t);

void
tensor_float_inv (tensor_float * t);

int
tensor_float_add (tensor_float * t1,
                       const tensor_float * t2);

int
tensor_float_sub (tensor_float * t1,
                       const tensor_float * t2);

int
tensor_float_mul (tensor_float * t1,
                       const tensor_float * t2);

int
tensor_float_div (tensor_float * t1,
                       const tensor_float * t2);

int
tensor_float_mod (tensor_float * t1,
                       const tensor_float * t2);

void
tensor_float_scale_add (tensor_float * t,
                                 const float s,
                                 const float a);

/* Arithmetic complex only operators */

void
tensor_float_conj (tensor_float * t);

void
tensor_float_arg (tensor_float * t);

/* Trigonometric operators */

void
tensor_float_sin (tensor_float * t);

void
tensor_float_cos (tensor_float * t);

void
tensor_float_tan (tensor_float * t);

/* Reciprocal trigonometric operators */

void
tensor_float_sec (tensor_float * t);

void
tensor_float_csc (tensor_float * t);

void
tensor_float_cot (tensor_float * t);

/* Inverse trigonometric operators */

void
tensor_float_arcsin (tensor_float * t);

void
tensor_float_arccos (tensor_float * t);

void
tensor_float_arctan (tensor_float * t);

tensor_float *
tensor_float_arctan2 (const tensor_float * y,
                           const tensor_float * x);

/* Reciprocal inverse trigonometric operators */

void
tensor_float_arcsec (tensor_float * t);

void
tensor_float_arccsc (tensor_float * t);

void
tensor_float_arccot (tensor_float * t);

/* Hyperbolic operators */

void
tensor_float_sinh (tensor_float * t);

void
tensor_float_cosh (tensor_float * t);

void
tensor_float_tanh (tensor_float * t);

/* Reciprocal hyperbolic operators */

void
tensor_float_sech (tensor_float * t);

void
tensor_float_csch (tensor_float * t);

void
tensor_float_coth (tensor_float * t);

/* Inverse hyperbolic operators */

void
tensor_float_arcsinh (tensor_float * t);

void
tensor_float_arccosh (tensor_float * t);

void
tensor_float_arctanh (tensor_float * t);

/* Reciprocal inverse hyperbolic operators */

void
tensor_float_arcsech (tensor_float * t);

void
tensor_float_arccsch (tensor_float * t);

void
tensor_float_arccoth (tensor_float * t);

/* Exponential operators */

void
tensor_float_pow (tensor_float * t, float p);

void
tensor_float_pow_real (tensor_float * t, float p);

void
tensor_float_sqrt (tensor_float * t);

void
tensor_float_cbrt (tensor_float * t);

void
tensor_float_exp (tensor_float * t);

void
tensor_float_exp2 (tensor_float * t);

void
tensor_float_exp10 (tensor_float * t);

void
tensor_float_expm1 (tensor_float * t);

/* Logarithmic operators */
 
void
tensor_float_log (tensor_float * t);

void
tensor_float_log2 (tensor_float * t);

void
tensor_float_log10 (tensor_float * t);

void
tensor_float_log1p (tensor_float * t);

void
tensor_float_logb (tensor_float * t);

/* Tensor statistics */

float
tensor_float_max (const tensor_float * t);

float
tensor_float_min (const tensor_float * t);

void
tensor_float_minmax (const tensor_float * t,
                          float * min, float * max);

size_t
tensor_float_max_index (const tensor_float * t);

size_t
tensor_float_min_index (const tensor_float * t);

void
tensor_float_minmax_index (const tensor_float * t,
                                size_t * min_index,
                                size_t * max_index);

double
tensor_float_sum (const tensor_float * t);

double
tensor_float_prod (const tensor_float * t);

double
tensor_float_mean (const tensor_float * t);

double
tensor_float_var (const tensor_float * t);

double
tensor_float_std (const tensor_float * t);

/* Rounding and truncation operators */

void
tensor_float_ceil (tensor_float * t);

void
tensor_float_floor (tensor_float * t);

void
tensor_float_round (tensor_float * t);

void
tensor_float_clip (tensor_float * t,
                        const float min, const float max);

/* Logical operators */

void
tensor_float_not (tensor_float * t);

tensor_int *
tensor_float_fcmp (const tensor_float * t1,
                        const tensor_float * t2,
                        const float eps);

tensor_int *
tensor_float_fcmpc (const tensor_float * t,
                         const float x, const float eps);

tensor_int *
tensor_float_cmp (const tensor_float * t1,
                       const tensor_float * t2);

tensor_int *
tensor_float_cmpc (const tensor_float * t,
                        const float x);

tensor_int *
tensor_float_and (const tensor_float * t1,
                       const tensor_float * t2);

tensor_int *
tensor_float_or (const tensor_float * t1,
                      const tensor_float * t2);

tensor_int *
tensor_float_xor (const tensor_float * t1,
                       const tensor_float * t2);

/* Tensor distributions */

void
tensor_float_set_uniform (tensor_float * t, const gsl_rng * rng);

void
tensor_float_set_normal (tensor_float * t, const gsl_rng * rng,
                              double mu, double sigma);

void
tensor_float_set_std_normal (tensor_float * t,
                                  const gsl_rng * rng);

void
tensor_float_set_uniform_int (tensor_float * t,
                                   const gsl_rng * rng,
                                   unsigned long int max);

/* Tensor sorting */

void
tensor_float_sort (tensor_float * t);

void
tensor_float_sort_index (size_t * p, const tensor_float * t);


#ifdef HAVE_INLINE

INLINE_FUN
float *
tensor_float_ptr_idx (tensor_float * t,
                           const size_t idx)
{
  return (float *) (t->data + idx);
}

INLINE_FUN
const float *
tensor_float_const_ptr_idx (const tensor_float * t,
                                 const size_t idx)
{
  return (const float *) (t->data + idx);
}

INLINE_FUN
size_t
tensor_float_tsize (const tensor_float * t)
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
tensor_float_is_view (const tensor_float * t)
{
  return (t->owner) ? 0 : 1;
}

INLINE_FUN
int
tensor_float_is_contiguous (const tensor_float * t)
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

#endif /* __TENSOR_FLOAT_H__ */

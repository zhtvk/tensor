/* tensor/tensor_complex_double.h
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

#ifndef __TENSOR_COMPLEX_DOUBLE_H__
#define __TENSOR_COMPLEX_DOUBLE_H__

#include <stdlib.h>
#include <stdarg.h>

#include <gsl/gsl_types.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_inline.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_check_range.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector_complex_double.h>
#include <gsl/gsl_matrix_complex_double.h>

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
  double * data;
  gsl_block_complex * block;
  int owner;
} tensor_complex;

/* Allocation */

tensor_complex *
tensor_complex_valloc (const size_t dim, va_list argp);

tensor_complex *
tensor_complex_alloc (const size_t dim, ...);

tensor_complex *
tensor_complex_aalloc (const size_t dim, const size_t * size);

tensor_complex *
tensor_complex_calloc (const size_t dim, ...);

void
tensor_complex_free (tensor_complex * t);

/* Tensor element access */

gsl_complex
tensor_complex_get (const tensor_complex * t, ...);

gsl_complex *
tensor_complex_ptr (tensor_complex * t, ...);

const gsl_complex *
tensor_complex_const_ptr (const tensor_complex * t, ...);

size_t
tensor_complex_index (const tensor_complex * t, const size_t i);

INLINE_DECL
gsl_complex *
tensor_complex_ptr_idx (tensor_complex * t,
                           const size_t idx);

INLINE_DECL
const gsl_complex *
tensor_complex_const_ptr_idx (const tensor_complex * t,
                                 const size_t idx);

void
tensor_complex_set (tensor_complex * t, const gsl_complex x, ...);

void
tensor_complex_set_zero (tensor_complex * t);

void
tensor_complex_set_one (tensor_complex * t);

void
tensor_complex_set_all (tensor_complex * t, const gsl_complex x);

/* Tensor properties */

int
tensor_complex_vfits_size (const tensor_complex * t, va_list argp);

int
tensor_complex_fits_size (const tensor_complex * t, ...);

int
tensor_complex_match_size (const tensor_complex * t1,
                              const tensor_complex * t2);

int
tensor_complex_match_tsize (const tensor_complex * t1,
                               const tensor_complex * t2);

int
tensor_complex_is_null (const tensor_complex * t);

int
tensor_complex_is_pos (const tensor_complex * t);

int
tensor_complex_is_neg (const tensor_complex * t);

int
tensor_complex_is_nonneg (const tensor_complex * t);

int
tensor_complex_is_nonpos (const tensor_complex * t);

int
tensor_complex_equal (const tensor_complex * t1,
                         const tensor_complex * t2);
int
tensor_complex_is_same (const tensor_complex * t);

int
tensor_complex_is_const (const tensor_complex * t,
                            const gsl_complex c);

INLINE_DECL
size_t
tensor_complex_tsize (const tensor_complex * t);

INLINE_DECL
int
tensor_complex_is_view (const tensor_complex * t);

INLINE_DECL
int
tensor_complex_is_contiguous (const tensor_complex * t);

/* Tensor file io */

int
tensor_complex_fread (FILE * stream, tensor_complex * t);

int
tensor_complex_fwrite (FILE * stream, const tensor_complex * t);

int
tensor_complex_fscanf (FILE * stream, tensor_complex * t);

int
tensor_complex_fprintf (FILE * stream, const tensor_complex * t, const char * format);

/* Tensor views */

tensor_complex *
tensor_complex_view (tensor_complex * t, ...);

const tensor_complex *
tensor_complex_const_view (const tensor_complex * t, ...);

tensor_complex *
tensor_complex_aview (tensor_complex * t, const size_t * range);

const tensor_complex *
tensor_complex_const_aview (const tensor_complex * t, const size_t * range);

tensor_complex *
tensor_complex_view_array (double * array, const size_t dim, ...);

const tensor_complex *
tensor_complex_const_view_array (const double * array, const size_t dim, ...);

tensor_complex *
tensor_complex_view_vector (gsl_vector_complex * vector);

const tensor_complex *
tensor_complex_const_view_vector (const gsl_vector_complex * vector);

_gsl_vector_complex_view
gsl_vector_complex_view_tensor (tensor_complex * t);

_gsl_vector_complex_const_view
gsl_vector_complex_const_view_tensor (const tensor_complex * t);

tensor_complex *
tensor_complex_view_matrix (gsl_matrix_complex * matrix);

const tensor_complex *
tensor_complex_const_view_matrix (const gsl_matrix_complex * matrix);

_gsl_matrix_complex_view
gsl_matrix_complex_view_tensor (tensor_complex * t);

_gsl_matrix_complex_const_view
gsl_matrix_complex_const_view_tensor (const tensor_complex * t);

/* Tensor operators */

tensor_complex *
tensor_complex_copy (const tensor_complex * t_in);

int
tensor_complex_assign (tensor_complex * t1, const tensor_complex * t2);

int
tensor_complex_swap (tensor_complex * t1, tensor_complex * t2);

void
tensor_complex_adjoin (tensor_complex * t);

int
tensor_complex_morph (tensor_complex * t, ...);

void
tensor_complex_deflate (tensor_complex * t);

int
tensor_complex_inflate (tensor_complex * t, const size_t didx);

tensor_complex *
tensor_complex_concat (const size_t didx, const size_t n, ...);

/* Arithmetic operators */

void
tensor_complex_abs (tensor_complex * t);

void
tensor_complex_neg (tensor_complex * t);

void
tensor_complex_inv (tensor_complex * t);

int
tensor_complex_add (tensor_complex * t1,
                       const tensor_complex * t2);

int
tensor_complex_sub (tensor_complex * t1,
                       const tensor_complex * t2);

int
tensor_complex_mul (tensor_complex * t1,
                       const tensor_complex * t2);

int
tensor_complex_div (tensor_complex * t1,
                       const tensor_complex * t2);

int
tensor_complex_mod (tensor_complex * t1,
                       const tensor_complex * t2);

void
tensor_complex_scale_add (tensor_complex * t,
                                 const double s,
                                 const double a);

/* Arithmetic complex only operators */

void
tensor_complex_conj (tensor_complex * t);

void
tensor_complex_arg (tensor_complex * t);

/* Trigonometric operators */

void
tensor_complex_sin (tensor_complex * t);

void
tensor_complex_cos (tensor_complex * t);

void
tensor_complex_tan (tensor_complex * t);

/* Reciprocal trigonometric operators */

void
tensor_complex_sec (tensor_complex * t);

void
tensor_complex_csc (tensor_complex * t);

void
tensor_complex_cot (tensor_complex * t);

/* Inverse trigonometric operators */

void
tensor_complex_arcsin (tensor_complex * t);

void
tensor_complex_arccos (tensor_complex * t);

void
tensor_complex_arctan (tensor_complex * t);

tensor_complex *
tensor_complex_arctan2 (const tensor_complex * y,
                           const tensor_complex * x);

/* Reciprocal inverse trigonometric operators */

void
tensor_complex_arcsec (tensor_complex * t);

void
tensor_complex_arccsc (tensor_complex * t);

void
tensor_complex_arccot (tensor_complex * t);

/* Hyperbolic operators */

void
tensor_complex_sinh (tensor_complex * t);

void
tensor_complex_cosh (tensor_complex * t);

void
tensor_complex_tanh (tensor_complex * t);

/* Reciprocal hyperbolic operators */

void
tensor_complex_sech (tensor_complex * t);

void
tensor_complex_csch (tensor_complex * t);

void
tensor_complex_coth (tensor_complex * t);

/* Inverse hyperbolic operators */

void
tensor_complex_arcsinh (tensor_complex * t);

void
tensor_complex_arccosh (tensor_complex * t);

void
tensor_complex_arctanh (tensor_complex * t);

/* Reciprocal inverse hyperbolic operators */

void
tensor_complex_arcsech (tensor_complex * t);

void
tensor_complex_arccsch (tensor_complex * t);

void
tensor_complex_arccoth (tensor_complex * t);

/* Exponential operators */

void
tensor_complex_pow (tensor_complex * t, gsl_complex p);

void
tensor_complex_pow_real (tensor_complex * t, double p);

void
tensor_complex_sqrt (tensor_complex * t);

void
tensor_complex_cbrt (tensor_complex * t);

void
tensor_complex_exp (tensor_complex * t);

void
tensor_complex_exp2 (tensor_complex * t);

void
tensor_complex_exp10 (tensor_complex * t);

void
tensor_complex_expm1 (tensor_complex * t);

/* Logarithmic operators */
 
void
tensor_complex_log (tensor_complex * t);

void
tensor_complex_log2 (tensor_complex * t);

void
tensor_complex_log10 (tensor_complex * t);

void
tensor_complex_log1p (tensor_complex * t);

void
tensor_complex_logb (tensor_complex * t);

/* Tensor statistics */

double
tensor_complex_max (const tensor_complex * t);

double
tensor_complex_min (const tensor_complex * t);

void
tensor_complex_minmax (const tensor_complex * t,
                          double * min, double * max);

size_t
tensor_complex_max_index (const tensor_complex * t);

size_t
tensor_complex_min_index (const tensor_complex * t);

void
tensor_complex_minmax_index (const tensor_complex * t,
                                size_t * min_index,
                                size_t * max_index);

double
tensor_complex_sum (const tensor_complex * t);

double
tensor_complex_prod (const tensor_complex * t);

double
tensor_complex_mean (const tensor_complex * t);

double
tensor_complex_var (const tensor_complex * t);

double
tensor_complex_std (const tensor_complex * t);

/* Rounding and truncation operators */

void
tensor_complex_ceil (tensor_complex * t);

void
tensor_complex_floor (tensor_complex * t);

void
tensor_complex_round (tensor_complex * t);

void
tensor_complex_clip (tensor_complex * t,
                        const gsl_complex min, const gsl_complex max);

/* Logical operators */

void
tensor_complex_not (tensor_complex * t);

tensor_int *
tensor_complex_fcmp (const tensor_complex * t1,
                        const tensor_complex * t2,
                        const double eps);

tensor_int *
tensor_complex_fcmpc (const tensor_complex * t,
                         const double x, const double eps);

tensor_int *
tensor_complex_cmp (const tensor_complex * t1,
                       const tensor_complex * t2);

tensor_int *
tensor_complex_cmpc (const tensor_complex * t,
                        const double x);

tensor_int *
tensor_complex_and (const tensor_complex * t1,
                       const tensor_complex * t2);

tensor_int *
tensor_complex_or (const tensor_complex * t1,
                      const tensor_complex * t2);

tensor_int *
tensor_complex_xor (const tensor_complex * t1,
                       const tensor_complex * t2);

/* Tensor distributions */

void
tensor_complex_set_uniform (tensor_complex * t, const gsl_rng * rng);

void
tensor_complex_set_normal (tensor_complex * t, const gsl_rng * rng,
                              double mu, double sigma);

void
tensor_complex_set_std_normal (tensor_complex * t,
                                  const gsl_rng * rng);

void
tensor_complex_set_uniform_int (tensor_complex * t,
                                   const gsl_rng * rng,
                                   unsigned long int max);

/* Tensor sorting */

void
tensor_complex_sort (tensor_complex * t);

void
tensor_complex_sort_index (size_t * p, const tensor_complex * t);


#ifdef HAVE_INLINE

INLINE_FUN
gsl_complex *
tensor_complex_ptr_idx (tensor_complex * t,
                           const size_t idx)
{
  return (gsl_complex *) (t->data + idx);
}

INLINE_FUN
const gsl_complex *
tensor_complex_const_ptr_idx (const tensor_complex * t,
                                 const size_t idx)
{
  return (const gsl_complex *) (t->data + idx);
}

INLINE_FUN
size_t
tensor_complex_tsize (const tensor_complex * t)
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
tensor_complex_is_view (const tensor_complex * t)
{
  return (t->owner) ? 0 : 1;
}

INLINE_FUN
int
tensor_complex_is_contiguous (const tensor_complex * t)
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

#endif /* __TENSOR_COMPLEX_DOUBLE_H__ */

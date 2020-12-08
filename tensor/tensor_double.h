/* tensor/tensor_double.h
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

#ifndef __TENSOR_DOUBLE_H__
#define __TENSOR_DOUBLE_H__

#include <stdlib.h>
#include <stdarg.h>

#include <gsl/gsl_types.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_inline.h>
#include <gsl/gsl_check_range.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector_double.h>
#include <gsl/gsl_matrix_double.h>

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
  gsl_block * block;
  int owner;
} tensor;

/* Allocation */

tensor *
tensor_valloc (const size_t dim, va_list argp);

tensor *
tensor_alloc (const size_t dim, ...);

tensor *
tensor_aalloc (const size_t dim, const size_t * size);

tensor *
tensor_calloc (const size_t dim, ...);

void
tensor_free (tensor * t);

/* Tensor element access */

double
tensor_get (const tensor * t, ...);

double *
tensor_ptr (tensor * t, ...);

const double *
tensor_const_ptr (const tensor * t, ...);

size_t
tensor_index (const tensor * t, const size_t i);

INLINE_DECL
double *
tensor_ptr_idx (tensor * t,
                           const size_t idx);

INLINE_DECL
const double *
tensor_const_ptr_idx (const tensor * t,
                                 const size_t idx);

void
tensor_set (tensor * t, const double x, ...);

void
tensor_set_zero (tensor * t);

void
tensor_set_one (tensor * t);

void
tensor_set_all (tensor * t, const double x);

/* Tensor properties */

int
tensor_vfits_size (const tensor * t, va_list argp);

int
tensor_fits_size (const tensor * t, ...);

int
tensor_match_size (const tensor * t1,
                              const tensor * t2);

int
tensor_match_tsize (const tensor * t1,
                               const tensor * t2);

int
tensor_is_null (const tensor * t);

int
tensor_is_pos (const tensor * t);

int
tensor_is_neg (const tensor * t);

int
tensor_is_nonneg (const tensor * t);

int
tensor_is_nonpos (const tensor * t);

int
tensor_equal (const tensor * t1,
                         const tensor * t2);
int
tensor_is_same (const tensor * t);

int
tensor_is_const (const tensor * t,
                            const double c);

INLINE_DECL
size_t
tensor_tsize (const tensor * t);

INLINE_DECL
int
tensor_is_view (const tensor * t);

INLINE_DECL
int
tensor_is_contiguous (const tensor * t);

/* Tensor file io */

int
tensor_fread (FILE * stream, tensor * t);

int
tensor_fwrite (FILE * stream, const tensor * t);

int
tensor_fscanf (FILE * stream, tensor * t);

int
tensor_fprintf (FILE * stream, const tensor * t, const char * format);

/* Tensor views */

tensor *
tensor_view (tensor * t, ...);

const tensor *
tensor_const_view (const tensor * t, ...);

tensor *
tensor_aview (tensor * t, const size_t * range);

const tensor *
tensor_const_aview (const tensor * t, const size_t * range);

tensor *
tensor_view_array (double * array, const size_t dim, ...);

const tensor *
tensor_const_view_array (const double * array, const size_t dim, ...);

tensor *
tensor_view_vector (gsl_vector * vector);

const tensor *
tensor_const_view_vector (const gsl_vector * vector);

_gsl_vector_view
gsl_vector_view_tensor (tensor * t);

_gsl_vector_const_view
gsl_vector_const_view_tensor (const tensor * t);

tensor *
tensor_view_matrix (gsl_matrix * matrix);

const tensor *
tensor_const_view_matrix (const gsl_matrix * matrix);

_gsl_matrix_view
gsl_matrix_view_tensor (tensor * t);

_gsl_matrix_const_view
gsl_matrix_const_view_tensor (const tensor * t);

/* Tensor operators */

tensor *
tensor_copy (const tensor * t_in);

int
tensor_assign (tensor * t1, const tensor * t2);

int
tensor_swap (tensor * t1, tensor * t2);

void
tensor_adjoin (tensor * t);

int
tensor_morph (tensor * t, ...);

void
tensor_deflate (tensor * t);

int
tensor_inflate (tensor * t, const size_t didx);

tensor *
tensor_concat (const size_t didx, const size_t n, ...);

/* Arithmetic operators */

void
tensor_abs (tensor * t);

void
tensor_neg (tensor * t);

void
tensor_inv (tensor * t);

int
tensor_add (tensor * t1,
                       const tensor * t2);

int
tensor_sub (tensor * t1,
                       const tensor * t2);

int
tensor_mul (tensor * t1,
                       const tensor * t2);

int
tensor_div (tensor * t1,
                       const tensor * t2);

int
tensor_mod (tensor * t1,
                       const tensor * t2);

void
tensor_scale_add (tensor * t,
                                 const double s,
                                 const double a);

/* Arithmetic complex only operators */

void
tensor_conj (tensor * t);

void
tensor_arg (tensor * t);

/* Trigonometric operators */

void
tensor_sin (tensor * t);

void
tensor_cos (tensor * t);

void
tensor_tan (tensor * t);

/* Reciprocal trigonometric operators */

void
tensor_sec (tensor * t);

void
tensor_csc (tensor * t);

void
tensor_cot (tensor * t);

/* Inverse trigonometric operators */

void
tensor_arcsin (tensor * t);

void
tensor_arccos (tensor * t);

void
tensor_arctan (tensor * t);

tensor *
tensor_arctan2 (const tensor * y,
                           const tensor * x);

/* Reciprocal inverse trigonometric operators */

void
tensor_arcsec (tensor * t);

void
tensor_arccsc (tensor * t);

void
tensor_arccot (tensor * t);

/* Hyperbolic operators */

void
tensor_sinh (tensor * t);

void
tensor_cosh (tensor * t);

void
tensor_tanh (tensor * t);

/* Reciprocal hyperbolic operators */

void
tensor_sech (tensor * t);

void
tensor_csch (tensor * t);

void
tensor_coth (tensor * t);

/* Inverse hyperbolic operators */

void
tensor_arcsinh (tensor * t);

void
tensor_arccosh (tensor * t);

void
tensor_arctanh (tensor * t);

/* Reciprocal inverse hyperbolic operators */

void
tensor_arcsech (tensor * t);

void
tensor_arccsch (tensor * t);

void
tensor_arccoth (tensor * t);

/* Exponential operators */

void
tensor_pow (tensor * t, double p);

void
tensor_pow_real (tensor * t, double p);

void
tensor_sqrt (tensor * t);

void
tensor_cbrt (tensor * t);

void
tensor_exp (tensor * t);

void
tensor_exp2 (tensor * t);

void
tensor_exp10 (tensor * t);

void
tensor_expm1 (tensor * t);

/* Logarithmic operators */
 
void
tensor_log (tensor * t);

void
tensor_log2 (tensor * t);

void
tensor_log10 (tensor * t);

void
tensor_log1p (tensor * t);

void
tensor_logb (tensor * t);

/* Tensor statistics */

double
tensor_max (const tensor * t);

double
tensor_min (const tensor * t);

void
tensor_minmax (const tensor * t,
                          double * min, double * max);

size_t
tensor_max_index (const tensor * t);

size_t
tensor_min_index (const tensor * t);

void
tensor_minmax_index (const tensor * t,
                                size_t * min_index,
                                size_t * max_index);

double
tensor_sum (const tensor * t);

double
tensor_prod (const tensor * t);

double
tensor_mean (const tensor * t);

double
tensor_var (const tensor * t);

double
tensor_std (const tensor * t);

/* Rounding and truncation operators */

void
tensor_ceil (tensor * t);

void
tensor_floor (tensor * t);

void
tensor_round (tensor * t);

void
tensor_clip (tensor * t,
                        const double min, const double max);

/* Logical operators */

void
tensor_not (tensor * t);

tensor_int *
tensor_fcmp (const tensor * t1,
                        const tensor * t2,
                        const double eps);

tensor_int *
tensor_fcmpc (const tensor * t,
                         const double x, const double eps);

tensor_int *
tensor_cmp (const tensor * t1,
                       const tensor * t2);

tensor_int *
tensor_cmpc (const tensor * t,
                        const double x);

tensor_int *
tensor_and (const tensor * t1,
                       const tensor * t2);

tensor_int *
tensor_or (const tensor * t1,
                      const tensor * t2);

tensor_int *
tensor_xor (const tensor * t1,
                       const tensor * t2);

/* Tensor distributions */

void
tensor_set_uniform (tensor * t, const gsl_rng * rng);

void
tensor_set_normal (tensor * t, const gsl_rng * rng,
                              double mu, double sigma);

void
tensor_set_std_normal (tensor * t,
                                  const gsl_rng * rng);

void
tensor_set_uniform_int (tensor * t,
                                   const gsl_rng * rng,
                                   unsigned long int max);

/* Tensor sorting */

void
tensor_sort (tensor * t);

void
tensor_sort_index (size_t * p, const tensor * t);


#ifdef HAVE_INLINE

INLINE_FUN
double *
tensor_ptr_idx (tensor * t,
                           const size_t idx)
{
  return (double *) (t->data + idx);
}

INLINE_FUN
const double *
tensor_const_ptr_idx (const tensor * t,
                                 const size_t idx)
{
  return (const double *) (t->data + idx);
}

INLINE_FUN
size_t
tensor_tsize (const tensor * t)
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
tensor_is_view (const tensor * t)
{
  return (t->owner) ? 0 : 1;
}

INLINE_FUN
int
tensor_is_contiguous (const tensor * t)
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

#endif /* __TENSOR_DOUBLE_H__ */

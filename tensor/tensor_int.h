/* tensor/tensor_int.h
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

#ifndef __TENSOR_INT_H__
#define __TENSOR_INT_H__

#include <stdlib.h>
#include <stdarg.h>

#include <gsl/gsl_types.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_inline.h>
#include <gsl/gsl_check_range.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector_int.h>
#include <gsl/gsl_matrix_int.h>

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
  int * data;
  gsl_block_int * block;
  int owner;
} tensor_int;

/* Allocation */

tensor_int *
tensor_int_valloc (const size_t dim, va_list argp);

tensor_int *
tensor_int_alloc (const size_t dim, ...);

tensor_int *
tensor_int_aalloc (const size_t dim, const size_t * size);

tensor_int *
tensor_int_calloc (const size_t dim, ...);

void
tensor_int_free (tensor_int * t);

/* Tensor element access */

int
tensor_int_get (const tensor_int * t, ...);

int *
tensor_int_ptr (tensor_int * t, ...);

const int *
tensor_int_const_ptr (const tensor_int * t, ...);

size_t
tensor_int_index (const tensor_int * t, const size_t i);

INLINE_DECL
int *
tensor_int_ptr_idx (tensor_int * t,
                           const size_t idx);

INLINE_DECL
const int *
tensor_int_const_ptr_idx (const tensor_int * t,
                                 const size_t idx);

void
tensor_int_set (tensor_int * t, const int x, ...);

void
tensor_int_set_zero (tensor_int * t);

void
tensor_int_set_one (tensor_int * t);

void
tensor_int_set_all (tensor_int * t, const int x);

/* Tensor properties */

int
tensor_int_vfits_size (const tensor_int * t, va_list argp);

int
tensor_int_fits_size (const tensor_int * t, ...);

int
tensor_int_match_size (const tensor_int * t1,
                              const tensor_int * t2);

int
tensor_int_match_tsize (const tensor_int * t1,
                               const tensor_int * t2);

int
tensor_int_is_null (const tensor_int * t);

int
tensor_int_is_pos (const tensor_int * t);

int
tensor_int_is_neg (const tensor_int * t);

int
tensor_int_is_nonneg (const tensor_int * t);

int
tensor_int_is_nonpos (const tensor_int * t);

int
tensor_int_equal (const tensor_int * t1,
                         const tensor_int * t2);
int
tensor_int_is_same (const tensor_int * t);

int
tensor_int_is_const (const tensor_int * t,
                            const int c);

INLINE_DECL
size_t
tensor_int_tsize (const tensor_int * t);

INLINE_DECL
int
tensor_int_is_view (const tensor_int * t);

INLINE_DECL
int
tensor_int_is_contiguous (const tensor_int * t);

/* Tensor file io */

int
tensor_int_fread (FILE * stream, tensor_int * t);

int
tensor_int_fwrite (FILE * stream, const tensor_int * t);

int
tensor_int_fscanf (FILE * stream, tensor_int * t);

int
tensor_int_fprintf (FILE * stream, const tensor_int * t, const char * format);

/* Tensor views */

tensor_int *
tensor_int_view (tensor_int * t, ...);

const tensor_int *
tensor_int_const_view (const tensor_int * t, ...);

tensor_int *
tensor_int_aview (tensor_int * t, const size_t * range);

const tensor_int *
tensor_int_const_aview (const tensor_int * t, const size_t * range);

tensor_int *
tensor_int_view_array (int * array, const size_t dim, ...);

const tensor_int *
tensor_int_const_view_array (const int * array, const size_t dim, ...);

tensor_int *
tensor_int_view_vector (gsl_vector_int * vector);

const tensor_int *
tensor_int_const_view_vector (const gsl_vector_int * vector);

_gsl_vector_int_view
gsl_vector_int_view_tensor (tensor_int * t);

_gsl_vector_int_const_view
gsl_vector_int_const_view_tensor (const tensor_int * t);

tensor_int *
tensor_int_view_matrix (gsl_matrix_int * matrix);

const tensor_int *
tensor_int_const_view_matrix (const gsl_matrix_int * matrix);

_gsl_matrix_int_view
gsl_matrix_int_view_tensor (tensor_int * t);

_gsl_matrix_int_const_view
gsl_matrix_int_const_view_tensor (const tensor_int * t);

/* Tensor operators */

tensor_int *
tensor_int_copy (const tensor_int * t_in);

int
tensor_int_assign (tensor_int * t1, const tensor_int * t2);

int
tensor_int_swap (tensor_int * t1, tensor_int * t2);

void
tensor_int_adjoin (tensor_int * t);

int
tensor_int_morph (tensor_int * t, ...);

void
tensor_int_deflate (tensor_int * t);

int
tensor_int_inflate (tensor_int * t, const size_t didx);

tensor_int *
tensor_int_concat (const size_t didx, const size_t n, ...);

/* Arithmetic operators */

void
tensor_int_abs (tensor_int * t);

void
tensor_int_neg (tensor_int * t);

void
tensor_int_inv (tensor_int * t);

int
tensor_int_add (tensor_int * t1,
                       const tensor_int * t2);

int
tensor_int_sub (tensor_int * t1,
                       const tensor_int * t2);

int
tensor_int_mul (tensor_int * t1,
                       const tensor_int * t2);

int
tensor_int_div (tensor_int * t1,
                       const tensor_int * t2);

int
tensor_int_mod (tensor_int * t1,
                       const tensor_int * t2);

void
tensor_int_scale_add (tensor_int * t,
                                 const int s,
                                 const int a);

/* Arithmetic complex only operators */

void
tensor_int_conj (tensor_int * t);

void
tensor_int_arg (tensor_int * t);

/* Trigonometric operators */

void
tensor_int_sin (tensor_int * t);

void
tensor_int_cos (tensor_int * t);

void
tensor_int_tan (tensor_int * t);

/* Reciprocal trigonometric operators */

void
tensor_int_sec (tensor_int * t);

void
tensor_int_csc (tensor_int * t);

void
tensor_int_cot (tensor_int * t);

/* Inverse trigonometric operators */

void
tensor_int_arcsin (tensor_int * t);

void
tensor_int_arccos (tensor_int * t);

void
tensor_int_arctan (tensor_int * t);

tensor_int *
tensor_int_arctan2 (const tensor_int * y,
                           const tensor_int * x);

/* Reciprocal inverse trigonometric operators */

void
tensor_int_arcsec (tensor_int * t);

void
tensor_int_arccsc (tensor_int * t);

void
tensor_int_arccot (tensor_int * t);

/* Hyperbolic operators */

void
tensor_int_sinh (tensor_int * t);

void
tensor_int_cosh (tensor_int * t);

void
tensor_int_tanh (tensor_int * t);

/* Reciprocal hyperbolic operators */

void
tensor_int_sech (tensor_int * t);

void
tensor_int_csch (tensor_int * t);

void
tensor_int_coth (tensor_int * t);

/* Inverse hyperbolic operators */

void
tensor_int_arcsinh (tensor_int * t);

void
tensor_int_arccosh (tensor_int * t);

void
tensor_int_arctanh (tensor_int * t);

/* Reciprocal inverse hyperbolic operators */

void
tensor_int_arcsech (tensor_int * t);

void
tensor_int_arccsch (tensor_int * t);

void
tensor_int_arccoth (tensor_int * t);

/* Exponential operators */

void
tensor_int_pow (tensor_int * t, int p);

void
tensor_int_pow_real (tensor_int * t, int p);

void
tensor_int_sqrt (tensor_int * t);

void
tensor_int_cbrt (tensor_int * t);

void
tensor_int_exp (tensor_int * t);

void
tensor_int_exp2 (tensor_int * t);

void
tensor_int_exp10 (tensor_int * t);

void
tensor_int_expm1 (tensor_int * t);

/* Logarithmic operators */
 
void
tensor_int_log (tensor_int * t);

void
tensor_int_log2 (tensor_int * t);

void
tensor_int_log10 (tensor_int * t);

void
tensor_int_log1p (tensor_int * t);

void
tensor_int_logb (tensor_int * t);

/* Tensor statistics */

int
tensor_int_max (const tensor_int * t);

int
tensor_int_min (const tensor_int * t);

void
tensor_int_minmax (const tensor_int * t,
                          int * min, int * max);

size_t
tensor_int_max_index (const tensor_int * t);

size_t
tensor_int_min_index (const tensor_int * t);

void
tensor_int_minmax_index (const tensor_int * t,
                                size_t * min_index,
                                size_t * max_index);

double
tensor_int_sum (const tensor_int * t);

double
tensor_int_prod (const tensor_int * t);

double
tensor_int_mean (const tensor_int * t);

double
tensor_int_var (const tensor_int * t);

double
tensor_int_std (const tensor_int * t);

/* Rounding and truncation operators */

void
tensor_int_ceil (tensor_int * t);

void
tensor_int_floor (tensor_int * t);

void
tensor_int_round (tensor_int * t);

void
tensor_int_clip (tensor_int * t,
                        const int min, const int max);

/* Logical operators */

void
tensor_int_not (tensor_int * t);

tensor_int *
tensor_int_fcmp (const tensor_int * t1,
                        const tensor_int * t2,
                        const int eps);

tensor_int *
tensor_int_fcmpc (const tensor_int * t,
                         const int x, const int eps);

tensor_int *
tensor_int_cmp (const tensor_int * t1,
                       const tensor_int * t2);

tensor_int *
tensor_int_cmpc (const tensor_int * t,
                        const int x);

tensor_int *
tensor_int_and (const tensor_int * t1,
                       const tensor_int * t2);

tensor_int *
tensor_int_or (const tensor_int * t1,
                      const tensor_int * t2);

tensor_int *
tensor_int_xor (const tensor_int * t1,
                       const tensor_int * t2);

/* Tensor distributions */

void
tensor_int_set_uniform (tensor_int * t, const gsl_rng * rng);

void
tensor_int_set_normal (tensor_int * t, const gsl_rng * rng,
                              double mu, double sigma);

void
tensor_int_set_std_normal (tensor_int * t,
                                  const gsl_rng * rng);

void
tensor_int_set_uniform_int (tensor_int * t,
                                   const gsl_rng * rng,
                                   unsigned long int max);

/* Tensor sorting */

void
tensor_int_sort (tensor_int * t);

void
tensor_int_sort_index (size_t * p, const tensor_int * t);


#ifdef HAVE_INLINE

INLINE_FUN
int *
tensor_int_ptr_idx (tensor_int * t,
                           const size_t idx)
{
  return (int *) (t->data + idx);
}

INLINE_FUN
const int *
tensor_int_const_ptr_idx (const tensor_int * t,
                                 const size_t idx)
{
  return (const int *) (t->data + idx);
}

INLINE_FUN
size_t
tensor_int_tsize (const tensor_int * t)
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
tensor_int_is_view (const tensor_int * t)
{
  return (t->owner) ? 0 : 1;
}

INLINE_FUN
int
tensor_int_is_contiguous (const tensor_int * t)
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

#endif /* __TENSOR_INT_H__ */

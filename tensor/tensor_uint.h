/* tensor/tensor_uint.h
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

#ifndef __TENSOR_UINT_H__
#define __TENSOR_UINT_H__

#include <stdlib.h>
#include <stdarg.h>

#include <gsl/gsl_types.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_inline.h>
#include <gsl/gsl_check_range.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector_uint.h>
#include <gsl/gsl_matrix_uint.h>

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
  unsigned int * data;
  gsl_block_uint * block;
  int owner;
} tensor_uint;

/* Allocation */

tensor_uint *
tensor_uint_valloc (const size_t dim, va_list argp);

tensor_uint *
tensor_uint_alloc (const size_t dim, ...);

tensor_uint *
tensor_uint_aalloc (const size_t dim, const size_t * size);

tensor_uint *
tensor_uint_calloc (const size_t dim, ...);

void
tensor_uint_free (tensor_uint * t);

/* Tensor element access */

unsigned int
tensor_uint_get (const tensor_uint * t, ...);

unsigned int *
tensor_uint_ptr (tensor_uint * t, ...);

const unsigned int *
tensor_uint_const_ptr (const tensor_uint * t, ...);

size_t
tensor_uint_index (const tensor_uint * t, const size_t i);

INLINE_DECL
unsigned int *
tensor_uint_ptr_idx (tensor_uint * t,
                           const size_t idx);

INLINE_DECL
const unsigned int *
tensor_uint_const_ptr_idx (const tensor_uint * t,
                                 const size_t idx);

void
tensor_uint_set (tensor_uint * t, const unsigned int x, ...);

void
tensor_uint_set_zero (tensor_uint * t);

void
tensor_uint_set_one (tensor_uint * t);

void
tensor_uint_set_all (tensor_uint * t, const unsigned int x);

/* Tensor properties */

int
tensor_uint_vfits_size (const tensor_uint * t, va_list argp);

int
tensor_uint_fits_size (const tensor_uint * t, ...);

int
tensor_uint_match_size (const tensor_uint * t1,
                              const tensor_uint * t2);

int
tensor_uint_match_tsize (const tensor_uint * t1,
                               const tensor_uint * t2);

int
tensor_uint_is_null (const tensor_uint * t);

int
tensor_uint_is_pos (const tensor_uint * t);

int
tensor_uint_is_neg (const tensor_uint * t);

int
tensor_uint_is_nonneg (const tensor_uint * t);

int
tensor_uint_is_nonpos (const tensor_uint * t);

int
tensor_uint_equal (const tensor_uint * t1,
                         const tensor_uint * t2);
int
tensor_uint_is_same (const tensor_uint * t);

int
tensor_uint_is_const (const tensor_uint * t,
                            const unsigned int c);

INLINE_DECL
size_t
tensor_uint_tsize (const tensor_uint * t);

INLINE_DECL
int
tensor_uint_is_view (const tensor_uint * t);

INLINE_DECL
int
tensor_uint_is_contiguous (const tensor_uint * t);

/* Tensor file io */

int
tensor_uint_fread (FILE * stream, tensor_uint * t);

int
tensor_uint_fwrite (FILE * stream, const tensor_uint * t);

int
tensor_uint_fscanf (FILE * stream, tensor_uint * t);

int
tensor_uint_fprintf (FILE * stream, const tensor_uint * t, const char * format);

/* Tensor views */

tensor_uint *
tensor_uint_view (tensor_uint * t, ...);

const tensor_uint *
tensor_uint_const_view (const tensor_uint * t, ...);

tensor_uint *
tensor_uint_aview (tensor_uint * t, const size_t * range);

const tensor_uint *
tensor_uint_const_aview (const tensor_uint * t, const size_t * range);

tensor_uint *
tensor_uint_view_array (unsigned int * array, const size_t dim, ...);

const tensor_uint *
tensor_uint_const_view_array (const unsigned int * array, const size_t dim, ...);

tensor_uint *
tensor_uint_view_vector (gsl_vector_uint * vector);

const tensor_uint *
tensor_uint_const_view_vector (const gsl_vector_uint * vector);

_gsl_vector_uint_view
gsl_vector_uint_view_tensor (tensor_uint * t);

_gsl_vector_uint_const_view
gsl_vector_uint_const_view_tensor (const tensor_uint * t);

tensor_uint *
tensor_uint_view_matrix (gsl_matrix_uint * matrix);

const tensor_uint *
tensor_uint_const_view_matrix (const gsl_matrix_uint * matrix);

_gsl_matrix_uint_view
gsl_matrix_uint_view_tensor (tensor_uint * t);

_gsl_matrix_uint_const_view
gsl_matrix_uint_const_view_tensor (const tensor_uint * t);

/* Tensor operators */

tensor_uint *
tensor_uint_copy (const tensor_uint * t_in);

int
tensor_uint_assign (tensor_uint * t1, const tensor_uint * t2);

int
tensor_uint_swap (tensor_uint * t1, tensor_uint * t2);

void
tensor_uint_adjoin (tensor_uint * t);

int
tensor_uint_morph (tensor_uint * t, ...);

void
tensor_uint_deflate (tensor_uint * t);

int
tensor_uint_inflate (tensor_uint * t, const size_t didx);

tensor_uint *
tensor_uint_concat (const size_t didx, const size_t n, ...);

/* Arithmetic operators */

void
tensor_uint_abs (tensor_uint * t);

void
tensor_uint_neg (tensor_uint * t);

void
tensor_uint_inv (tensor_uint * t);

int
tensor_uint_add (tensor_uint * t1,
                       const tensor_uint * t2);

int
tensor_uint_sub (tensor_uint * t1,
                       const tensor_uint * t2);

int
tensor_uint_mul (tensor_uint * t1,
                       const tensor_uint * t2);

int
tensor_uint_div (tensor_uint * t1,
                       const tensor_uint * t2);

int
tensor_uint_mod (tensor_uint * t1,
                       const tensor_uint * t2);

void
tensor_uint_scale_add (tensor_uint * t,
                                 const unsigned int s,
                                 const unsigned int a);

/* Arithmetic complex only operators */

void
tensor_uint_conj (tensor_uint * t);

void
tensor_uint_arg (tensor_uint * t);

/* Trigonometric operators */

void
tensor_uint_sin (tensor_uint * t);

void
tensor_uint_cos (tensor_uint * t);

void
tensor_uint_tan (tensor_uint * t);

/* Reciprocal trigonometric operators */

void
tensor_uint_sec (tensor_uint * t);

void
tensor_uint_csc (tensor_uint * t);

void
tensor_uint_cot (tensor_uint * t);

/* Inverse trigonometric operators */

void
tensor_uint_arcsin (tensor_uint * t);

void
tensor_uint_arccos (tensor_uint * t);

void
tensor_uint_arctan (tensor_uint * t);

tensor_uint *
tensor_uint_arctan2 (const tensor_uint * y,
                           const tensor_uint * x);

/* Reciprocal inverse trigonometric operators */

void
tensor_uint_arcsec (tensor_uint * t);

void
tensor_uint_arccsc (tensor_uint * t);

void
tensor_uint_arccot (tensor_uint * t);

/* Hyperbolic operators */

void
tensor_uint_sinh (tensor_uint * t);

void
tensor_uint_cosh (tensor_uint * t);

void
tensor_uint_tanh (tensor_uint * t);

/* Reciprocal hyperbolic operators */

void
tensor_uint_sech (tensor_uint * t);

void
tensor_uint_csch (tensor_uint * t);

void
tensor_uint_coth (tensor_uint * t);

/* Inverse hyperbolic operators */

void
tensor_uint_arcsinh (tensor_uint * t);

void
tensor_uint_arccosh (tensor_uint * t);

void
tensor_uint_arctanh (tensor_uint * t);

/* Reciprocal inverse hyperbolic operators */

void
tensor_uint_arcsech (tensor_uint * t);

void
tensor_uint_arccsch (tensor_uint * t);

void
tensor_uint_arccoth (tensor_uint * t);

/* Exponential operators */

void
tensor_uint_pow (tensor_uint * t, unsigned int p);

void
tensor_uint_pow_real (tensor_uint * t, unsigned int p);

void
tensor_uint_sqrt (tensor_uint * t);

void
tensor_uint_cbrt (tensor_uint * t);

void
tensor_uint_exp (tensor_uint * t);

void
tensor_uint_exp2 (tensor_uint * t);

void
tensor_uint_exp10 (tensor_uint * t);

void
tensor_uint_expm1 (tensor_uint * t);

/* Logarithmic operators */
 
void
tensor_uint_log (tensor_uint * t);

void
tensor_uint_log2 (tensor_uint * t);

void
tensor_uint_log10 (tensor_uint * t);

void
tensor_uint_log1p (tensor_uint * t);

void
tensor_uint_logb (tensor_uint * t);

/* Tensor statistics */

unsigned int
tensor_uint_max (const tensor_uint * t);

unsigned int
tensor_uint_min (const tensor_uint * t);

void
tensor_uint_minmax (const tensor_uint * t,
                          unsigned int * min, unsigned int * max);

size_t
tensor_uint_max_index (const tensor_uint * t);

size_t
tensor_uint_min_index (const tensor_uint * t);

void
tensor_uint_minmax_index (const tensor_uint * t,
                                size_t * min_index,
                                size_t * max_index);

double
tensor_uint_sum (const tensor_uint * t);

double
tensor_uint_prod (const tensor_uint * t);

double
tensor_uint_mean (const tensor_uint * t);

double
tensor_uint_var (const tensor_uint * t);

double
tensor_uint_std (const tensor_uint * t);

/* Rounding and truncation operators */

void
tensor_uint_ceil (tensor_uint * t);

void
tensor_uint_floor (tensor_uint * t);

void
tensor_uint_round (tensor_uint * t);

void
tensor_uint_clip (tensor_uint * t,
                        const unsigned int min, const unsigned int max);

/* Logical operators */

void
tensor_uint_not (tensor_uint * t);

tensor_int *
tensor_uint_fcmp (const tensor_uint * t1,
                        const tensor_uint * t2,
                        const unsigned int eps);

tensor_int *
tensor_uint_fcmpc (const tensor_uint * t,
                         const unsigned int x, const unsigned int eps);

tensor_int *
tensor_uint_cmp (const tensor_uint * t1,
                       const tensor_uint * t2);

tensor_int *
tensor_uint_cmpc (const tensor_uint * t,
                        const unsigned int x);

tensor_int *
tensor_uint_and (const tensor_uint * t1,
                       const tensor_uint * t2);

tensor_int *
tensor_uint_or (const tensor_uint * t1,
                      const tensor_uint * t2);

tensor_int *
tensor_uint_xor (const tensor_uint * t1,
                       const tensor_uint * t2);

/* Tensor distributions */

void
tensor_uint_set_uniform (tensor_uint * t, const gsl_rng * rng);

void
tensor_uint_set_normal (tensor_uint * t, const gsl_rng * rng,
                              double mu, double sigma);

void
tensor_uint_set_std_normal (tensor_uint * t,
                                  const gsl_rng * rng);

void
tensor_uint_set_uniform_int (tensor_uint * t,
                                   const gsl_rng * rng,
                                   unsigned long int max);

/* Tensor sorting */

void
tensor_uint_sort (tensor_uint * t);

void
tensor_uint_sort_index (size_t * p, const tensor_uint * t);


#ifdef HAVE_INLINE

INLINE_FUN
unsigned int *
tensor_uint_ptr_idx (tensor_uint * t,
                           const size_t idx)
{
  return (unsigned int *) (t->data + idx);
}

INLINE_FUN
const unsigned int *
tensor_uint_const_ptr_idx (const tensor_uint * t,
                                 const size_t idx)
{
  return (const unsigned int *) (t->data + idx);
}

INLINE_FUN
size_t
tensor_uint_tsize (const tensor_uint * t)
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
tensor_uint_is_view (const tensor_uint * t)
{
  return (t->owner) ? 0 : 1;
}

INLINE_FUN
int
tensor_uint_is_contiguous (const tensor_uint * t)
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

#endif /* __TENSOR_UINT_H__ */

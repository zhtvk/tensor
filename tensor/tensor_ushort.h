/* tensor/tensor_ushort.h
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

#ifndef __TENSOR_USHORT_H__
#define __TENSOR_USHORT_H__

#include <stdlib.h>
#include <stdarg.h>

#include <gsl/gsl_types.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_inline.h>
#include <gsl/gsl_check_range.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector_ushort.h>
#include <gsl/gsl_matrix_ushort.h>

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
  unsigned short * data;
  gsl_block_ushort * block;
  int owner;
} tensor_ushort;

/* Allocation */

tensor_ushort *
tensor_ushort_valloc (const size_t dim, va_list argp);

tensor_ushort *
tensor_ushort_alloc (const size_t dim, ...);

tensor_ushort *
tensor_ushort_aalloc (const size_t dim, const size_t * size);

tensor_ushort *
tensor_ushort_calloc (const size_t dim, ...);

void
tensor_ushort_free (tensor_ushort * t);

/* Tensor element access */

unsigned short
tensor_ushort_get (const tensor_ushort * t, ...);

unsigned short *
tensor_ushort_ptr (tensor_ushort * t, ...);

const unsigned short *
tensor_ushort_const_ptr (const tensor_ushort * t, ...);

size_t
tensor_ushort_index (const tensor_ushort * t, const size_t i);

INLINE_DECL
unsigned short *
tensor_ushort_ptr_idx (tensor_ushort * t,
                           const size_t idx);

INLINE_DECL
const unsigned short *
tensor_ushort_const_ptr_idx (const tensor_ushort * t,
                                 const size_t idx);

void
tensor_ushort_set (tensor_ushort * t, const unsigned short x, ...);

void
tensor_ushort_set_zero (tensor_ushort * t);

void
tensor_ushort_set_one (tensor_ushort * t);

void
tensor_ushort_set_all (tensor_ushort * t, const unsigned short x);

/* Tensor properties */

int
tensor_ushort_vfits_size (const tensor_ushort * t, va_list argp);

int
tensor_ushort_fits_size (const tensor_ushort * t, ...);

int
tensor_ushort_match_size (const tensor_ushort * t1,
                              const tensor_ushort * t2);

int
tensor_ushort_match_tsize (const tensor_ushort * t1,
                               const tensor_ushort * t2);

int
tensor_ushort_is_null (const tensor_ushort * t);

int
tensor_ushort_is_pos (const tensor_ushort * t);

int
tensor_ushort_is_neg (const tensor_ushort * t);

int
tensor_ushort_is_nonneg (const tensor_ushort * t);

int
tensor_ushort_is_nonpos (const tensor_ushort * t);

int
tensor_ushort_equal (const tensor_ushort * t1,
                         const tensor_ushort * t2);
int
tensor_ushort_is_same (const tensor_ushort * t);

int
tensor_ushort_is_const (const tensor_ushort * t,
                            const unsigned short c);

INLINE_DECL
size_t
tensor_ushort_tsize (const tensor_ushort * t);

INLINE_DECL
int
tensor_ushort_is_view (const tensor_ushort * t);

INLINE_DECL
int
tensor_ushort_is_contiguous (const tensor_ushort * t);

/* Tensor file io */

int
tensor_ushort_fread (FILE * stream, tensor_ushort * t);

int
tensor_ushort_fwrite (FILE * stream, const tensor_ushort * t);

int
tensor_ushort_fscanf (FILE * stream, tensor_ushort * t);

int
tensor_ushort_fprintf (FILE * stream, const tensor_ushort * t, const char * format);

/* Tensor views */

tensor_ushort *
tensor_ushort_view (tensor_ushort * t, ...);

const tensor_ushort *
tensor_ushort_const_view (const tensor_ushort * t, ...);

tensor_ushort *
tensor_ushort_aview (tensor_ushort * t, const size_t * range);

const tensor_ushort *
tensor_ushort_const_aview (const tensor_ushort * t, const size_t * range);

tensor_ushort *
tensor_ushort_view_array (unsigned short * array, const size_t dim, ...);

const tensor_ushort *
tensor_ushort_const_view_array (const unsigned short * array, const size_t dim, ...);

tensor_ushort *
tensor_ushort_view_vector (gsl_vector_ushort * vector);

const tensor_ushort *
tensor_ushort_const_view_vector (const gsl_vector_ushort * vector);

_gsl_vector_ushort_view
gsl_vector_ushort_view_tensor (tensor_ushort * t);

_gsl_vector_ushort_const_view
gsl_vector_ushort_const_view_tensor (const tensor_ushort * t);

tensor_ushort *
tensor_ushort_view_matrix (gsl_matrix_ushort * matrix);

const tensor_ushort *
tensor_ushort_const_view_matrix (const gsl_matrix_ushort * matrix);

_gsl_matrix_ushort_view
gsl_matrix_ushort_view_tensor (tensor_ushort * t);

_gsl_matrix_ushort_const_view
gsl_matrix_ushort_const_view_tensor (const tensor_ushort * t);

/* Tensor operators */

tensor_ushort *
tensor_ushort_copy (const tensor_ushort * t_in);

int
tensor_ushort_assign (tensor_ushort * t1, const tensor_ushort * t2);

int
tensor_ushort_swap (tensor_ushort * t1, tensor_ushort * t2);

void
tensor_ushort_adjoin (tensor_ushort * t);

int
tensor_ushort_morph (tensor_ushort * t, ...);

void
tensor_ushort_deflate (tensor_ushort * t);

int
tensor_ushort_inflate (tensor_ushort * t, const size_t didx);

tensor_ushort *
tensor_ushort_concat (const size_t didx, const size_t n, ...);

/* Arithmetic operators */

void
tensor_ushort_abs (tensor_ushort * t);

void
tensor_ushort_neg (tensor_ushort * t);

void
tensor_ushort_inv (tensor_ushort * t);

int
tensor_ushort_add (tensor_ushort * t1,
                       const tensor_ushort * t2);

int
tensor_ushort_sub (tensor_ushort * t1,
                       const tensor_ushort * t2);

int
tensor_ushort_mul (tensor_ushort * t1,
                       const tensor_ushort * t2);

int
tensor_ushort_div (tensor_ushort * t1,
                       const tensor_ushort * t2);

int
tensor_ushort_mod (tensor_ushort * t1,
                       const tensor_ushort * t2);

void
tensor_ushort_scale_add (tensor_ushort * t,
                                 const unsigned short s,
                                 const unsigned short a);

/* Arithmetic complex only operators */

void
tensor_ushort_conj (tensor_ushort * t);

void
tensor_ushort_arg (tensor_ushort * t);

/* Trigonometric operators */

void
tensor_ushort_sin (tensor_ushort * t);

void
tensor_ushort_cos (tensor_ushort * t);

void
tensor_ushort_tan (tensor_ushort * t);

/* Reciprocal trigonometric operators */

void
tensor_ushort_sec (tensor_ushort * t);

void
tensor_ushort_csc (tensor_ushort * t);

void
tensor_ushort_cot (tensor_ushort * t);

/* Inverse trigonometric operators */

void
tensor_ushort_arcsin (tensor_ushort * t);

void
tensor_ushort_arccos (tensor_ushort * t);

void
tensor_ushort_arctan (tensor_ushort * t);

tensor_ushort *
tensor_ushort_arctan2 (const tensor_ushort * y,
                           const tensor_ushort * x);

/* Reciprocal inverse trigonometric operators */

void
tensor_ushort_arcsec (tensor_ushort * t);

void
tensor_ushort_arccsc (tensor_ushort * t);

void
tensor_ushort_arccot (tensor_ushort * t);

/* Hyperbolic operators */

void
tensor_ushort_sinh (tensor_ushort * t);

void
tensor_ushort_cosh (tensor_ushort * t);

void
tensor_ushort_tanh (tensor_ushort * t);

/* Reciprocal hyperbolic operators */

void
tensor_ushort_sech (tensor_ushort * t);

void
tensor_ushort_csch (tensor_ushort * t);

void
tensor_ushort_coth (tensor_ushort * t);

/* Inverse hyperbolic operators */

void
tensor_ushort_arcsinh (tensor_ushort * t);

void
tensor_ushort_arccosh (tensor_ushort * t);

void
tensor_ushort_arctanh (tensor_ushort * t);

/* Reciprocal inverse hyperbolic operators */

void
tensor_ushort_arcsech (tensor_ushort * t);

void
tensor_ushort_arccsch (tensor_ushort * t);

void
tensor_ushort_arccoth (tensor_ushort * t);

/* Exponential operators */

void
tensor_ushort_pow (tensor_ushort * t, unsigned short p);

void
tensor_ushort_pow_real (tensor_ushort * t, unsigned short p);

void
tensor_ushort_sqrt (tensor_ushort * t);

void
tensor_ushort_cbrt (tensor_ushort * t);

void
tensor_ushort_exp (tensor_ushort * t);

void
tensor_ushort_exp2 (tensor_ushort * t);

void
tensor_ushort_exp10 (tensor_ushort * t);

void
tensor_ushort_expm1 (tensor_ushort * t);

/* Logarithmic operators */
 
void
tensor_ushort_log (tensor_ushort * t);

void
tensor_ushort_log2 (tensor_ushort * t);

void
tensor_ushort_log10 (tensor_ushort * t);

void
tensor_ushort_log1p (tensor_ushort * t);

void
tensor_ushort_logb (tensor_ushort * t);

/* Tensor statistics */

unsigned short
tensor_ushort_max (const tensor_ushort * t);

unsigned short
tensor_ushort_min (const tensor_ushort * t);

void
tensor_ushort_minmax (const tensor_ushort * t,
                          unsigned short * min, unsigned short * max);

size_t
tensor_ushort_max_index (const tensor_ushort * t);

size_t
tensor_ushort_min_index (const tensor_ushort * t);

void
tensor_ushort_minmax_index (const tensor_ushort * t,
                                size_t * min_index,
                                size_t * max_index);

double
tensor_ushort_sum (const tensor_ushort * t);

double
tensor_ushort_prod (const tensor_ushort * t);

double
tensor_ushort_mean (const tensor_ushort * t);

double
tensor_ushort_var (const tensor_ushort * t);

double
tensor_ushort_std (const tensor_ushort * t);

/* Rounding and truncation operators */

void
tensor_ushort_ceil (tensor_ushort * t);

void
tensor_ushort_floor (tensor_ushort * t);

void
tensor_ushort_round (tensor_ushort * t);

void
tensor_ushort_clip (tensor_ushort * t,
                        const unsigned short min, const unsigned short max);

/* Logical operators */

void
tensor_ushort_not (tensor_ushort * t);

tensor_int *
tensor_ushort_fcmp (const tensor_ushort * t1,
                        const tensor_ushort * t2,
                        const unsigned short eps);

tensor_int *
tensor_ushort_fcmpc (const tensor_ushort * t,
                         const unsigned short x, const unsigned short eps);

tensor_int *
tensor_ushort_cmp (const tensor_ushort * t1,
                       const tensor_ushort * t2);

tensor_int *
tensor_ushort_cmpc (const tensor_ushort * t,
                        const unsigned short x);

tensor_int *
tensor_ushort_and (const tensor_ushort * t1,
                       const tensor_ushort * t2);

tensor_int *
tensor_ushort_or (const tensor_ushort * t1,
                      const tensor_ushort * t2);

tensor_int *
tensor_ushort_xor (const tensor_ushort * t1,
                       const tensor_ushort * t2);

/* Tensor distributions */

void
tensor_ushort_set_uniform (tensor_ushort * t, const gsl_rng * rng);

void
tensor_ushort_set_normal (tensor_ushort * t, const gsl_rng * rng,
                              double mu, double sigma);

void
tensor_ushort_set_std_normal (tensor_ushort * t,
                                  const gsl_rng * rng);

void
tensor_ushort_set_uniform_int (tensor_ushort * t,
                                   const gsl_rng * rng,
                                   unsigned long int max);

/* Tensor sorting */

void
tensor_ushort_sort (tensor_ushort * t);

void
tensor_ushort_sort_index (size_t * p, const tensor_ushort * t);


#ifdef HAVE_INLINE

INLINE_FUN
unsigned short *
tensor_ushort_ptr_idx (tensor_ushort * t,
                           const size_t idx)
{
  return (unsigned short *) (t->data + idx);
}

INLINE_FUN
const unsigned short *
tensor_ushort_const_ptr_idx (const tensor_ushort * t,
                                 const size_t idx)
{
  return (const unsigned short *) (t->data + idx);
}

INLINE_FUN
size_t
tensor_ushort_tsize (const tensor_ushort * t)
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
tensor_ushort_is_view (const tensor_ushort * t)
{
  return (t->owner) ? 0 : 1;
}

INLINE_FUN
int
tensor_ushort_is_contiguous (const tensor_ushort * t)
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

#endif /* __TENSOR_USHORT_H__ */

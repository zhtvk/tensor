/* tensor/tensor_uchar.h
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

#ifndef __TENSOR_UCHAR_H__
#define __TENSOR_UCHAR_H__

#include <stdlib.h>
#include <stdarg.h>

#include <gsl/gsl_types.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_inline.h>
#include <gsl/gsl_check_range.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector_uchar.h>
#include <gsl/gsl_matrix_uchar.h>

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
  unsigned char * data;
  gsl_block_uchar * block;
  int owner;
} tensor_uchar;

/* Allocation */

tensor_uchar *
tensor_uchar_valloc (const size_t dim, va_list argp);

tensor_uchar *
tensor_uchar_alloc (const size_t dim, ...);

tensor_uchar *
tensor_uchar_aalloc (const size_t dim, const size_t * size);

tensor_uchar *
tensor_uchar_calloc (const size_t dim, ...);

void
tensor_uchar_free (tensor_uchar * t);

/* Tensor element access */

unsigned char
tensor_uchar_get (const tensor_uchar * t, ...);

unsigned char *
tensor_uchar_ptr (tensor_uchar * t, ...);

const unsigned char *
tensor_uchar_const_ptr (const tensor_uchar * t, ...);

size_t
tensor_uchar_index (const tensor_uchar * t, const size_t i);

INLINE_DECL
unsigned char *
tensor_uchar_ptr_idx (tensor_uchar * t,
                           const size_t idx);

INLINE_DECL
const unsigned char *
tensor_uchar_const_ptr_idx (const tensor_uchar * t,
                                 const size_t idx);

void
tensor_uchar_set (tensor_uchar * t, const unsigned char x, ...);

void
tensor_uchar_set_zero (tensor_uchar * t);

void
tensor_uchar_set_one (tensor_uchar * t);

void
tensor_uchar_set_all (tensor_uchar * t, const unsigned char x);

/* Tensor properties */

int
tensor_uchar_vfits_size (const tensor_uchar * t, va_list argp);

int
tensor_uchar_fits_size (const tensor_uchar * t, ...);

int
tensor_uchar_match_size (const tensor_uchar * t1,
                              const tensor_uchar * t2);

int
tensor_uchar_match_tsize (const tensor_uchar * t1,
                               const tensor_uchar * t2);

int
tensor_uchar_is_null (const tensor_uchar * t);

int
tensor_uchar_is_pos (const tensor_uchar * t);

int
tensor_uchar_is_neg (const tensor_uchar * t);

int
tensor_uchar_is_nonneg (const tensor_uchar * t);

int
tensor_uchar_is_nonpos (const tensor_uchar * t);

int
tensor_uchar_equal (const tensor_uchar * t1,
                         const tensor_uchar * t2);
int
tensor_uchar_is_same (const tensor_uchar * t);

int
tensor_uchar_is_const (const tensor_uchar * t,
                            const unsigned char c);

INLINE_DECL
size_t
tensor_uchar_tsize (const tensor_uchar * t);

INLINE_DECL
int
tensor_uchar_is_view (const tensor_uchar * t);

INLINE_DECL
int
tensor_uchar_is_contiguous (const tensor_uchar * t);

/* Tensor file io */

int
tensor_uchar_fread (FILE * stream, tensor_uchar * t);

int
tensor_uchar_fwrite (FILE * stream, const tensor_uchar * t);

int
tensor_uchar_fscanf (FILE * stream, tensor_uchar * t);

int
tensor_uchar_fprintf (FILE * stream, const tensor_uchar * t, const char * format);

/* Tensor views */

tensor_uchar *
tensor_uchar_view (tensor_uchar * t, ...);

const tensor_uchar *
tensor_uchar_const_view (const tensor_uchar * t, ...);

tensor_uchar *
tensor_uchar_aview (tensor_uchar * t, const size_t * range);

const tensor_uchar *
tensor_uchar_const_aview (const tensor_uchar * t, const size_t * range);

tensor_uchar *
tensor_uchar_view_array (unsigned char * array, const size_t dim, ...);

const tensor_uchar *
tensor_uchar_const_view_array (const unsigned char * array, const size_t dim, ...);

tensor_uchar *
tensor_uchar_view_vector (gsl_vector_uchar * vector);

const tensor_uchar *
tensor_uchar_const_view_vector (const gsl_vector_uchar * vector);

_gsl_vector_uchar_view
gsl_vector_uchar_view_tensor (tensor_uchar * t);

_gsl_vector_uchar_const_view
gsl_vector_uchar_const_view_tensor (const tensor_uchar * t);

tensor_uchar *
tensor_uchar_view_matrix (gsl_matrix_uchar * matrix);

const tensor_uchar *
tensor_uchar_const_view_matrix (const gsl_matrix_uchar * matrix);

_gsl_matrix_uchar_view
gsl_matrix_uchar_view_tensor (tensor_uchar * t);

_gsl_matrix_uchar_const_view
gsl_matrix_uchar_const_view_tensor (const tensor_uchar * t);

/* Tensor operators */

tensor_uchar *
tensor_uchar_copy (const tensor_uchar * t_in);

int
tensor_uchar_assign (tensor_uchar * t1, const tensor_uchar * t2);

int
tensor_uchar_swap (tensor_uchar * t1, tensor_uchar * t2);

void
tensor_uchar_adjoin (tensor_uchar * t);

int
tensor_uchar_morph (tensor_uchar * t, ...);

void
tensor_uchar_deflate (tensor_uchar * t);

int
tensor_uchar_inflate (tensor_uchar * t, const size_t didx);

tensor_uchar *
tensor_uchar_concat (const size_t didx, const size_t n, ...);

/* Arithmetic operators */

void
tensor_uchar_abs (tensor_uchar * t);

void
tensor_uchar_neg (tensor_uchar * t);

void
tensor_uchar_inv (tensor_uchar * t);

int
tensor_uchar_add (tensor_uchar * t1,
                       const tensor_uchar * t2);

int
tensor_uchar_sub (tensor_uchar * t1,
                       const tensor_uchar * t2);

int
tensor_uchar_mul (tensor_uchar * t1,
                       const tensor_uchar * t2);

int
tensor_uchar_div (tensor_uchar * t1,
                       const tensor_uchar * t2);

int
tensor_uchar_mod (tensor_uchar * t1,
                       const tensor_uchar * t2);

void
tensor_uchar_scale_add (tensor_uchar * t,
                                 const unsigned char s,
                                 const unsigned char a);

/* Arithmetic complex only operators */

void
tensor_uchar_conj (tensor_uchar * t);

void
tensor_uchar_arg (tensor_uchar * t);

/* Trigonometric operators */

void
tensor_uchar_sin (tensor_uchar * t);

void
tensor_uchar_cos (tensor_uchar * t);

void
tensor_uchar_tan (tensor_uchar * t);

/* Reciprocal trigonometric operators */

void
tensor_uchar_sec (tensor_uchar * t);

void
tensor_uchar_csc (tensor_uchar * t);

void
tensor_uchar_cot (tensor_uchar * t);

/* Inverse trigonometric operators */

void
tensor_uchar_arcsin (tensor_uchar * t);

void
tensor_uchar_arccos (tensor_uchar * t);

void
tensor_uchar_arctan (tensor_uchar * t);

tensor_uchar *
tensor_uchar_arctan2 (const tensor_uchar * y,
                           const tensor_uchar * x);

/* Reciprocal inverse trigonometric operators */

void
tensor_uchar_arcsec (tensor_uchar * t);

void
tensor_uchar_arccsc (tensor_uchar * t);

void
tensor_uchar_arccot (tensor_uchar * t);

/* Hyperbolic operators */

void
tensor_uchar_sinh (tensor_uchar * t);

void
tensor_uchar_cosh (tensor_uchar * t);

void
tensor_uchar_tanh (tensor_uchar * t);

/* Reciprocal hyperbolic operators */

void
tensor_uchar_sech (tensor_uchar * t);

void
tensor_uchar_csch (tensor_uchar * t);

void
tensor_uchar_coth (tensor_uchar * t);

/* Inverse hyperbolic operators */

void
tensor_uchar_arcsinh (tensor_uchar * t);

void
tensor_uchar_arccosh (tensor_uchar * t);

void
tensor_uchar_arctanh (tensor_uchar * t);

/* Reciprocal inverse hyperbolic operators */

void
tensor_uchar_arcsech (tensor_uchar * t);

void
tensor_uchar_arccsch (tensor_uchar * t);

void
tensor_uchar_arccoth (tensor_uchar * t);

/* Exponential operators */

void
tensor_uchar_pow (tensor_uchar * t, unsigned char p);

void
tensor_uchar_pow_real (tensor_uchar * t, unsigned char p);

void
tensor_uchar_sqrt (tensor_uchar * t);

void
tensor_uchar_cbrt (tensor_uchar * t);

void
tensor_uchar_exp (tensor_uchar * t);

void
tensor_uchar_exp2 (tensor_uchar * t);

void
tensor_uchar_exp10 (tensor_uchar * t);

void
tensor_uchar_expm1 (tensor_uchar * t);

/* Logarithmic operators */
 
void
tensor_uchar_log (tensor_uchar * t);

void
tensor_uchar_log2 (tensor_uchar * t);

void
tensor_uchar_log10 (tensor_uchar * t);

void
tensor_uchar_log1p (tensor_uchar * t);

void
tensor_uchar_logb (tensor_uchar * t);

/* Tensor statistics */

unsigned char
tensor_uchar_max (const tensor_uchar * t);

unsigned char
tensor_uchar_min (const tensor_uchar * t);

void
tensor_uchar_minmax (const tensor_uchar * t,
                          unsigned char * min, unsigned char * max);

size_t
tensor_uchar_max_index (const tensor_uchar * t);

size_t
tensor_uchar_min_index (const tensor_uchar * t);

void
tensor_uchar_minmax_index (const tensor_uchar * t,
                                size_t * min_index,
                                size_t * max_index);

double
tensor_uchar_sum (const tensor_uchar * t);

double
tensor_uchar_prod (const tensor_uchar * t);

double
tensor_uchar_mean (const tensor_uchar * t);

double
tensor_uchar_var (const tensor_uchar * t);

double
tensor_uchar_std (const tensor_uchar * t);

/* Rounding and truncation operators */

void
tensor_uchar_ceil (tensor_uchar * t);

void
tensor_uchar_floor (tensor_uchar * t);

void
tensor_uchar_round (tensor_uchar * t);

void
tensor_uchar_clip (tensor_uchar * t,
                        const unsigned char min, const unsigned char max);

/* Logical operators */

void
tensor_uchar_not (tensor_uchar * t);

tensor_int *
tensor_uchar_fcmp (const tensor_uchar * t1,
                        const tensor_uchar * t2,
                        const unsigned char eps);

tensor_int *
tensor_uchar_fcmpc (const tensor_uchar * t,
                         const unsigned char x, const unsigned char eps);

tensor_int *
tensor_uchar_cmp (const tensor_uchar * t1,
                       const tensor_uchar * t2);

tensor_int *
tensor_uchar_cmpc (const tensor_uchar * t,
                        const unsigned char x);

tensor_int *
tensor_uchar_and (const tensor_uchar * t1,
                       const tensor_uchar * t2);

tensor_int *
tensor_uchar_or (const tensor_uchar * t1,
                      const tensor_uchar * t2);

tensor_int *
tensor_uchar_xor (const tensor_uchar * t1,
                       const tensor_uchar * t2);

/* Tensor distributions */

void
tensor_uchar_set_uniform (tensor_uchar * t, const gsl_rng * rng);

void
tensor_uchar_set_normal (tensor_uchar * t, const gsl_rng * rng,
                              double mu, double sigma);

void
tensor_uchar_set_std_normal (tensor_uchar * t,
                                  const gsl_rng * rng);

void
tensor_uchar_set_uniform_int (tensor_uchar * t,
                                   const gsl_rng * rng,
                                   unsigned long int max);

/* Tensor sorting */

void
tensor_uchar_sort (tensor_uchar * t);

void
tensor_uchar_sort_index (size_t * p, const tensor_uchar * t);


#ifdef HAVE_INLINE

INLINE_FUN
unsigned char *
tensor_uchar_ptr_idx (tensor_uchar * t,
                           const size_t idx)
{
  return (unsigned char *) (t->data + idx);
}

INLINE_FUN
const unsigned char *
tensor_uchar_const_ptr_idx (const tensor_uchar * t,
                                 const size_t idx)
{
  return (const unsigned char *) (t->data + idx);
}

INLINE_FUN
size_t
tensor_uchar_tsize (const tensor_uchar * t)
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
tensor_uchar_is_view (const tensor_uchar * t)
{
  return (t->owner) ? 0 : 1;
}

INLINE_FUN
int
tensor_uchar_is_contiguous (const tensor_uchar * t)
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

#endif /* __TENSOR_UCHAR_H__ */

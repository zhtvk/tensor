/* tensor/tensor_char.h
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

#ifndef __TENSOR_CHAR_H__
#define __TENSOR_CHAR_H__

#include <stdlib.h>
#include <stdarg.h>

#include <gsl/gsl_types.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_inline.h>
#include <gsl/gsl_check_range.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector_char.h>
#include <gsl/gsl_matrix_char.h>

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
  char * data;
  gsl_block_char * block;
  int owner;
} tensor_char;

/* Allocation */

tensor_char *
tensor_char_valloc (const size_t dim, va_list argp);

tensor_char *
tensor_char_alloc (const size_t dim, ...);

tensor_char *
tensor_char_aalloc (const size_t dim, const size_t * size);

tensor_char *
tensor_char_calloc (const size_t dim, ...);

void
tensor_char_free (tensor_char * t);

/* Tensor element access */

char
tensor_char_get (const tensor_char * t, ...);

char *
tensor_char_ptr (tensor_char * t, ...);

const char *
tensor_char_const_ptr (const tensor_char * t, ...);

size_t
tensor_char_index (const tensor_char * t, const size_t i);

INLINE_DECL
char *
tensor_char_ptr_idx (tensor_char * t,
                           const size_t idx);

INLINE_DECL
const char *
tensor_char_const_ptr_idx (const tensor_char * t,
                                 const size_t idx);

void
tensor_char_set (tensor_char * t, const char x, ...);

void
tensor_char_set_zero (tensor_char * t);

void
tensor_char_set_one (tensor_char * t);

void
tensor_char_set_all (tensor_char * t, const char x);

/* Tensor properties */

int
tensor_char_vfits_size (const tensor_char * t, va_list argp);

int
tensor_char_fits_size (const tensor_char * t, ...);

int
tensor_char_match_size (const tensor_char * t1,
                              const tensor_char * t2);

int
tensor_char_match_tsize (const tensor_char * t1,
                               const tensor_char * t2);

int
tensor_char_is_null (const tensor_char * t);

int
tensor_char_is_pos (const tensor_char * t);

int
tensor_char_is_neg (const tensor_char * t);

int
tensor_char_is_nonneg (const tensor_char * t);

int
tensor_char_is_nonpos (const tensor_char * t);

int
tensor_char_equal (const tensor_char * t1,
                         const tensor_char * t2);
int
tensor_char_is_same (const tensor_char * t);

int
tensor_char_is_const (const tensor_char * t,
                            const char c);

INLINE_DECL
size_t
tensor_char_tsize (const tensor_char * t);

INLINE_DECL
int
tensor_char_is_view (const tensor_char * t);

INLINE_DECL
int
tensor_char_is_contiguous (const tensor_char * t);

/* Tensor file io */

int
tensor_char_fread (FILE * stream, tensor_char * t);

int
tensor_char_fwrite (FILE * stream, const tensor_char * t);

int
tensor_char_fscanf (FILE * stream, tensor_char * t);

int
tensor_char_fprintf (FILE * stream, const tensor_char * t, const char * format);

/* Tensor views */

tensor_char *
tensor_char_view (tensor_char * t, ...);

const tensor_char *
tensor_char_const_view (const tensor_char * t, ...);

tensor_char *
tensor_char_aview (tensor_char * t, const size_t * range);

const tensor_char *
tensor_char_const_aview (const tensor_char * t, const size_t * range);

tensor_char *
tensor_char_view_array (char * array, const size_t dim, ...);

const tensor_char *
tensor_char_const_view_array (const char * array, const size_t dim, ...);

tensor_char *
tensor_char_view_vector (gsl_vector_char * vector);

const tensor_char *
tensor_char_const_view_vector (const gsl_vector_char * vector);

_gsl_vector_char_view
gsl_vector_char_view_tensor (tensor_char * t);

_gsl_vector_char_const_view
gsl_vector_char_const_view_tensor (const tensor_char * t);

tensor_char *
tensor_char_view_matrix (gsl_matrix_char * matrix);

const tensor_char *
tensor_char_const_view_matrix (const gsl_matrix_char * matrix);

_gsl_matrix_char_view
gsl_matrix_char_view_tensor (tensor_char * t);

_gsl_matrix_char_const_view
gsl_matrix_char_const_view_tensor (const tensor_char * t);

/* Tensor operators */

tensor_char *
tensor_char_copy (const tensor_char * t_in);

int
tensor_char_assign (tensor_char * t1, const tensor_char * t2);

int
tensor_char_swap (tensor_char * t1, tensor_char * t2);

void
tensor_char_adjoin (tensor_char * t);

int
tensor_char_morph (tensor_char * t, ...);

void
tensor_char_deflate (tensor_char * t);

int
tensor_char_inflate (tensor_char * t, const size_t didx);

tensor_char *
tensor_char_concat (const size_t didx, const size_t n, ...);

/* Arithmetic operators */

void
tensor_char_abs (tensor_char * t);

void
tensor_char_neg (tensor_char * t);

void
tensor_char_inv (tensor_char * t);

int
tensor_char_add (tensor_char * t1,
                       const tensor_char * t2);

int
tensor_char_sub (tensor_char * t1,
                       const tensor_char * t2);

int
tensor_char_mul (tensor_char * t1,
                       const tensor_char * t2);

int
tensor_char_div (tensor_char * t1,
                       const tensor_char * t2);

int
tensor_char_mod (tensor_char * t1,
                       const tensor_char * t2);

void
tensor_char_scale_add (tensor_char * t,
                                 const char s,
                                 const char a);

/* Arithmetic complex only operators */

void
tensor_char_conj (tensor_char * t);

void
tensor_char_arg (tensor_char * t);

/* Trigonometric operators */

void
tensor_char_sin (tensor_char * t);

void
tensor_char_cos (tensor_char * t);

void
tensor_char_tan (tensor_char * t);

/* Reciprocal trigonometric operators */

void
tensor_char_sec (tensor_char * t);

void
tensor_char_csc (tensor_char * t);

void
tensor_char_cot (tensor_char * t);

/* Inverse trigonometric operators */

void
tensor_char_arcsin (tensor_char * t);

void
tensor_char_arccos (tensor_char * t);

void
tensor_char_arctan (tensor_char * t);

tensor_char *
tensor_char_arctan2 (const tensor_char * y,
                           const tensor_char * x);

/* Reciprocal inverse trigonometric operators */

void
tensor_char_arcsec (tensor_char * t);

void
tensor_char_arccsc (tensor_char * t);

void
tensor_char_arccot (tensor_char * t);

/* Hyperbolic operators */

void
tensor_char_sinh (tensor_char * t);

void
tensor_char_cosh (tensor_char * t);

void
tensor_char_tanh (tensor_char * t);

/* Reciprocal hyperbolic operators */

void
tensor_char_sech (tensor_char * t);

void
tensor_char_csch (tensor_char * t);

void
tensor_char_coth (tensor_char * t);

/* Inverse hyperbolic operators */

void
tensor_char_arcsinh (tensor_char * t);

void
tensor_char_arccosh (tensor_char * t);

void
tensor_char_arctanh (tensor_char * t);

/* Reciprocal inverse hyperbolic operators */

void
tensor_char_arcsech (tensor_char * t);

void
tensor_char_arccsch (tensor_char * t);

void
tensor_char_arccoth (tensor_char * t);

/* Exponential operators */

void
tensor_char_pow (tensor_char * t, char p);

void
tensor_char_pow_real (tensor_char * t, char p);

void
tensor_char_sqrt (tensor_char * t);

void
tensor_char_cbrt (tensor_char * t);

void
tensor_char_exp (tensor_char * t);

void
tensor_char_exp2 (tensor_char * t);

void
tensor_char_exp10 (tensor_char * t);

void
tensor_char_expm1 (tensor_char * t);

/* Logarithmic operators */
 
void
tensor_char_log (tensor_char * t);

void
tensor_char_log2 (tensor_char * t);

void
tensor_char_log10 (tensor_char * t);

void
tensor_char_log1p (tensor_char * t);

void
tensor_char_logb (tensor_char * t);

/* Tensor statistics */

char
tensor_char_max (const tensor_char * t);

char
tensor_char_min (const tensor_char * t);

void
tensor_char_minmax (const tensor_char * t,
                          char * min, char * max);

size_t
tensor_char_max_index (const tensor_char * t);

size_t
tensor_char_min_index (const tensor_char * t);

void
tensor_char_minmax_index (const tensor_char * t,
                                size_t * min_index,
                                size_t * max_index);

double
tensor_char_sum (const tensor_char * t);

double
tensor_char_prod (const tensor_char * t);

double
tensor_char_mean (const tensor_char * t);

double
tensor_char_var (const tensor_char * t);

double
tensor_char_std (const tensor_char * t);

/* Rounding and truncation operators */

void
tensor_char_ceil (tensor_char * t);

void
tensor_char_floor (tensor_char * t);

void
tensor_char_round (tensor_char * t);

void
tensor_char_clip (tensor_char * t,
                        const char min, const char max);

/* Logical operators */

void
tensor_char_not (tensor_char * t);

tensor_int *
tensor_char_fcmp (const tensor_char * t1,
                        const tensor_char * t2,
                        const char eps);

tensor_int *
tensor_char_fcmpc (const tensor_char * t,
                         const char x, const char eps);

tensor_int *
tensor_char_cmp (const tensor_char * t1,
                       const tensor_char * t2);

tensor_int *
tensor_char_cmpc (const tensor_char * t,
                        const char x);

tensor_int *
tensor_char_and (const tensor_char * t1,
                       const tensor_char * t2);

tensor_int *
tensor_char_or (const tensor_char * t1,
                      const tensor_char * t2);

tensor_int *
tensor_char_xor (const tensor_char * t1,
                       const tensor_char * t2);

/* Tensor distributions */

void
tensor_char_set_uniform (tensor_char * t, const gsl_rng * rng);

void
tensor_char_set_normal (tensor_char * t, const gsl_rng * rng,
                              double mu, double sigma);

void
tensor_char_set_std_normal (tensor_char * t,
                                  const gsl_rng * rng);

void
tensor_char_set_uniform_int (tensor_char * t,
                                   const gsl_rng * rng,
                                   unsigned long int max);

/* Tensor sorting */

void
tensor_char_sort (tensor_char * t);

void
tensor_char_sort_index (size_t * p, const tensor_char * t);


#ifdef HAVE_INLINE

INLINE_FUN
char *
tensor_char_ptr_idx (tensor_char * t,
                           const size_t idx)
{
  return (char *) (t->data + idx);
}

INLINE_FUN
const char *
tensor_char_const_ptr_idx (const tensor_char * t,
                                 const size_t idx)
{
  return (const char *) (t->data + idx);
}

INLINE_FUN
size_t
tensor_char_tsize (const tensor_char * t)
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
tensor_char_is_view (const tensor_char * t)
{
  return (t->owner) ? 0 : 1;
}

INLINE_FUN
int
tensor_char_is_contiguous (const tensor_char * t)
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

#endif /* __TENSOR_CHAR_H__ */

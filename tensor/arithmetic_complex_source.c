/* tensor/arithmetic_complex_source.c
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

#include "oper.h"


/* Arithmetic operators */

void
FUNCTION (tensor, abs) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA_REAL (t, idx) = HYPOT (DATA_REAL (t, idx),
                                  DATA_IMAG (t, idx));
      
      DATA_IMAG (t, idx) = 0.;
    }
}

void
FUNCTION (tensor, neg) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  BASE x = ZERO;
  
  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      if (GSL_COMPLEX_EQ (DATA (t, idx), x))
        continue;
      
      DATA_REAL (t, idx) = -(DATA_REAL (t, idx));

      DATA_IMAG (t, idx) = -(DATA_IMAG (t, idx));
    }
}

void
FUNCTION (tensor, inv) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  ATOMIC rabs;

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      rabs = 1 / HYPOT (DATA_REAL (t, idx), DATA_IMAG (t, idx));

      DATA_REAL (t, idx) = (DATA_REAL (t, idx) * rabs) * rabs;

      DATA_IMAG (t, idx) = -((DATA_IMAG (t, idx) * rabs) * rabs);
    }  
}

int
FUNCTION (tensor, add) (TYPE (tensor) * t1,
                        const TYPE (tensor) * t2)
{
#if GSL_RANGE_CHECK
  
  if (GSL_RANGE_COND(1))
    {
      if(!FUNCTION (tensor, match_size) (t1, t2))
        return GSL_EBADLEN;
    }

#endif  /* GSL_RANGE_CHECK */

  const size_t n = FUNCTION (tensor, tsize) (t1);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx1 = FUNCTION (tensor, index) (t1, i);
      size_t idx2 = FUNCTION (tensor, index) (t2, i);

      DATA_REAL (t1, idx1) += CONST_DATA_REAL (t2, idx2);
      DATA_IMAG (t1, idx1) += CONST_DATA_IMAG (t2, idx2);
    }
  
  return GSL_SUCCESS;
}

int
FUNCTION (tensor, sub) (TYPE (tensor) * t1,
                        const TYPE (tensor) * t2)
{
#if GSL_RANGE_CHECK
  
  if (GSL_RANGE_COND(1))
    {
      if(!FUNCTION (tensor, match_size) (t1, t2))
        return GSL_EBADLEN;
    }

#endif  /* GSL_RANGE_CHECK */

  const size_t n = FUNCTION (tensor, tsize) (t1);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx1 = FUNCTION (tensor, index) (t1, i);
      size_t idx2 = FUNCTION (tensor, index) (t2, i);

      DATA_REAL (t1, idx1) -= CONST_DATA_REAL (t2, idx2);
      DATA_IMAG (t1, idx1) -= CONST_DATA_IMAG (t2, idx2);
    }
  
  return GSL_SUCCESS;  
}

int
FUNCTION (tensor, mul) (TYPE (tensor) * t1,
                        const TYPE (tensor) * t2)
{
#if GSL_RANGE_CHECK
  
  if (GSL_RANGE_COND(1))
    {
      if(!FUNCTION (tensor, match_size) (t1, t2))
        return GSL_EBADLEN;
    }

#endif  /* GSL_RANGE_CHECK */

  const size_t n = FUNCTION (tensor, tsize) (t1);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx1 = FUNCTION (tensor, index) (t1, i);
      size_t idx2 = FUNCTION (tensor, index) (t2, i);

      const ATOMIC t1_re = CONST_DATA_REAL (t1, idx1);
      const ATOMIC t1_im = CONST_DATA_IMAG (t1, idx1);
      
      const ATOMIC t2_re = CONST_DATA_REAL (t2, idx2);
      const ATOMIC t2_im = CONST_DATA_IMAG (t2, idx2);
      
      DATA_REAL (t1, idx1) = t1_re * t2_re - t1_im * t2_im;

      DATA_IMAG (t1, idx1) = t1_re * t2_im + t1_im * t2_re;
    }
  
  return GSL_SUCCESS;  
}

int
FUNCTION (tensor, div) (TYPE (tensor) * t1,
                        const TYPE (tensor) * t2)
{
#if GSL_RANGE_CHECK
  
  if (GSL_RANGE_COND(1))
    {
      if(!FUNCTION (tensor, match_size) (t1, t2))
        return GSL_EBADLEN;
    }

#endif  /* GSL_RANGE_CHECK */

  const size_t n = FUNCTION (tensor, tsize) (t1);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx1 = FUNCTION (tensor, index) (t1, i);
      size_t idx2 = FUNCTION (tensor, index) (t2, i);

      const ATOMIC t1_re = CONST_DATA_REAL (t1, idx1);
      const ATOMIC t1_im = CONST_DATA_IMAG (t1, idx1);
      
      const ATOMIC t2_re = CONST_DATA_REAL (t2, idx2);
      const ATOMIC t2_im = CONST_DATA_IMAG (t2, idx2);

      const ATOMIC s = 1 / HYPOT (t2_re, t2_im);
      const ATOMIC s_re = s * t2_re;
      const ATOMIC s_im = s * t2_im;
      
      DATA_REAL (t1, idx1) = (t1_re * s_re + t1_im * s_im) * s;

      DATA_IMAG (t1, idx1) = (t1_im * s_re - t1_re * s_im) * s;
    }
  
  return GSL_SUCCESS;  
}

void
FUNCTION (tensor, conj) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA_IMAG (t, idx) = -(DATA_IMAG (t, idx));
    }
}

void
FUNCTION (tensor, arg) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA_REAL (t, idx) = ATAN2 (DATA_IMAG (t, idx),
                                  DATA_REAL (t, idx));
      DATA_IMAG (t, idx) = 0;
    }
}

/* tensor/arithmetic_source.c
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

#if !defined(UNSIGNED)

void
FUNCTION (tensor, abs) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = ABS (DATA (t, idx));
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

      if (DATA (t, idx) == x)
        continue;
      
      DATA (t, idx) = -(DATA (t, idx));
    }
}

#endif  /* !defined(UNSIGNED) */

#if FP

void
FUNCTION (tensor, inv) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = 1 / DATA (t, idx);
    }  
}

#endif  /* FP */

int
FUNCTION (tensor, add) (TYPE (tensor) * t1,
                        const TYPE (tensor) * t2)
{
#if GSL_RANGE_CHECK
  
  if (GSL_RANGE_COND(1))
    {
      if (!FUNCTION (tensor, match_size) (t1, t2))
        return GSL_EBADLEN;
    }

#endif  /* GSL_RANGE_CHECK */

  const size_t n = FUNCTION (tensor, tsize) (t1);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx1 = FUNCTION (tensor, index) (t1, i);
      size_t idx2 = FUNCTION (tensor, index) (t2, i);

      DATA (t1, idx1) += CONST_DATA (t2, idx2);
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
      if (!FUNCTION (tensor, match_size) (t1, t2))
        return GSL_EBADLEN;
    }

#endif  /* GSL_RANGE_CHECK */

  const size_t n = FUNCTION (tensor, tsize) (t1);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx1 = FUNCTION (tensor, index) (t1, i);
      size_t idx2 = FUNCTION (tensor, index) (t2, i);

      DATA (t1, idx1) -= CONST_DATA (t2, idx2);
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
      if (!FUNCTION (tensor, match_size) (t1, t2))
        return GSL_EBADLEN;
    }

#endif  /* GSL_RANGE_CHECK */

  const size_t n = FUNCTION (tensor, tsize) (t1);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx1 = FUNCTION (tensor, index) (t1, i);
      size_t idx2 = FUNCTION (tensor, index) (t2, i);

      DATA (t1, idx1) *= CONST_DATA (t2, idx2);
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
      if (!FUNCTION (tensor, match_size) (t1, t2))
        return GSL_EBADLEN;      
    }

#endif  /* GSL_RANGE_CHECK */

  const size_t n = FUNCTION (tensor, tsize) (t1);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx1 = FUNCTION (tensor, index) (t1, i);
      size_t idx2 = FUNCTION (tensor, index) (t2, i);

      DATA (t1, idx1) /= CONST_DATA (t2, idx2);
    }
  
  return GSL_SUCCESS;  
}

#if !FP

int
FUNCTION (tensor, mod) (TYPE (tensor) * t1,
                        const TYPE (tensor) * t2)
{
#if GSL_RANGE_CHECK
  
  if (GSL_RANGE_COND(1))
    {
      if (!FUNCTION (tensor, match_size) (t1, t2))
        return GSL_EBADLEN;
    }

#endif  /* GSL_RANGE_CHECK */

  const size_t n = FUNCTION (tensor, tsize) (t1);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx1 = FUNCTION (tensor, index) (t1, i);
      size_t idx2 = FUNCTION (tensor, index) (t2, i);

      DATA (t1, idx1) %= CONST_DATA (t2, idx2);
    }
  
  return GSL_SUCCESS;  
}

#endif  /* !FP */

void
FUNCTION (tensor, scale_add) (TYPE (tensor) * t,
                              const ATOMIC s,
                              const ATOMIC a)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) *= s;
      DATA (t, idx) += a;
    }
}

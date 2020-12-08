/* tensor/trig_source.c
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


#if FP

/* Trigonometric operators */

void
FUNCTION (tensor, sin) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = SIN (DATA (t, idx));
    }
}

void
FUNCTION (tensor, cos) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = COS (DATA (t, idx));
    }
}

void
FUNCTION (tensor, tan) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = TAN (DATA (t, idx));
    }
}

/* Reciprocal trigonometric operators */

void
FUNCTION (tensor, sec) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = 1 / (COS (DATA (t, idx)));
    }
}

void
FUNCTION (tensor, csc) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = 1 / (SIN (DATA (t, idx)));
    }
}

void
FUNCTION (tensor, cot) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = 1 / (TAN (DATA (t, idx)));
    }
}

/* Inverse trigonometric operators */

void
FUNCTION (tensor, arcsin) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = ASIN (DATA (t, idx));
    }
}

void
FUNCTION (tensor, arccos) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = ACOS (DATA (t, idx));
    }
}

void
FUNCTION (tensor, arctan) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = ATAN (DATA (t, idx));
    }
}

TYPE (tensor) *
  FUNCTION (tensor,arctan2) (const TYPE (tensor) * y,
                             const TYPE (tensor) * x)
{
#if GSL_RANGE_CHECK
  
  if (GSL_RANGE_COND(1))
    {
      if (!FUNCTION (tensor, match_size) (y, x))
        return 0;
    }

#endif  /* GSL_RANGE_CHECK */

  const size_t n = FUNCTION (tensor, tsize) (y);

  if (n == 0)
    {
      GSL_ERROR_NULL ("arctan2 of empty tensors", GSL_EINVAL);
    }

  TYPE (tensor) * res =
    FUNCTION (tensor, aalloc) (y->dim, y->size);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx1 = FUNCTION (tensor, index) (y, i);
      size_t idx2 = FUNCTION (tensor, index) (x, i);
      size_t idx3 = FUNCTION (tensor, index) (res, i);

      DATA (res, idx3) = ATAN2 (CONST_DATA (y, idx1),
                                CONST_DATA (x, idx2));
    }

  return res;
}

/* Reciprocal inverse trigonometric operators */

void
FUNCTION (tensor, arcsec) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = ACOS (1 / DATA (t, idx));
    }
}

void
FUNCTION (tensor, arccsc) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = ASIN (1 / DATA (t, idx));
    }
}

void
FUNCTION (tensor, arccot) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = ATAN (1 / DATA (t, idx));
    }
}

/* Hyperbolic operators */

void
FUNCTION (tensor, sinh) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = SINH (DATA (t, idx));
    }
}

void
FUNCTION (tensor, cosh) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = COSH (DATA (t, idx));
    }
}

void
FUNCTION (tensor, tanh) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = TANH (DATA (t, idx));
    }
}

/* Reciprocal hyperbolic operators */

void
FUNCTION (tensor, sech) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = 1 / (COSH (DATA (t, idx)));
    }
}

void
FUNCTION (tensor, csch) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = 1 / (SINH (DATA (t, idx)));
    }
}

void
FUNCTION (tensor, coth) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = 1 / (TANH (DATA (t, idx)));
    }
}

/* Inverse hyperbolic operators */

void
FUNCTION (tensor, arcsinh) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = ASINH (DATA (t, idx));
    }
}

void
FUNCTION (tensor, arccosh) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = ACOSH (DATA (t, idx));
    }
}

void
FUNCTION (tensor, arctanh) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);
      
      DATA (t, idx) = ATANH (DATA (t, idx));
    }
}

/* Reciprocal inverse hyperbolic operators */

void
FUNCTION (tensor, arcsech) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = ACOSH (1 / DATA (t, idx));
    }
}  

void
FUNCTION (tensor, arccsch) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = ASINH (1 / DATA (t, idx));
    }
}  

void
FUNCTION (tensor, arccoth) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = ATANH (1 / DATA (t, idx));
    }
}  

#endif  /* FP */

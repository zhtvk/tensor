/* tensor/logical_source.c
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


void
FUNCTION (tensor, not) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = !(DATA (t, idx));
    }
}

#if FP

tensor_int *
FUNCTION (tensor, fcmp) (const TYPE (tensor) * t1,
                         const TYPE (tensor) * t2,
                         const ATOMIC eps)
{
  /* Approximately compare to float tensor elementwise */

#if GSL_RANGE_CHECK
  
  if (GSL_RANGE_COND(1))
    {
      if (!FUNCTION (tensor, match_tsize) (t1, t2))
        return 0;
    }

#endif  /* GSL_RANGE_CHECK */

  const size_t n = FUNCTION (tensor, tsize) (t1);

  if (n == 0)
    {
      GSL_ERROR_NULL ("fcmp of empty tensors", GSL_EINVAL);
    }

  int exponent;
  ATOMIC max, delta, diff;

  tensor_int * res = tensor_int_aalloc (t1->dim, t1->size);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx1 = FUNCTION (tensor, index) (t1, i);
      size_t idx2 = FUNCTION (tensor, index) (t2, i);
      size_t idx3 = tensor_int_index (res, i);

      /* Find the exponent of the largest absolute value */

      max = (ABS (CONST_DATA (t1, idx1)) >
             ABS (CONST_DATA (t2, idx2))) ?
        CONST_DATA (t1, idx1) : CONST_DATA (t2, idx2);

      FREXP (max, &exponent);

      /* Calculate delta and compare with difference */

      delta = LDEXP (eps, exponent);

      diff = CONST_DATA (t1, idx1) - CONST_DATA (t2, idx2);

      if (diff > delta)
        res->data[idx3] = 1;
      else if (diff < -delta)
        res->data[idx3] = -1;
      else
        res->data[idx3] = 0;
    }

  return res;
}

#endif  /* FP */

#if FP

tensor_int *
FUNCTION (tensor, fcmpc) (const TYPE (tensor) * t,
                          const ATOMIC x, const ATOMIC eps)
{
  /* Approximately compare float tensor elements to a constant x */

  const size_t n = FUNCTION (tensor, tsize) (t);

  if (n == 0)
    {
      GSL_ERROR_NULL ("fcmpc of an empty tensor", GSL_EINVAL);
    }

  int exponent;
  ATOMIC max, delta, diff;

  tensor_int * res = tensor_int_aalloc (t->dim, t->size);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx1 = FUNCTION (tensor, index) (t, i);
      size_t idx2 = tensor_int_index (res, i);

      /* Find the exponent of the largest absolute value */

      max = (ABS (CONST_DATA (t, idx1)) > ABS (x)) ?
        CONST_DATA (t, idx1) : x;

      FREXP (max, &exponent);

      /* Calculate delta and compare with difference */

      delta = LDEXP (eps, exponent);

      diff = CONST_DATA (t, idx1) - x;

      if (diff > delta)
        {
          res->data[idx2] = 1;
        }
      else if (diff < -delta)
        {
          res->data[idx2] = -1;
        }
      else
        {
          res->data[idx2] = 0;
        }
    }

  return res;
}

#endif  /* FP */

tensor_int *
FUNCTION (tensor, cmp) (const TYPE (tensor) * t1,
                        const TYPE (tensor) * t2)
{
  
#if GSL_RANGE_CHECK
  
  if (GSL_RANGE_COND(1))
    {
      if (!FUNCTION (tensor, match_size) (t1, t2))
        return 0;
    }

#endif  /* GSL_RANGE_CHECK */

  const size_t n = FUNCTION (tensor, tsize) (t1);

  if (n == 0)
    {
      GSL_ERROR_NULL ("cmp of empty tensors", GSL_EINVAL);
    }

  tensor_int * res = tensor_int_aalloc (t1->dim, t1->size);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx1 = FUNCTION (tensor, index) (t1, i);
      size_t idx2 = FUNCTION (tensor, index) (t2, i);
      size_t idx3 = tensor_int_index (res, i);

      if (CONST_DATA (t1, idx1) == CONST_DATA (t2, idx2))
        {
          res->data[idx3] = 0;
        }
      else if (CONST_DATA (t1, idx1) < CONST_DATA (t2, idx2))
        {
          res->data[idx3] = -1;
        }
      else
        {
          res->data[idx3] = 1;
        }
    }

  return res;
}

tensor_int *
FUNCTION (tensor, cmpc) (const TYPE (tensor) * t,
                         const ATOMIC x)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  if (n == 0)
    {
      GSL_ERROR_NULL ("cmpc of an empty tensor", GSL_EINVAL);
    }

  tensor_int * res = tensor_int_aalloc (t->dim, t->size);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx1 = FUNCTION (tensor, index) (t, i);
      size_t idx2 = tensor_int_index (res, i);

      if (CONST_DATA (t, idx1) == x)
        {
          res->data[idx2] = 0;
        }
      else if (CONST_DATA (t, idx1) < x)
        {
          res->data[idx2] = -1;
        }
      else
        {
          res->data[idx2] = 1;
        }
    }

  return res;  
}

tensor_int *
FUNCTION (tensor, and) (const TYPE (tensor) * t1,
                        const TYPE (tensor) * t2)
{
  
#if GSL_RANGE_CHECK
  
  if (GSL_RANGE_COND(1))
    {
      if (!FUNCTION (tensor, match_size) (t1, t2))
        return 0;
    }

#endif  /* GSL_RANGE_CHECK */

  const size_t n = FUNCTION (tensor, tsize) (t1);

  if (n == 0)
    {
      GSL_ERROR_NULL ("logical and of empty tensors", GSL_EINVAL);
    }

  tensor_int * res = tensor_int_aalloc (t1->dim, t1->size);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx1 = FUNCTION (tensor, index) (t1, i);
      size_t idx2 = FUNCTION (tensor, index) (t2, i);
      size_t idx3 = tensor_int_index (res, i);

      res->data[idx3] = CONST_DATA (t1, idx1) && CONST_DATA (t2, idx2);
    }

  return res;
}

tensor_int *
FUNCTION (tensor, or) (const TYPE (tensor) * t1,
                       const TYPE (tensor) * t2)
{
  
#if GSL_RANGE_CHECK
  
  if (GSL_RANGE_COND(1))
    {
      if (!FUNCTION (tensor, match_size) (t1, t2))
        return 0;
    }

#endif  /* GSL_RANGE_CHECK */

  const size_t n = FUNCTION (tensor, tsize) (t1);

  if (n == 0)
    {
      GSL_ERROR_NULL ("logical or of empty tensors", GSL_EINVAL);
    }

  tensor_int * res = tensor_int_aalloc (t1->dim, t1->size);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx1 = FUNCTION (tensor, index) (t1, i);
      size_t idx2 = FUNCTION (tensor, index) (t2, i);
      size_t idx3 = tensor_int_index (res, i);

      res->data[idx3] = CONST_DATA (t1, idx1) || CONST_DATA (t2, idx2);
    }

  return res;
}

tensor_int *
FUNCTION (tensor, xor) (const TYPE (tensor) * t1,
                        const TYPE (tensor) * t2)
{
  
#if GSL_RANGE_CHECK
  
  if (GSL_RANGE_COND(1))
    {
      if (!FUNCTION (tensor, match_size) (t1, t2))
        return 0;
    }

#endif  /* GSL_RANGE_CHECK */

  const size_t n = FUNCTION (tensor, tsize) (t1);

  if (n == 0)
    {
      GSL_ERROR_NULL ("logical xor of empty tensors", GSL_EINVAL);
    }

  tensor_int * res = tensor_int_aalloc (t1->dim, t1->size);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx1 = FUNCTION (tensor, index) (t1, i);
      size_t idx2 = FUNCTION (tensor, index) (t2, i);
      size_t idx3 = tensor_int_index (res, i);

      res->data[idx3] =
        (CONST_DATA (t1, idx1) && !CONST_DATA (t2, idx2)) ||
        (!CONST_DATA (t1, idx1) && CONST_DATA (t2, idx2));
    }

  return res;
}

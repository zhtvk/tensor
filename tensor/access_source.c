/* tensor/access_source.c
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

BASE
FUNCTION (tensor, get) (const TYPE (tensor) * t, ...)
{
  va_list argp1, argp2;

#ifdef va_copy
  va_copy (argp2, argp1);
#else
  argp2 = argp1;
#endif  /* va_copy */
  
#if GSL_RANGE_CHECK
  if (GSL_RANGE_COND(1)) 
    {      
      va_start (argp1, t);
      
      if (!FUNCTION (tensor, vfits_size) (t, argp1))
        {
          const BASE zero = ZERO;
          return zero;
        }

      va_end (argp1);
    }
#endif  /* GSL_RANGE_CHECK */

  va_start (argp2, t);

  size_t d, loc = 0;
  for (d = 0; d < t->dim; ++d)
    {
      loc += (va_arg (argp2, size_t) * t->stride[d]);
    }

  va_end (argp2);

  return *(BASE *) (t->data + MULTIPLICITY * loc);
}

BASE *
FUNCTION (tensor, ptr) (TYPE (tensor) * t, ...)
{
  va_list argp1, argp2;

#ifdef va_copy
  va_copy (argp2, argp1);
#else
  argp2 = argp1;
#endif  /* va_copy */
  
#if GSL_RANGE_CHECK
  if (GSL_RANGE_COND(1)) 
    {      
      va_start (argp1, t);
      
      if (!FUNCTION (tensor, vfits_size) (t, argp1))
        return 0;

      va_end (argp1);
    }
#endif  /* GSL_RANGE_CHECK */

  va_start (argp2, t);

  size_t d, loc = 0;
  for (d = 0; d < t->dim; ++d)
    {
      loc += (va_arg (argp2, size_t) * t->stride[d]);
    }

  va_end (argp2);

  return (BASE *) (t->data + MULTIPLICITY * loc);
}

const BASE *
FUNCTION (tensor, const_ptr) (const TYPE (tensor) * t, ...)
{
  va_list argp1, argp2;

#ifdef va_copy
  va_copy (argp2, argp1);
#else
  argp2 = argp1;
#endif  /* va_copy */
  
#if GSL_RANGE_CHECK
  if (GSL_RANGE_COND(1)) 
    {      
      va_start (argp1, t);

      if (!FUNCTION (tensor, vfits_size) (t, argp1))
        return 0;

      va_end (argp1);
    }
#endif  /* GSL_RANGE_CHECK */

  va_start (argp2, t);

  size_t d, loc = 0;
  for (d = 0; d < t->dim; ++d)
    {
      loc += (va_arg (argp2, size_t) * t->stride[d]);
    }

  va_end (argp2);

  return (const BASE *) (t->data + MULTIPLICITY * loc);
}

size_t
FUNCTION (tensor, index) (const TYPE (tensor) * t, const size_t i)
{
  /* Return the index of the i-th consecutive element of tensor t taking
     into account strides, such that t->data[index] gives the value of
     the i-th element of t. */

#if GSL_RANGE_CHECK
  if (GSL_RANGE_COND(1))
    {
      const size_t n = FUNCTION (tensor, tsize) (t);
      if (i >= n)
        {
          char reason[1000];
          sprintf(reason,
                  "index %zu out of range for "
                  "tensor of total size %zu",
                  i, n);
          GSL_ERROR_NULL(reason, GSL_EINVAL);
        }
    }
#endif  /* GSL_RANGE_CHECK */

  size_t idx[t->dim];

  size_t d, index = 0, ctg_stride = 1;
  for (d = 0; d < t->dim; ++d)
    {
      idx[t->dim - d - 1] =
        (i / ctg_stride) %
        t->size[t->dim - d - 1];
      
      index += idx[t->dim - d - 1] * t->stride[t->dim - d - 1];

      ctg_stride *= t->size[t->dim - d - 1];
    }

  index *= MULTIPLICITY;

  return index;
}

void
FUNCTION (tensor, set) (TYPE (tensor) * t, const BASE x, ...)
{
  va_list argp1, argp2;

#ifdef va_copy
  va_copy (argp2, argp1);
#else
  argp2 = argp1;
#endif  /* va_copy */
  
#if GSL_RANGE_CHECK
  if (GSL_RANGE_COND(1)) 
    {      
      va_start (argp1, x);
      
      if (!FUNCTION (tensor, vfits_size) (t, argp1))
        return;

      va_end (argp1);
    }
#endif  /* GSL_RANGE_CHECK */

  va_start (argp2, x);

  size_t d, loc = 0;
  for (d = 0; d < t->dim; ++d)
    {
      loc += (va_arg (argp2, size_t) * t->stride[d]);
    }

  va_end (argp2);

  *(BASE *) (t->data + MULTIPLICITY * loc) = x;
}

void
FUNCTION (tensor, set_zero) (TYPE (tensor) * t)
{
  const BASE zero = ZERO; 
  FUNCTION (tensor, set_all) (t, zero);
}

void
FUNCTION (tensor, set_one) (TYPE (tensor) * t)
{
  const BASE one = ONE;
  FUNCTION (tensor, set_all) (t, one);
}

void
FUNCTION (tensor, set_all) (TYPE (tensor) * t, const BASE x)
{
  const size_t n = FUNCTION (tensor, tsize) (t);
  
  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      *(BASE *) (t->data + idx) = x; 
    }  
}

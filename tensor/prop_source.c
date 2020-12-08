/* tensor/prop_source.c
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

int
FUNCTION (tensor, vfits_size) (const TYPE (tensor) * t, va_list argp)
{
  if (t->dim == 0)
    {
      GSL_ERROR_NULL("cannot index tensor of dim 0", GSL_EINVAL);
    }
  
  size_t d, idx;
  for (d = 0; d < t->dim; ++d)
    {
      idx = va_arg (argp, size_t);
      if (idx >= t->size[d])
        {
          char reason[1000];
          sprintf(reason,
                  "index %zu out of range for "
                  "tensor dim %zu of size %zu",
                  idx, d, t->size[d]);
          GSL_ERROR_NULL(reason, GSL_EINVAL);
        }
    }

  return 1;
}

int
FUNCTION (tensor, fits_size) (const TYPE (tensor) * t, ...)
{
  va_list argp;

  va_start (argp, t);

  int result;
  result = FUNCTION (tensor, vfits_size) (t, argp);

  va_end (argp);

  return result;
}

int
FUNCTION (tensor, match_size) (const TYPE (tensor) * t1,
                               const TYPE (tensor) * t2)
{
  if (t1->dim != t2->dim)
    {
      char reason[1000];
      sprintf(reason, "first tensor dim %zu doesn't "
              "match second tensor dim %zu",
              t1->dim, t2->dim);
      GSL_ERROR_NULL (reason, GSL_EBADLEN);
    }

  size_t d;
  for (d = 0; d < t1->dim; ++d)
    {
      if (t1->size[d] != t2->size[d])
        {
          char reason[1000];
          sprintf(reason, "first tensor size %zu doesn't "
                  "match second tensor size %zu at dim %zu",
                  t1->dim, t2->dim, d);
          GSL_ERROR_NULL (reason, GSL_EBADLEN);
        }
    }

  return 1;
}

int
FUNCTION (tensor, match_tsize) (const TYPE (tensor) * t1,
                                const TYPE (tensor) * t2)
{
  size_t n1 = FUNCTION (tensor, tsize) (t1);
  size_t n2 = FUNCTION (tensor, tsize) (t2);

  if (n1 != n2)
    {
      char reason[1000];
      sprintf(reason, "first tensor total size %zu doesn't "
              "match second tensor total size %zu", n1, n2);

      GSL_ERROR_NULL (reason, GSL_EBADLEN);      
    }

  return 1;
}

int
FUNCTION (tensor, is_null) (const TYPE (tensor) * t)
{
  size_t i, m, idx;
  for (i = 0; i < FUNCTION (tensor, tsize) (t); ++i)
    {
      idx = FUNCTION (tensor, index) (t, i);
      
      for (m = 0; m < MULTIPLICITY; ++m)
        {
          if (t->data[idx + m] != 0.0)
            return 0;
        }
    }

  return 1;
}

int
FUNCTION (tensor, is_pos) (const TYPE (tensor) * t)
{
  size_t i, m, idx;
  for (i = 0; i < FUNCTION (tensor, tsize) (t); ++i)
    {
      idx = FUNCTION (tensor, index) (t, i);
      
      for (m = 0; m < MULTIPLICITY; ++m)
        {
          if (t->data[idx + m] <= 0.0)
            return 0;
        }
    }

  return 1;
}

int
FUNCTION (tensor, is_neg) (const TYPE (tensor) * t)
{
  size_t i, m, idx;
  for (i = 0; i < FUNCTION (tensor, tsize) (t); ++i)
    {
      idx = FUNCTION (tensor, index) (t, i);
      
      for (m = 0; m < MULTIPLICITY; ++m)
        {
          if (t->data[idx + m] >= 0.0)
            return 0;
        }
    }

  return 1;
}

int
FUNCTION (tensor, is_nonneg) (const TYPE (tensor) * t)
{
  size_t i, m, idx;
  for (i = 0; i < FUNCTION (tensor, tsize) (t); ++i)
    {
      idx = FUNCTION (tensor, index) (t, i);
      
      for (m = 0; m < MULTIPLICITY; ++m)
        {
          if (t->data[idx + m] < 0.0)
            return 0;
        }
    }

  return 1;
}

int
FUNCTION (tensor, is_nonpos) (const TYPE (tensor) * t)
{
  size_t i, m, idx;
  for (i = 0; i < FUNCTION (tensor, tsize) (t); ++i)
    {
      idx = FUNCTION (tensor, index) (t, i);
      
      for (m = 0; m < MULTIPLICITY; ++m)
        {
          if (t->data[idx + m] > 0.0)
            return 0;
        }
    }

  return 1;
}

int
FUNCTION (tensor, equal) (const TYPE (tensor) * t1,
                          const TYPE (tensor) * t2)
{
#if GSL_RANGE_CHECK
  
  if (GSL_RANGE_COND(1))
    {
      if (!FUNCTION (tensor, match_size) (t1, t2))
        return GSL_EBADLEN;
    }

#endif  /* GSL_RANGE_CHECK */

  size_t n1;
  n1 = FUNCTION (tensor, tsize) (t1);

  size_t i, m, idx1, idx2;
  for (i = 0; i < n1; ++i)
    {
      idx1 = FUNCTION (tensor, index) (t1, i);
      idx2 = FUNCTION (tensor, index) (t2, i);
      
      for (m = 0; m < MULTIPLICITY; ++m)
        {
          if (t1->data[idx1 + m] != t2->data[idx2 + m])
            return 0;
        }
    }

  return 1;
}

int
FUNCTION (tensor, is_same) (const TYPE (tensor) * t)
{
  size_t i, m, idx;
  for (i = 0; i < FUNCTION (tensor, tsize) (t); ++i)
    {
      idx = FUNCTION (tensor, index) (t, i);
      
      for (m = 0; m < MULTIPLICITY; ++m)
        {
          if (t->data[idx + m] != t->data[m])
            return 0;
        }
    }

  return 1;
}

int
FUNCTION (tensor, is_const) (const TYPE (tensor) * t,
                             const BASE c)
{
  if (t->dim == 0)
    return 0;

  const BASE x = *(BASE *) (t->data);

  int res = 0;
  
#if (defined(BASE_GSL_COMPLEX_LONG) || defined(BASE_GSL_COMPLEX) || defined(BASE_GSL_COMPLEX_FLOAT))

  if (GSL_COMPLEX_EQ (x, c))
    res = 1;
  
#else
  
  if (x == c)
    res = 1;
  
#endif  /* (defined(BASE_GSL_COMPLEX_LONG) ||
           defined(BASE_GSL_COMPLEX) ||
           defined(BASE_GSL_COMPLEX_FLOAT)) */

  res = res && FUNCTION (tensor, is_same) (t);

  return res;
}

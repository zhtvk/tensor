/* tensor/stat_source.c
 *
 * Copyright (C) 1996, 1997, 1998, 1999, 2000, 2007 Jim Davies, Brian
 * Gough
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


ATOMIC
FUNCTION (tensor, max) (const TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

#if GSL_RANGE_CHECK
  if (GSL_RANGE_COND(1))
    {
      if (n == 0)
        GSL_ERROR ("max of an empty tensor", GSL_EINVAL);
    }
#endif  /* GSL_RANGE_CHECK */
  
  ATOMIC max = t->data[0];

  size_t i;
  for (i = 0; i < n; ++i)
    {
      if (t->data[i] > max)
        max = t->data[i];
    }

  return max;
}

ATOMIC
FUNCTION (tensor, min) (const TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

#if GSL_RANGE_CHECK
  if (GSL_RANGE_COND(1))
    {
      if (n == 0)
        GSL_ERROR ("min of an empty tensor", GSL_EINVAL);
    }
#endif  /* GSL_RANGE_CHECK */
  
  ATOMIC min = t->data[0];

  size_t i;
  for (i = 0; i < n; ++i)
    {
      if (t->data[i] < min)
        min = t->data[i];
    }

  return min;
}

void
FUNCTION (tensor, minmax) (const TYPE (tensor) * t,
                           ATOMIC * min, ATOMIC * max)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

#if GSL_RANGE_CHECK
  if (GSL_RANGE_COND(1))
    {
      if (n == 0)
        GSL_ERROR_VOID ("minmax of an empty tensor", GSL_EINVAL);
    }
#endif  /* GSL_RANGE_CHECK */
  
  *min = t->data[0];
  *max = t->data[0];

  size_t i;
  for (i = 0; i < n; ++i)
    {
      if (t->data[i] < *min)
        *min = t->data[i];

      if (t->data[i] > *max)
        *max = t->data[i];
    }
}

size_t
FUNCTION (tensor, max_index) (const TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

#if GSL_RANGE_CHECK
  if (GSL_RANGE_COND(1))
    {
      if (n == 0)
        GSL_ERROR ("max_index of an empty tensor", GSL_EINVAL);
    }
#endif  /* GSL_RANGE_CHECK */

  ATOMIC max = t->data[0];
  size_t max_index = 0;

  size_t i;
  for (i = 0; i < n; ++i)
    {
      if (t->data[i] > max)
        {
          max = t->data[i];
          max_index = i;
        }
    }

  return max_index;
} 

size_t
FUNCTION (tensor, min_index) (const TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

#if GSL_RANGE_CHECK
  if (GSL_RANGE_COND(1))
    {
      if (n == 0)
        GSL_ERROR ("min_index of an empty tensor", GSL_EINVAL);
    }
#endif  /* GSL_RANGE_CHECK */
  
  ATOMIC min = t->data[0];
  size_t min_index = 0;

  size_t i;
  for (i = 0; i < n; ++i)
    {
      if (t->data[i] < min)
        {
          min = t->data[i];
          min_index = i;
        }
    }

  return min_index;
}

void
FUNCTION (tensor, minmax_index) (const TYPE (tensor) * t,
                                 size_t * min_index,
                                 size_t * max_index)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

#if GSL_RANGE_CHECK
  if (GSL_RANGE_COND(1))
    {
      if (n == 0)
        GSL_ERROR_VOID ("minmax_index of an empty tensor", GSL_EINVAL);
    }
#endif  /* GSL_RANGE_CHECK */
  
  ATOMIC min = t->data[0];
  ATOMIC max = t->data[0];
  *min_index = 0;
  *max_index = 0;

  size_t i;
  for (i = 0; i < n; ++i)
    {
      if (t->data[i] < min)
        {
          min = t->data[i];
          *min_index = i;
        }

      if (t->data[i] > max)
        {
          max = t->data[i];
          *max_index = i;
        }
    }
}

double
FUNCTION (tensor, sum) (const TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

#if GSL_RANGE_CHECK
  if (GSL_RANGE_COND(1))
    {
      if (n == 0)
        GSL_ERROR ("sum of an empty tensor", GSL_EINVAL);
    }
#endif  /* GSL_RANGE_CHECK */
  
  long double sum = 0;

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);
      
      sum += t->data[idx];
    }

  return (double) sum;
}

double
FUNCTION (tensor, prod) (const TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

#if GSL_RANGE_CHECK
  if (GSL_RANGE_COND(1))
    {
      if (n == 0)
        GSL_ERROR ("product of an empty tensor", GSL_EINVAL);
    }
#endif  /* GSL_RANGE_CHECK */
  
  long double prod = 1;

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);
      
      prod *= t->data[idx];
    }

  return (double) prod;
}

double
FUNCTION (tensor, mean) (const TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

#if GSL_RANGE_CHECK
  if (GSL_RANGE_COND(1))
    {
      if (n == 0)
        GSL_ERROR ("mean of an empty tensor", GSL_EINVAL);
    }
#endif  /* GSL_RANGE_CHECK */
  
  long double mean = 0;

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      /* Recurrence mean  */
      /* mu_n = mu_(n-1) + (x_n - mu_(n-1)) / (n + 1) */
      
      mean += ((long double) t->data[idx] - mean) / (i + 1);
    }

  return (double) mean;
}

double
FUNCTION (tensor, var) (const TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

#if GSL_RANGE_CHECK
  if (GSL_RANGE_COND(1))
    {
      if (n == 0)
        GSL_ERROR ("variance of an empty tensor", GSL_EINVAL);
    }
#endif  /* GSL_RANGE_CHECK */
  
  long double mean = FUNCTION (tensor, mean) (t);

  long double var = 0;
  
  long double diff_mean;
  
  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      /* Using recurrence for the average */
      diff_mean = t->data[idx] - mean;
      
      var += (diff_mean * diff_mean - var) / (i + 1);
    }

  return (double) var;
}

double
FUNCTION (tensor, std) (const TYPE (tensor) * t)
{
  double var = FUNCTION (tensor, var) (t);
  return sqrt (var);
}

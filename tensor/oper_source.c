/* tensor/oper_source.c
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


TYPE (tensor) *
FUNCTION (tensor, copy) (const TYPE (tensor) * t_in)
{
  if (t_in == 0)
    {
      GSL_ERROR_VAL ("cannot copy from null tensor",
                     GSL_ENOMEM, 0);
    }

  TYPE (tensor) * t_out;

  t_out = (TYPE (tensor) *) malloc (sizeof (TYPE (tensor)));

  if (t_out == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for tensor struct",
                     GSL_ENOMEM, 0);
    }

  t_out->dim = t_in->dim;

  t_out->size = (size_t *) malloc (sizeof (size_t) * t_out->dim);
  
  if (t_out->size == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for tensor sizes",
                     GSL_ENOMEM, 0);
    }

  memcpy(t_out->size, t_in->size, sizeof (size_t) * t_out->dim);

  t_out->stride = (size_t *) malloc (sizeof (size_t) * t_out->dim);

  if (t_out->stride == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for tensor strides",
                     GSL_ENOMEM, 0);
    }

  /* Recalculate strides */
  /* Output tensor will be contiguous after copying */
  /* Calculate total number of output tensor elements while there */
  size_t i, stride = 1, n = 1;
  for (i = 0; i < t_out->dim; ++i)
    {
      t_out->stride[t_out->dim - i - 1] = stride;
      stride *= t_out->size[t_out->dim - i - 1];

      n *= t_out->size[t_out->dim - i - 1];
    }

  TYPE (gsl_block) * block;
  block = FUNCTION (gsl_block, alloc) (n);

  if (block == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for block",
                     GSL_ENOMEM, 0);
    }

  t_out->data = block->data;
  t_out->block = block;
  t_out->owner = 1;

  /* Copy tensor elements such that the strides are accounted for  */
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t_in, i);

      *(BASE *) (t_out->data + MULTIPLICITY * i) =
        *(const BASE *) (t_in->data + idx);
    }

  return t_out;
}

int
FUNCTION (tensor, assign) (TYPE (tensor) * t1,
                           const TYPE (tensor) * t2)
{
#if GSL_RANGE_CHECK

  if (GSL_RANGE_COND(1))
    {
      if (!FUNCTION (tensor, match_tsize) (t1, t2))
        return GSL_EBADLEN;
    }

#endif  /* GSL_RANGE_CHECK */

  size_t n = FUNCTION (tensor, tsize) (t1);

  size_t i, idx1, idx2;
  for (i = 0; i < n; ++i)
    {
      idx1 = FUNCTION (tensor, index) (t1, i);
      idx2 = FUNCTION (tensor, index) (t2, i);

      DATA (t1, idx1) = CONST_DATA (t2, idx2);
    }

  return GSL_SUCCESS;
}

int
FUNCTION (tensor, swap) (TYPE (tensor) * t1,
                         TYPE (tensor) * t2)
{
#if GSL_RANGE_CHECK

  if (GSL_RANGE_COND(1))
    {
      if (!FUNCTION (tensor, match_tsize) (t1, t2))
        return GSL_EBADLEN;
    }

#endif  /* GSL_RANGE_CHECK */

  size_t n = FUNCTION (tensor, tsize) (t1);

  BASE x;
  size_t i, idx1, idx2;
  for (i = 0; i < n; ++i)
    {
      idx1 = FUNCTION (tensor, index) (t1, i);
      idx2 = FUNCTION (tensor, index) (t2, i);

      x = DATA (t1, idx1);
      DATA (t1, idx1) = DATA (t2, idx2);
      DATA (t2, idx2) = x;
    }

  return GSL_SUCCESS;
}

void
FUNCTION (tensor, adjoin) (TYPE (tensor) * t)
{
  if (FUNCTION (tensor, is_contiguous) (t))
    return;

  TYPE (tensor) * u;

  u = FUNCTION (tensor, copy) (t);

  /* Move u to t */

  if (t->owner)
    {
      FUNCTION (gsl_block, free) (t->block);
    }

  free (t->size);
  free (t->stride);

  t->dim = u->dim;
  t->size = u->size;
  t->stride = u->stride;
  t->data = u->data;
  t->block = u->block;
  t->owner = u->owner;

  free (u);
}

int
FUNCTION (tensor, morph) (TYPE (tensor) * t, ...)
{
  va_list argp;

  va_start (argp, t);

  size_t size[t->dim];

  size_t i, new_tsize = 1;
  for (i = 0; i < t->dim; ++i)
    {
      size[i] = va_arg(argp, size_t);
      new_tsize *= size[i];
    }

  va_end (argp);

  size_t n = FUNCTION (tensor, tsize) (t);

#if GSL_RANGE_CHECK

  if (GSL_RANGE_COND(1))
    {
      if (new_tsize != n)
        {
          char reason[1000];
          sprintf(reason,
                  "morph total size %zu does not"
                  "equal tensor total size %zu",
                  new_tsize, n);
          GSL_ERROR (reason, GSL_EINVAL);
        }
    }

#endif  /* GSL_RANGE_CHECK */

  /* Adjoin tensor */

  FUNCTION (tensor, adjoin) (t);

  /* Adjust size and stride */

  size_t stride = 1;
  for (i = 0; i < t->dim; ++i)
    {
      t->stride[t->dim - i - 1] = stride;

      t->size[t->dim - i - 1] = size[t->dim - i - 1];

      stride *= t->size[t->dim - i - 1];
    }

  return GSL_SUCCESS;
}

void
FUNCTION (tensor, deflate) (TYPE (tensor) * t)
{
  size_t new_dim = t->dim;
  size_t new_size[t->dim];
  size_t new_stride[t->dim];

  size_t i, j = 0;
  for (i = 0; i < t->dim; ++i)
    {
      if (t->size[i] == 1)
        {
          --new_dim;
        }
      else
        {
          new_size[j] = t->size[i];
          new_stride[j] = t->stride[i];
          ++j;
        }
    }

  /* Change dim, sizes, and strides */

  t->dim = new_dim;

  t->size = (size_t *) realloc (t->size, sizeof (size_t) * t->dim);
  memcpy (t->size, new_size, sizeof (size_t) * t->dim);

  t->stride = (size_t *) realloc (t->stride, sizeof (size_t) * t->dim);
  memcpy (t->stride, new_stride, sizeof (size_t) * t->dim);
}

int
FUNCTION (tensor, inflate) (TYPE (tensor) * t, const size_t didx)
{
#if GSL_RANGE_CHECK

  if (GSL_RANGE_COND(1))
    {
      if (didx > t->dim)
        {
          char reason[1000];
          sprintf(reason,
                  "inflate dimension index %zu out of "
                  "range for tensor with dim %zu + 1",
                  didx, t->dim);
          GSL_ERROR (reason, GSL_EINVAL);
        }
    }

#endif  /* GSL_RANGE_CHECK */

  size_t new_size[t->dim + 1];
  size_t new_stride[t->dim + 1];

  size_t i, j = t->dim - 1;
  for (i = 0; i <= t->dim; ++i)
    {
      if (i == 0 && t->dim - i == didx)
        {
          new_size[t->dim - i] = 1;
          new_stride[t->dim - i] = 1;
        }
      else if (t->dim - i == didx)
        {
          new_size[t->dim - i] = 1;
          new_stride[t->dim - i] =
            new_size[t->dim - i + 1] * new_stride[t->dim - i + 1];
        }
      else
        {
          new_size[t->dim - i] = t->size[j];
          new_stride[t->dim - i] = t->stride[j];
          --j;
        }
    }

  ++(t->dim);

  t->size = (size_t *) realloc (t->size, sizeof (size_t) * t->dim);
  memcpy (t->size, new_size, sizeof (size_t) * t->dim);

  t->stride = (size_t *) realloc (t->stride, sizeof (size_t) * t->dim);
  memcpy (t->stride, new_stride, sizeof (size_t) * t->dim);

  return GSL_SUCCESS;
}

TYPE (tensor) *
FUNCTION (tensor, concat) (const size_t didx, const size_t n, ...)
{
  va_list argp;

  va_start (argp, n);

  const TYPE (tensor) * t[n];

  size_t i;
  for (i = 0; i < n; ++i)
    {
      t[i] = va_arg (argp, const TYPE (tensor) *);
    }

  va_end (argp);

#if GSL_RANGE_CHECK

  if (GSL_RANGE_COND(1))
    {
      if (n < 2)
        {
          GSL_ERROR_NULL("concat number of tensor "
                         "operands is less than two",
                         GSL_EINVAL);
        }

      for (i = 0; i < n; ++i)
        {
          if (t[i]->dim != t[0]->dim)
            {
              char reason[1000];
              sprintf(reason,
                      "concat tensor %zu dim %zu do "
                      "not match first tensor dim %zu ",
                      i, t[i]->dim, t[0]->dim);
              GSL_ERROR_NULL(reason, GSL_EINVAL);
            }
        }

      for (i = 0; i < n; ++i)
        {
          if (didx > t[i]->dim)
            {
              char reason[1000];
              sprintf(reason,
                      "concat dimension index %zu out of "
                      "range for tensor %zu with dim %zu",
                      didx, i, t[i]->dim);
              GSL_ERROR_NULL(reason, GSL_EINVAL);
            }
        }

      size_t j;
      for (i = 0; i < n; ++i)
        {
          for (j = 0; j < t[i]->dim; ++j)
            {
              if (j != didx)
                {
                  if (t[i]->size[j] != t[0]->size[j])
                    {
                      char reason[1000];
                      sprintf(reason,
                              "concat tensor %zu size %zu does "
                              "not match first tensor size %zu at "
                              "dimension index %zu",
                              i, t[i]->size[j], t[0]->size[j], j);
                      GSL_ERROR_NULL(reason, GSL_EINVAL);
                    }
                }
              else
                continue;
            }
        }
    }

#endif  /* GSL_RANGE_CHECK */

  size_t new_size[t[0]->dim];
  memcpy (new_size, t[0]->size, sizeof (size_t) * t[0]->dim);
  for (i = 1; i < n; ++i)
    new_size[didx] += t[i]->size[didx];

  TYPE (tensor) * res;
  res = FUNCTION (tensor, aalloc) (t[0]->dim, new_size);

  size_t range[res->dim * 3];
  for (i = 0; i < res->dim; ++i)
    {
      range[i * 3] = 0;
      range[i * 3 + 1] = res->size[i];
      range[i * 3 + 2] = 1;
    }

  TYPE (tensor) * view;

  size_t offset = 0;
  for (i = 0; i < n; ++i)
    {
      range[didx * 3] = offset;
      range[didx * 3 + 1] = t[i]->size[didx];

      view = FUNCTION (tensor, aview) (res, range);

      FUNCTION (tensor, assign) (view, t[i]);

      FUNCTION (tensor, free) (view);

      offset += t[i]->size[didx];
    }

  return res;
}

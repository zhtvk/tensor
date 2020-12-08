/* tensor/init_source.c
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

TYPE (tensor) *
FUNCTION (tensor, valloc) (const size_t dim, va_list argp)
{
  TYPE (tensor) * t;

  t = (TYPE (tensor) *) malloc (sizeof (TYPE (tensor)));

  if (t == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for tensor struct",
                     GSL_ENOMEM, 0);
    }

  t->dim = dim;

  t->size = (size_t *) malloc (sizeof (size_t) * dim);

  if (t->size == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for tensor sizes",
                     GSL_ENOMEM, 0);
    }

  t->stride = (size_t *) malloc (sizeof (size_t) * dim);

  if (t->stride == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for tensor strides",
                     GSL_ENOMEM, 0);
    }

  size_t i;
  for (i = 0; i < dim; ++i)
    {
      t->size[i] = va_arg (argp, size_t);

      /* Check for dim of zero size */
      if (t->size[i] == 0)
        {
          /* Free partial tensor */
          free (t->size);
          free (t->stride);
          free (t);
          /* Produce an error */
          char reason[1000];
          sprintf(reason, "failed to allocate tensor with "
                  "invalid size 0 for dim %zu", i);
          GSL_ERROR_NULL(reason, GSL_EINVAL);
        }
    }

  /* Overflow for stride and n for large dimensions? */
  size_t stride = 1, n = 1;
  for (i = 0; i < dim; ++i)
    {
      t->stride[dim - i - 1] = stride;
      stride *= t->size[dim - i - 1];

      n *= t->size[dim - i - 1];
    }

  /* Zero-dim tensor */
  if (t->dim == 0)
    n = 0;

  TYPE (gsl_block) * block;
  block = FUNCTION (gsl_block, alloc) (n);

  if (block == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for block",
                     GSL_ENOMEM, 0);
    }

  t->data = block->data;
  t->block = block;
  t->owner = 1;

  return t;
}

TYPE (tensor) *
FUNCTION (tensor, alloc) (const size_t dim, ...)
{
  va_list argp;
  
  va_start (argp, dim);

  TYPE (tensor) * t;
  
  t = FUNCTION (tensor, valloc) (dim, argp);

  va_end (argp);

  return t;
}

TYPE (tensor) *
FUNCTION (tensor, aalloc) (const size_t dim, const size_t * size)
{
  TYPE (tensor) * t;

  t = (TYPE (tensor) *) malloc (sizeof (TYPE (tensor)));

  if (t == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for tensor struct",
                     GSL_ENOMEM, 0);
    }

  t->dim = dim;

  t->size = (size_t *) malloc (sizeof (size_t) * dim);

  if (t->size == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for tensor sizes",
                     GSL_ENOMEM, 0);
    }

  t->stride = (size_t *) malloc (sizeof (size_t) * dim);

  if (t->stride == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for tensor strides",
                     GSL_ENOMEM, 0);
    }

  size_t i;
  for (i = 0; i < dim; ++i)
    {
      t->size[i] = size[i];

      /* Check for dim of zero size */
      if (t->size[i] == 0)
        {
          /* Free partial tensor */
          free (t->size);
          free (t->stride);
          free (t);
          /* Produce an error */
          char reason[1000];
          sprintf(reason, "failed to allocate tensor with "
                  "invalid size 0 for dim %zu", i);
          GSL_ERROR_NULL(reason, GSL_EINVAL);
        }
    }

  /* Overflow for stride and n for large dimensions? */
  size_t stride = 1, n = 1;
  for (i = 0; i < dim; ++i)
    {
      t->stride[dim - i - 1] = stride;
      stride *= t->size[dim - i - 1];

      n *= t->size[dim - i - 1];
    }

  /* Zero-dim tensor */
  if (t->dim == 0)
    n = 0;

  TYPE (gsl_block) * block;
  block = FUNCTION (gsl_block, alloc) (n);

  if (block == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for block",
                     GSL_ENOMEM, 0);
    }

  t->data = block->data;
  t->block = block;
  t->owner = 1;

  return t;
}

TYPE (tensor) *
FUNCTION (tensor, calloc) (const size_t dim, ...)
{
  va_list argp;
  
  va_start (argp, dim);

  TYPE (tensor) * t;
  
  t = FUNCTION (tensor, valloc) (dim, argp);

  va_end (argp);

  if (t == 0)
    return 0;

  /* Set tensor elements to zero */
  const BASE zero = ZERO;
  size_t i;
  const size_t n = FUNCTION (tensor, tsize) (t);
  for (i = 0; i < n; ++i)
    *(BASE *) (t->data + MULTIPLICITY * i) = zero;

  return t;
}

void
FUNCTION (tensor, free) (TYPE (tensor) * t)
{
  RETURN_IF_NULL (t);

  if (t->owner)
    {
      FUNCTION (gsl_block, free) (t->block);
    }

  free (t->size);
  free (t->stride);
  free (t);
}

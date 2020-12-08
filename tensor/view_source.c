/* tensor/view_source.c
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

#include "view.h"

QUALIFIED_TYPE (tensor) *
  FUNCTION (tensor, view) (QUALIFIED_TYPE (tensor) * t, ...)
{
  va_list argp;

  va_start (argp, t);

  /* Triplets of offset, size, step for each dim */
  size_t d;
  size_t offset[t->dim];
  size_t size[t->dim];
  size_t step[t->dim];
  for (d = 0; d < t->dim; ++d)
    {
      offset[d] = va_arg (argp, size_t);
      size[d] = va_arg (argp, size_t);
      step[d] = va_arg (argp, size_t);
    }

  va_end (argp);
       
#if GSL_RANGE_CHECK
  if (GSL_RANGE_COND(1))
    {
      for (d = 0; d < t->dim; ++d)
        {
          if (size[d] == 0 || step[d] == 0 ||
              offset[d] >= t->size[d] ||
              offset[d] + size[d] > t->size[d])
            {
              char reason[1000];
              sprintf(reason,
                      "view index range (%zu, %zu, %zu) "
                      "invalid for tensor dim %zu of size %zu",
                      offset[d], offset[d] + size[d],
                      step[d], d, t->size[d]);
              GSL_ERROR_NULL(reason, GSL_EINVAL);
            }
        }
    }
#endif  /* GSL_RANGE_CHECK */
  
  TYPE (tensor) * v;
  
  v = (TYPE (tensor) *) malloc (sizeof (TYPE (tensor)));

  if (v == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for view struct",
                     GSL_ENOMEM, 0);
    }

  v->dim = t->dim;

  v->size = (size_t *) malloc (sizeof (size_t) * v->dim);

  if (v->size == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for view sizes",
                     GSL_ENOMEM, 0);
    }

  memcpy(v->size, size, sizeof (size_t) * v->dim);

  v->stride = (size_t *) malloc (sizeof (size_t) * v->dim);

  if (v->stride == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for view strides",
                     GSL_ENOMEM, 0);
    }

  /* Calculate strides and offset index*/
  size_t oidx = 0;
  for (d = 0; d < t->dim; ++d)
    {
      v->stride[d] = t->stride[d] * step[d];

      oidx += offset[d] * t->stride[d];
    }

  oidx *= MULTIPLICITY;

  v->data = t->data + oidx;
  v->block = 0;
  v->owner = 0;

  return (QUALIFIED_TYPE (tensor) *) v;
}

QUALIFIED_TYPE (tensor) *
  FUNCTION (tensor, aview) (QUALIFIED_TYPE (tensor) * t,
                            const size_t * range)
{
  /* Triplets of offset, size, step for each dim */
  size_t d;
  size_t offset[t->dim];
  size_t size[t->dim];
  size_t step[t->dim];
  for (d = 0; d < t->dim; ++d)
    {
      offset[d] = range[d * 3];
      size[d] = range[d * 3 + 1];
      step[d] = range[d * 3 + 2];
    }
       
#if GSL_RANGE_CHECK
  if (GSL_RANGE_COND(1))
    {
      for (d = 0; d < t->dim; ++d)
        {
          if (size[d] == 0 || step[d] == 0 ||
              offset[d] >= t->size[d] ||
              offset[d] + size[d] > t->size[d])
            {
              char reason[1000];
              sprintf(reason,
                      "view index range (%zu, %zu, %zu) "
                      "invalid for tensor dim %zu of size %zu",
                      offset[d], offset[d] + size[d],
                      step[d], d, t->size[d]);
              GSL_ERROR_NULL(reason, GSL_EINVAL);
            }
        }
    }
#endif  /* GSL_RANGE_CHECK */
  
  TYPE (tensor) * v;
  
  v = (TYPE (tensor) *) malloc (sizeof (TYPE (tensor)));

  if (v == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for view struct",
                     GSL_ENOMEM, 0);
    }

  v->dim = t->dim;

  v->size = (size_t *) malloc (sizeof (size_t) * v->dim);

  if (v->size == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for view sizes",
                     GSL_ENOMEM, 0);
    }

  memcpy(v->size, size, sizeof (size_t) * v->dim);

  v->stride = (size_t *) malloc (sizeof (size_t) * v->dim);

  if (v->stride == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for view strides",
                     GSL_ENOMEM, 0);
    }

  /* Calculate strides and offset index*/
  size_t oidx = 0;
  for (d = 0; d < t->dim; ++d)
    {
      v->stride[d] = t->stride[d] * step[d];

      oidx += offset[d] * t->stride[d];
    }

  oidx *= MULTIPLICITY;

  v->data = t->data + oidx;
  v->block = 0;
  v->owner = 0;

  return (QUALIFIED_TYPE (tensor) *) v;
}

QUALIFIED_TYPE (tensor) *
  FUNCTION (tensor, view_array) (QUALIFIER ATOMIC * array,
                                 const size_t dim, ...)
{
  /* Zero-dim view */
  if (dim == 0)
    {
      char reason[1000];
      sprintf(reason, "failed to allocate view with "
              "0 dimensions from array");
      GSL_ERROR_NULL(reason, GSL_EINVAL);
    }
  
  TYPE (tensor) * v;
  
  v = (TYPE (tensor) *) malloc (sizeof (TYPE (tensor)));

  if (v == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for view struct",
                     GSL_ENOMEM, 0);
    }

  v->dim = dim;

  v->size = (size_t *) malloc (sizeof (size_t) * v->dim);

  if (v->size == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for view sizes",
                     GSL_ENOMEM, 0);
    }

  v->stride = (size_t *) malloc (sizeof (size_t) * v->dim);

  if (v->stride == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for view strides",
                     GSL_ENOMEM, 0);
    }

  va_list argp;  
  va_start (argp, dim);

  size_t i;
  for (i = 0; i < dim; ++i)
    {
      v->size[i] = va_arg (argp, size_t);

      /* Check for dim of zero size */
      if (v->size[i] == 0)
        {
          /* Free partial view */
          free (v->size);
          free (v->stride);
          free (v);
          /* Produce an error */
          char reason[1000];
          sprintf(reason, "failed to allocate view with "
                  "invalid size 0 for dim %zu from array", i);

          va_end (argp);
          
          GSL_ERROR_NULL(reason, GSL_EINVAL);
        }
    }

  va_end (argp);

  size_t stride = 1;
  for (i = 0; i < dim; ++i)
    {
      v->stride[dim - i - 1] = stride;
      stride *= v->size[dim - i - 1];
    }

  v->data = (ATOMIC *) array;
  v->block = 0;
  v->owner = 0;

  return (QUALIFIED_TYPE (tensor) *) v;
}

QUALIFIED_TYPE (tensor) *
  FUNCTION (tensor, view_vector)
  (QUALIFIED_TYPE (gsl_vector) * vector)
{
  TYPE (tensor) * view;
  
  view = (TYPE (tensor) *) malloc (sizeof (TYPE (tensor)));

  if (view == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for view struct",
                     GSL_ENOMEM, 0);
    }

  view->dim = 1;

  view->size = (size_t *) malloc (sizeof (size_t) * view->dim);

  if (view->size == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for view sizes",
                     GSL_ENOMEM, 0);
    }

  view->stride = (size_t *) malloc (sizeof (size_t) * view->dim);

  if (view->stride == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for view strides",
                     GSL_ENOMEM, 0);
    }

  view->size[0] = vector->size;
  view->stride[0] = vector->stride;

  view->data = vector->data;
  view->block = 0;
  view->owner = 0;

  return (QUALIFIED_TYPE (tensor) *) view;
}

QUALIFIED_VIEW (_gsl_vector, view)
  FUNCTION (gsl_vector, view_tensor)
  (QUALIFIED_TYPE (tensor) * t)
{
  QUALIFIED_VIEW (_gsl_vector, view) v = NULL_VECTOR_VIEW;
  
  if (t->dim != 1)
    {
      char reason[1000];
      sprintf(reason,
              "cannot create a vector view "
              "from a tensor with dimension %zu",
              t->dim);
      GSL_ERROR_VAL(reason, GSL_EINVAL, v);
    }

  TYPE (gsl_vector) vector;
  
  vector.size = t->size[0];
  vector.stride = t->stride[0];
  vector.data = t->data;
  vector.block = 0;
  vector.owner = 0;

  v.vector = vector;
  
  return v;
}

QUALIFIED_TYPE (tensor) *
  FUNCTION (tensor, view_matrix)
  (QUALIFIED_TYPE (gsl_matrix) * matrix)
{
  TYPE (tensor) * view;
  
  view = (TYPE (tensor) *) malloc (sizeof (TYPE (tensor)));

  if (view == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for view struct",
                     GSL_ENOMEM, 0);
    }

  view->dim = 2;

  view->size = (size_t *) malloc (sizeof (size_t) * view->dim);

  if (view->size == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for view sizes",
                     GSL_ENOMEM, 0);
    }

  view->stride = (size_t *) malloc (sizeof (size_t) * view->dim);

  if (view->stride == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for view strides",
                     GSL_ENOMEM, 0);
    }

  view->size[0] = matrix->size1;
  view->size[1] = matrix->size2;
  
  view->stride[0] = matrix->tda;
  view->stride[1] = 1;

  view->data = matrix->data;
  view->block = 0;
  view->owner = 0;

  return (QUALIFIED_TYPE (tensor) *) view;
}

QUALIFIED_VIEW (_gsl_matrix, view)
  FUNCTION (gsl_matrix, view_tensor)
  (QUALIFIED_TYPE (tensor) * t)
{
  QUALIFIED_VIEW (_gsl_matrix, view) v = NULL_MATRIX_VIEW;
  
  if (t->dim != 2)
    {
      char reason[1000];
      sprintf(reason,
              "cannot create a matrix view "
              "from a tensor with dimension %zu",
              t->dim);
      GSL_ERROR_VAL(reason, GSL_EINVAL, v);
    }

  TYPE (gsl_matrix) matrix; 

  matrix.size1 = t->size[0];
  matrix.size2 = t->size[1];
  matrix.tda = t->stride[0];
  matrix.data = t->data;
  matrix.block = 0;
  matrix.owner = 0;

  v.matrix = matrix;
  
  return v;
}

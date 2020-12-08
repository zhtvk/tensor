/* tensor/file_source.c
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
FUNCTION (tensor, fread) (FILE * stream, TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);
  
  if (FUNCTION (tensor, is_contiguous) (t))
    {      
      size_t items = fread (t->data,
                            MULTIPLICITY * sizeof (ATOMIC),
                            n, stream);
      if (items != n)
        {
          GSL_ERROR ("fread failed", GSL_EFAILED);
        }
    }
  else
    {
      size_t i;
      for (i = 0; i < n; ++i)
        {
          size_t idx = FUNCTION (tensor, index) (t, i);

          size_t items = fread (t->data + idx,
                                MULTIPLICITY * sizeof (ATOMIC),
                                1, stream);
          if (items != 1)
            {
              GSL_ERROR ("fread failed", GSL_EFAILED);
            }
        }
    }

  return GSL_SUCCESS;
}

int
FUNCTION (tensor, fwrite) (FILE * stream,
                           const TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);
  
  if (FUNCTION (tensor, is_contiguous) (t))
    {      
      size_t items = fwrite (t->data,
                             MULTIPLICITY * sizeof (ATOMIC),
                             n, stream);
      if (items != n)
        {
          GSL_ERROR ("fwrite failed", GSL_EFAILED);
        }
    }
  else
    {
      size_t i;
      for (i = 0; i < n; ++i)
        {
          size_t idx = FUNCTION (tensor, index) (t, i);
          
          size_t items = fwrite (t->data + idx,
                                 MULTIPLICITY * sizeof (ATOMIC),
                                 1, stream);
          if (items != 1)
            {
              GSL_ERROR ("fwrite failed", GSL_EFAILED);
            }
        }
    }

  return GSL_SUCCESS;  
}

#if !(USES_LONGDOUBLE && !HAVE_PRINTF_LONGDOUBLE)

int
FUNCTION (tensor, fscanf) (FILE * stream, TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      size_t m;
      for (m = 0; m < MULTIPLICITY; ++m)
        {
          ATOMIC_IO tmp;

          int status = fscanf (stream, IN_FORMAT, &tmp);

          t->data[idx + m] = tmp;

          if (status != 1)
            {
              GSL_ERROR ("fscanf failed", GSL_EFAILED);
            }
        }
    }

  return GSL_SUCCESS;
}

int
FUNCTION (tensor, fprintf) (FILE * stream,
                            const TYPE (tensor) * t,
                            const char * format)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      int status;
      size_t m;
      for (m = 0; m < MULTIPLICITY; ++m)
        {
          if (m > 0)
            {
              status = putc (' ', stream);

              if (status == EOF)
                {
                  GSL_ERROR ("putc failed", GSL_EFAILED);
                }
              
            }
          
          status = fprintf (stream, format,
                            t->data[idx + m]);
          
          if (status < 0)
            {
              GSL_ERROR ("fprintf failed", GSL_EFAILED);
            }
        }

      status = putc ('\n', stream);

      if (status == EOF)
        {
          GSL_ERROR ("putc failed", GSL_EFAILED);
        }
    }

  return GSL_SUCCESS;
}

#endif  /* !(USES_LONGDOUBLE && !HAVE_PRINTF_LONGDOUBLE) */

/* tensor/explog_complex_source.c
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


/* Exponential operators */

void
FUNCTION (tensor, pow) (TYPE (tensor) * t, BASE p)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = gsl_complex_pow (DATA (t, idx), p);
    }
}

void
FUNCTION (tensor, pow_real) (TYPE (tensor) * t, ATOMIC p)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = gsl_complex_pow_real (DATA (t, idx), p);
    }
}

void
FUNCTION (tensor, sqrt) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = gsl_complex_sqrt (DATA (t, idx));
    }
}

void
FUNCTION (tensor, cbrt) (TYPE (tensor) * t)
{
  FUNCTION (tensor, pow_real) (t, 1. / 3);
}

void
FUNCTION (tensor, exp) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = gsl_complex_exp (DATA (t, idx));
    }
}

void
FUNCTION (tensor, exp2) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  gsl_complex b;
  GSL_REAL (b) = 2;
  GSL_IMAG (b) = 0;

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = gsl_complex_pow (b, DATA (t, idx));
    }
}

void
FUNCTION (tensor, exp10) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  gsl_complex b;
  GSL_REAL (b) = 10;
  GSL_IMAG (b) = 0;

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = gsl_complex_pow (b, DATA (t, idx));
    }
}

/* Logarithmic operators */

void
FUNCTION (tensor, log) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = gsl_complex_log (DATA (t, idx));
    }
}

void
FUNCTION (tensor, log2) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = gsl_complex_mul_real
        (gsl_complex_log ((DATA (t, idx))),
         1 / LOG (2));
    }
}

void
FUNCTION (tensor, log10) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = gsl_complex_log10 (DATA (t, idx));
    }
}


/* tensor/trig_complex_source.c
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


/* Trigonometric operators */

void
FUNCTION (tensor, sin) (TYPE (tensor) * t)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      DATA (t, idx) = gsl_complex_sin (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_cos (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_tan (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_sec (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_csc (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_cot (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_arcsin (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_arccos (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_arctan (DATA (t, idx));
    }
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

      DATA (t, idx) = gsl_complex_arcsec (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_arccsc (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_arccot (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_sinh (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_cosh (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_tanh (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_sech (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_csch (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_coth (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_arcsinh (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_arccosh (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_arctanh (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_arcsech (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_arccsch (DATA (t, idx));
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

      DATA (t, idx) = gsl_complex_arccoth (DATA (t, idx));
    }
}  


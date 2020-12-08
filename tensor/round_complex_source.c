/* tensor/round_complex_source.c
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
FUNCTION (tensor, clip) (TYPE (tensor) * t,
                         const BASE min, const BASE max)
{
  const size_t n = FUNCTION (tensor, tsize) (t);

  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      if (DATA_REAL (t, idx) < GSL_REAL (min))
        DATA_REAL (t, idx) = GSL_REAL (min);

      if (DATA_IMAG (t, idx) < GSL_IMAG (min))
        DATA_IMAG (t, idx) = GSL_IMAG (min);

      if (DATA_REAL (t, idx) > GSL_REAL (max))
        DATA_REAL (t, idx) = GSL_REAL (max);

      if (DATA_IMAG (t, idx) > GSL_IMAG (max))
        DATA_IMAG (t, idx) = GSL_IMAG (max);
    }
}

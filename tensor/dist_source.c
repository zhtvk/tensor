/* tensor/dist_source.c
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

#if FP

void
FUNCTION (tensor, set_uniform) (TYPE (tensor) * t,
                                const gsl_rng * rng)
{
  const size_t n = FUNCTION (tensor, tsize) (t);
  
  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      *(ATOMIC *) (t->data + idx) = (ATOMIC) gsl_rng_uniform (rng);
    }  
}

void
FUNCTION (tensor, set_normal) (TYPE (tensor) * t,
                               const gsl_rng * rng,
                               double mu, double sigma)
{
  const size_t n = FUNCTION (tensor, tsize) (t);
  
  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      *(ATOMIC *) (t->data + idx) =
        (ATOMIC) mu +
        (ATOMIC) gsl_ran_gaussian (rng, sigma);
    }
}

void
FUNCTION (tensor, set_std_normal) (TYPE (tensor) * t,
                                   const gsl_rng * rng)
{
  FUNCTION (tensor, set_normal) (t, rng, 0.0, 1.0);
}

#endif  /* FP */

void
FUNCTION (tensor, set_uniform_int) (TYPE (tensor) * t,
                                    const gsl_rng * rng,
                                    unsigned long int max)
{
  const size_t n = FUNCTION (tensor, tsize) (t);
  
  size_t i;
  for (i = 0; i < n; ++i)
    {
      size_t idx = FUNCTION (tensor, index) (t, i);

      *(ATOMIC *) (t->data + idx) =
        (ATOMIC) gsl_rng_uniform_int (rng, max);
    }
}

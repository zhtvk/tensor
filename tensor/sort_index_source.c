/* tensor/sort_index_source.c
 *
 * Implement Heap sort -- direct and indirect sorting Based on
 * descriptions in Sedgewick "Algorithms in C"
 *
 * Copyright (C) 1999 Thomas Walter
 *
 * 18 February 2000: Modified for GSL by Brian Gough
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


static inline void
FUNCTION (tensor, downheap) (size_t * p,
                             const TYPE (tensor) * t,
                             const size_t N, size_t k);

static inline void
FUNCTION (tensor, downheap) (size_t * p,
                             const TYPE (tensor) * t,
                             const size_t N, size_t k)
{
  const size_t pki = p[k];
  BASE v = t->data[FUNCTION (tensor, index) (t, pki)];

  while (k <= N / 2)
    {
      size_t j = 2 * k;

      if (j < N &&
          t->data[FUNCTION (tensor, index) (t, p[j])] <
          t->data[FUNCTION (tensor, index) (t, p[j + 1])])
        {
          j++;
        }

      /* Avoid infinite loop if nan */
      if (!(v < t->data[FUNCTION (tensor, index) (t, p[j])]))
        {
          break;
        }

      p[k] = p[j];

      k = j;
    }

  p[k] = pki;
}

void
FUNCTION (tensor, sort_index) (size_t * p, const TYPE (tensor) * t)
{
  size_t n = FUNCTION (tensor, tsize) (t);
  size_t i, N, k;

  /* No data to sort */
  if (n == 0)
    {
      return;
    }

  /* Set permutation to identity */
  for (i = 0; i < n; ++i)
    p[i] = i;

  /* We have n_data elements, last element is at 'n_data-1', first at
     '0' Set N to the last element number. */

  N = n - 1;

  k = N / 2;
  /* Compensate the first use of 'k--' */
  k++;
  do
    {
      k--;
      FUNCTION (tensor, downheap) (p, t, N, k);
    }
  while (k > 0);

  while (N > 0)
    {
      /* first swap the elements */
      size_t tmp = p[0];
      p[0] = p[N];
      p[N] = tmp;

      /* then process the heap */
      N--;

      FUNCTION (tensor, downheap) (p, t, N, 0);
    }
}

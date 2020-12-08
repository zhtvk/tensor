#include <stdio.h>
#include <tensor/tensor.h>

int
main (void)
{
  tensor * t = tensor_alloc (3, 2, 3, 4);

  size_t i, j, k;

  for (i = 0; i < 2; ++i)
    for (j = 0; j < 3; ++j)
      for (k = 0; k < 4; ++k)
        {
          tensor_set (t, i * 0.2 + j * 0.3 + k, i, j, k);
        }

  for (i = 0; i < 3; ++i)       /* INDEX OUT OF RANGE ERROR */
    for (j = 0; j < 3; ++j)
      for (k = 0; k < 4; ++k)
        {
          printf ("t (%zu, %zu, %zu) = %g\n", i, j, k, 
                  tensor_get (t, i, j, k));
        }

  tensor_free (t);

  return 0;
}

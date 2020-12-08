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

  printf("Tensor t elements: \n");
  
  for (i = 0; i < t->size[0]; ++i)
      for (j = 0; j < t->size[1]; ++j)
          for (k = 0; k < t->size[2]; ++k)
            {
              printf ("t (%zu, %zu, %zu) = %g\n", i, j, k, 
                      tensor_get (t, i, j, k));
            }

  tensor * v = tensor_view (t,
                            RANGE (0, t->size[0], 1),
                            RANGE (0, t->size[1], 2),
                            RANGE (0, t->size[2], 2));

  /* Sets elements where both row and column index is even to zero */
  tensor_set_zero (v);

  printf("\n");
  printf("Tensor t elements: \n");
  
  for (i = 0; i < t->size[0]; ++i)
      for (j = 0; j < t->size[1]; ++j)
          for (k = 0; k < t->size[2]; ++k)
            {
              printf ("t (%zu, %zu, %zu) = %g\n", i, j, k, 
                      tensor_get (t, i, j, k));
            }

  tensor_free (v);
  tensor_free (t);

  return 0;
}


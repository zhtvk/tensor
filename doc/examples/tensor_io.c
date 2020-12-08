#include <stdio.h>
#include <tensor/tensor.h>

int
main (void)
{
  size_t i, j, k, diff = 0;
  double t_el, u_el;
  
  tensor * t = tensor_alloc (3, 10, 10, 10);
  tensor * u = tensor_alloc (3, 10, 10, 10);

  for (i = 0; i < 10; ++i)
    for (j = 0; j < 10; ++j)
      for (k = 0; k < 10; ++k)
        {
          tensor_set (t, i * 0.2 + j * 0.3 + k, i, j, k);
        }

  FILE * f = fopen ("test.dat", "wb");
  tensor_fwrite (f, t);
  fclose (f);

  f = fopen ("test.dat", "rb");
  tensor_fread (f, u);
  fclose (f);

  for (i = 0; i < 10; ++i)
    for (j = 0; j < 10; ++j)
      for (k = 0; k < 10; ++k)
        {
          t_el = tensor_get (t, i, j, k);
          u_el = tensor_get (u, i, j, k);

          if (t_el != u_el)
            ++diff;
        }

  tensor_free (t);
  tensor_free (u);

  printf ("differences = %zu (should be zero)\n", diff);
  
  return (diff > 0);
}

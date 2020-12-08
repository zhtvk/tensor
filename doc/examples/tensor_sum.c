#include <stdio.h>
#include <tensor/tensor.h>

int
main (void)
{
  tensor * t = tensor_alloc (3, 2, 3, 4);

  tensor_set_one (t);

  printf ("Element's sum: %g\n", tensor_sum (t));

  tensor_free (t);

  return 0;
}

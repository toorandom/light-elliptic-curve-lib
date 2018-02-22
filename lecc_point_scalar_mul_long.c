#include "lecc.h"
void
lecc_point_scalar_mul_long (long k, point_t * a, point_t * r)
{
  int i;
  point_t *t1, *a_acum;
  t1 = lecc_point_alloc ();
  a_acum = lecc_point_alloc ();

  lecc_point_clean (a_acum);
  lecc_point_clean (t1);
  for (i = 0; i < k; i++)
    {
      lecc_point_add (a, a_acum, t1);
      lecc_point_clean (a_acum);
      lecc_point_copy (a_acum, t1);
      lecc_point_clean (t1);
    }
  lecc_point_copy (r, a_acum);
  lecc_point_free (a_acum);
  lecc_point_free (t1);
  return;
}


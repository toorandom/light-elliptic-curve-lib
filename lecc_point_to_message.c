#include "lecc.h"
void
lecc_point_to_message (point_t * a, bint * ret)
{
  bint *kint, *t;
  kint = bint_alloc (8, POSITIVE);
  t = bint_alloc (8, POSITIVE);
  kint->digits[0] = K;
  kint->sign = POSITIVE;
  kint->len = 1;
  ret = bint_div (a->x, kint, ret, t);
  bint_free (kint);
  bint_free(t);
  return;
}

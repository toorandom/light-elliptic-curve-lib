#include "lecc.h"
extern bint *p, *b, *base_x, *base_y, *p_minus_1_by_2, *p_plus_1_by_4;

void
lecc_free_parameters (void)
{
  bint_free (p);
  bint_free (b);
  bint_free (base_x);
  bint_free (base_y);
  bint_free (p_minus_1_by_2);
  bint_free (p_plus_1_by_4);
  return;
}


#include "lecc.h"
void
lecc_point_normalize (point_t * k)
{
  bint_normalize (k->x);
  bint_normalize (k->y);
  return;
}


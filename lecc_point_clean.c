#include "lecc.h"
void
lecc_point_clean (point_t * a)
{
  bint_clean (a->x);
  bint_clean (a->y);
  a->x->len = 1;
  a->y->len = 1;
  a->infinity = 1;
}

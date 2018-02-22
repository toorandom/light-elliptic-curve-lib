#include "lecc.h"
void
lecc_point_free (point_t * m)
{
  bint_free (m->x);
  bint_free (m->y);
  sfree (m);
  return;
}


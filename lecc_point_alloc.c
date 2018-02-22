#include "lecc.h"
extern bint *p;
void *
lecc_point_alloc ()
{
  point_t *z;
  z = calloc (1, sizeof (struct point));
  z->x = bint_alloc (p->len*2, POSITIVE);
  z->y = bint_alloc (p->len*2, POSITIVE);
  return z;
}


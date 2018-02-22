#include "lecc.h"
int
points_are_equal (const point_t * a, const point_t * b)
{
  int x, y;
  x = bint_cmp (a->x, b->x);
  y = bint_cmp (a->y, b->y);
  return ((x == y) & (x == EQUAL));
}


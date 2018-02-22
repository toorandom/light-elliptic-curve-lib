#include "lecc.h"
void
lecc_point_copy (point_t * dst, point_t * src)
{
  dst->infinity = src->infinity;
  bint_copy (dst->x, src->x);
  bint_copy (dst->y, src->y);
  return;
}

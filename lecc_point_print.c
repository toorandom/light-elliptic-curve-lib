#include "lecc.h"
void
lecc_point_print (point_t * m, char *name)
{
  if (name != NULL)
    printf ("\n");
  printf ("%s\nx=",name);
  bint_print (m->x);
  printf ("y=");
  bint_print (m->y);
  return;
}


#include "lecc.h"
extern bint *p;
void
lecc_point_add (point_t * a, point_t * b, point_t * r)
{
  bint *s, *t1, *t2, *t3, *t4, *t5, *t;
  int fsize = (a->x->len + b->x->len + p->len) * 3 + 1;
  bint_clean (r->x);
  bint_clean (r->y);
  r->infinity = 0;
  lecc_point_normalize (a);
  lecc_point_normalize (b);

  if (points_are_equal (a, b))
    {
      lecc_point_double (a, r);
      return;
    }

  if (a->infinity)
    {
      lecc_point_copy (r, (point_t *) b);
      return;
    }
  if (b->infinity)
    {
      lecc_point_copy (r, (point_t *) a);
      return;
    }


  t = bint_alloc (a->y->len + b->y->len, POSITIVE);

  if (bint_is_zero (bint_add (a->y, b->y, t)))
    {
      printf ("infinito!!!\n");
      bint_clean (r->x);
      bint_clean (r->y);
      bint_free (t);
      r->infinity = 1;
      return;
    }

  if (a->infinity)
    if (!b->infinity)
      {
        bint_copy (r->x, a->x);
        bint_copy (r->y, a->y);
        lecc_point_normalize (r);
        r->infinity = 0;
        bint_free (t);
        return;
      }


  if (a->infinity)
    if (!b->infinity)
      {
        bint_copy (r->x, b->x);
        bint_copy (r->y, b->y);
        r->infinity = 0;
        lecc_point_normalize (r);
        bint_free (t);
        return;
      }
  s = bint_alloc (fsize, POSITIVE);
  t1 = bint_alloc (fsize, POSITIVE);
  t2 = bint_alloc (fsize, POSITIVE);
  t3 = bint_alloc (fsize, POSITIVE);
  t4 = bint_alloc (fsize, POSITIVE);
  t5 = bint_alloc (fsize, POSITIVE);
/* We calculate the substractions for the slope */
  t1 = bint_sub (b->y, a->y, t1);
  t2 = bint_sub (b->x, a->x, t2);


/* here we t3=a->y-b->y and  t4 = a->x - b->x modulo p */
  t3 = bint_mod (t1, p, t3);
  t4 = bint_mod (t2, p, t4);


/* t5 has the inverse a->x - b->x */

  t5 = bint_inverse (t4, p, t5);

/*
 * Checked until here on december 20
 *  t5 = bint_inverse (t2, p, t5);   // quitar
 */

  bint_clean (t1);
  bint_clean (t2);
  t1 = bint_mul (t5, t3, t1);

/* here is the slope */
  bint_clean (s);

  s = bint_mod (t1, p, s);
  bint_clean (t1);
  bint_clean (t2);
  bint_clean (t3);
  bint_clean (t4);
  bint_clean (t5);

/* We calculate to t1 = s^2 */
  bint_copy (t5, s);
  t1 = bint_mul (s, t5, t1);

  t2 = bint_mod (t1, p, t2);

  bint_clean (t1);
  bint_copy (t1, t2);
  bint_clean (t2);
  bint_clean (t5);

/* We calculate t2 = s^2 - a->x */
  t2 = bint_sub (t1, a->x, t2);

/* We calculate t1 = t2 - b->x  = (s^2 - a->x) - b->x */
  bint_clean (t1);
  t1 = bint_sub (t2, b->x, t1);
/* Here we have the x coordinate of the sum */

  r->x = bint_mod (t1, p, r->x);

  bint_clean (t1);
  bint_clean (t2);
  bint_clean (t3);
  bint_clean (t4);

/* Calculating t2 = a->x - r->x */
  t2 = bint_sub (a->x, r->x, t2);

  t3 = bint_mod (t2, p, t3);

  bint_clean (t2);
  bint_copy (t2, t3);
  bint_clean (t3);
/* We calculate t3 = s*(a->x - r->x) */

  t3 = bint_mul (s, t2, t3);

  t4 = bint_sub (t3, a->y, t4);

  r->y = bint_mod (t4, p, r->y);

  bint_free (s);
  bint_free (t1);
  bint_free (t2);
  bint_free (t3);
  bint_free (t4);
  bint_free (t5);
  bint_free (t);
  //    lecc_point_normalize(r);

  return;

}

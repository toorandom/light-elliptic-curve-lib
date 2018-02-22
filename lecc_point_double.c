#include "lecc.h"
 extern bint *p;
void
lecc_point_double (point_t * a, point_t * r)
{
  bint *s, *t1, *t2, *t3, *t4, *t5;
  lecc_point_normalize (a);
  t1 = bint_alloc (a->x->len + a->y->len + p->len , POSITIVE);
  t2 = bint_alloc (a->x->len + a->y->len + p->len , POSITIVE);
  t3 = bint_alloc (a->x->len +  a->y->len + p->len , POSITIVE);
  s = bint_alloc (a->x->len *  a->y->len + p->len, POSITIVE);
  if (a->infinity)
    {
      r->infinity = 1;
      bint_clean (r->x);
      bint_clean (r->y);
      r->x->len = 1;
      r->y->len = 1;
      lecc_point_normalize (r);
      bint_free (t1);
      bint_free (t2);
      bint_free (t3);
      bint_free (s);
      return;
    }

/* First we calculate the derivative in the point a */

/* This is t2 = 3*(a->x)^2 + A  (A=-3 so we just dec three times) */
  bint_clean (t1);
  bint_clean (t2);
  bint_clean (t3);
  bint_clean (s);
  bint_copy (t3, a->x);
  t1 = bint_mul (a->x, t3, t1);

  t2 = bint_mul_long (t1, 3, t2);
  bint_clean (t1);
  bint_clean (t3);

/* This is because (3x^2 + A)  and A = -3 */
  bint_dec (t2);
  bint_dec (t2);
  bint_dec (t2);


/* whis is t3 = 1/(2*a->y) */
  t1 = bint_mul_long (a->y, 2, t1);


  t3 = bint_inverse (t1, p, t3);
/* Now we calculate t2*t3 = s */
  s = bint_mul (t2, t3, s);
  bint_clean (t1);
  bint_mod (s, p, t1);
  bint_clean (s);
  bint_copy (s, t1);
  bint_clean (t1);
  bint_clean (t2);
  bint_clean (t3);

/* Now we calculate the x coordinate of the resulting point */
  bint_copy (t3, s);
  t1 = bint_mul (s, t3, t1);
  t2 = bint_mul_long (a->x, 2, t2);
  r->x = bint_sub (t1, t2, r->x);
  bint_clean (t1);
  bint_clean (t2);
  bint_clean (t3);



  t1 = bint_mod (r->x, p, t1);
  bint_clean (r->x);
  bint_copy (r->x, t1);
/* Now we calculate the y coordinate of the resulting point */
  bint_clean (t1);
  t1 = bint_sub (a->x, r->x, t1);
  t2 = bint_mul (s, t1, t2);
  bint_clean (t1);
  t3 = bint_mod (t2, p, t3);
  bint_clean (t2);
  bint_copy (t2, t3);

  r->y = bint_sub (t2, a->y, r->y);

  r->infinity = 0;

  bint_clean (t1);
  bint_clean (t2);

  t1 = bint_mod (r->x, p, t1);
  t2 = bint_mod (r->y, p, t2);

  bint_clean (r->x);
  bint_clean (r->y);

  bint_copy (r->x, t1);
  bint_copy (r->y, t2);
  bint_free (t1);
  bint_free (t2);
  bint_free (t3);
  bint_free (s);
  lecc_point_normalize (r);

  return;

}


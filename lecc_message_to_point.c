#include "lecc.h"
extern bint *p, *b, *base_x, *base_y, *p_minus_1_by_2, *p_plus_1_by_4;

void
lecc_message_to_point (bint * x, point_t * Q)
{
  int j;
  point_t ret;
  bint **xj, **sj, *J, *t, *t2, *t3, *t4;
  xj = calloc (K + 1 + 10, sizeof (bint) + 1);
  sj = calloc (K + 1 + 10, sizeof (bint) + 1);
  t = bint_alloc (x->len * 10, POSITIVE);
  t2 = bint_alloc (x->len * 10, POSITIVE);
  t3 = bint_alloc ((x->len * 10) + 10, POSITIVE);
  t4 = bint_alloc ((x->len * 10) + 10, POSITIVE);
  bint_clean (Q->x);
  bint_clean (Q->y);

  J = bint_alloc (320, POSITIVE);
  J->digits[0] = 0;
  J->len = 1;
  t = bint_mul_long (x, K, t);
  bint_normalize (t);
  for (j = 0; j < K; j++)
    {

      xj[j] = bint_alloc (x->len * 10, POSITIVE);
      bint_clean (xj[j]);
      bint_copy (xj[j], t);
      bint_inc (t);
    }
  for (j = 0; j < K; j++)
  {
	  if(j == 5)
		  exit(EXIT_FAILURE);
      sj[j] = bint_alloc (xj[j]->len * 6, POSITIVE);
      bint_debug(xj[j],"x");
      t = bint_pow2long (xj[j], 3, t);
      bint_debug(t,"y");
      printf("y-(x^3)\n");
      bint_debug(xj[j],"x");
      t2 = bint_mul_long (xj[j], 3, t2);
      bint_debug(t2,"y");
      printf("y-(3*x)\n");
      bint_debug(t,"x");
      bint_debug(t2,"y");
      t3 = bint_sub (t, t2, t3);
      bint_debug(t3,"z");
      printf("(x-y)-z\n"); 
      bint_debug(t3,"x");
      bint_debug(b,"y");
      t4 = bint_add (t3, b, t4);
      bint_debug(t4,"z");
      printf("x+y-z\n");
      bint_debug(t4,"x");
      bint_debug(p,"y");
      bint_mod (t4, p, sj[j]);
      bint_debug(sj[j],"z");
      printf("(x%%y)-z\n");
      bint_normalize (sj[j]);
      bint_clean (t4);
      bint_debug(sj[j],"x");
      bint_debug(p_minus_1_by_2,"q");
      bint_debug(p,"p");
      t4 = bint_mod_exp (sj[j], p_minus_1_by_2, p, t4);
      bint_debug(t4,"z");


      if (bint_is_one (t4))
        {
		printf("bint is one\n");
		bint_debug(Q->y,"mod_exp");
          /* Calculate square root of sj[j] mod p */
          bint_clean (Q->y);
          bint_mod_exp (sj[j], p_plus_1_by_4, p, Q->y);
          bint_copy (Q->x, xj[j]);
          break;
        }
      bint_clean (t);
    }


  for (j - 1; j >= 0; j--)
    bint_free (sj[j]);
  for (j = 0; j < K; j++)
    bint_free (xj[j]);


  bint_free (t);
  bint_free (t2);
  bint_free (t3);
  bint_free (t4);
  bint_free (J);

  sfree (xj);
  sfree (sj);

  Q->infinity = 0;
  return;
}

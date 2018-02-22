#include "lecc.h"
extern bint *p;
void
lecc_point_scalar_mul (bint * k, point_t * a, point_t * dst)
{
  point_t *u, *tp, *a2;
  bint *t1, *t2, *t3, *t4, *k_bak;
  int kbin_len, bit;
  _ulong i;
  if (a->infinity == 1)
    {
      lecc_point_clean (dst);
      dst->infinity = 1;
      return;
    }
  bint_normalize (k);
  lecc_point_normalize (a);
  kbin_len = bint_getbitsize (k);
  tp = lecc_point_alloc ();
  a2 = lecc_point_alloc ();
  t1 = bint_alloc (p->len * 2, POSITIVE);
  t2 = bint_alloc (p->len * 2, POSITIVE);
  t3 = bint_alloc (p->len * 2, POSITIVE);
  t4 = bint_alloc (p->len * 2, POSITIVE);
  k_bak = bint_alloc (k->len + 1, POSITIVE);
  bint_copy (k_bak, k);

  lecc_point_clean (a2);
  a2->infinity = 1;
  for (i = 0; i < kbin_len; i++)
    {
      lecc_point_double (a2, tp);
      lecc_point_clean (a2);
      lecc_point_copy (a2, tp);
      lecc_point_clean (tp);
      if (bit =
          bint_bitget (k, i + (((k->len * sizeof (_ulong)) * 8) - kbin_len)))
        {
          lecc_point_add (a, a2, tp);
          lecc_point_clean (a2);
          lecc_point_copy (a2, tp);
        }

    }
  lecc_point_copy (dst, a2);
  lecc_point_normalize (dst);
  bint_free (t1);
  bint_free (t2);
  bint_free (t3);
  bint_free (t4);
  lecc_point_free (tp);
  dst->infinity = 0;
  bint_copy (k, k_bak);
  bint_free (k_bak);
  lecc_point_free (a2);

  return;

}

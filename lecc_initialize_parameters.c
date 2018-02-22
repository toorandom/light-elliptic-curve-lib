#include "lecc.h"
#include "sgprimes.h"
#include "curve-constants.h"

/* Global numbers i will need */
bint *p, *b, *base_x, *base_y, *p_minus_1_by_2, *p_plus_1_by_4;


void
lecc_initialize_parameters (void)
{
  p = bint_alloc (sizeof (PRIME_256_A) + 1, POSITIVE);
  b = bint_alloc (sizeof (COEF_B_CURVE_A) + 1, POSITIVE);
  base_x = bint_alloc (sizeof (BASE_POINT_X_CURVE_A) + 1, POSITIVE);
  base_y = bint_alloc (sizeof (BASE_POINT_Y_CURVE_A) + 1, POSITIVE);
  p_plus_1_by_4 = bint_alloc (sizeof (PRIME_256_A_PLUS_1_BY_4) + 1, POSITIVE);
  p_minus_1_by_2 = bint_alloc (sizeof (PRIME_256_A_MINUS_1_BY_2)+1, POSITIVE);
  p = atobint (PRIME_256_A, sizeof (PRIME_256_A)-1 , POSITIVE, p);
  bint_debug(p,"p1");
  b = atobint (COEF_B_CURVE_A, sizeof (COEF_B_CURVE_A) - 1, POSITIVE, b);
  base_x =
    atobint (BASE_POINT_X_CURVE_A, sizeof (BASE_POINT_X_CURVE_A) - 1,
             POSITIVE, base_x);
  base_y =
    atobint (BASE_POINT_Y_CURVE_A, sizeof (BASE_POINT_Y_CURVE_A) - 1,
             POSITIVE, base_y);
  p_minus_1_by_2 =
    atobint (PRIME_256_A_MINUS_1_BY_2, sizeof (PRIME_256_A_MINUS_1_BY_2)-1   ,
             POSITIVE, p_minus_1_by_2);
  bint_debug(p_minus_1_by_2,"p2");
  p_plus_1_by_4 =
    atobint (PRIME_256_A_PLUS_1_BY_4, sizeof (PRIME_256_A_PLUS_1_BY_4) - 1,
             POSITIVE, p_plus_1_by_4);
  return;
}

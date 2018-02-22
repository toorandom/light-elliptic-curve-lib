/*
Elgamal routines using finite group on a elliptic curve
Eduardo Ruiz Duarte
beck@math.co.ro
*/
#include "lecc.h"
/*
extern bint *base_x;
extern bint *base_y;
extern bint *p;
*/
extern bint *base_x, *base_y, *p;
void
elgamal_genkeys_ecc (point_t * public, bint * priv)
{
  point_t *gen = lecc_point_alloc ();
  bint_copy (gen->x, base_x);
  bint_copy (gen->y, base_y);
  gen->infinity = 0;
  priv = bint_random (priv, p);
  bint_normalize (priv);
  bint_debug(priv,"priv");
  lecc_point_scalar_mul (priv, gen, public);
  lecc_point_free (gen);
  return;
}

void
elgamal_crypt_ecc (point_t * m, point_t * pub, point_t * c1, point_t * c2)
{
  bint *t = bint_alloc (p->len * p->len * p->len, POSITIVE);
  point_t *gen = lecc_point_alloc (), *tmp;
  bint_copy (gen->x, base_x);
  bint_copy (gen->y, base_y);
  gen->infinity = 0;
  printf("Random crap\n");
  t = bint_random (t,p);
  tmp = lecc_point_alloc ();
  printf("Ciphertext 1\n");
  lecc_point_scalar_mul (t, gen, c1);
  printf("Ciphertext 2\n");
  lecc_point_scalar_mul (t, pub, tmp);
  printf("Adding point to Ciphertext 2\n");
  lecc_point_add (tmp, m, c2);
  lecc_point_free (tmp);
  lecc_point_free (gen);
  bint_free (t);
  return;
}

void
elgamal_decrypt (point_t * c1, point_t * c2, bint * priv, point_t * plain)
{
  point_t *tmp;
  bint *t1;
  tmp = lecc_point_alloc ();
  t1 = bint_alloc (p->len * p->len * p->len, POSITIVE);
  bint_clean (t1);
  lecc_point_scalar_mul (priv, c1, tmp);
  tmp->y->sign = NEGATIVE;
  lecc_point_add (c2, tmp, plain);
  lecc_point_free (tmp);
  bint_free (t1);
  return;
}
extern bint *b;
int
main (int argc , char **argv)
{
  point_t *pub, *plain_point, *c1, *c2, *out_point;
  bint *priv, *plain_number,*out_number;

  if((argv[1] == NULL) || (strlen(argv[1])<=8) || (strlen(argv[1]) > 24)) {
    fprintf(stderr,"First argument must be the string to cipher it has to be at least 9 bytes and max 24 bytes (192 bits)\n");
    exit(EXIT_FAILURE);
  }
  printf("parameters\n");
  lecc_initialize_parameters ();
  printf("end parameters\n");
  priv = bint_alloc (p->len * p->len * p->len, POSITIVE);
  plain_number = bint_alloc (p->len * p->len, POSITIVE);
  out_number = bint_alloc (p->len * p->len, POSITIVE);
  printf("end bint alocs\n");
  pub = lecc_point_alloc ();
  plain_point = lecc_point_alloc ();
  c1 = lecc_point_alloc ();
  c2 = lecc_point_alloc ();
  out_point = lecc_point_alloc ();
  printf("end lecc alloc\n");

  plain_number = atobint(argv[1],strlen(argv[1]),POSITIVE,plain_number);
  printf("Using this prime\n");
  bint_debug(p,"p");
  printf("Using this B\n");
  bint_debug(b,"B");
  printf("------------------------\n");
  printf("Using this integer as plaintext\nplaintext=");
  bint_print(plain_number);
  printf("------------------------\n");
  printf("Converting integer to point in elliptic curve...\n");
  lecc_message_to_point (plain_number, plain_point);
  lecc_point_print (plain_point, "Plain point");
  printf("------------------------\n");
  printf("Generating public and private keys\n");
  elgamal_genkeys_ecc (pub, priv);
    
  printf("priv=%p,len=%d\n",priv,priv->len);
  lecc_point_print (pub,"Public key");
  printf("------------------------\n");
  printf("Ciphering Plain point..\n");
  elgamal_crypt_ecc (plain_point, pub, c1, c2);
  lecc_point_print(c1,"Ciphered message1");
  lecc_point_print(c2,"Ciphered message2");
  printf("------------------------\n");
  printf("Deciphering ciphered messages with private key:\n");
  bint_debug(priv,"priv");
  printf("priv=%p,len=%d\n",priv,priv->len);
  elgamal_decrypt (c1, c2, priv, out_point);
  lecc_point_print(out_point, "Point decrypted");
  lecc_point_to_message(out_point,out_number);
  printf("------------------------\n");
  printf("Decrypted integer\nplaintext=");
  bint_print(out_number);
  bint_free(priv);
  bint_free(plain_number);
  bint_free(out_number);
  lecc_point_free(plain_point);
  lecc_point_free(pub);
  lecc_point_free(c1);
  lecc_point_free(c2);
  lecc_point_free(out_point);
  lecc_free_parameters ();
  return 0;
}

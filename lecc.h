/* We will use this curve y2 = x3 - 3x + B mod P of prime order R, this settings are recomended for ECC by NIST  */
#ifndef _LECC_H
#define _LECC_H
#include <lightmp.h>

/* This constant defines the probability of 1/2^k to fail when embedding a plaintext to a point in a curve */
#define K 0x100


typedef struct point {
bint *x,*y;
int infinity;
} point_t;
void
lecc_point_normalize(point_t *);
void
lecc_point_double (point_t * , point_t * );
void
lecc_point_add (point_t *, point_t *, point_t *);
void *
lecc_point_alloc (void);
void
lecc_point_print (point_t *, char *);
void
lecc_point_free (point_t * );


#endif /* _LECC_H */

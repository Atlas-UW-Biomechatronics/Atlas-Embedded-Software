#ifndef _REGOPS_
    #define _REGOPS_

/* Bit Masks to clear 1, 2, 3, and 4 bits at once */
#define BLEN_1 0x01
#define BLEN_2 0x03
#define BLEN_3 0x07
#define BLEN_4 0x15

/* Set and Clear Bits from register value */
#define SETBITV(R, P) R |= 0x01<<P
#define CLRBITV(R, P) R &= ~(0x01<<P)
/* Set and Clear Bits from register address */
#define SETBITA(R, P)  *R |= 0x01<<P
#define CLRBITA(R, P)  *R &= ~(0x01<<P)
/* Read the value of a bit from register value */
#define READBITV(R, P) ((R>>P)%2)
/* Read the value of a bit from register address */
#define READBITA( R, P ) ((*R>>P)%2)

/* Set Multiple Bits in a Register */
#define SETREGV(R, S, V, L) R = (R&~(L<<S))|(V<<S)
#define SETREGA(R, S, V, L) *R = (*R&~(L<<S))|(V<<S)
/* Read Multiple Bits in a Register */
#define READREGV(R, S, L) (R&(L<<S))>>S
#define READREGA(R, S, L) (*R&(L<<S))>>S

#endif

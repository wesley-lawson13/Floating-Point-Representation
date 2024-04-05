/*
 * Author: Wesley Lawson - lawsonwe@bc.edu
 */

#ifdef DOUBLE
#define FP_TYPE double
#define FP_SCAN_TYPE "%lf"
#define FP_SIZE sizeof(double) * BITS_PER_BYTE
#define U_TYPE unsigned long
#define BIAS 1023
#define ZERO_EXPONENT (-1022)
#define EXPONENT_LENGTH 11
#else
#define FP_TYPE float
#define FP_SCAN_TYPE "%f"
#define FP_SIZE sizeof(float) * BITS_PER_BYTE
#define U_TYPE unsigned int
#define BIAS 127
#define ZERO_EXPONENT (-126)
#define EXPONENT_LENGTH 8
#endif
#define BITS_PER_BYTE 8
#define SIGN_LENGTH 1
#define MANTISSA_LENGTH (FP_SIZE - EXPONENT_LENGTH - SIGN_LENGTH) 
#define INF (1.0/0.0)

struct Components {
    U_TYPE mantissa : MANTISSA_LENGTH;
    unsigned int exponent : EXPONENT_LENGTH;
    unsigned int sign : SIGN_LENGTH;
};

union Converter {
    FP_TYPE type;
    U_TYPE u;
    struct Components c;
};

void print_reconstitution(struct Components);

FP_TYPE power_of_2(int);

void print_denormalized(struct Components);

void print_normalized(struct Components);

void print_components(U_TYPE, struct Components);

void print_bits(U_TYPE, int);

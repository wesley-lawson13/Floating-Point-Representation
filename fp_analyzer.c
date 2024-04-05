#include <stdio.h>

#include "fp_analyzer.h"

// checks if a floating-point number is in normalized or denormalized form.
void print_reconstitution(struct Components c) {
    if (c.exponent == 0) {
        print_denormalized(c);
    } else {
        print_normalized(c);
    }
}

// computes the value of the power of 2 exponent. 
FP_TYPE power_of_2(int exponent) {
    FP_TYPE result = 1.0;
    int index;
    if (exponent >= 0) {
        for (index = 0; index < exponent; ++index) {
            result *= 2.0;
        }
    } else {
        for (index = 0; index > exponent; --index) {
            result /= 2;
        }
    }
    return result;
}

// prints an appropriate output for the input 0 or a very small fraction. 
void print_denormalized(struct Components c) {
    if (c.mantissa == 0) {
        printf("Original value: ");
        if (c.sign == 1) {
            puts("-0.0");
        } else {
            puts("0.0");
        }
    } else {
        puts("Original value:");
        int sign;
        int exponent;
        FP_TYPE mantissa = c.mantissa / power_of_2(MANTISSA_LENGTH);
        printf("(-1)^{%d} x %.45f x 2^{1 - %d}", c.sign, mantissa, BIAS);
        putchar('\n');
        exponent = ZERO_EXPONENT;
        FP_TYPE denominator = power_of_2(-exponent);
        if (c.sign == 1) {
            sign = -1;
            printf("  = %d x %f x 2^{%d}", sign, mantissa, exponent); 
            putchar('\n');
            printf("  = %d x %.45f x 1/%.0f\n", sign, mantissa, denominator);
        } else {
            sign = 1;
            printf("  = %d x %f x 2^{%d}", sign, mantissa, exponent); 
            putchar('\n');
            printf("  = %.45f x 1/%.0f\n", mantissa, denominator);
        }
        FP_TYPE multiplier = power_of_2(exponent);
        FP_TYPE product = sign * mantissa * multiplier;
        printf("  = %.45f\n", product);
    }
}

// prints an appropriate output for normalized floating-point inputs. 
void print_normalized(struct Components c) {
    puts("Original value:");
    int sign;
    FP_TYPE mantissa = c.mantissa / power_of_2(MANTISSA_LENGTH);
    int exponent = c.exponent;
    printf("(-1)^{%d} x (1 + %f) x 2^{%d - %d}", c.sign, mantissa, exponent, BIAS);
    putchar('\n');
    FP_TYPE significand = 1 + mantissa;
    exponent -= BIAS;
    if (c.sign == 1) {
        sign = -1;
    } else {
        sign = 1;
    }
    printf("  = %d x %f x 2^{%d}", sign, significand, exponent);
    putchar('\n');
    FP_TYPE multiplier = power_of_2(exponent);
    FP_TYPE denominator = power_of_2(-exponent);
    if (exponent < 0 && sign < 0) {
        printf("  = %d x %.f x 1/%.0f\n", sign, significand, denominator);
    } else if (exponent < 0 && sign > 0) {
        printf("  = %f x 1/%.0f\n", significand, denominator);
    } else if (exponent >= 0 && sign < 0) { 
        printf("  = %d x %f x %.0f\n", sign, significand, multiplier);
    } else {
        printf("  = %f x %.0f\n", significand, multiplier);
    }
    FP_TYPE product = sign * significand * multiplier;
    printf("  = %.45f\n", product);
}

// Prints the binary representation of each component of a floating-point number. 
void print_components(U_TYPE input, struct Components c) {
    printf("All bits: ");
    print_bits(input, FP_SIZE);
    printf("Sign: ");
    print_bits(c.sign, SIGN_LENGTH);
    printf("Exponent: ");
    print_bits(c.exponent, EXPONENT_LENGTH);
    printf("Mantissa: ");
    print_bits(c.mantissa, MANTISSA_LENGTH);
}

// Computes and prints the binary representation of a floating-point number. 
void print_bits(U_TYPE input, int num_bits) {
    U_TYPE mask = 1ul << (num_bits - 1);
    while (mask) {
        putchar(((input & mask) != 0) + '0');
        mask >>= 1;
    }
    putchar('\n');
}

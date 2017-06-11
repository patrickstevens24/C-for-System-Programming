/*
 * pws24-hw7.c
 *
 *  Created on: May 30, 2016
 *      Author: Patrick Stevens
 */
 
#include <stdio.h>

typedef union {
    float num;
    unsigned int bits : 32;
} Float;

typedef unsigned char BYTE;

void fraction(Float fbin) {
    BYTE b;
    double num = 1.0;
    double den = 2.0;
    int expon, unbias, sign;
    float fraction = 1.0, result = 1.0;

    unbias = ((fbin.bits & 0x7F800000) >> 23) - 127; 
    sign = (fbin.bits & 0x80000000) >> 31; 
    fbin.bits = fbin.bits << 9;

    printf("\nCreating the fraction:\n");
    printf("fraction = 1.000000 (the implicit 1)\n");

    for (int i = 0; i < 23; i++) {
        b = (fbin.bits & 0x80000000) >> 31;
        fraction = num / den;

        if (b == 1) {
            result += fraction;
            printf("fraction = %f, after adding %f\n", result, fraction);
        } 
        else
            printf("fraction = %f, after skipping %f\n", result, fraction);  
        
        fbin.bits = fbin.bits << 1;
        den += den;
    }
    
    printf("\nApplying the exponent:\n");
    printf("unbiased exponent = %d\n", unbias);
    if (unbias > 0) {
        for (int i = 0; i < unbias; i++)
            printf("times 2 = %f\n", result *= 2);
    }
    else {
        for (int i = 0; i > unbias; i--)
            printf("divided by 2 = %f\n", result /= 2);
    }
    if (sign == 1)  
        result -= (result * 2);
    
    printf("\nFinal Answer: %f\n", result);
}

void printFB(Float fbin) {
    int i;

    printf("Your float in 32 bits: ");
    for (i = 0; i < 32; i++) {
        printf("%d", (fbin.bits & 0x80000000) >> 31);
        fbin.bits = fbin.bits << 1;
    }
    printf("\n");
}

void printGen(Float fbin) {
    for (int i = 0; i < 32; i++) {
        if (i == 0)   {
            printf("Sign: ");
        } else if (i == 1) {
            printf("\nExponent: ");
        } else if (i == 9) {
            printf("\nFraction: ");
        }

        printf("%d", (fbin.bits & 0x80000000) >> 31);        
        fbin.bits = fbin.bits << 1;
    }
    printf("\n");
}

int main (void) {
    float fn;
    printf("Enter a float: ");
    //input
    scanf("%f", &fn); 
    printf("Your float was read as: %f\n", fn);

    Float fbin;
    fbin.num = fn;

    printFB(fbin);
    printGen(fbin);
    fraction(fbin);

    return 0;
}


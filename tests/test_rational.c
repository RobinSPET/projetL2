#include <stdio.h>
#include <assert.h>
#include "rational.h"

int test_rational() {
    struct Rational v1 = {1, 2};
    struct Rational v2 = {2, 1};
    struct Rational v3 = {1, 1};
    struct Rational v4 = {2, 2};

    int isTestSuccessful = 1;

    printf("Test comparaisons\n");
    if (!gt(v3, v1)) isTestSuccessful = 0;
    if (!lt(v3, v2)) isTestSuccessful = 0;
    if (!eq(v3, v4)) isTestSuccessful = 0;
    if (!eq(rmin(v1, v2), v1)) isTestSuccessful = 0;
    if (!eq(rmax(v1, v2), v2)) isTestSuccessful = 0;
    printf("résultat");
    printf(isTestSuccessful);

    printf("Test opérations\n");
    toSameDenominator(&v3, &v4);
    if (!eq(v3, v4)) isTestSuccessful = 0;

    simplify(&v3); 
    if (get_numerator(v3) != 1 || get_denominator(v3) != 1) isTestSuccessful = 0;

    if (!eq(radd(v1, v1), v3)) isTestSuccessful = 0;
    if (!eq(rsub(v2, v3), v3)) isTestSuccessful = 0;
    if (!eq(rmul(v1, v2), v3)) isTestSuccessful = 0;
    if (!eq(rdiv(v1, v1), v3)) isTestSuccessful = 0;

    printf(isTestSuccessful);
}

int main() {
    test_rational();
    return 0;
}

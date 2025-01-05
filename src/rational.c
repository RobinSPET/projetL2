#include "rational.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "util.h"

long long get_numerator(struct Rational r) {
	return r.numerator;
}

long long get_denominator(struct Rational r) {
	return r.denominator;
}

void set_numerator(struct Rational * r, long long new_numerator) {
	assert(r);
	r->numerator = new_numerator;
}

void set_denominator(struct Rational * r, long long new_denominator) {
	assert(r);
	r->denominator = new_denominator;
}

/**
 * Restitue le plus Grand Diviseur Commun de \p a et \p b .
 *
 * @param[in] a
 * @param[in] b
 * @return PGCD(a,b)
 */
static long long gcd(long long a, long long b) {
    if (b == 0) {
        if (a == 0) {
            fprintf(stderr, "Erreur : gcd(%lld, %lld) n'est pas défini.\n", a, b);
            exit(EXIT_FAILURE);
        }
        return llabs(a); // Retourne la valeur absolue de a
    }
    return gcd(b, a % b);
}

void simplify(struct Rational *r) {
    assert(r);
    if (r->denominator == 0) {
        fprintf(stderr, "Erreur : Dénominateur nul dans simplify.\n");
        exit(EXIT_FAILURE);
    }

    long long g = gcd(r->numerator, r->denominator);

    if (g > 1) {
        r->numerator /= g;
        r->denominator /= g;
    }

    // Normaliser le signe : le dénominateur doit être positif
    if (r->denominator < 0) {
        r->numerator = -r->numerator;
        r->denominator = -r->denominator;
    }
}

/**
 * Factorise le code de mise à égalité des rationnels
 * @param[in] *r1
 * @param[in] *r2
 */
void toSameDenominator(struct Rational *r1, struct Rational *r2) {
	struct Rational tmp = *r1;

  	set_numerator(r1, get_numerator(*r1) * get_denominator(*r2));
  	set_denominator(r1, get_denominator(*r1) * get_denominator(*r2));

  	set_numerator(r2, get_numerator(*r2) * get_denominator(tmp));
  	set_denominator(r2, get_denominator(*r2) * get_denominator(tmp));
}

int gt(struct Rational a, struct Rational b) {
	if (get_denominator(a) != get_denominator(b)) {
		toSameDenominator(&a, &b);
	}

    if (get_numerator(a) > get_numerator(b)) return 1;

    return 0;
}

int lt(struct Rational a, struct Rational b) {
	if (get_denominator(a) != get_denominator(b)) {
		toSameDenominator(&a, &b);
	}

	if (get_numerator(a) < get_numerator(b)) return 1;
	return 0;
}

int gte(struct Rational a, struct Rational b) {
	if (get_denominator(a) != get_denominator(b)) {
		toSameDenominator(&a, &b);
	}

	if (get_numerator(a) >= get_numerator(b)) return 1;
	return 0;
}

int lte(struct Rational a, struct Rational b) {
	if (get_denominator(a) != get_denominator(b)) {
		toSameDenominator(&a, &b);
	}

	if (get_numerator(a) <= get_numerator(b)) return 1;
	return 0;
}

int eq(struct Rational a, struct Rational b) {
	if (get_denominator(a) != get_denominator(b)) {
		toSameDenominator(&a, &b);
	}

	if (get_numerator(a) == get_numerator(b)) return 1;
	return 0;
}

int neq(struct Rational a, struct Rational b) {
	if (get_denominator(a) != get_denominator(b)) {
		toSameDenominator(&a, &b);
	}

	if (get_numerator(a) != get_numerator(b)) return 1;
	return 0;
}

// Pensez à simplifier le résultat.
struct Rational radd(struct Rational a, struct Rational b) {
    struct Rational res;

    // Calculer le dénominateur commun
    long long common_denominator = a.denominator * b.denominator;

    res.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
    res.denominator = common_denominator;

    simplify(&res);
    return res;
}

// Pensez à simplifier le résultat.
struct Rational rsub(struct Rational a, struct Rational b) {
    struct Rational res;

    // Calculer le dénominateur commun
    long long common_denominator = a.denominator * b.denominator;

    res.numerator = a.numerator * b.denominator - b.numerator * a.denominator;
    res.denominator = common_denominator;

    simplify(&res);
    return res;
}

// Pensez à simplifier le résultat.
struct Rational rmul(struct Rational a, struct Rational b) {
	struct Rational res;

	set_numerator(&res, get_numerator(a) * get_numerator(b));
	set_denominator(&res, get_denominator(a) * get_denominator(b));

    simplify(&res);
	return res;
}

// Pensez à simplifier le résultat.
struct Rational rdiv(struct Rational a, struct Rational b) {
    if (b.numerator == 0) {
        fprintf(stderr, "Erreur : Division par zéro dans rdiv.\n");
        exit(EXIT_FAILURE);
    }

    struct Rational bReverted = {
        .numerator = b.denominator,
        .denominator = b.numerator
    };

    return rmul(a, bReverted);
}

struct Rational rmax(struct Rational a, struct Rational b) {
	if (get_denominator(a) != get_denominator(b)) toSameDenominator(&a, &b);

    if (gt(a, b)) return a;
    return b;
}

struct Rational rmin(struct Rational a, struct Rational b) {
	if (get_denominator(a) != get_denominator(b)) toSameDenominator(&a, &b);

	if (lt(a, b)) return a;
	return b;
}

void print_rational(struct Rational r) {
	printf("==================================\n");
	printf("===== Numérateur : %lld =====\n", get_numerator(r));
	printf("===== Dénominateur : %lld =====\n", get_denominator(r));
	printf("==================================\n");
}
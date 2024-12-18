#include "../include/rational.h"

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
	if (b == 0) perror("gcd: division par 0");

    int reste = a % b;

    if (reste == 0) return b;

    return gcd(b,reste);
}

void simplify(struct Rational * r) {
	assert(r);

	long long g = gcd(get_numerator(*r), get_denominator(*r));

	if (g == 1 || g == 0) return;

	set_numerator(r, get_numerator(*r) / g);
	set_denominator(r, get_denominator(*r) / g);
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

	// Libération mémoire de la variable temporaire
	free(&tmp);
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
    if (get_denominator(a) != get_denominator(b)) toSameDenominator(&a, &b);

    set_numerator(&res, get_numerator(a) + get_numerator(b));
    set_denominator(&res, get_denominator(a) + get_denominator(b));

    simplify(&res);
  	return res;
}

// Pensez à simplifier le résultat.
struct Rational rsub(struct Rational a, struct Rational b) {
	struct Rational res;
    if (get_denominator(a) != get_denominator(b)) toSameDenominator(&a, &b);

	set_numerator(&res, get_numerator(a) - get_numerator(b));
	set_denominator(&res, get_denominator(a) - get_denominator(b));

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
	struct Rational res;

	struct Rational bReverted;
	set_numerator(&bReverted, get_denominator(b));
	set_denominator(&bReverted, get_numerator(b));

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
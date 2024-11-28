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
 * Restitue le Plus Grand Diviseur Commun de \p a et \p b .
 *
 * @param[in] a
 * @param[in] b
 * @return PGCD(a,b)
 */
static long long gcd(long long a, long long b) {
    int reste = a % b;

    if (reste == 0) return b;

    return gcd(b,reste);
}

void simplify(struct Rational * r) {
	assert(r);
	// TODO
}

int gt(struct Rational a, struct Rational b) {
	// TODO
}

int lt(struct Rational a, struct Rational b) {
	// TODO
}

int gte(struct Rational a, struct Rational b) {
	// TODO
}

int lte(struct Rational a, struct Rational b) {
	// TODO
}

int eq(struct Rational a, struct Rational b) {
	// TODO
}

int neq(struct Rational a, struct Rational b) {
	// TODO
}

// Pensez à simplifier le résultat.
struct Rational radd(struct Rational a, struct Rational b) {
	struct Rational res;
    res.numerator = a.numerator + b.numerator;
    res.denominator = a.denominator + b.denominator;
    simplify(&res);
  	return res;
}

// Pensez à simplifier le résultat.
struct Rational rsub(struct Rational a, struct Rational b) {
	struct Rational res;
	res.numerator = a.numerator - b.numerator;
	res.denominator = a.denominator - b.denominator;
    simplify(&res);
	return res;
}

// Pensez à simplifier le résultat.
struct Rational rmul(struct Rational a, struct Rational b) {
	struct Rational res;
	res.numerator = a.numerator * b.numerator;
	res.denominator = a.denominator * b.denominator;
    simplify(&res);
	return res;
}

// Pensez à simplifier le résultat.
struct Rational rdiv(struct Rational a, struct Rational b) {
	struct Rational res;
	res.numerator = a.numerator / b.numerator;
	res.denominator = a.denominator / b.denominator;
	simplify(&res);
	return res;
}

struct Rational rmax(struct Rational a, struct Rational b) {
	// TODO
}

struct Rational rmin(struct Rational a, struct Rational b) {
	// TODO
}

void print_rational(struct Rational r) {
	printf("==================================\n");
	printf("===== Numérateur : %lld =====\n", r.numerator);
	printf("===== Dénominateur : %lld =====\n", r.denominator);
	printf("==================================\n");
}
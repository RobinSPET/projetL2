#include "../include/rational.h"
#include "../src/rational.c"
#include "../include/geometry.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "util.h"


struct Point * new_point(struct Rational x, struct Rational y) {
	struct Point *p = (struct Point *)malloc(sizeof(struct Point));

	if (p == NULL) {
		perror("Erreur d'allocation mémoire");
		return NULL;
	}

    p->x = x;
    p->y = y;

    return p;
}

void free_point(struct Point *p){
	assert(p);

	free(p);
	p = NULL;
}

struct Rational get_x(const struct Point * p) {
	assert(p);
	return p->x;
}

struct Rational get_y(const struct Point * p) {
	assert(p);
	return p->y;
}

void set_x(struct Point * p, struct Rational new_x) {
	assert(p);
	p->x = new_x;
}

void set_y(struct Point * p, struct Rational new_y) {
	assert(p);
	p->y = new_y;
}

void print_point(const void * p) {
	assert(p);
	const struct Point *point = (const struct Point *)p;

	printf("============== Point ==============\n");
	printf("===== abscisse : %lld =====\n", get_numerator(get_x(point))/get_denominator(get_x(point)));
	printf("===== ordonnée : %lld =====\n", get_numerator(get_y(point))/get_denominator(get_y(point)));
	printf("===================================\n");
}

struct Segment * new_segment(struct Point * endpoint1, struct Point * endpoint2) {
	struct Segment *s = (struct Segment *)malloc(sizeof(struct Segment));

	if (s == NULL) {
		perror("Erreur d'allocation mémoire");
		return NULL;
	}

	s->endpoint1 = endpoint1;
	s->endpoint2 = endpoint2;

	return s;
}

void free_segment(void * s) {
	assert(s);

	free(s);
	s = NULL;
}

struct Point * get_endpoint1(const struct Segment * s) {
	assert(s);
	return s->endpoint1;
}

struct Point * get_endpoint2(const struct Segment * s) {
	assert(s);
	return s->endpoint2;
}

void set_endpoint1(struct Segment * s, struct Point * new_endpoint) {
	assert(s);
	assert(new_endpoint);
	s->endpoint1 = new_endpoint;
}

void set_endpoint2(struct Segment * s, struct Point * new_endpoint) {
	assert(s);
	assert(new_endpoint);
	s->endpoint2 = new_endpoint;
}

void print_segment(const void * s) {
	assert(s);
    const struct Segment *segment = (const struct Segment *)s;

	printf("============= Segment =============\n");
	printf("=========== endpoint 1 : ==========\n");
	print_point(get_endpoint1(segment));
	printf("=========== endpoint 2 : ==========\n");
	print_point(get_endpoint2(segment));
	printf("==================================\n");
}

int point_precedes(const void * p1, const void * p2) {
	assert(p1);
	assert(p2);

	return lt(get_x((p1)), get_x(p2)) || (eq(get_x(p1), get_x(p2)) && gt(get_y(p1), get_y(p2)));
}

int segment_precedes(const struct Segment * s1, const struct Segment * s2, struct Rational x0) {
	assert(s1);
	assert(s2);
	assert(lte(rmin(get_x(get_endpoint1(s1)), get_x(get_endpoint2(s1))), x0) &&
		   lte(x0, rmax(get_x(get_endpoint1(s1)), get_x(get_endpoint2(s1)))));
	assert(lte(rmin(get_x(get_endpoint1(s2)), get_x(get_endpoint2(s2))), x0) &&
		   lte(x0, rmax(get_x(get_endpoint1(s2)), get_x(get_endpoint2(s2)))));

	// Calcul de y1 au croisement avec x0
	struct Rational t = rdiv(rsub(x0, get_x(get_endpoint1(s1))), rsub(get_x(get_endpoint2(s1)), get_x(get_endpoint1(s1))));
	struct Rational y1 = radd(get_y(get_endpoint1(s1)), rmul(t, rsub(get_y(get_endpoint2(s1)), get_y(get_endpoint1(s1)))));

	// Calcul de y2 au croisement avec x0
	t = rdiv(rsub(x0, get_x(get_endpoint1(s2))), rsub(get_x(get_endpoint2(s2)), get_x(get_endpoint1(s2))));
	struct Rational y2 = radd(get_y(get_endpoint1(s2)), rmul(t, rsub(get_y(get_endpoint2(s2)), get_y(get_endpoint1(s2)))));

  	if (gt(y1, y2)) return 1;

	return 0;
}

/**
 * Vérifie l'orientation du point \p q par rapport au segment défini par les points \p p et \p r .
 *
 * @param[in] p
 * @param[in] q
 * @param[in] r
 * @return
 * 0 si les trois points sont colinéaires,
 * 1 si \p q se trouve dans le sens horaire (clockwise) par rapport au segment [\p p, \p r ],
 * -1 si \p q se trouve dans le sens anti-horaire (counterclockwise) par rapport au segment [\p p, \p r ].
 */
static int get_orientation(const struct Point * p, const struct Point * q, const struct Point * r) {
	assert(p);
	assert(q);
	assert(r);
	struct Rational val =
				rsub(
					rmul(
						rsub(get_y(q), get_y(p)),
						rsub(get_x(r), get_x(q))
						),
					rmul(
						rsub(get_x(q), get_x(p)),
						rsub(get_y(r), get_y(q))
						)
					);
	if (eq(val, (struct Rational) {0,1}))
		return 0;
	else if (gt(val, (struct Rational) {0,1}))
		return 1;
	else
		return -1;
}

/**
 * Vérifie si le point \p q est inclus dans le carré défini par les points \p p et \p r .
 * Si \p p , \p q , \p r sont colinéaires, alors \p q se trouve dans le segment [\p p, \p r ].
 *
 * Remarque : Si le point \p q se trouve dans le bord du carré défini par les points \p p et \p r ,
 * alors on considère que \p q est inclus dans le carré.
 *
 * @param[in] p
 * @param[in] q
 * @param[in] r
 * @return 1 si \p q est inclus dans le carré définit par les points \p p et \p r , sinon 0.
 */
static int is_included(const struct Point * p, const struct Point * q, const struct Point * r) {
	assert(p);
	assert(q);
	assert(r);
	if (lte(rmin(get_x(p), get_x(r)), get_x(q)) && lte(get_x(q), rmax(get_x(p), get_x(r))) &&
		lte(rmin(get_y(p), get_y(r)), get_y(q)) && lte(get_y(q), rmax(get_y(p), get_y(r))))
			return 1;
	return 0;
}

int do_intersect(const struct Segment * s1, const struct Segment * s2) {
	assert(s1);
	assert(s2);

	// Find the four orientations needed for general and special cases
	int o1 = get_orientation(get_endpoint1(s1), get_endpoint2(s1), get_endpoint1(s2));
	int o2 = get_orientation(get_endpoint1(s1), get_endpoint2(s1), get_endpoint2(s2));
	int o3 = get_orientation(get_endpoint1(s2), get_endpoint2(s2), get_endpoint1(s1));
	int o4 = get_orientation(get_endpoint1(s2), get_endpoint2(s2), get_endpoint2(s1));

	// General case
	if ((min(o1, o2) == -1 && max(o1, o2) == 1) && (min(o3, o4) == -1 && max(o3, o4) == 1)) return 1;

	// Special Cases
	// p1, q1 and p2 are co-linear and p2 lies on segment p1q1
	if (o1 == 0 && is_included(get_endpoint1(s1), get_endpoint1(s2), get_endpoint2(s1))) {
		return 2;
	}

	// p1, q1 and q2 are co-linear and q2 lies on segment p1q1
	if (o2 == 0 && is_included(get_endpoint1(s1), get_endpoint2(s2), get_endpoint2(s1))) {
		return 2;
	}

	// p2, q2 and p1 are co-linear and p1 lies on segment p2q2
	if (o3 == 0 && is_included(get_endpoint1(s2), get_endpoint1(s1), get_endpoint2(s2))) {
		return 2;
	}

	// p2, q2 and q1 are co-linear and q1 lies on segment p2q2
	if (o4 == 0 && is_included(get_endpoint1(s2), get_endpoint2(s1), get_endpoint2(s2))) {
		return 2;
	}

	return 0; // Doesn't fall in any of the above cases
}

struct Point * get_intersection_point(const struct Segment * s1, const struct Segment * s2) {
	assert(s1);
	assert(s2);

	struct Point * A = get_endpoint1(s1);
	struct Point * B = get_endpoint2(s1);
	struct Point * C = get_endpoint1(s2);
	struct Point * D = get_endpoint2(s2);

	if (do_intersect(s1, s2) != 1) return NULL;

	struct Rational determinant = rsub(rmul(rsub(get_x(B), get_x(A)), rsub(get_y(D), get_y(C))), rmul(rsub(get_y(B), get_y(A)), rsub(get_x(D), get_x(C))));

	struct Rational t = rdiv( rsub( rmul( rsub(get_x(C), get_x(A)), rsub(get_y(D), get_y(C))), rmul( rsub(get_y(C), get_y(A)), rsub( get_x(D), get_x(C)))), determinant);
	struct Rational u = rdiv( rsub( rmul( rsub(get_x(C), get_x(A)), rsub(get_y(B), get_y(A))), rmul( rsub(get_y(C), get_y(A)), rsub( get_x(B), get_x(A)))), determinant);

	struct Rational test0 = {0, 0};
	struct Rational test1 = {1, 1};

	if (lte(test0, t) && gte(t, test1) && lte(test0, u) && gte(u, test1)) {
		struct Rational x = rmul(radd(get_x(A), t), rsub(get_x(B), get_x(A)));
		struct Rational y = rmul(radd(get_y(A), t), rsub(get_y(B), get_y(A)));

		return new_point(x, y);
	}

	return NULL;
}

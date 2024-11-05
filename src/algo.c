#include "algo.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "util.h"
#include "rational.h"
#include "list.h"
#include "tree.h"
#include "geometry.h"

// ATTENTION : Pour simplifier vos algorithmes, pensez à comparer les deux points
// de chaque segment à l'aide de la fonction point_precedes et enregistrer le point
// qui précède sur le membre endpoint1 de la struct Segment, tandis que l'autre
// point sur le membre endpoint2 de la struct Segment.
struct list_t * load_segments(const char * input_filename) {
	// TODO
}

void save_intersections(const char * output_filename, const struct list_t * intersections) {
	// TODO
}

struct list_t * all_pairs(const struct list_t * segments) {
	assert(segments);
	// TODO
}

///////////////////////////////////////////////////////////////////////////////
//////////////////// ALGORITHME DE Bentley-Ottmann ///////////////////////////
///////////////////////////////////////////////////////////////////////////////

struct Event * new_event(int type, struct Point * event_point, struct Segment * s1, struct Segment * s2) {
	// TODO
}

int get_event_type(const struct Event * event) {
	assert(event);
	// TODO
}

struct Point * get_event_point(const struct Event * event) {
	assert(event);
	// TODO
}

struct Segment * get_event_segment1(const struct Event * event) {
	assert(event);
	// TODO
}

struct Segment * get_event_segment2(const struct Event * event) {
	assert(event);
	// TODO
}

/**
 * Initialise la structure des événements (arbre binaire de recherche) avec les
 * événements connus d'avance (début et fin des segments de la liste
 * \p segments ).
 * Pour rappel, l'arbre est ordonné selon l'ordre impliqué par la fonction
 * point_precedes.
 *
 * @param[in] segments
 * @return l'arbre des événements connus d'avance
 */
static struct tree_t * initialize_events(const struct list_t * segments) {
	assert(segments);
	// TODO
}

/**
 * Vérifie si les segments \p s1 et \p s2 s'intersectent après la position de
 * l'événement \p event . Si oui et si cette intersection n'est pas détectée
 * auparavant, elle sera ajoutée dans la structure des événements (\p events ),
 * ainsi que dans la liste des intersections (\p intersections ).
 *
 * @param[in] s1
 * @param[in] s2
 * @param[in] event
 * @param[in,out] events
 * @param[in,out] intersections
 */
static void test_and_set_intersection(struct Segment * s1, struct Segment * s2, struct Event * event, struct tree_t * events, struct list_t * intersections) {
	assert(s1);
	assert(s2);
	assert(event);
	assert(events);
	assert(intersections);
	// TODO
}

/**
 * Gestion de l'événement \p event de type intersection.
 * L'état de la ligne de balayage décrite par la liste \p status doit être mis
 * à jour. La structure des événements (\p events ) ainsi que la liste des
 * intersections (\p intersections ) seront éventuellement mises à jour si une
 * nouvelle intersection sera détectée (utilisez la procedure
 * test_and_set_intersection).
 *
 * @param[in] event
 * @param[in,out] status
 * @param[in,out] events
 * @param[in,out] intersections
 */
static void handle_intersection_event(struct Event * event, struct list_t * status, struct tree_t * events, struct list_t * intersections) {
	assert(event);
	assert(status);
	assert(events);
	assert(intersections);
	// TODO
}

/**
 * Gestion de l'événement \p event de type begin.
 * L'état de la ligne de balayage décrite par la liste \p status doit être mis
 * à jour. La structure des événements (\p events ) ainsi que la liste des
 * intersections (\p intersections ) seront éventuellement mises à jour si une
 * nouvelle intersection sera détectée (utilisez la procedure
 * test_and_set_intersection).
 *
 * @param[in] event
 * @param[in,out] status
 * @param[in,out] events
 * @param[in,out] intersections
 */
static void handle_begin_event(struct Event * event, struct list_t * status, struct tree_t * events, struct list_t * intersections) {
	assert(event);
	assert(status);
	assert(events);
	assert(intersections);
	// TODO
}

/**
 * Gestion de l'événement \p event de type end.
 * L'état de la ligne de balayage décrite par la liste \p status doit être mis
 * à jour. La structure des événements (\p events ) ainsi que la liste des
 * intersections (\p intersections ) seront éventuellement mises à jour si une
 * nouvelle intersection sera détectée (utilisez la procedure
 * test_and_set_intersection).
 *
 * @param[in] event
 * @param[in,out] status
 * @param[in,out] events
 * @param[in,out] intersections
 */
static void handle_end_event(struct Event * event, struct list_t * status, struct tree_t * events, struct list_t * intersections) {
	assert(event);
	assert(status);
	assert(events);
	assert(intersections);
	// TODO
}

struct list_t * BentleyOttmann(const struct list_t * segments) {
	assert(segments);
	// TODO
}

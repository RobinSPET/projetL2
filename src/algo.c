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
    FILE *file = fopen(input_filename, "r");
    if (!file) { // si le fichier n'a pas pu etre ouvert
        fprintf(stderr, "le fichier est impossible à ouvrir %s\n", input_filename);
        return NULL;
    }

    struct list_t *segment_list = list_create();
    assert(segment_list != NULL);

    int x1, y1, x2, y2;
    while (fscanf(file, "%d/%d %d/%d", &x1, &y1, &x2, &y2) == 4) {
        Segment s = create_segment(x1, y1, x2, y2);
        list_push_back(segment_list, &s, sizeof(Segment));
    }

    fclose(file);
    return segment_list;
}

// Ranger dans un fichier texte de nom output_filename les points d'intersection qui sont contenus dans la liste intersections.

void save_intersections(const char *output_filename, const struct list_t *intersections) {
    FILE *file = fopen(output_filename, "w");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    struct list_node_t *current_node = intersections->head;
    while (current_node) {
        struct Point *point = (struct Point *)get_list_node_data(current_node);

        struct Rational x = get_x(point);
        struct Rational y = get_y(point);

        struct list_node_t *next_node = get_successor(current_node);
        if (next_node) {
            struct Point *next_point = (struct Point *)get_list_node_data(next_node);
            struct Rational next_x = get_x(next_point);
            struct Rational next_y = get_y(next_point);

            fprintf(file, "%lld/%lld,%lld/%lld %lld/%lld,%lld/%lld\n", //correction avec le bon format
                    x.numerator, x.denominator, y.numerator, y.denominator,
                    next_x.numerator, next_x.denominator, next_y.numerator, next_y.denominator);

            current_node = next_node;//prochain segment

        } else {
            break; 
        }
    }
    fclose(file);
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

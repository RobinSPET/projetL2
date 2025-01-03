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
struct list_t *load_segments(const char *input_filename) {
    FILE *file = fopen(input_filename, "r");
    if (!file) {
        fprintf(stderr, "Le fichier est impossible à ouvrir %s\n", input_filename);
        return NULL;
    }

    struct list_t *segment_list = list_create();
    assert(segment_list != NULL);

    long long x1_num, x1_denom, y1_num, y1_denom;
    long long x2_num, x2_denom, y2_num, y2_denom;

    while (fscanf(file, "%lld/%lld,%lld/%lld %lld/%lld,%lld/%lld", &x1_num, &x1_denom, &y1_num, &y1_denom,&x2_num, &x2_denom, &y2_num, &y2_denom) == 8) {
        struct Rational x1 = {x1_num, x1_denom};
        struct Rational y1 = {y1_num, y1_denom};
        struct Rational x2 = {x2_num, x2_denom};
        struct Rational y2 = {y2_num, y2_denom};
        
        struct Point *p1 = new_point(x1, y1);
        struct Point *p2 = new_point(x2, y2);

        struct Segment *s = new_segment(p1, p2);
        list_push_back(segment_list, &s, sizeof(struct Segment));
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

        fprintf(file, "%lld/%lld,%lld/%lld\n",
            get_numerator(x), get_denominator(x), get_numerator(y), get_denominator(y));

        current_node = get_successor(current_node);
    }
    fclose(file);
}

struct list_t * all_pairs(const struct list_t * segments) {
	assert(segments);
	
	struct list_t * intersections = new_list();

	struct list_node_t * noeud1 = get_head(segments);
	while (noeud1){
		struct Segment * s1 = get_list_node_data(noeud1);

		struct list_node_t * noeud2 = get_successor(noeud1);
		while (noeud2){
			struct Segment * s2 = get_list_node_data(noeud2);

			struct Point * intersection = get_intersection_point(s1, s2);
			if (intersection) list_insert_last(segments, intersection);

			noeud2 = get_successeur(noeud2);
		}

		noeud1 = get_successeur(noeud1);
	}
}


///////////////////////////////////////////////////////////////////////////////
//////////////////// ALGORITHME DE Bentley-Ottmann ///////////////////////////
///////////////////////////////////////////////////////////////////////////////

struct Event * new_event(int type, struct Point * event_point, struct Segment * s1, struct Segment * s2) {
	// TODO
	struct Event *event = malloc(sizeof(struct Event));
    if (!event) {
        fprintf(stderr, "il est impossible d'allouer de la mémoire.\n");
        exit(EXIT_FAILURE);
    }
    event->type = type;
    event->event_point = event_point;
    event->s1 = s1;
    event->s2 = s2;
    return event;
}

int get_event_type(const struct Event * event) {
	assert(event);
	return event->type;
}

struct Point * get_event_point(const struct Event * event) {
	assert(event);
	return event->event_point;
}

struct Segment * get_event_segment1(const struct Event * event) {
	assert(event);
	return event->s1;
}

struct Segment * get_event_segment2(const struct Event * event) {
	assert(event);
	return event->s2;
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
	struct tree_t *events = tree_new();

    struct list_node_t *node = list_first(segments);
    while (node != NULL) {
        struct Segment *segment = list_get_data(node);

        struct Event *begin_event = new_event(1, get_endpoint1(segment), segment, NULL);
        tree_insert(events, begin_event, (int (*)(const void *, const void *))event_precedes);

        struct Event *end_event = new_event(2, get_endpoint2(segment), segment, NULL);
        tree_insert(events, end_event, (int (*)(const void *, const void *))event_precedes);

        node = list_next(node);
    }

    return events;
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


	struct Point intersection;

    if (segments_intersect(s1, s2, &intersection)) {
        if (point_precedes(event->event_point, &intersection)) {
            struct Event *existing_event = tree_find(events, &intersection, (int (*)(const void *, const void *))point_equals);

            if (!existing_event) {
                struct Event *intersection_event = new_event(0, &intersection, s1, s2);
                tree_insert(events, intersection_event, (int (*)(const void *, const void *))event_precedes);
                list_append(intersections, &intersection);
            }
        }
    }
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
    struct Segment *s1 = get_event_segment1(event);
    struct Segment *s2 = get_event_segment2(event);

    list_swap(status, s1, s2);

    struct list_node_t *node_s1 = list_find(status, s1);
    struct list_node_t *node_s2 = list_find(status, s2);

    if (node_s1 && list_prev(node_s1)) {
        struct Segment *prev_segment = list_get_data(list_prev(node_s1));
        test_and_set_intersection(prev_segment, s1, event, events, intersections);
    }

    if (node_s2 && list_next(node_s2)) {
        struct Segment *next_segment = list_get_data(list_next(node_s2));
        test_and_set_intersection(next_segment, s2, event, events, intersections);
    }
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
	struct Segment *segment = get_event_segment1(event);
    assert(segment);

    list_insert_sorted(status, segment, (int (*)(const void *, const void *))segment_precedes);

    struct list_node_t *node = list_find(status, segment);
    assert(node);

    if (list_prev(node)) {
        struct Segment *prev_segment = list_get_data(list_prev(node));
        test_and_set_intersection(prev_segment, segment, event, events, intersections);
    }

    if (list_next(node)) {
        struct Segment *next_segment = list_get_data(list_next(node));
        test_and_set_intersection(segment, next_segment, event, events, intersections);
    }
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
	struct Segment *segment = get_event_segment1(event);
    assert(segment);

    struct list_node_t *node = list_find(status, segment);
    if (node) {
        struct list_node_t *prev_node = list_prev(node);
        struct list_node_t *next_node = list_next(node);

        list_remove(status, node);

        if (prev_node && next_node) {
            struct Segment *prev_segment = list_get_data(prev_node);
            struct Segment *next_segment = list_get_data(next_node);
            test_and_set_intersection(prev_segment, next_segment, event, events, intersections);
        }
    }
}

struct list_t * BentleyOttmann(const struct list_t * segments) {
	assert(segments);
	struct list_t *status = list_new();             
    struct list_t *intersections = list_new();      
    struct tree_t *events = initialize_events(segments); 

    struct Event *event;
    while ((event = tree_extract_min(events)) != NULL) {
        switch (get_event_type(event)) {
            case 0: 
                handle_intersection_event(event, status, events, intersections);
                break;
            case 1: 
                handle_begin_event(event, status, events, intersections);
                break;
            case 2: 
                handle_end_event(event, status, events, intersections);
                break;
        }
        free(event); 
    }

    tree_free(events);
    list_free(status);

    return intersections;
}

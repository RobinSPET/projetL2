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
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s\n", input_filename);
        return NULL;
    }

    struct list_t *segment_list = new_list();
    assert(segment_list);

    long long x1_num, x1_denom, y1_num, y1_denom;
    long long x2_num, x2_denom, y2_num, y2_denom;

    while (fscanf(file, "%lld/%lld,%lld/%lld %lld/%lld,%lld/%lld", &x1_num, &x1_denom, &y1_num, &y1_denom, &x2_num, &x2_denom, &y2_num, &y2_denom) == 8) {
        // Vérifier les dénominateurs non nuls
        if (x1_denom == 0 || y1_denom == 0 || x2_denom == 0 || y2_denom == 0) {
            fprintf(stderr, "Erreur : Segment avec dénominateur nul dans %s\n", input_filename);
            continue;
        }

        struct Rational x1 = {x1_num, x1_denom};
        struct Rational y1 = {y1_num, y1_denom};
        struct Rational x2 = {x2_num, x2_denom};
        struct Rational y2 = {y2_num, y2_denom};

        struct Point *p1 = new_point(x1, y1);
        struct Point *p2 = new_point(x2, y2);

        // Vérifier que les deux points ne sont pas identiques
        if (point_precedes(p1, p2) == 0 && point_precedes(p2, p1) == 0) {
            fprintf(stderr, "Erreur : Points identiques dans un segment, ignoré.\n");
            free_point(p1);
            free_point(p2);
            continue;
        }

        struct Segment *s = new_segment(p1, p2);
        list_insert_last(segment_list, s);
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

        printf("call get_x from save\n");
        struct Rational x = get_x(point);
        struct Rational y = get_y(point);

        fprintf(file, "print: %lld/%lld,%lld/%lld\n",
            get_numerator(x), get_denominator(x), get_numerator(y), get_denominator(y));

        current_node = get_successor(current_node);
    }
    fclose(file);
}

struct list_t * all_pairs(const struct list_t * segments) {
	assert(segments);
	
	struct list_t * intersections = new_list();

	struct list_node_t * noeud1 = get_list_head(segments);
	while (noeud1){
		struct Segment * s1 = get_list_node_data(noeud1);

		struct list_node_t * noeud2 = get_successor(noeud1);
		while (noeud2){
			struct Segment * s2 = get_list_node_data(noeud2);

			struct Point * intersection = get_intersection_point(s1, s2);
			if (intersection) list_insert_last(intersections, intersection);

			noeud2 = get_successor(noeud2);
		}

		noeud1 = get_successor(noeud1);
	}

    return intersections;
}


///////////////////////////////////////////////////////////////////////////////
//////////////////// ALGORITHME DE Bentley-Ottmann ///////////////////////////
///////////////////////////////////////////////////////////////////////////////

struct Event * new_event(int type, struct Point * event_point, struct Segment * s1, struct Segment * s2) {
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

void delete_event(struct Event * event){
    assert(event);

    if (get_event_point(event)) free_point(get_event_point(event));
    if (get_event_segment1(event)) free_segment(get_event_segment1(event));
    if (get_event_segment2(event)) free_segment(get_event_segment2(event));

    if (event) {
        free(event);
        event = NULL;
    }
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
	struct tree_t *events = new_tree();

    struct list_node_t *node = get_list_head(segments);

    while (node != NULL) {
        struct Event *begin_event = new_event(1, get_endpoint1(get_list_node_data(node)), get_list_node_data(node), NULL);
        tree_insert(events, get_endpoint1(get_list_node_data(node)), begin_event, point_precedes);
        
        struct Event *end_event = new_event(2, get_endpoint2(get_list_node_data(node)), get_list_node_data(node), NULL);
        tree_insert(events, get_endpoint2(get_list_node_data(node)), end_event, point_precedes);

        node = get_successor(node);
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

    if (do_intersect(s1, s2)) {
        struct Point *intersection = get_intersection_point(s1, s2);

        if (point_precedes(get_event_point(event), intersection)) {

            if (!tree_find_node(get_root(events), intersection, (int (*)(const void *, const void *))point_precedes)) {
                struct Event *intersection_event = new_event(0, intersection, s1, s2);
                tree_insert(events, get_event_point(intersection_event), intersection_event, (int (*)(const void *, const void *))point_precedes);
            }

            if (!list_find_node(intersections, intersection)) {
                list_insert_sorted(intersections, intersection, point_precedes);
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

    if (get_event_type(event) != 0) {
        fprintf(stderr, "Erreur : handle_intersection_event appelé pour un événement non intersection.\n");
        return;
    }
    
    struct Segment *segment1 = get_event_segment1(event);
    struct Segment *segment2 = get_event_segment2(event);

    struct list_node_t *node1 = list_find_node(status, segment1);
    struct list_node_t *node2 = list_find_node(status, segment2);

    if (!node1 || !node2) {
        fprintf(stderr, "Erreur : Segments non trouvés dans la ligne de balayage\n");
        return;
    }
    list_swap_nodes_data(node1, node2);

    printf("handle intersection");
    struct Segment *above = get_predecessor(node1) ? get_list_node_data(get_predecessor(node1)) : NULL;
    struct Segment *below = get_successor(node2) ? get_list_node_data(get_successor(node2)) : NULL;

    if (above) {
        test_and_set_intersection(above, segment1, event, events, intersections);
    }
    if (below) {
        test_and_set_intersection(segment2, below, event, events, intersections);
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

    struct Segment *new_segment = get_event_segment1(event);
    assert(new_segment);

    printf("trying insert..");
    list_insert_sorted(status, new_segment, (int (*)(const void *, const void *))segment_precedes);
    printf("passed !");
    struct list_node_t *node = list_find_node(status, new_segment);

    printf("handle_begin");
    if (node){
        struct Segment *prev_segment = get_predecessor(node) ? (struct Segment *)get_list_node_data(get_predecessor(node)) : NULL;
        struct Segment *next_segment = get_successor(node) ? (struct Segment *)get_list_node_data(get_successor(node)) : NULL;
        printf("passed1");
        if (prev_segment) {
            test_and_set_intersection(prev_segment, new_segment, event, events, intersections);
            printf("passed2");
        }
        if (next_segment) {
            test_and_set_intersection(new_segment, next_segment, event, events, intersections);
            printf("passed3");
        }
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

    struct Segment *end_segment = get_event_segment1(event);

    struct list_node_t *node = list_find_node(status, end_segment);
    if (!node) return; // Si le segment n'est pas trouvé, on ne fait rien.

    struct Segment *prev_segment = NULL;
    struct Segment *next_segment = NULL;

    // récupérer les voisins
    if (get_predecessor(node)) {
        prev_segment = get_list_node_data(get_predecessor(node));
    }
    if (get_successor(node)) {
        next_segment = (struct Segment *)get_list_node_data(get_successor(node));
    }

    list_remove_node(status, node);

    // test d'une nouvelle intersection entre les anciens voisins (s'ils existent)
    if (prev_segment && next_segment) {
        test_and_set_intersection(prev_segment, next_segment, event, events, intersections);
    }
}

struct list_t * BentleyOttmann(const struct list_t * segments) {
    assert(segments);

    struct tree_t *events = initialize_events(segments); 
    struct list_t *status = new_list();                   
    struct list_t *intersections = new_list();            

    while (!tree_is_empty(events)) {
        // extrait l'événement avec la plus petite coordonnée
        struct Event *event = tree_remove(events, get_tree_node_key(tree_find_min(get_root(events))), point_precedes);

        switch (get_event_type(event)) {
            case 1:
                handle_begin_event(event, status, events, intersections);
                break;

            case 2: 
                handle_end_event(event, status, events, intersections);
                break;

            case 0: 
                handle_intersection_event(event, status, events, intersections);
                break;

            default:
                // type d'événement inconnu
                assert(0 && "Type d'événement inconnu !");
                break;
        }

        // Libérer la mémoire de l'événement traité (alloué dynamiquement)
        delete_event(event);
    }

    // Libération des variables temporaires
    delete_tree(events, (void (*)(void *))free_point, (void (*)(void *))free_segment); // cast pour faire passer les pointeurs des fonctions
    delete_list(status, free_segment);

    // Retourner la liste des intersections détectées
    return intersections;
}

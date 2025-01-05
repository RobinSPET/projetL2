#include "list.h"
#include "geometry.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "util.h"

/********************************************************************
 * list_node_t
 ********************************************************************/

/**
 * Construit et initialise un nouveau nœud d'une liste doublement chaînée.
 * Le paramètre \p data correspond à la donnée à affecter au nouveau nœud.
 * 
 * @param[in] data
 * @return le nouveau nœud créé
 */
static struct list_node_t * new_list_node(void * data) {
	
    struct list_node_t *node = malloc(sizeof(struct list_node_t));
    if (!node) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
	
    node->data = data;
    node->successor = NULL;
    node->predecessor = NULL;

    return node;
}

void *get_list_node_data(const struct list_node_t *node) {
    assert(node); 
    return node->data;
}

struct list_node_t *get_successor(const struct list_node_t *node) {
    assert(node); 
    return node->successor;
}

struct list_node_t *get_predecessor(const struct list_node_t *node) {
    assert(node); 
    return node->predecessor;
}

void set_list_node_data(struct list_node_t *node, void *new_data) {
    assert(node); 
    node->data = new_data; 
}

void set_successor(struct list_node_t *node, struct list_node_t *new_successor) {
    assert(node); 
    node->successor = new_successor; 
}

void set_predecessor(struct list_node_t *node, struct list_node_t *new_predecessor) {
    assert(node); 
    node->predecessor = new_predecessor; 
}

/********************************************************************
 * list_t (Double-Linked List)
 ********************************************************************/

struct list_t * new_list() {
	struct list_t *L = malloc(sizeof(struct list_t));
    if (!L) {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour la liste\n");
        exit(EXIT_FAILURE);
    }

    L->head = NULL;
    L->tail = NULL;
    L->size = 0;

    return L;
}

int list_is_empty(const struct list_t * L) {
	assert(L);
	return (L->size == 0);
}

unsigned int get_list_size(const struct list_t * L) {
	assert(L);
	return L->size;
}

struct list_node_t * get_list_head(const struct list_t * L) {
	assert(L);
	return L->head;
}

struct list_node_t * get_list_tail(const struct list_t * L) {
	assert(L);
	return L->tail;
}

void increase_list_size(struct list_t * L) {
	assert(L);
	L->size++;
}

void decrease_list_size(struct list_t * L) {
	assert(L);
	if (L->size > 0) {
        L->size--;
    } else {
        fprintf(stderr, "Erreur : Impossible de réduire une liste de taille nulle\n");
    }
}

void set_list_size(struct list_t * L, unsigned int new_size) {
	assert(L);
	L->size = new_size;
}

void set_list_head(struct list_t * L, struct list_node_t * new_head) {
	assert(L);
	L->head = new_head;
}

void set_list_tail(struct list_t * L, struct list_node_t * new_tail) {
	assert(L);
	L->tail = new_tail;
}

void delete_list(struct list_t * L, void (*freeData)(void *)) {
	assert(L);
	struct list_node_t *current = get_list_head(L);

    while (current) {
        if (freeData && get_list_node_data(current)) {
            freeData(get_list_node_data(current));
        }

        if (current) free(current); 
        current = current->successor;
    }

    if (L) {
        free(L); 
        L = NULL;
    }
}

void view_list(const struct list_t * L, void (*viewData)(const void *)) {
	assert(L);
	struct list_node_t *current = L->head;
    while (current) {
        viewData(current->data); 
        current = current->successor;
    }
}

int is_node_already_in_list(struct list_t *L, void *data){
    assert(L);
    assert(data);

    struct list_node_t * curr = get_list_head(L);
    while(curr){
        if (curr == get_list_node_data(data)) return 1;
        curr = get_successor(curr);
    }
    return 0;
}

void list_insert_first(struct list_t * L, void * data) {
	assert(L);
    assert(!is_node_already_in_list(L, data));

	struct list_node_t *new_node = new_list_node(data);
    new_node->predecessor = NULL;

    if (L->head) {
        new_node->successor = L->head;
        L->head->predecessor = new_node;
    }
    L->head = new_node;
    
    increase_list_size(L);
}

void list_insert_last(struct list_t * L, void * data) {
	assert(L);
    assert(!is_node_already_in_list(L, data));

	struct list_node_t *new_node = new_list_node(data);
    new_node->successor = NULL;

    if (L->tail) {
        new_node->predecessor = L->tail;
        L->tail->successor = new_node;

    } else {
        L->head = new_node; 
    }
    L->tail = new_node;
    increase_list_size(L);
}

void list_insert_after(struct list_t * L, void * data, struct list_node_t * node) {
	assert(L);
	assert(node);
    assert(!is_node_already_in_list(L, data));

	struct list_node_t *new_node = new_list_node(data);

    new_node->predecessor = node;
    new_node->successor = node->successor;

    if (node->successor) {
        node->successor->predecessor = new_node;
    } else {
        L->tail = new_node; 
    }
    node->successor = new_node;
    increase_list_size(L);
}

void print_list(struct list_t *L){
    assert(L);

    struct list_node_t *curr = get_list_head(L);
    while (curr){
        printf("========== List ==========");
        print_segment(get_list_node_data(curr));
        printf("=========================="); 

        curr = get_successor(curr);
    }
}

void list_insert_sorted(struct list_t *list, void *data, int (*comparator)(const void *, const void *)) {
    assert(list);
    assert(data);
    assert(comparator);
    assert(!is_node_already_in_list(list, data));

    if (get_list_head(list)){
        struct list_node_t *current = get_list_head(list);
        if (!current) {
            fprintf(stderr, "Erreur : Tentative d'accès à un nœud NULL dans list_insert_sorted.\n");
            return;
        }
        if (!current->data) {
            fprintf(stderr, "Erreur : Le champ data d'un nœud est NULL.\n");
            return;
        }

        while (current && comparator(current->data, data) < 0) {
            current = get_successor(current);
        }

        if (!current) {
            list_insert_last(list, data);  // Ajout en fin de liste
        } else if (current == get_list_head(list)) {
            list_insert_first(list, data);  // Ajout en début de liste
        } else {
            if (!current->data || !get_predecessor(current)) {
                fprintf(stderr, "Erreur : Donnée NULL rencontrée lors de la comparaison.\n");
                return;
            }
            list_insert_after(list, data, get_predecessor(current));  // Ajout au milieu
        }
    } else {
        list_insert_last(list, data);
    }
}

void * list_remove_first(struct list_t * L) {
	assert(L);
	
    if (!L->head) {
        fprintf(stderr, "Erreur de tentative de suppression dans une liste vide\n");
        return NULL;
    }

    struct list_node_t *old_head = L->head;
    void *data = old_head->data;

    L->head = old_head->successor;

    free(old_head);
    decrease_list_size(L);

    return data;                           
}

void * list_remove_last(struct list_t * L) {
	assert(L);

	if (!L->tail) {
        fprintf(stderr, "Erreur de tentative de suppression dans une liste vide\n");
        return NULL;
    }

    struct list_node_t *old_tail = L->tail; 
    void *data = old_tail->data;           

    L->tail = old_tail->predecessor;       

    free(old_tail);
    decrease_list_size(L);

    return data;
}

void * list_remove_node(struct list_t * L, struct list_node_t * node) {
	assert(L);
	assert(node);

    if (node->predecessor) node->predecessor->successor = node->successor; 

    if (node->successor) node->successor->predecessor = node->predecessor; 

    void *data = node->data;
    free(node);              
    decrease_list_size(L);   
    return data;
}

struct list_node_t * list_find_node(struct list_t * L, void * data) {
	assert(L);
	struct list_node_t *current = L->head;

    while (current) {
        if (current->data == data) { 
            return current; 
        }
        current = current->successor; 
    }
    return NULL;
}

void list_swap_nodes_data(struct list_node_t * node1, struct list_node_t * node2) {
	assert(node1);
	assert(node2);
	
    void *temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}
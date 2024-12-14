#include "list.h"

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
	// TODO
}

int list_is_empty(const struct list_t * L) {
	assert(L);
	// TODO
}

unsigned int get_list_size(const struct list_t * L) {
	assert(L);
	// TODO
}

struct list_node_t * get_list_head(const struct list_t * L) {
	assert(L);
	// TODO
}

struct list_node_t * get_list_tail(const struct list_t * L) {
	assert(L);
	// TODO
}

void increase_list_size(struct list_t * L) {
	assert(L);
	// TODO
}

void decrease_list_size(struct list_t * L) {
	assert(L);
	// TODO
}

void set_list_size(struct list_t * L, unsigned int new_size) {
	assert(L);
	// TODO
}

void set_list_head(struct list_t * L, struct list_node_t * new_head) {
	assert(L);
	// TODO
}

void set_list_tail(struct list_t * L, struct list_node_t * new_tail) {
	assert(L);
	// TODO
}

void delete_list(struct list_t * L, void (*freeData)(void *)) {
	assert(L);
	// TODO
}

void view_list(const struct list_t * L, void (*viewData)(const void *)) {
	assert(L);
	// TODO
}

void list_insert_first(struct list_t * L, void * data) {
	assert(L);
	// TODO
}

void list_insert_last(struct list_t * L, void * data) {
	assert(L);
	// TODO
}

void list_insert_after(struct list_t * L, void * data, struct list_node_t * node) {
	assert(L);
	assert(node);
	// TODO
}

void * list_remove_first(struct list_t * L) {
	assert(L);
	assert(get_list_head(L) && get_list_tail(L));
	// TODO
}

void * list_remove_last(struct list_t * L) {
	assert(L);
	assert(get_list_head(L) && get_list_tail(L));
	// TODO
}

void * list_remove_node(struct list_t * L, struct list_node_t * node) {
	assert(L);
	assert(get_list_head(L) && get_list_tail(L));
	// TODO
}

struct list_node_t * list_find_node(struct list_t * L, void * data) {
	assert(L);
	// TODO
}

void list_swap_nodes_data(struct list_node_t * node1, struct list_node_t * node2) {
	assert(node1);
	assert(node2);
	// TODO
}
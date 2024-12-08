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
	// Allouer la mémoire pour le nouveau nœud
    struct list_node_t *node = malloc(sizeof(struct list_node_t));
    if (!node) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
	// Initialiser les champs du nœud
    node->data = data;
    node->successor = NULL;
    node->predecessor = NULL;

    return node;
}

void *get_list_node_data(const struct list_node_t *node) {
    assert(node); // Vérifie que le pointeur est non nul
    return node->data;
}

struct list_node_t *get_successor(const struct list_node_t *node) {
    assert(node); // Vérifie que le pointeur est non nul
    return node->successor;
}

struct list_node_t *get_predecessor(const struct list_node_t *node) {
    assert(node); // Vérifie que le pointeur est non nul
    return node->predecessor;
}

void set_list_node_data(struct list_node_t *node, void *new_data) {
    assert(node); // Vérifie que le pointeur est non nul
    node->data = new_data; // Met à jour le champ 'data'
}

void set_successor(struct list_node_t *node, struct list_node_t *new_successor) {
    assert(node); // Vérifie que le pointeur est non nul
    node->successor = new_successor; // Met à jour le champ 'successor'
}

void set_predecessor(struct list_node_t *node, struct list_node_t *new_predecessor) {
    assert(node); // Vérifie que le pointeur est non nul
    node->predecessor = new_predecessor; // Met à jour le champ 'predecessor'
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
	struct list_node_t *current = L->head;
    struct list_node_t *next;

    while (current) {
        next = current->successor;

        if (freeData) {
            freeData(current->data); // Libère les données du nœud si nécessaire
        }

        free(current); // Libère le nœud
        current = next;
    }

    free(L); // Libère la structure de la liste
}

void view_list(const struct list_t * L, void (*viewData)(const void *)) {
	assert(L);
	struct list_node_t *current = L->head;
    while (current) {
        viewData(current->data); // Applique la fonction de visualisation aux données
        current = current->successor;
    }
}

void list_insert_first(struct list_t * L, void * data) {
	assert(L);
	struct list_node_t *new_node = new_list_node(data);
    if (L->head) {
        new_node->successor = L->head;
        L->head->predecessor = new_node;
    } else {
        L->tail = new_node; // Si la liste était vide, le nouvel élément devient aussi la queue
    }
    L->head = new_node;
    increase_list_size(L);
}

void list_insert_last(struct list_t * L, void * data) {
	assert(L);
	struct list_node_t *new_node = new_list_node(data);
    if (L->tail) {
        new_node->predecessor = L->tail;
        L->tail->successor = new_node;
    } else {
        L->head = new_node; // Si la liste était vide, le nouvel élément devient aussi la tête
    }
    L->tail = new_node;
    increase_list_size(L);
}

void list_insert_after(struct list_t * L, void * data, struct list_node_t * node) {
	assert(L);
	assert(node);
	struct list_node_t *new_node = new_list_node(data);
    new_node->successor = node->successor;
    new_node->predecessor = node;

    if (node->successor) {
        node->successor->predecessor = new_node;
    } else {
        L->tail = new_node; // Si le nœud donné est la queue, met à jour la queue
    }
    node->successor = new_node;
    increase_list_size(L);
}

void * list_remove_first(struct list_t * L) {
	assert(L);
	assert(get_list_head(L) && get_list_tail(L));
	struct list_node_t *old_head = L->head;
    void *data = old_head->data;

    L->head = old_head->successor;
    if (L->head) {
        L->head->predecessor = NULL;
    } else {
        L->tail = NULL; // Si la liste devient vide, met aussi à jour la queue
    }
    free(old_head);
    decrease_list_size(L);

    return data;
}

void * list_remove_last(struct list_t * L) {
	assert(L);
	assert(get_list_head(L) && get_list_tail(L));
	struct list_node_t *old_tail = L->tail;
    void *data = old_tail->data;

    L->tail = old_tail->predecessor;
    if (L->tail) {
        L->tail->successor = NULL;
    } else {
        L->head = NULL; // Si la liste devient vide, met aussi à jour la tête
    }
    free(old_tail);
    decrease_list_size(L);

    return data;
}

void * list_remove_node(struct list_t * L, struct list_node_t * node) {
	assert(L);
	assert(get_list_head(L) && get_list_tail(L));
	if (node->predecessor) {
        node->predecessor->successor = node->successor;
    } else {
        L->head = node->successor; // Si c'est la tête, met à jour la tête
    }

    if (node->successor) {
        node->successor->predecessor = node->predecessor;
    } else {
        L->tail = node->predecessor; // Si c'est la queue, met à jour la queue
    }

    void *data = node->data;
    free(node);
    decrease_list_size(L);

    return data;
}

struct list_node_t * list_find_node(struct list_t * L, void * data) {
	assert(L);
	struct list_node_t *current = L->head;
    while (current) {
        if (current->data == data) { // Vérifie si la donnée correspond (même si elle est NULL)
            return current; // Retourne le nœud trouvé
        }
        current = current->successor; // Passe au nœud suivant
    }
    return NULL; // Retourne NULL si la donnée n'est pas trouvée
}

void list_swap_nodes_data(struct list_node_t * node1, struct list_node_t * node2) {
	assert(node1);
	assert(node2);
	// Échange les données entre les deux nœuds
    void *temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}
#include "tree.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

/********************************************************************
 * tree_node_t
 ********************************************************************/

/**
 * Construit et initialise un nouveau nœud d'un arbre binaire de recherche.
 * Le facteur d'équilibre est initialisé à zero.
 * 
 * @param[in] key Clé du nouveau nœud.
 * @param[in] data Donnée à affecter au nouveau nœud.
 * @return le nouveau nœud créé
 */
static struct tree_node_t * new_tree_node(void * key, void * data) {
	struct tree_node_t *t = (struct Point *)malloc(sizeof(struct tree_node_t));

	if (t == NULL) {
		perror("Erreur d'allocation mémoire");
		return NULL;
	}

    t->key = key;
    t->data = data;
	t->left = NULL;
	t->right = NULL;

    return t;
}

void * get_tree_node_key(const struct tree_node_t * node) {
	assert(node);
	return node->key;
}

void * get_tree_node_data(const struct tree_node_t * node) {
	assert(node);
	return node->data;
}

struct tree_node_t * get_left(const struct tree_node_t * node) {
	assert(node);
	return node->left;
}

struct tree_node_t * get_right(const struct tree_node_t * node) {
	assert(node);
	return node->right;
}

void set_tree_node_key(struct tree_node_t * node, void * new_key) {
	assert(node);
	node->key = new_key;
}

void set_tree_node_data(struct tree_node_t * node, void * new_data) {
	assert(node);
	node->data = new_data;
}

void set_left(struct tree_node_t * node, struct tree_node_t * new_left) {
	assert(node);
	node->left = new_left;
}

void set_right(struct tree_node_t * node, struct tree_node_t * new_right) {
	assert(node);
	node->right = new_right;
}

/*********************************************************************
 * tree_t
 *********************************************************************/

struct tree_t * new_tree() {
	// TODO
}

int tree_is_empty(const struct tree_t * T) {
	assert(T);
	// TODO
}

unsigned int get_tree_size(const struct tree_t * T) {
	assert(T);
	// TODO
}

struct tree_node_t * get_root(const struct tree_t * T) {
	assert(T);
	// TODO
}

void increase_tree_size(struct tree_t * T) {
	assert(T);
	// TODO
}

void decrease_tree_size(struct tree_t * T) {
	assert(T);
	// TODO
}

void set_root(struct tree_t * T, struct tree_node_t * new_root) {
	assert(T);
	// TODO
}

/**
 * Libérer récursivement le sous-arbre raciné au nœud \p curr .
 * Dans le cas où le pointeur de fonction \p freeKey (respectivement
 * \p freeData ) n'est pas NULL, la mémoire de la clé (respectivement de la
 * donnée) du nœud actuel est aussi libérée.
 * NB : procédure récursive.
 * 
 * @param[in] curr
 * @param[in] freeKey 
 * @param[in] freeData 
 */
static void delete_tree_node(struct tree_node_t * curr, void (*freeKey)(void *), void (*freeData)(void *)) {
	// TODO
}

// NB : Utiliser la procédure récursive delete_tree_node.
void delete_tree(struct tree_t * T, void (*freeKey)(void *), void (*freeData)(void *)) {
	assert(T);
	// TODO
}

/**
 * Afficher récursivement le sous-arbre raciné au nœud \p curr en utilisant un
 * ordre infixe.
 * NB : procédure récursive.
 *
 * @param[in] curr 
 * @param[in] viewKey 
 * @param[in] viewData 
 */
static void view_tree_inorder(struct tree_node_t * curr, void (*viewKey)(const void *), void (*viewData)(const void *)) {
	// TODO
}

// NB : Utiliser la procédure récursive view_tree_inorder.
void view_tree(const struct tree_t * T, void (*viewKey)(const void * key), void (*viewData)(const void * data)) {
	assert(T);
	// TODO
}

/**
 * Insérer un nouveau nœud de clé \p key et de donnée \p data au sous-arbre
 * binaire de recherche raciné au nœud \p curr .
 * Les clés sont comparées en utilisant le pointeur de fonction \p precedes .
 * Le nœud curant \p curr est en entrée/sortie et doit être mis à jour.
 * NB : fonction récursive.
 * 
 * @param[in,out] curr
 * @param[in] key 
 * @param[in] data 
 * @param[in] precedes
 */
static void insert_tree_node(struct tree_node_t ** curr, void * key, void * data,
							int (*precedes)(const void *, const void *)) {
	// TODO
}

// NB : Utiliser la fonction récursive insert_tree_node.
void tree_insert(struct tree_t * T, void * key, void * data, int (*precedes)(const void * a, const void * b)) {
	assert(T);
	// TODO
}

struct tree_node_t * tree_find_min(struct tree_node_t * curr) {
	assert(curr);
	// TODO
}

struct tree_node_t * tree_find_max(struct tree_node_t * curr) {
	assert(curr);
	// TODO
}

struct tree_node_t * tree_find_node(struct tree_node_t * curr, const void * key, int (*precedes)(const void *, const void *)) {
	// TODO
}

struct tree_node_t * tree_find_predecessor(struct tree_node_t * curr, const void * key, int (*precedes)(const void *, const void *)) {
	assert(curr);
	// TODO
}

struct tree_node_t * tree_find_successor(struct tree_node_t * curr, const void * key, int (*precedes)(const void *, const void *)) {
	assert(curr);
	// TODO
}

/**
 * Supprimer le nœud de clé \p key du sous-arbre binaire de recherche raciné au
 * nœud \p curr . La donnée du nœud supprimé est restituée, tandis que la
 * mémoire du nœud avec clé \p key est libérée (mais pas la mémoire de la clé).
 * Les clés sont comparées en utilisant le pointeur de fonction \p precedes.
 * Le nœud curant \p curr est en entrée/sortie et doit être mis à jour.
 * NB : fonction récursive.
 * 
 * @param[in,out] curr
 * @param[in] key
 * @param[in] precedes
 * @return la donnée du nœud supprimé
 */
static void * remove_tree_node(struct tree_node_t ** curr, void * key, int (*precedes)(const void *, const void *)) {
	assert(curr);
	// TODO
}

// NB : Utiliser la fonction récursive remove_tree_node.
void * tree_remove(struct tree_t * T, void * key, int (*precedes)(const void * a, const void * b)) {
	assert(T);
	// TODO
}
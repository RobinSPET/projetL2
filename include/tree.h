#pragma once

struct tree_node_t {
    void * key ;
    void * data ;
    struct tree_node_t * left ;
    struct tree_node_t * right ;
};
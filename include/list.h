#pragma once

struct list_node_t {
    void * data;
    struct list_node_t * successor, * predecessor;
};

struct list_t {
    struct list_node_t * head , * tail ;
    unsigned int size ;
};
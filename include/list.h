#pragma once

struct list_node_t {
    void * data;
    struct list_node_t * successor, * predecessor;
};
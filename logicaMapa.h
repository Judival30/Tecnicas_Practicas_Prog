#ifndef LOGICA_MAPA_H
#define LOGICA_MAPA_H

#include "logicaInicial.h"

#define VERTEX_NUMBER 5

/* Prototipos para las funciones de lista. */
Node *create_vertex_node(int data);
List create_simple_list();
void add_node_to_list(List *list, int data);
void print_simple_list(List list);

/* Prototipos para las funciones propias del grafo. */
void create_graph(List *arr);
void add_node_to_graph(List *arr, int node, int data);
void print_graph(List *graph);

#endif
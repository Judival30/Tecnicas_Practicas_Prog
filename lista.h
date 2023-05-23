#ifndef LISTA_H
#define LISTA_H
#include <stdio.h>
/* Estructuras necesarias para representar el grafo. */
typedef struct Objeto
{
    char *data;
    struct Objeto *next;
} Objeto;

typedef struct List
{
    int size;
    Objeto *head;
} List;
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

/* Funciones de tratado de lista para inventario */
List create_list();
Objeto *create_node(char *data);
void push(List *list, char *data);
void pop(List *list);
void print_list(List list);

#endif
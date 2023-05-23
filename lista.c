#include "prototipos.h"

List create_list()
{
    List list;
    list.size = 0;
    list.head = NULL;
    return list;
}
Objeto *create_node(char *data)
{
    Objeto *node = (Objeto *)malloc(sizeof(Objeto));
    node->data = (char *)malloc(strlen(data) + 1);
    strcpy(node->data, data);
    node->next = NULL;
    return node;
}
void pop(List *list)
{
    if (list->size == 0)
    {
        printf("Lista vacía.\n");
        return;
    }
    Objeto *ref = NULL;
    Objeto *n = list->head;
    while (n->next != NULL)
    {
        ref = n;
        n = n->next;
    }
    if (ref == NULL)
    {
        list->head = NULL;
    }
    else
    {
        ref->next = NULL;
    }
    free(n->data);
    free(n);
    list->size--;
}
void push(List *l, char *data)
{
    Objeto *node = create_node(data);
    if (l->size == 0)
    {
        l->head = node;
    }
    else
    {
        Objeto *n = l->head;
        while (n->next != NULL)
        {
            n = n->next;
        }
        n->next = node;
    }
    l->size += 1;
}
void print_list(List list)
{

    int i = 0;
    Objeto *tmp = list.head;
    while (i < list.size)
    {
        printf("%d. %s\n", i + 1, tmp->data);
        tmp = tmp->next;
        i += 1;
    }
}
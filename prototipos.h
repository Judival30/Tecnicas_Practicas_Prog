#ifndef LOGICA_CENTRAL
#define LOGICA_CENTRAL

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*Constantes:*/
// Menu principal
#define EXPLORAR 1
#define AVANZAR 2
#define ESTADISTICAS 3
#define INVENTARIO 4
#define BESTIARIO 5
#define SALIR 6

// explorar:
#define ANTORCHA 1
#define OBJETO 2
#define FUENTE_HABILIDAD 3
#define NADA 0

// pelea
#define ATAQUE_LIGERO 1
#define ATAQUE_PESADO 2
#define PARRY 3

// Clases de jugador
#define GUERRERO 1
#define MAGO 2
#define LADRON 3
#define CLERICO 4

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

typedef struct Enemy
{
    char *name;
    int vida;
    char *descrip;
} Enemy;

typedef struct Jugador
{
    char *name;
    int vida;
    int stamina;
    int dano;
    int agilidad;
    int fuenteHabilidad;
    List Inventario;
    char clase[9];

} Jugador;

/*Prototipos*/

// Funciones que inician las estructuras
void inicializar_jugador(Jugador *jug, char *n);
void inicializar_enemy(Enemy *ene, char *n, int v, char *des);
// Funciones de tratado de lista para inventario
List create_list();
Objeto *create_node(char *data);
void push(List *list, char *data);
void pop(List *list);
void print_list(List list);
// Funciones de logica central
void menu();
void menuPrincipal(Jugador *jug, Enemy *enemys);
void bestiario(Enemy *enemys);
void printLinea();
void explorar(Jugador *jud);
Enemy pelea(int x, Jugador *jug, Enemy *enemys);
void inventario(Jugador *jug);
void estadisticas(Jugador *jug);
// dibujos
void dibujo();
#endif
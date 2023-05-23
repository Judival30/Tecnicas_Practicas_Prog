#ifndef LOGICA_INICIAL
#define LOGICA_INICIAL

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "funcionesAux.h"
#include "lista.h"
#include "logicaBatalla.h"

// Menu principal
#define EXPLORAR 1
#define AVANZAR 2
#define ESTADISTICAS 3
#define INVENTARIO 4
#define BESTIARIO 5
#define SALIR 6

// Clases de jugador
#define GUERRERO 1
#define MAGO 2
#define LADRON 3
#define CLERICO 4

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

// Funciones que inician las estructuras
void inicializar_jugador(Jugador *jug, char *n);
void inicializar_enemy(Enemy *ene, char *n, int v, char *des);
void menu();
void menuPrincipal(Jugador *jug, Enemy *enemys);

#endif

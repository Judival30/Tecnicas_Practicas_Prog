#ifndef LOGICA_BATALLA
#define LOGICA_BATALLA

#include "logicaInicial.h"

// pelea
#define ATAQUE_LIGERO 1
#define ATAQUE_PESADO 2
#define PARRY 3

Enemy pelea(int x, Jugador *jug, Enemy *enemys);

#endif
#ifndef LOGICA_CENTRAL
#define LOGICA_CENTRAL

#include "logicaInicial.h"
#include "logicaMapa.h"

// explorar:
#define ANTORCHA 1
#define OBJETO 2
#define FUENTE_HABILIDAD 3
#define NADA 0

void explorar(Jugador *jud);
void inventario(Jugador *jug);
void estadisticas(Jugador *jug);
void bestiario(Enemy *enemys);
// void avanzar();

#endif
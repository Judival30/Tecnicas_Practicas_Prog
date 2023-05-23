#include "prototipos.h"

Enemy pelea(int x, Jugador *jug, Enemy *enemys)
{

    int vidaIniBoss = enemys[x].vida;
    int vidaIniJugador = jug->vida;
    int staminaIni = jug->stamina;
    int ataque;
    int prob, probEnemy;
    while (jug->vida > 0 && enemys[x].vida > 0)
    {
        printf("\nJefe: %s\nVida Jefe: %d/%d", enemys[x].name, enemys[x].vida, vidaIniBoss);
        printf("\nJugador\nVida: %d/%d\nStamina: %d/%d", jug->vida, vidaIniJugador, jug->stamina, staminaIni);

        printf("\n");
        printf("\nTipos de ataque:\n1.Ataque ligero\n2.Ataque pesado\n3.Parry\nSeleccione una opcion > ");
        scanf("%d", &ataque);
        printLinea();

        switch (ataque)
        {
        case ATAQUE_LIGERO:

            enemys[x].vida -= jug->dano / 2;
            jug->stamina -= 2;

            printf("\nAtaque ligero efectivo");

            // El enemigo tiene 80% de acierto
            srand(time(NULL));
            probEnemy = rand() % 11;
            if (probEnemy <= 8)
            {
                jug->vida -= 250;
                printf("\nUn ataque enemigo te ha impactado");
            }
            else
            {
                printf("\nEl enemigo ha fallado su ataque, es tu turno");
            }

            break;

        case ATAQUE_PESADO:

            if (jug->stamina > 3)
            {
                // Probabilida de acierto del ataque
                srand(time(NULL));
                prob = jug->agilidad - rand() % 5;
                if (prob >= 6)
                {
                    enemys[x].vida -= jug->dano;
                    printf("\nAtaque pesado efectivo");
                    jug->stamina -= 3;
                }
                else
                {
                    printf("\nEl ataque ha fallado, pierdes el turno");
                }
            }

            // El enemigo tiene 80% de acierto
            srand(time(NULL));
            probEnemy = rand() % 11;
            if (probEnemy <= 8)
            {
                jug->vida -= 250;
                printf("\nUn ataque enemigo te ha impactado");
            }
            else
            {
                printf("\nEl enemigo ha fallado su ataque, es tu turno");
            }

            break;

        case PARRY:
            // Probabilidad del parry
            srand(time(NULL));
            prob = jug->agilidad - rand() % 5;
            if (prob >= 7)
            {
                enemys[x].vida -= jug->dano * 2;
                printf("\nHas noqueado al enemigo y ha sufrido mucho dano");
            }
            jug->stamina -= 4;

            break;
        }
        jug->stamina += 2;
    }
    if (jug->vida <= 0)
    {
        printf("\nHas muerto");
    }
    else
    {
        printf("\nFelicidades, has conseguido vencer a %s", enemys[x].name);
        enemys[x].vida = 0;
    }
    return enemys[x];
}
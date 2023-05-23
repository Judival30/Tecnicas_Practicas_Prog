#include "prototipos.h"

void explorar(Jugador *jud)
{
    int option, i, save, k, j;
    int arreglo[10] = {1, 1, 2, 2, 2, 3, 3, 0, 0, 0};

    char objetos[8][10] = {"Espada", "Escudo", "Arco", "Flechas", "Veneno", "Armadura", "Pandeyuca", "Talisman"};
    srand(time(NULL));
    i = rand() % 10;
    switch (arreglo[i])
    {
    case NADA:
        printLinea();
        printf("\nNo has encontrado nada\nVolviendo al menu...");

        break;
    case ANTORCHA:
        printLinea();
        printf("\nHas encontrado una antorcha!\nDesea guardar la partida?\n1.Si\n2.No\nSelecciona una opcion >");
        scanf("%d", &save);
        if (save == 1)
        {
            printf("\nGuardando la partida...\nSe ha guardado correctamente\nVolviendo al menu");
        }
        else if (save == 2)
        {
            printf("\nVolviendo al menu...");
        }
        else
        {
            printf("\nLa opcion ingresada no existe\nVolviendo al menu");
        }

        break;
    case OBJETO:
        srand(time(NULL));
        k = rand() % 8;
        printLinea();
        printf("\nHas encontrado: %s", objetos[k]);
        push(&(jud->Inventario), objetos[k]);

        break;
    case FUENTE_HABILIDAD:
        printLinea();
        printf("\nHas encontrado una fuente de habilidad");
        jud->fuenteHabilidad++;
        break;
    default:
        break;
    }
}
void inventario(Jugador *jug)
{
    printLinea();
    if ((jug->Inventario).size == 0)
    {
        printf("\nEl inventario está vacio\nExplora para adquirir objetos");
    }
    else
    {
        printf("\nInventario:\n");
        print_list(jug->Inventario);
    }
}

void estadisticas(Jugador *jug)
{
    printLinea();
    printf("\nClase: %s\nVida restante: %d\nAgilidad %d\nStamina %d\nDano %d", jug->clase, jug->vida, jug->agilidad, jug->stamina, jug->dano);
}

void bestiario(Enemy *enemys)
{

    int i = 0;
    char *space;
    printf("\nBestiario:");
    for (i = 0; i < 4; i++)
    {
        if (enemys[i].vida == 0)
        {
            printf("\n\n%s\nVida: %d\nDescripcion: %s",
                   enemys[i].name, enemys[i].vida, enemys[i].descrip);
        }
    }
    printf("\n");
}
#include "prototipos.h"

void inicializar_jugador(Jugador *jug, char *n)
{
    int clase;
    printf("\nSelecciona una clase:\n\n1. Guerrero: Vida: 2000, Stamina: 20, Dano: 750, Agilidad: 5.\n\nLos guerreros tienen mucha vida y resistencia, lo que les permite aguantar mucho daño y\n mantenerse en pie durante mucho tiempo en el campo de batalla. Aunque no son muy agiles, su\n fuerza y habilidad con armas pesadas les permiten infligir un gran dano.\n\n2. Mago: Vida: 750, Stamina: 10, Dano: 200, Agilidad: 13.\n\nLos magos no tienen mucha vida ni resistencia fisica, pero su habilidad con la magia les permite \ncausar un gran dano a distancia. Son muy agiles y pueden evadir los ataques enemigos con\n facilidad, pero necesitan gestionar su stamina cuidadosamente para no quedarse sin mana durante \nuna pelea.\n\n3. Ladron: Vida: 1000, Stamina: 15, Dano: 500, Agilidad: 12.\n\nLos ladrones tienen una vida y resistencia media, pero son muy ágiles y hábiles con armas agiles\n como dagas y arcos. Pueden infligir un gran dano con ataques criticos y pueden desactivar trampas\n y abrir cerraduras.\n\n4. Clerigo: Vida: 1500, Stamina: 15, Dano: 300, Agilidad: 8.\n\nLos clerigos tienen una vida y resistencia media, pero su habilidad con la magia divina les permite\n curar a los aliados y causar un dano magico a los enemigos. No son muy agiles, pero\n tienen habilidades para proteger a sus aliados y resistir el dano mágico.\n\nElija una opcion>");
    jug->name = (char *)malloc(strlen(n) + 1);
    strcpy(jug->name, n);
    scanf("%d", &clase);
    switch (clase)
    {
    case GUERRERO:
        jug->vida = 2000;
        jug->stamina = 20;
        jug->dano = 750;
        jug->agilidad = 5;
        strcpy(jug->clase, "Guerrero");
        break;
    case MAGO:
        jug->vida = 750;
        jug->stamina = 10;
        jug->dano = 200;
        jug->agilidad = 13;
        strcpy(jug->clase, "Mago");
        break;
    case LADRON:
        jug->vida = 1000;
        jug->stamina = 15;
        jug->dano = 500;
        jug->agilidad = 12;
        strcpy(jug->clase, "Ladron");
        break;
    case CLERICO:
        jug->vida = 1500;
        jug->stamina = 15;
        jug->dano = 300;
        jug->agilidad = 8;
        strcpy(jug->clase, "Clerico");
        break;
    default:
        break;
    }
    jug->fuenteHabilidad = 0;
    jug->Inventario = create_list();
}

void inicializar_enemy(Enemy *ene, char *n, int v, char *des)
{
    ene->name = (char *)malloc(strlen(n) + 1);
    strcpy(ene->name, n);
    ene->vida = v;
    ene->descrip = (char *)malloc(strlen(des) + 1);
    strcpy(ene->descrip, des);
}
void menu(Enemy *enemys)

{
    Jugador jug;
    int option;
    char nombre[15];
    while (option != 2)
    {
        printLinea();
        printf("\n1.Juego Nuevo \n2.Salir");
        printf("\nElija  una opcion > ");
        scanf("%d", &option);
        printLinea();

        switch (option)
        {
        case 1:
            system("cls");
            printLinea();
            dibujo();
            printLinea();
            printf("\nIngrese su nombre: ");
            scanf("%s", nombre);
            inicializar_jugador(&jug, nombre);

            printf("\nEstas listo %s para esta aventura?\n\nIniciando juego...", jug.name);
            menuPrincipal(&jug, enemys);
            break;
        case 2:
            printf("\nSaliendo...");
            break;
        default:
            printf("\nLa opcion indicada no existe...");
            break;
        }
    }
}

void menuPrincipal(Jugador *jug, Enemy *enemys)
{
    int option, j, flag, x;
    while (option != 6 && jug->vida > 0)
    {
        printLinea();
        printf("\n1. Explorar \n2. Avanzar \n3. Estadisticas \n4. Inventario \n5. Bestiario \n6. Salir");
        printf("\nElija  una opcion > ");
        scanf("%d", &option);
        switch (option)
        {
        case EXPLORAR:
            printLinea();
            printf("\nExplorando...");
            explorar(jug);
            break;
        case AVANZAR:
            j = 0;
            flag = 0;
            while (j < 4 && flag == 0)
            {
                if (enemys[j].vida > 0)
                {
                    printLinea();
                    printf("\nHas encontrado a %s", enemys[j].name);
                    x = j;
                    flag = 1;
                }
                j++;
            }

            if (flag == 1)
            {
                enemys[x] = pelea(x, jug, enemys);
            }

            break;
        case ESTADISTICAS:
            estadisticas(jug);

            break;
        case INVENTARIO:
            inventario(jug);
            break;
        case BESTIARIO:
            printLinea();
            bestiario(enemys);
            break;
        case SALIR:
            printf("\nSaliendo...");
            break;
        default:
            printf("\nLa opcion indicada no existe...");
            break;
        }
    }
}

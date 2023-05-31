#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*Constantes:*/
#define VERTEX_NUMBER 5
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
#define FUENTE_HABILIDAD 4
#define POCION 3
#define NADA 0

// pelea
#define ATAQUE_LIGERO 1
#define ATAQUE_PESADO 2
#define PARRY 3
#define HEAL 4
#define ATAQUE_MAGICO 5
#define ESQUIVAR 6

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
    int posGf;
    int pociones;

} Jugador;

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

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
char *infoLista(List list, int position);
void remove_string(List *list, char *data);
void insertSorted(List *list, Objeto *objeto);
// Funciones de logica central
void menu(Enemy *enemys, List *grafo);
void menuPrincipal(Jugador *jug, Enemy *enemys, List *grafo);
void bestiario(Enemy *enemys);
void printLinea();
void explorar(Jugador *jud, Enemy *enemys);
Enemy pelea(int x, Jugador *jug, Enemy *enemys);
void inventario(Jugador *jug);
void estadisticas(Jugador *jug);
// dibujos
void dibujo();
void dibujo2();
// grafo
Node *create_vertex_node(int data);
List create_simple_list();
void add_node_to_list(List *list, int data);
void print_simple_list(List list);
void create_graph(List *arr);
void add_node_to_graph(List *arr, int node, int data);
void print_graph(List *graph);
void zonaActual(int node, List *graph, int *numNeighbors);
// Guardado
void guardarEstadisticas(Jugador *jugador, Enemy *enemigos, int numEnemigos);
void cargarEstadisticas(Jugador *jugador, Enemy **enemigos, int *numEnemigos);

int main()
{
    // Inicializar NPC's
    Enemy Avorathoe, Borvath, Crysanthea, Gorgath, Xoron_Dragon_del_Abismo;
    inicializar_enemy(&Avorathoe, "Avorathoe, el Devorador de Almas", 1500, "\nUna bestia gigantesca con multiples cabezas, cada una con una boca llena de dientes afilados y \nojos ardientes. Se dice que Avorathoe se alimenta de las almas de los guerreros caidos en batalla, \nlo que le otorga un poder inmenso y lo convierte en una amenaza para todos los que se \ninterponen en su camino.");
    inicializar_enemy(&Borvath, "Borvath, el Cazador Oscuro", 2000, "\nUn ser humanoide vestido con una capa oscura y una mascara de cuervo. Borvath es un asesino \nimplacable que persigue a los enemigos mas peligrosos del reino, siempre en busca de su \nproxima presa. Se dice que su verdadera identidad es un misterio, y que incluso los guerreros \nmas poderosos tiemblan ante su presencia.");
    inicializar_enemy(&Crysanthea, "Crysanthea, la Reina del Hielo", 3000, "\nUna mujer hermosa con cabello blanco y ojos azules como el hielo. Se rumorea que Crysanthea \nes una poderosa hechicera que controla el frio y la nieve, y que ha construido su fortaleza en un \nreino de eterno invierno. Se dice que sus enemigos se congelan hasta la muerte en su presencia, \ny que su magia es capaz de crear tormentas de nieve mortales.");
    inicializar_enemy(&Gorgath, "Gorgath, el Coloso de Piedra", 4000, "\nUna criatura gigantesca hecha completamente de piedra, con una fuerza y una resistencia \nimpresionantes. Se dice que Gorgath fue creado por los dioses antiguos como un guardian de un \ntemplo sagrado, pero que ha sido corrompido por el poder oscuro. Ahora, se levanta en el \ncamino de aquellos que buscan penetrar en el templo, listo para aplastarlos con sus enormes \nmanos de roca.");
    inicializar_enemy(&Xoron_Dragon_del_Abismo, " Xoron Dragon del Abismo", 1250, "Un temible dragon que habita en el abismo y lanza fuego y caos a su paso");
    Enemy *arregloEnemys = (Enemy *)calloc(5, sizeof(Enemy));
    arregloEnemys[0] = Avorathoe;
    arregloEnemys[1] = Borvath;
    arregloEnemys[2] = Crysanthea;
    arregloEnemys[3] = Gorgath;
    arregloEnemys[4] = Xoron_Dragon_del_Abismo;
    List graph[VERTEX_NUMBER];
    create_graph(graph);

    add_node_to_graph(graph, 0, 1);
    add_node_to_graph(graph, 0, 2);
    add_node_to_graph(graph, 1, 0);
    add_node_to_graph(graph, 1, 3);
    add_node_to_graph(graph, 1, 4);
    add_node_to_graph(graph, 2, 0);
    add_node_to_graph(graph, 2, 4);
    add_node_to_graph(graph, 3, 1);
    add_node_to_graph(graph, 4, 1);
    add_node_to_graph(graph, 4, 2);

    menu(arregloEnemys, graph);
    return 0;
}

void inicializar_jugador(Jugador *jug, char *n)
{
    int clase;
    printf("\nSelecciona una clase:\n\n1. Guerrero: Vida: 2000, Stamina: 20, Dano: 750, Agilidad: 5.\n\nLos guerreros tienen mucha vida y resistencia, lo que les permite aguantar mucho daño y\n mantenerse en pie durante mucho tiempo en el campo de batalla. Aunque no son muy agiles, su\n fuerza y habilidad con armas pesadas les permiten infligir un gran dano.\n\n2. Mago: Vida: 750, Stamina: 10, Dano: 200, Agilidad: 13.\n\nLos magos no tienen mucha vida ni resistencia fisica, pero su habilidad con la magia les permite \ncausar un gran dano a distancia. Son muy agiles y pueden evadir los ataques enemigos con\n facilidad, pero necesitan gestionar su stamina cuidadosamente para no quedarse sin mana durante \nuna pelea.\n\n3. Ladron: Vida: 1000, Stamina: 15, Dano: 500, Agilidad: 12.\n\nLos ladrones tienen una vida y resistencia media, pero son muy agiles y habiles con armas agiles\n como dagas y arcos. Pueden infligir un gran dano con ataques criticos y pueden desactivar trampas\n y abrir cerraduras.\n\n4. Clerigo: Vida: 1500, Stamina: 15, Dano: 300, Agilidad: 8.\n\nLos clerigos tienen una vida y resistencia media, pero su habilidad con la magia divina les permite\n curar a los aliados y causar un dano magico a los enemigos. No son muy agiles, pero\n tienen habilidades para proteger a sus aliados y resistir el dano magico.\n\nElija una opcion> ");
    jug->name = (char *)malloc(strlen(n) + 1);
    strcpy(jug->name, n);
    scanf("%d", &clase);
    switch (clase)
    {
    case GUERRERO:
        jug->vida = 2000;
        jug->stamina = 20;
        jug->dano = 750;
        jug->agilidad = 3;
        jug->posGf = 0;
        jug->pociones = 0;
        strcpy(jug->clase, "Guerrero");
        break;
    case MAGO:
        jug->vida = 750;
        jug->stamina = 10;
        jug->dano = 200;
        jug->agilidad = 5;
        jug->posGf = 0;
        jug->pociones = 0;
        strcpy(jug->clase, "Mago");
        break;
    case LADRON:
        jug->vida = 1000;
        jug->stamina = 15;
        jug->dano = 500;
        jug->agilidad = 6;
        jug->posGf = 0;
        jug->pociones = 0;
        strcpy(jug->clase, "Ladron");
        break;
    case CLERICO:
        jug->vida = 1500;
        jug->stamina = 15;
        jug->dano = 300;
        jug->agilidad = 1;
        jug->posGf = 0;
        jug->pociones = 0;
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
// Funciones metodos para la lista del inventario

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
        printf("Lista vacia.\n");
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
char *infoLista(List list, int position)
{

    Objeto *current = list.head;
    int i = 1;

    // Recorrer la lista hasta la posicion deseada
    while (i < position)
    {
        current = current->next;
        i++;
    }

    return current->data;
}
void remove_string(List *list, char *data)
{
    if (list->size == 0)
    {
        printf("Lista vacia.\n");
        return;
    }

    Objeto *current = list->head;
    Objeto *previous = NULL;

    // Buscar el nodo que contiene la cadena de texto
    while (current != NULL)
    {
        if (strcmp(current->data, data) == 0)
        {
            break;
        }
        previous = current;
        current = current->next;
    }

    // Si se encontro el nodo, eliminarlo
    if (current != NULL)
    {
        if (previous == NULL)
        {
            // El nodo a eliminar es el primero de la lista
            list->head = current->next;
        }
        else
        {
            // El nodo a eliminar esta en medio o al final de la lista
            previous->next = current->next;
        }

        free(current->data);
        free(current);
        list->size--;

        printf("Cadena eliminada: %s\n", data);
    }
    else
    {
        printf("Cadena no encontrada: %s\n", data);
    }
}
void insertSorted(List *list, Objeto *objeto)
{
    if (list->head == NULL || strcmp(objeto->data, list->head->data) < 0)
    {
        objeto->next = list->head;
        list->head = objeto;
    }
    else
    {
        Objeto *current = list->head;
        while (current->next != NULL && strcmp(objeto->data, current->next->data) > 0)
        {
            current = current->next;
        }
        objeto->next = current->next;
        current->next = objeto;
    }

    list->size++;
}
// Grafo
void zonaActual(int node, List *graph, int *numNeighbors)
{
    List list = graph[node];
    Node *current = list.head->next;
    int i = 0;
    printf("\nZona actual: %d\n", list.head->data);
    printf("A que zona quieres ir?: ");
    while (current != NULL)
    {
        printf("%d ", current->data);
        numNeighbors[i] = current->data;
        current = current->next;
        i++;
    }
    printf("\n");
    printf("Quedarse en zona actual: %d\n ", node);
}

Node *create_vertex_node(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;

    return node;
}

List create_simple_list()
{
    List list;
    list.size = 0;
    list.head = NULL;

    return list;
}

void add_node_to_list(List *list, int data)
{
    Node *node = create_vertex_node(data);

    Node *temp = list->head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = node;
    list->size += 1;
}

void print_simple_list(List list)
{
    Node *temp = list.head;

    printf("Vertice ");
    for (int i = 0; i < list.size; i++)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL");
}

void create_graph(List *arr)
{
    for (int i = 0; i < VERTEX_NUMBER; i++)
    {
        List list = create_simple_list();
        list.head = create_vertex_node(i);
        list.size = 1;

        arr[i] = list;
    }
}

void add_node_to_graph(List *arr, int node, int data)
{
    List *list = &arr[node];
    add_node_to_list(list, data);
}

void print_graph(List *graph)
{
    for (int i = 0; i < VERTEX_NUMBER; i++)
    {
        print_simple_list(graph[i]);
        printf("\n");
    }
}

// Logica central

void menu(Enemy *enemys, List *grafo)

{
    Jugador jug;
    int option, empty;
    char nombre[15];
    char archivo[17];
    dibujo2();
    while (option != 3)
    {
        printLinea();
        printf("\n1.Juego Nuevo \n2.Continuar\n3.Salir");
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
            menuPrincipal(&jug, enemys, grafo);
            break;
        case 2:
            archivo[17] = "estadisticas.txt";
            empty = isFileEmpty(archivo);
            if (empty != 1)
            {
                int numEnemys;
                cargarEstadisticas(&jug, &enemys, &numEnemys);
                menuPrincipal(&jug, enemys, grafo);
            }
        case 3:
            printf("\nSaliendo...");
            break;
        default:
            printf("\nLa opcion indicada no existe...");
            break;
        }
    }
}

void menuPrincipal(Jugador *jug, Enemy *enemys, List *grafo)
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
            explorar(jug, enemys);
            break;
        case AVANZAR:
            flag = 0;
            int pos;
            int zonasPosibles[5];
            if (enemys[jug->posGf].vida > 0)
                enemys[jug->posGf] = pelea(jug->posGf, jug, enemys);
            else
            {
                zonaActual(jug->posGf, grafo, &zonasPosibles);
                printf("\nSeleccione una zona > ");
                while (flag == 0)
                {
                    scanf("%d", &pos);
                    int i;
                    if (pos == jug->posGf)
                    {
                        flag = 1;
                        printf("\nRegresando al menu");
                    }
                    for (i = 0; i < 5 && flag == 0; i++)
                    {
                        if (pos == zonasPosibles[i])
                            flag = 1;
                    }
                    if (flag == 0)
                        printf("\nSeleccion invalida, seleccione una opcion valida");
                }
                jug->posGf = pos;
                if (enemys[pos].vida > 0)
                {
                    enemys[pos] = pelea(pos, jug, enemys);
                }
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

void printLinea()
{
    printf("\n------------------------------------------------------------------------------------------------------\n");
}

void explorar(Jugador *jud, Enemy *enemys)
{
    int option, i, save, k, j;
    int arreglo[10] = {1, 1, 2, 2, 2, 3, 3, 0, 0, 0};

    char objetos[5][21] = {"Anillo Abisal", "Hacha Espiral", "Pandeyuca", "Escudo Ancestral", "Orbe Cosmico"};
    char descripciones[5][100] = {
        "Un anillo imbuido de poderes oscuros que aumenta la resistencia a la magia.",
        "Un hacha maldita que gana fuerza a medida que se derrama la sangre del enemigo.",
        "Una llama eterna que arde sin descanso, otorgando vida y calor a su portador.",
        "Un escudo ancestral pasado de generacion en generacion, resistente a todo daño.",
        "Un orbe cosmico que revela secretos ancestrales y otorga vision mas alla de la realidad."};
    char objetos2[5][21] = {"Espada Solar", "Ojo Embrujado", "Baston Lunar", "Gema Carcasa", "Calavera Fria"};
    char descripciones2[5][100] = {
        "Una poderosa espada imbuida con la energia del sol, capaz de infligir daño radiante.",
        "Un ojo misterioso y encantado que concede visiones y percepciones sobrenaturales.",
        "Un baston que canaliza la energia de la luna, otorgando poderes magicos y curativos.",
        "Una gema resplandeciente que protege al portador al absorber el daño entrante.",
        "Una calavera helada que emana frio y corrompe el alma de aquellos que la tocan."};
    char objetos3[5][21] = {"Llave Olvidada", "Fuego Livido", "Velo Sombrio", "Flor Ceniza", "Corazon Negro"};
    char descripciones3[5][100] = {
        "Una antigua llave que abre puertas olvidadas y revela tesoros ocultos.",
        "Un fuego palido y oscuro que consume todo a su paso, infundiendo terror en los corazones.",
        "Un velo impregnado de sombras que oculta al portador de los ojos curiosos.",
        "Una delicada flor que crece en cenizas y representa la renacer y la esperanza.",
        "Un corazon negro y lleno de oscuridad, corrupto por la maldad mas profunda."};
    char objetos4[5][21] = {"Martillo Ferreo", "Pluma Ardiente", "Sortija ignea", "Golem Sombra", "Linterna Solar"};
    char descripciones4[5][100] = {
        "Un imponente martillo de hierro forjado con habilidad y resistencia sobrehumanas.",
        "Una pluma ardiente que arroja chispas y permite escribir en llamas.",
        "Una sortija ardiente que otorga proteccion contra el fuego y aumenta los poderes piromanticos.",
        "Un gigantesco golem de sombras que obedece las ordenes de su portador y lucha a su lado.",
        "Una linterna encantada que ilumina las zonas mas oscuras y ahuyenta a las criaturas de la noche."};
    char objetos5[5][21] = {"Grillete Onix", "Cetro Icaro", "Idolo Tenebroso", "Efigie Ardiente", "Perla Lunar"};
    char descripciones5[5][100] = {
        "Un grillete hecho de onix negro que encierra el poder de las sombras y controla la voluntad.",
        "Un cetro de diseño antiguo, tallado con plumas de angel y bendecido con el poder del vuelo.",
        "Un idolo oscuro y misterioso, adorado por aquellos que se deleitan en la oscuridad y el caos.",
        "Una efigie ardiente que emana calor y protege al portador de los elementos del fuego.",
        "Una hermosa perla que brilla con la luz de la luna, concediendo sabiduria y magia lunar."};
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
            guardarEstadisticas(jud, enemys, 4);
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
        k = rand() % 5;
        printLinea();
        Objeto *dato;
        switch (jud->posGf)
        {
        case 0:
            printf("\nHas encontrado: %s\nDescripcion: %s", objetos[k], descripciones[k]);
            dato = create_node(objetos[k]);
            insertSorted(&(jud->Inventario), dato);
            break;
        case 1:
            printf("\nHas encontrado: %s\nDescripcion: %s", objetos2[k], descripciones2[k]);
            dato = create_node(objetos2[k]);
            insertSorted(&(jud->Inventario), dato);
            break;
        case 2:
            printf("\nHas encontrado: %s\nDescripcion: %s", objetos3[k], descripciones3[k]);
            dato = create_node(objetos3[k]);
            insertSorted(&(jud->Inventario), dato);
            break;
        case 3:
            printf("\nHas encontrado: %s\nDescripcion: %s", objetos4[k], descripciones4[k]);
            dato = create_node(objetos4[k]);
            insertSorted(&(jud->Inventario), dato);
            break;
        case 4:
            printf("\nHas encontrado: %s\nDescripcion: %s", objetos5[k], descripciones5[k]);
            dato = create_node(objetos5[k]);
            insertSorted(&(jud->Inventario), dato);
            break;
        default:
            break;
        }

        break;
    case FUENTE_HABILIDAD:
        printLinea();
        printf("\nHas encontrado una fuente de habilidad");
        jud->fuenteHabilidad++;
        break;
    case POCION:
        printLinea();
        printf("\nHas encontrado una pocion");
        jud->pociones++;
        break;
    default:
        break;
    }
}

Enemy pelea(int x, Jugador *jug, Enemy *enemys)
{

    int vidaIniBoss = enemys[x].vida;
    int vidaIniJugador = jug->vida;
    int staminaIni = jug->stamina;
    int ataque;
    int prob, probEnemy;
    int iniStamina = jug->stamina;
    while (jug->vida > 0 && enemys[x].vida > 0)
    {
        printf("\nJefe: %s\nVida Jefe: %d/%d", enemys[x].name, enemys[x].vida, vidaIniBoss);
        printf("\nJugador\nVida: %d/%d\nStamina: %d/%d", jug->vida, vidaIniJugador, jug->stamina, staminaIni);

        printf("\n");
        printf("\nTipos de ataque:\n1.Ataque ligero\n2.Ataque pesado\n3.Parry\n4.Curarse\n5.Ataque Magico\n6.Esquivar\nSeleccione una opcion > ");
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
            else
                printf("\nHas fallado el parry pierdes turno");
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

            jug->stamina -= 4;

            break;
        case HEAL:
            if (jug->pociones > 0)
            {
                jug->vida += 400;
                jug->pociones--;
                printf("\nCantidad de pociones restante: %d", jug->pociones);
            }
            else
                printf("\nNo tienes pociones disponibles, pierdes turno");
            if (jug->vida > vidaIniJugador)
                jug->vida = vidaIniJugador;
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
        case ATAQUE_MAGICO:
            enemys[x].vida -= (jug->dano * jug->agilidad) / 4;
            jug->stamina -= 4;

            printf("\nAtaque magico efectivo");

            // El enemigo tiene 80% de acierto
            srand(time(NULL));
            probEnemy = rand() % 11;
            if (probEnemy <= 8)
            {
                jug->vida -= 150;
                printf("\nUn ataque enemigo te ha impactado");
            }
            else
            {
                printf("\nEl enemigo ha fallado su ataque, es tu turno");
            }
            break;
        case ESQUIVAR:
            srand(time(NULL));
            int probEsqui = rand() % 11;
            probEsqui += jug->agilidad;
            if (prob > 7)
            {
                printf("\nHas Esquivado el ataque");
                if (jug->stamina < iniStamina)
                    jug->stamina += 2;
            }
            else
            {
                printf("\nUn ataque enemigo te ha impactado");
                jug->vida -= 300;
                jug->stamina -= 4;
            }
            printf("\n");
            break;
        }

        if (jug->stamina < iniStamina)
            jug->stamina += 2;
    }
    if (jug->vida <= 0)
    {
        printf("\nHas muerto");
    }
    else
    {
        printf("\nFelicidades, has conseguido vencer a %s\nRecompensa 2 puntos de habilidad", enemys[x].name);
        enemys[x].vida = 0;
        jug->fuenteHabilidad += 4;
    }
    jug->vida = vidaIniJugador;
    return enemys[x];
}

void inventario(Jugador *jug)
{
    printLinea();
    if ((jug->Inventario).size == 0)
    {
        printf("\nEl inventario esta vacio\nExplora para adquirir objetos");
    }
    else
    {
        printf("\nInventario:\n");
        print_list(jug->Inventario);
    }
}

void guardarEstadisticas(Jugador *jugador, Enemy *enemigos, int numEnemigos)
{
    FILE *archivo = fopen("estadisticas.txt", "w");

    fprintf(archivo, "Jugador:\n");
    fprintf(archivo, "Nombre: %s\n", jugador->name);
    fprintf(archivo, "Vida: %d\n", jugador->vida);
    fprintf(archivo, "Stamina: %d\n", jugador->stamina);
    fprintf(archivo, "Daño: %d\n", jugador->dano);
    fprintf(archivo, "Agilidad: %d\n", jugador->agilidad);
    fprintf(archivo, "Fuente de Habilidad: %d\n", jugador->fuenteHabilidad);
    fprintf(archivo, "Clase: %s\n", jugador->clase);
    fprintf(archivo, "Posicion en el juego: %d\n", jugador->posGf);
    fprintf(archivo, "Pociones: %d\n", jugador->pociones);
    fprintf(archivo, "\n");
    fprintf(archivo, "Inventario:\n");
    Objeto *current = jugador->Inventario.head;
    while (current != NULL)
    {
        fprintf(archivo, "Objeto: %s\n", current->data);
        current = current->next;
    }
    fprintf(archivo, "\n");
    fprintf(archivo, "Enemigos:\n");
    for (int i = 0; i < numEnemigos; i++)
    {
        fprintf(archivo, "Nombre: %s\n", enemigos[i].name);
        fprintf(archivo, "Vida: %d\n", enemigos[i].vida);
        fprintf(archivo, "Descripcion: %s\n", enemigos[i].descrip);
        fprintf(archivo, "\n");
    }

    fclose(archivo);
}

void cargarEstadisticas(Jugador *jugador, Enemy **enemigos, int *numEnemigos)
{
    FILE *archivo = fopen("estadisticas.txt", "r");

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), archivo) != NULL)
    {
        if (strcmp(buffer, "Jugador:\n") == 0)
        {
            fgets(buffer, sizeof(buffer), archivo); // Leer nombre
            jugador->name = strdup(buffer + strlen("Nombre: "));
            fgets(buffer, sizeof(buffer), archivo); // Leer vida
            jugador->vida = atoi(buffer + strlen("Vida: "));
            fgets(buffer, sizeof(buffer), archivo); // Leer stamina
            jugador->stamina = atoi(buffer + strlen("Stamina: "));
            fgets(buffer, sizeof(buffer), archivo); // Leer daño
            jugador->dano = atoi(buffer + strlen("Daño: "));
            fgets(buffer, sizeof(buffer), archivo); // Leer agilidad
            jugador->agilidad = atoi(buffer + strlen("Agilidad: "));
            fgets(buffer, sizeof(buffer), archivo); // Leer fuente de habilidad
            jugador->fuenteHabilidad = atoi(buffer + strlen("Fuente de Habilidad: "));
            fgets(buffer, sizeof(buffer), archivo); // Leer clase
            strcpy(jugador->clase, buffer + strlen("Clase: "));
            fgets(buffer, sizeof(buffer), archivo); // Leer posicion en el juego
            jugador->posGf = atoi(buffer + strlen("Posicion en el juego: "));
            fgets(buffer, sizeof(buffer), archivo); // Leer pociones
            jugador->pociones = atoi(buffer + strlen("Pociones: "));
        }
        else if (strcmp(buffer, "Inventario:\n") == 0)
        {
            List inventario = create_list();
            while (fgets(buffer, sizeof(buffer), archivo) != NULL && strcmp(buffer, "\n") != 0)
            {
                if (strncmp(buffer, "Objeto: ", strlen("Objeto: ")) == 0)
                {
                    char *objeto = strdup(buffer + strlen("Objeto: "));
                    push(&inventario, objeto);
                }
            }
            jugador->Inventario = inventario;
        }
        else if (strcmp(buffer, "Enemigos:\n") == 0)
        {
            // Codigo para cargar enemigos
        }
    }

    fclose(archivo);
}

int isFileEmpty(const char *filename)
{
    FILE *file = fopen(filename, "r");

    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
    {
        fclose(file);
        return 1; // El archivo esta vacio
    }

    fclose(file);
    return 0; // El archivo no esta vacio
}

void estadisticas(Jugador *jug)
{
    int opcion;
    printLinea();
    printf("\nClase: %s\nVida restante: %d\nAgilidad %d\nStamina %d\nDano %d", jug->clase, jug->vida, jug->agilidad, jug->stamina, jug->dano);
    printf("\nQuieres utilizar los puntos de habilidad?, punto de habilidad actuales: %d\n1. Si\n2.No\nSeleccione una opcion > ", jug->fuenteHabilidad);
    scanf("%d", &opcion);
    while (opcion != 1 && opcion != 2)
    {
        printf("\nSeleccion invalida\nEscoja otra opcion > ");
        scanf("%d", &opcion);
    }
    if (opcion == 1)
    {
        int h;
        printf("\nQue desea mejorar?\n1. Vida\n2. dano\n3. agilidad\n4. Stamina\nElija una opcion > ");
        scanf("%d", &h);
        switch (h)
        {
        case 1:
            jug->vida += 100;
            break;
        case 2:
            jug->dano += 25;
            break;
        case 3:
            jug->agilidad += 1;
            break;
        case 4:
            jug->stamina += 1;
            break;
        default:
            printf("\nSeleccion invalidad, Saliendo...");
            break;
        }
        jug->fuenteHabilidad--;
    }
}
void dibujo()
{
    printf("      _                      _______                      _\n");
    printf("   _dMMMb._              .adOOOOOOOOOba.              _,dMMMb_\n");
    printf("  dP'  ~YMMb            dOOOOOOOOOOOOOOOb            aMMP~  `Yb\n");
    printf("  V      ~\"Mb          dOOOOOOOOOOOOOOOOOb          dM\"~      V\n");
    printf("           `Mb.       dOOOOOOOOOOOOOOOOOOOb       ,dM'\n");
    printf("            `YMb._   |OOOOOOOOOOOOOOOOOOOOO|   _,dMP'\n");
    printf("       __     `YMMM| OP'~\"YOOOOOOOOOOOP\"~`YO |MMMP'     __\n");
    printf("     ,dMMMb.     ~~' OO     `YOOOOOP'     OO `~~     ,dMMMb.\n");
    printf("  _,dP~  `YMba_      OOb      `OOO'      dOO      _aMMP'  ~Yb._\n");
    printf(" <MMP'     `~YMMa_   YOOo   @  OOO  @   oOOP   _adMP~'      `YMM>\n");
    printf("              `YMMMM\\`OOOo     OOO     oOOO'/MMMMP'\n");
    printf("      ,aa.     `~YMMb `OOOb._,dOOOb._,dOOO'dMMP~'       ,aa.\n");
    printf("    ,dMYYMba._         `OOOOOOOOOOOOOOOOO'          _,adMYYMb.\n");
    printf("   ,MP'   `YMMba._      OOOOOOOOOOOOOOOOO       _,adMMP'   `YM.\n");
    printf("   MP'        ~YMMMba._ YOOOOPVVVVVYOOOOP  _,adMMMMP~       `YM\n");
    printf("   YMb           ~YMMMM\\`OOOOI`````IOOOOO'/MMMMP~           dMP\n");
    printf("    `Mb.           `YMMMb`OOOI,,,,,IOOOO'dMMMP'           ,dM'\n");
    printf("      `'                  `OObNNNNNdOO'                   `'\n");
    printf("                            `~OOOOO~'  \n");
}
void dibujo2()
{
    printf(" _   __        _         _      _         ___       _                      _                           \n");
    printf("| | / /       (_)       | |    | |       / _ \\     | |                    | |                          \n");
    printf("| |/ /  _ __   _   __ _  | |__  | |_     / /_\\ \\  __| |__   __  ___  _ __  | |_  _   _  _ __   ___  ___ \n");
    printf("|    \\ | '_ \\ | | / _` | | '_ \\ | __|    |  _  | / _` |\\ \\ / / / _ \\| '_ \\ | __|| | | || '__| / _ \\/ __|\n");
    printf("| |\\  \\| | | || || (_| | | | | || |_     | | | || (_| | \\ V / |  __/| | | || |_ | |_| || |   |  __/\\__ \\\n");
    printf("\\_| \\_/|_| |_|\\__, | |_| |_| \\__|    \\_| |_/ \\__,_|  \\_/   \\___||_| |_| \\__| \\__,_||_|    \\___||___/\n");
    printf("               __/ |                                                                                   \n");
    printf("              |___/                                                                                    \n");
}
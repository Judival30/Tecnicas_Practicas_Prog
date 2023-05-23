#include "prototipos.h"

int main()
{
    // Inicializar NPC's
    Enemy Vorathor, Morvath, Crysanthea, Gorgath;
    inicializar_enemy(&Vorathor, "Vorathor, el Devorador de Almas", 0, "\nUna bestia gigantesca con multiples cabezas, cada una con una boca llena de dientes afilados y \nojos ardientes. Se dice que Vorathor se alimenta de las almas de los guerreros caidos en batalla, \nlo que le otorga un poder inmenso y lo convierte en una amenaza para todos los que se \ninterponen en su camino.");
    inicializar_enemy(&Morvath, "Morvath, el Cazador Oscuro", 0, "\nUn ser humanoide vestido con una capa oscura y una mascara de cuervo. Morvath es un asesino \nimplacable que persigue a los enemigos más peligrosos del reino, siempre en busca de su \npróxima presa. Se dice que su verdadera identidad es un misterio, y que incluso los guerreros \nmás poderosos tiemblan ante su presencia.");
    inicializar_enemy(&Crysanthea, "Crysanthea, la Reina del Hielo", 3000, "\nUna mujer hermosa con cabello blanco y ojos azules como el hielo. Se rumorea que Crysanthea \nes una poderosa hechicera que controla el frio y la nieve, y que ha construido su fortaleza en un \nreino de eterno invierno. Se dice que sus enemigos se congelan hasta la muerte en su presencia, \ny que su magia es capaz de crear tormentas de nieve mortales.");
    inicializar_enemy(&Gorgath, "Gorgath, el Coloso de Piedra", 4000, "\nUna criatura gigantesca hecha completamente de piedra, con una fuerza y una resistencia \nimpresionantes. Se dice que Gorgath fue creado por los dioses antiguos como un guardián de un \ntemplo sagrado, pero que ha sido corrompido por el poder oscuro. Ahora, se levanta en el \ncamino de aquellos que buscan penetrar en el templo, listo para aplastarlos con sus enormes \nmanos de roca.");
    Enemy *arregloEnemys = (Enemy *)calloc(4, sizeof(Enemy));
    arregloEnemys[0] = Vorathor;
    arregloEnemys[1] = Morvath;
    arregloEnemys[2] = Crysanthea;
    arregloEnemys[3] = Gorgath;
    menu(arregloEnemys);
    return 0;
}
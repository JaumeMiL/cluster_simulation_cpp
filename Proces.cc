#include "Proces.hh"
using namespace std;

/** @file Proces.cc
    @brief Codi de la classe Proces.
*/

Proces:: Proces() {}
void Proces:: crear_proces() {
    cin >> id_proces >> q_memoria >> temps;
}
int Proces:: consultar_id() const {
    return id_proces;
} 
int Proces:: consultar_quantitat_memoria() const {
    return q_memoria;
}
int Proces:: consultar_temps() const {
    return temps;
}
void Proces:: imprimir_proces() const {
    cout << id_proces << ' ' << q_memoria << ' ' << temps << endl;
}
int Proces:: afegir_temps(int nou_temps) {
    temps -= nou_temps; //decremento el temps amb el nou temps
    return temps;
}
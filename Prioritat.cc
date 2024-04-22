#include "Prioritat.hh"
using namespace std;

/** @file Prioritat.cc
    @brief Codi de la classe Prioritat.
*/

Prioritat::Prioritat() {
    processos_enviats = processos_rebutjats = 0;
}

int Prioritat::mida_llista() const {
    return cua_pendents.size();
}

Proces Prioritat::retornar_eliminar_proces() {
    list<Proces>::iterator it = cua_pendents.begin();
    Proces p = *it;
    cua_pendents.erase(it); //elimino el procés
    return p; //retorno el procés eliminat
}


void Prioritat::modificar_enviats_rebutjats(const int&e, const int&r) {
    //modifico els processos enviats i rebutjats
    processos_enviats += e;
    processos_rebutjats += r;
}

bool Prioritat::te_processos_pendents() const {
    if (cua_pendents.empty()) return false; //no hi ha processos
    else return true; //hi ha processos
}


bool Prioritat::conte_proces(const int &idp) const {
    for (list<Proces>::const_iterator it = cua_pendents.begin(); it != cua_pendents.end(); ++it) {
        if (it->consultar_id() == idp) return true; //existeix un procés a la llista
    }
    return false;
}


void Prioritat::afegir_proces(const Proces& p) {
    list<Proces>::iterator it = cua_pendents.end();
    cua_pendents.insert(it, p); //afegeix un procés a la llista
}

void Prioritat::imprimir_prioritat() const {
    //imprimeix tots els processos de la cua_pendents i els comptadors
    for (list<Proces>::const_iterator it = cua_pendents.begin(); it != cua_pendents.end(); ++it) {
        it->imprimir_proces();
    }
    cout << processos_enviats << " " << processos_rebutjats << endl;
}

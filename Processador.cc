#include "Processador.hh"
using namespace std;

/** @file Processador.cc
    @brief Codi de la classe Processador.
*/

Processador::Processador() {}

bool Processador::existeix_proces_mateix_id(int idproces) const { 
    map<int, int>::const_iterator it = id_posicio.find(idproces); //fent un find busquem l'iterador
    if (it == id_posicio.end()) return false;
    else return true;
}

bool Processador::te_processos_executant() const {
    if (id_posicio.empty()) return false; //miro si està buit o no
    else return true;
}

void Processador::afegir_forat(int pos, int mida) {
    map<int, set<int>>::iterator it = forats.find(mida); //find al mapa de forats per trobar el forat.
    if (it != forats.end())
        (*it).second.insert(pos); //si el forat ja existeix només s'afegeix la posició al forat.
    else {
        set<int> aux;
        aux.insert(pos);
        forats.insert(make_pair(mida, aux)); //si no existeix es crea un nou forat amb la posició i la mida.
    }
}


bool Processador::afegir_proces(Proces p) {
    int mem_proc = p.consultar_quantitat_memoria(); //memòria necessària pel procés
    map<int, set<int>>::iterator it = forats.lower_bound(mem_proc); //forat més ajustat amb prou espai disponible

    if (it == forats.end()) return false; //si no existeix cap forat disponible, retorna fals

    int pos_forat = *((*it).second.begin()); //mirem la posició del forat trobat
    int memoria_sobrant = (*it).first - mem_proc; //calcula la quantitat de memòria sobrant després d'afegir el procés

    if (memoria_sobrant != 0) afegir_forat(pos_forat + mem_proc, memoria_sobrant); //si hi ha memòria sobrant afegeix un forat

    //afegim el procés als maps
    id_posicio.insert(make_pair(p.consultar_id(), pos_forat));
    posicio_proces.insert(make_pair(pos_forat, p));

    //elimino el forat
    (*it).second.erase((*it).second.begin());
    if ((*it).second.empty()) {
        forats.erase(it); //
    }

    lliure -= mem_proc; //decremento la memòria lliure del processador
    return true; //retorno cert per indicar que s'ha afegit el procés
}


void Processador::forat_superior(map<int, Proces>::iterator it, int& tamfinal, int& posfinal) {
    int pos_actual = (*it).first;
    int posf, tamf;
    if (pos_actual == 0) {//No hi ha forat superior
        tamf = 0;
        posfinal = 0;
    } else if (it == posicio_proces.begin()) {//Té forat a dalt i és el primer procés
        tamf = pos_actual;
        posf = 0;
        tamfinal += pos_actual;
        posfinal = 0;
    } else {//Té forat a dalt i no és el primer procés
        --it;
        int pos_proc_ant = (*it).first;
        int mida_proc_ant = (*it).second.consultar_quantitat_memoria();
        posfinal = pos_proc_ant + mida_proc_ant; //posfinal del forat
        posf = posfinal;
        tamf = pos_actual - posfinal;
        tamfinal += tamf;
    }

    if (tamf > 0) {
        map<int, set<int>>::iterator itf = forats.find(tamf);
        (*itf).second.erase(posf);
        if ((*itf).second.empty()) forats.erase(itf);
    }
}

void Processador::forat_inferior(map<int, Proces>::iterator it, int& tamfinal) {
    int pos_actual = (*it).first;
    int tam_proces = (*it).second.consultar_quantitat_memoria();
    int posf, tamf;
    ++it;
    if (pos_actual == capacitat - tam_proces) {  // No té forat després
        tamf = 0;
        posf = -1;
    } else if (it == posicio_proces.end()) {  // Té forat a sota i és l'últim procés
        posf = pos_actual + tam_proces;
        tamf = capacitat - posf;
        tamfinal += tamf;
    } else {  // Té forat a sota i no és l'últim procés
        int pos_proc_desp = (*it).first;
        posf = pos_actual + tam_proces;
        tamf = pos_proc_desp - posf;
        tamfinal += tamf;
    }
    if (tamf > 0) {
        map<int, set<int>>::iterator itf = forats.find(tamf);
        (*itf).second.erase(posf);
        if ((*itf).second.empty()) forats.erase(itf);
    }
}

void Processador::eliminar_proces(int idp) {
    //busca la posició d'un procés
    map<int, int>::iterator itpos = id_posicio.find(idp);
    int pos = (*itpos).second;

    //busca el procés
    map<int, Proces>::iterator it = posicio_proces.find(pos);
    int mida_proces = (*it).second.consultar_quantitat_memoria();
    int tamfinal = mida_proces;
    int posfinal = pos;

    //comprova si tenim forat superior i actualitza la mida final i posició final del nou forat que es crearà
    forat_superior(it, tamfinal, posfinal);
    
    //comprova si tenim forat inferiror i actualitza la mida final del nou forat que es crearà
    forat_inferior(it, tamfinal);

    //afegeix un nou forat ajuntant-lo amb els contigus en cas d'existir
    afegir_forat(posfinal, tamfinal);
    
    //incrementa la memòria lliure
    lliure += mida_proces;

    //elimina el procés de la posició i l'ID
    posicio_proces.erase(it);
    id_posicio.erase(idp);
}


int Processador::modificar_posicio_proces(map<int, Proces>::iterator& it, int pos_final) {
    //busquem la posició del procés
    map<int, int>::iterator itpos = id_posicio.find((*it).second.consultar_id());
    (*itpos).second = pos_final;

    //obté la mida original del procés
    int mida_proces = (*it).second.consultar_quantitat_memoria();

    //afegeix el nou procés a la nova posició i actualitza l'iterador
    pair<map<int, Proces>::iterator, bool> p = posicio_proces.insert(make_pair(pos_final, (*it).second));
    if (p.second) {
        posicio_proces.erase(it);
        it = p.first;
    }

    return mida_proces;
}


void Processador::avancar_temps(int t) {
    map<int, Proces>::iterator it = posicio_proces.begin();
    while (it != posicio_proces.end()) {
        //avança el temps del procés
        if ((*it).second.afegir_temps(t) <= 0) {
            //si ha acabat (o sigui retorna un temps negatiu) l'elimina
            map<int, Proces>::iterator itaux = it;
            ++itaux;
            eliminar_proces((*it).second.consultar_id());
            it = itaux;
        } else {
            //si el procés no ha acabat avança l'iterador
            ++it;
        }
    }
}

void Processador::compactar() {
    int pos = 0;
    for (map<int, Proces>::iterator it = posicio_proces.begin(); it != posicio_proces.end(); ++it) {
        //modifica la posició del procés
        int mida = modificar_posicio_proces(it, pos);
        pos += mida;
    }

    //modifiquem els forats
    if (capacitat != lliure) {
        forats.clear();
        afegir_forat(pos, lliure);
    }
}


void Processador::llegir_processador() {
    //crea el processador i un forat de la seva mida ja que en aquest moment el processador no conté processos.
    cin >> capacitat;
    lliure = capacitat;
    afegir_forat(0, capacitat);
}


void Processador::imprimir_processador() const {
    //imprimeix els processos del processador.
    for (map<int, Proces>::const_iterator it = posicio_proces.begin(); it != posicio_proces.end(); ++it) {
        cout << (*it).first << ' ';
        (*it).second.imprimir_proces();
    }
}


int Processador::consultar_lliure() const {
    return lliure;
}

int Processador::mida_forat_ajustat(const int& mida) {
    //busca el forat més ajustat a la mida
    map<int, set<int>>::iterator it = forats.lower_bound(mida);
    if (it == forats.end()) { //retorna -1 si no es troba
        return -1;
    } else {
        //si es troba retorna la seva mida
        return (*it).first;
    }
}

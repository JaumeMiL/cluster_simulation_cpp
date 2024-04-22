#include "AreaEspera.hh"
using namespace std;

/** @file AreaEspera.cc
    @brief Codi de la classe AreaEspera.
*/

AreaEspera::AreaEspera() {}

void AreaEspera::llegir_area_espera() {
    int vegades;
    cin >> vegades;

    //afegeix la prioritat a l'àrea d'espera
    for (int i = 1; i <= vegades; ++i) {
        string id;
        cin >> id;
        Prioritat p;
        area_espera.insert(make_pair(id, p));
    }
}

char AreaEspera::alta_proces_espera(const string& idpri, const Proces& p) {
    //busca la prioritat
    map<string, Prioritat>::iterator it = area_espera.find(idpri);
    int id_proces = p.consultar_id();

    if (it == area_espera.end()) return '1';  //no existeix
    else if (it->second.conte_proces(id_proces)) return '2';  //el procés ja existeix a la prioritat
    else {
        it->second.afegir_proces(p);  //afegeix el procés a la prioritat
        return '0';
    }
}

char AreaEspera::imprimir_prioritat(const string& idprior) {
    //busca la prioritat
    map<string, Prioritat>::iterator it = area_espera.find(idprior);

    if (it == area_espera.end()) return '1';  //no existeix
    else {
        it->second.imprimir_prioritat();  //imprimeix la prioritat
        return '0';
    }
}

void AreaEspera::imprimir_area_espera() {
    //imprimeix totes les prioritats fent un for i passant per cada prioritat
    map<string, Prioritat>::iterator it;
    for (it = area_espera.begin(); it != area_espera.end(); ++it) {
        cout << it->first << endl;
        it->second.imprimir_prioritat();
    }
}

char AreaEspera::alta_prioritat(const string& idpri) {
    //busca la prioritat
    map<string, Prioritat>::iterator it = area_espera.find(idpri);

    if (it != area_espera.end()) return '1';  //ja existeix
    else {
        Prioritat p;
        area_espera.insert(make_pair(idpri, p));  //crea una nova prioritat amb aquest identificador
        return '0';
    }
}

char AreaEspera::baixa_prioritat(const string& idpri) {
    //busca la prioritat
    map<string, Prioritat>::iterator it = area_espera.find(idpri);

    if (it == area_espera.end()) return '1'; //no existeix
    else if (it->second.te_processos_pendents()) return '2'; //té processos pendents
    else {
        area_espera.erase(idpri); //elimina la prioritat
        return '0';
    }
}

void AreaEspera::enviar_processos_cluster(int n, Cluster& c) {
    //envia processos al cluster fins a un nombre màxim (n) o fins a acabar els processos disponibles
    map<string, Prioritat>::iterator it = area_espera.begin();
    int proc_enviats = 0, proc_enviats_total = 0, proc_rebutjats = 0;

    //prioritat a prioritat
    while (proc_enviats_total < n and it != area_espera.end()) {
        int mida_llista = it->second.mida_llista();

        //procés a procés
        while (mida_llista > 0 and proc_enviats_total < n) {
            Proces p = it->second.retornar_eliminar_proces();
            pair<bool, string> r = c.processador_ideal(p);

            if (r.first) {
                //hem trobat un processador disponible
                string nom_processador = r.second;
                c.alta_proces_processador(nom_processador, p);
                ++proc_enviats_total;
                ++proc_enviats;
            } else {
                //no tenim processador disponible
                ++proc_rebutjats;
                it->second.afegir_proces(p);  //tornem a afegir el procés al final de la prioritat
            }
            --mida_llista;
        }
        it->second.modificar_enviats_rebutjats(proc_enviats, proc_rebutjats);
        proc_enviats = proc_rebutjats = 0;
        ++it;
    }
}

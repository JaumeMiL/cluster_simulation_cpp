#include "Cluster.hh"
using namespace std;

/** @file Cluster.cc
    @brief Codi de la classe Cluster.
*/

Cluster::Cluster() {}

const BinTree<string>& Cluster::get_acl() const { //retornarem l'arbre
    return acl;
}

void Cluster::i_configurar_cluster(BinTree<string>& a, map<string, Processador>& m) {
    string x;
    cin >> x; //llegeixo o asterisc
    if (x != "*") { //si no entra un asterisc retornem recursivament la funció
        Processador p;
        p.llegir_processador();
        m.insert(make_pair(x, p));
        BinTree<string> esq, dre;
        i_configurar_cluster(esq, m);
        i_configurar_cluster(dre, m);
        a = BinTree<string>(x, esq, dre);
    }
}

void Cluster::configurar_cluster() {
    i_configurar_cluster(acl, mcl); //crido la funció recursiva per crear el cluster
}


char Cluster::imprimir_processador(string idp) {
    map<string, Processador>::iterator it = mcl.find(idp); //busco el processador
    if (it == mcl.end()) return '1'; //error si no existeix
    else {
        it->second.imprimir_processador(); //imprimeixo el processador
        return '0';
    }
}

void Cluster::imprimir_processadors_cluster() {
    for (map<string, Processador>::iterator it = mcl.begin(); it != mcl.end(); ++it) { //recorro tots els processos i els vaig imprimint un a un
        cout << it->first << endl;
        it->second.imprimir_processador();
    }
}

void Cluster::imprimir_estructura_cluster(const BinTree<string>& acl) {
    if (acl.empty()) cout << ' '; //si està buit imprimeixo un espai
    else {
        cout << "(" << acl.value(); //imprimeixo el valor
        //crido recursivament
        imprimir_estructura_cluster(acl.left());
        imprimir_estructura_cluster(acl.right());
        cout << ")";
    }
}

char Cluster::modificar_arbre(BinTree<string>& a, const Cluster& c2, const string& idp) {
    if (a.empty()) return '1'; //arbre és buit
    else if (a.value() == idp) {
        if (not a.left().empty() or not a.right().empty()) return '3'; //l'arbre té fills
        else {
            mcl.erase(idp); //elimino el processador amb l'identificador passat

            //afegiexo els nous processadors a l'arbre i al mapa
            for (map<string, Processador>::const_iterator it2 = c2.mcl.begin(); it2 != c2.mcl.end(); ++it2) {
                mcl.insert(make_pair(it2->first, it2->second));
            }
            a = c2.acl; 
            return '0'; //retorno 0 si tot ha anat bé
        }
    }
    else {
        BinTree<string> esq, dret;
        esq = a.left(); //obté l'arbre esquerre
        dret = a.right(); //obté l'arbre dret
        char c = modificar_arbre(esq, c2, idp); //crido recursivament a modifica l'arbre esquerre
        if (c == '1') c = modificar_arbre(dret, c2, idp); //crido recursivament a modifica l'arbre dret si l'anterior no va funcionar
        a = BinTree<string>(a.value(), esq, dret); //creo el nou arbre amb els canvis realitzats
        return c;
    }
}

char Cluster::modificar_cluster(const string& idp, Cluster& c2) {
    map<string, Processador>::iterator it = mcl.find(idp);
    if (it == mcl.end()) return '1'; //no existeix
    else if (it->second.te_processos_executant()) return '2'; //té processos en execució
    else return modificar_arbre(acl, c2, idp); //modifica l'arbre
}

void Cluster::resetejar_cluster() {
    BinTree<string> cl1;
    acl = cl1; //crea un arbre net
    mcl.clear(); //neteja el mapa del cluster
}

char Cluster::alta_proces_processador(string idprocessador, const Proces& p) {
    map<string, Processador>::iterator it = mcl.find(idprocessador);
    if (it == mcl.end()) return '1'; //no existeix
    else if (it->second.existeix_proces_mateix_id(p.consultar_id())) return '2'; //ja existeix un procés amb aquest identificador
    else if (!it->second.afegir_proces(p)) return '3'; //no es pot afegir el procés al processador
    else return '0'; //afegit correctament
}

char Cluster::baixa_proces_processador(string idprocessador, int idproces) {
    map<string, Processador>::iterator it = mcl.find(idprocessador);
    if (it == mcl.end()) return '1'; //no existeix
    else if (!it->second.existeix_proces_mateix_id(idproces)) return '2'; //no existeix un procés amb aquest identificador
    else {
        it->second.eliminar_proces(idproces); //eliminat correctament
        return '0';
    }
}

void Cluster::avancar_temps(int t) {
    for (map<string, Processador>::iterator it = mcl.begin(); it != mcl.end(); ++it) {
        it->second.avancar_temps(t); //afegeixo temps a tots els processadors del cluster
    }
}

char Cluster::compactar_memoria_processador(string idprocessador) {
    map<string, Processador>::iterator it = mcl.find(idprocessador);
    if (it == mcl.end()) return '1'; //no existeix
    else {
        it->second.compactar(); //compacta la memòria
        return '0';
    }
}

void Cluster::compactar_memoria_cluster() {
    for (map<string, Processador>::iterator it = mcl.begin(); it != mcl.end(); ++it) {
        it->second.compactar(); //compacta la memòria de tots els processadors
    }
}

pair<bool, string> Cluster::processador_ideal(const Proces& p) {
    string nom_processador = "$";
    int mem_lliure = 0;
    int forat_ajustat = 2147483647; //poso l'enter més gran que pot existir, així s'actualitzarà sempre a la comparació
    int profunditat_ideal = 0;
    processador_ideal_arbre(nom_processador, acl, p, 0, mem_lliure, forat_ajustat, profunditat_ideal); //crido la funció que em retorna el processador ideal
    pair<bool, string> r = make_pair(false, "$");
    if (nom_processador != "$") r = make_pair(true, nom_processador);
    return r;
}

void Cluster::processador_ideal_arbre(string& nom_processador, const BinTree<string>& acl, const Proces& p, int profunditat, int& mem_lliure, int& forat_ajustat, int& profunditat_ideal) {
    if (not acl.empty()) {
        string idp = acl.value();
        map<string, Processador>::iterator it = mcl.find(idp);
        int forat = it->second.mida_forat_ajustat(p.consultar_quantitat_memoria());
        int lliure_processador = it->second.consultar_lliure();

        if (forat != -1 and not it->second.existeix_proces_mateix_id(p.consultar_id())) {
            //si hi ha forat seguim
            if (forat < forat_ajustat or (forat == forat_ajustat and lliure_processador > mem_lliure) or (forat == forat_ajustat and lliure_processador == mem_lliure and profunditat < profunditat_ideal)) {
                //si el nou processador compleix les condicions anteriors, actualitzo el processador ideal
                nom_processador = idp;
                forat_ajustat = forat;
                mem_lliure = lliure_processador;
                profunditat_ideal = profunditat;
            }
        }

        //crido a la funció de manera recursiva
        processador_ideal_arbre(nom_processador, acl.left(), p, ++profunditat, mem_lliure, forat_ajustat, profunditat_ideal);
        processador_ideal_arbre(nom_processador, acl.right(), p, ++profunditat, mem_lliure, forat_ajustat, profunditat_ideal);
    }
}

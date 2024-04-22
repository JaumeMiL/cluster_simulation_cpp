/** @file AreaEspera.hh
    @brief Especificació de la classe AreaEspera
*/
#ifndef _AREAESPERA_HH_ 
#define _AREAESPERA_HH_

#include "Proces.hh"
#include "Prioritat.hh"
#include "Cluster.hh"

#ifndef NO_DIAGRAM 
#include <string>
#include <iostream>
#include <map>
#endif

using namespace std;

/** @class AreaEspera
    @brief Representa tota una cua de processos que estan a l'espera de ser executats pels processadors del cluster.
*/

class AreaEspera {
public:

//Constructores:

/** @brief Constructor per defecte.
    \pre <em>Cert</em>
    \post El resultat és la creació d'una àrea d'espera. */
AreaEspera();

/** @brief Llegeix les prioritats
    \pre <em>Si existia una llista de prioritats anteriors s'elimina</em>
    \post A l'àrea d'espera ja hi ha entrats tota la llista d'esperes. */
void llegir_area_espera();

/** @brief Afegir un procés a l'espera.
    \pre <em> Llegeix un procés i un identificador de prioritat</em>
    \post Imprimeix error si la prioritat no existeix o si la prioritat ja conté aquest procés. En cas contrari, el procés entra a l'àrea d'espera. */
char alta_proces_espera(const string& idpri, const Proces& p);

/** @brief Imprimeix la prioritat
    \pre <em>Entra un identificador de prioritat</em>
    \post Imprimeix error si aquesta prioritat no existeix. En cas contrari, s'imprimeixen el processos pendents en ordre decreixent i el nombre de rebutjades de tots ells.*/
char imprimir_prioritat(const string& idprior);

/** @brief Imprimeix l'àrea d'espera
    \pre <em>Cert</em>
    \post Imprimeix tots els processos pendents de l'àrea d'espera per ordre de prioritat. */
void imprimir_area_espera();


//Modificadores:

/** @brief Afegeix una prioritat a l'àrea d'espera.
    \pre <em>Identificador de prioritat</em>
    \post Treu un error si la prioritat ja existeix i sinó s'afegeix la prioritat. */
char alta_prioritat(const string& idpri);

/** @brief Elimina una prioritat de l'àrea d'espera.
    \pre <em>Identificador de prioritat</em>
    \post Imprimeix un missatge d'error o s'elimina la prioritat de l'àrea d'espera. */
char baixa_prioritat(const string& idpri);


/** @brief Envia al cluster els processos pendents.
    \pre <em>Entra un enter no negatiu i un cluster</em>
    \post Els 'n' processos s'intenten colocar al cluster en ordre de prioritat, sinó són retornats a l'àrea d'espera. Si no hi ha 'n' processos s'intentaran afegir el màxim de processos possibles. */
void enviar_processos_cluster(int n, Cluster& c);

/** @brief Decideix a quin processador del cluster s'ha d'afegir un procés.
    \pre <em>Llegeix la memòria disponible de cada un dels processadors i si hi cap el procés</em>
    \post Segons les regles de desempat, retorna l'identificador del processador ideal. */
string processador_ideal (string nom_processador, BinTree<string>& acl, const map <string,Processador>&mcl, const Proces&p, int profunditat, int esquerra, int mem_lliure, int forat_ajustat, int profunditat_ideal, int esquerra_ideal);


private:
    /** @brief Mapa que conté les prioritats de l'àrea d'espera.*/
    map<string, Prioritat> area_espera;
};
#endif // _AREAESPERA_HH_
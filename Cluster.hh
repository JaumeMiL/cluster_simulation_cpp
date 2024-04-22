/** @file Cluster.hh
    @brief Especificació de la classe Cluster.
*/
#ifndef _CLUSTER_HH_ 
#define _CLUSTER_HH_

#include "Processador.hh"
#include "Proces.hh"

#ifndef NO_DIAGRAM 
#include <string> 
#include <iostream>
#include <map>
#include "BinTree.hh"
#endif

using namespace std;

/** @class Cluster
    @brief Representa una concentració de processadors diferents. Aquests processadors estan distribuïts en forma d'arbre binari dins del cluster.
*/

class Cluster {
public:

//Constructores:

/** @brief Constructor per defecte.
    \pre <em>cert</em>
    \post El resultat és la creació d'un cluster. */
Cluster();

/** @brief Llegir processadors del cluster
    \pre <em>Si existia un cluster anterior aquest s'elimina</em>
    \post El cluster conté els nous processadors. */
void configurar_cluster();

//Consultores:

/** @brief Imprimeix el processador
    \pre <em>Entra un identificador de processador</em>
    \post Imprimeix error si el processador no existeix. En cas contrari s'imprimeixen els processos del processador en ordre creixent per posicions de memòria.*/
char imprimir_processador(string idp);

/** @brief Imprimeix el processadors del cluster
    \pre <em>Cert</em>
    \post Imprimeix tots els processadors del cluster en ordre creixent.*/
void imprimir_processadors_cluster();

/** @brief Imprimeix l'estructura de processadors del cluster
    \pre <em>Reb l'arbre del cluster</em>
    \post Imprimeix l'estructura de processadors del cluster.*/
void imprimir_estructura_cluster(const BinTree<string>& acl);

/** @brief Serveix per retornar l'arbre    
    \pre <em>cert</em>
    \post Retorna l'arbre.*/
const BinTree<string>& get_acl() const;



//Modificadores:

/** @brief Modifica els processadors del cluster
    \pre <em>Llegeix l'identificador d'un processador del cluster i un nou cluster</em>
    \post El cluster conté els nous processadors. */
char modificar_cluster(const string& idp, Cluster& c2);

/** @brief Llegir processadors del cluster
    \pre <em>Existeix un cluster</em>
    \post Es retorna un cluster buit, sense processadors */
void resetejar_cluster();

/** @brief Afegir un procés a un processador.
    \pre <em>Llegeix un identificador d'un processador.</em>
    \post Imprimeix error si alguna de les precondicions són certes. En cas contrari, el procés passa a executar-se en aquell processador.*/
char alta_proces_processador(string idprocessador, const Proces& p);

/** @brief Eliminar un procés d'un processador.
    \pre <em>Llegeix un identificador de processador i un de procés.</em>
    \post Imprimeix error si no existeix el processador o si el procés no està inclòs dins. En cas contrari, s'elimina el procés del processador.*/
char baixa_proces_processador(string idprocessador, int idproces);

/** @brief Avançar temps
    \pre <em>T, enter no negatiu</em>
    \post Avança el temps corresponent i s'eliminen els processos actius que hagin esgotat el temps.*/
void avancar_temps(int t);

/** @brief Compacta la memòria d'un processador.
    \pre <em>Llegeix un identificador de processador i comprova si existeix_processador.</em>
    \post Imprimeix error si no existeix el processador. En cas contrari, es mouen tots els processos per no deixar buits.*/
char compactar_memoria_processador(string idprocesador); 

/** @brief Compacta la memòria del cluster.
    \pre <em>Cert.</em>
    \post Es mouen tots els processos per no deixar buits.*/
void compactar_memoria_cluster(); 

/** @brief Busca el processador ideal i afegeix el procés a dins.
    \pre <em>Passo un processador. Crida a una funció auxiliar.</em>
    \post Retorna true si s'ha pogut afegir o fals en cas contrari. En cas de poder-se afegir retorna l'identificador del processador.*/
pair<bool,string> processador_ideal(const Proces& p);


private:
    /** @brief Arbre binari que conté els processadors del cluster en l'ordre corresponent.*/
    BinTree <string> acl;

    /** @brief Mapa que conté els processadors del cluster ordenats.*/
    map <string,Processador> mcl;

    /** @brief Funció recursiva controlada per configurar cluster.
        \pre <em>Passo un arbre i un mapa que al principi estan buits.</em>
        \post Es creen un arbra i un mapa nous de manera recursiva.*/
    static void i_configurar_cluster(BinTree<string>& a, map<string,Processador>& m);
    
    /** @brief Funció recursiva controlada per modificar cluster.
        \pre <em>Passo un arbre, un cluster i un identificador.</em>
        \post Canvia el processador de l'identificador pel nou arbre que el va afegint recursivament.*/
    char modificar_arbre(BinTree<string>& a, const Cluster& c2, const string& idp);

    /** @brief Funció recursiva controlada per processador ideal.
        \pre <em>Passo un arbre, un string i un procés a més de totes les variables que condicionaran si el processador és millor o no.</em>
        \post Es van actualitzant els paràmetres per trobar el millor processador.*/
    void processador_ideal_arbre (string& nom_processador, const BinTree<string>& acl, const Proces&p, int profunditat, int& mem_lliure, int& forat_ajustat, int& profunditat_ideal);

};
#endif //_CLUSTER_HH_
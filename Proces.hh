/** @file Proces.hh
    @brief Especificació de la classe Proces.
*/
#ifndef _PROCES_HH_ 
#define _PROCES_HH_

#ifndef NO_DIAGRAM
#include <iostream>
#include <string> 
#endif

using namespace std;

/** @class Proces
    @brief Representa un procés que haurà de ser executat per un processador del cluster.
*/

class Proces {
public:
//Constructores:

/** @brief Constructor per defecte.
    \pre <em>Cert</em>
    \post El resultat és la creació d'un procés. */
Proces();

/** @brief Creador del procés. 
    \pre <em>Cert</em>
    \post Es crea el procés. */
void crear_proces();

//Consultores:

/** @brief Consultador de l'identificador. 
    \pre <em>Cert</em>
    \post Treu l'id. */
int consultar_id() const;

/** @brief Consultador de la quantitat de memòria que ocupa. 
    \pre <em>Cert</em>
    \post Treu la quantitat de memòria que ocupa. */
int consultar_quantitat_memoria() const;

/** @brief Consultador de la quantitat de temps que ja ha concorregut. 
    \pre <em>Cert</em>
    \post Treu la quantitat de temps concorregut. */
int consultar_temps() const;

/** @brief Imprimeix el procés.
    \pre <em>Cert</em>
    \post S'imprimeixen els valors del procés.*/
void imprimir_proces() const;

//Modificadores:

/** @brief Fa passar el temps.
    \pre <em>Cert</em>
    \post Es treu temps restant al procés.*/
int afegir_temps(int nou_temps);


private:
    /** @brief id_proces indica l'identificador del procés.*/
    int id_proces;
    /** @brief q_memoria indica la quantitat de memòria que ocupa el procés.*/
    int q_memoria;
    /** @brief temps indica el temps que necessita el procés per ser executat.*/
    int temps;
};
#endif //_PROCES_HH_
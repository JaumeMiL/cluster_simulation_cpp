/** @file Prioritat.hh
    @brief Especificació de la classe Prioritat.
*/
#ifndef _PRIORITAT_HH_ 
#define _PRIORITAT_HH_

#include "Proces.hh"

#ifndef NO_DIAGRAM 
#include <string> 
#include <iostream>
#include <list>
#endif

using namespace std;

/** @class Prioritat
    @brief Representa la prioritat per ser executat de casdascun dels processos pendents que estroben a l'àrea d'espera.
*/

class Prioritat {
public:
//Constructores:
/** @brief Constructor per defecte.
    \pre <em>Cert</em>
    \post El resultat és la creació d'una prioritat. */
Prioritat();

//Consultores:

/** @brief Consultador de la mida de la llista. 
    \pre <em>Cert</em>
    \post Treu la mida de la llista. */
int mida_llista () const;

/** @brief Consultador de processos pendents. 
    \pre <em>Cert</em>
    \post Treu Cert si en té, fals en cas contrari. */
bool te_processos_pendents() const;

/** @brief Consulta si una prioritat té un procés específic. 
    \pre <em>Identificador de procés</em>
    \post Treu el resultat de la comparació d'aquest identificador amb tots els de la prioritat. */
bool conte_proces(const int & idp) const;

/** @brief Afegir procés a la prioritat. 
    \pre <em>Entrem un procés</em>
    \post La prioritat conté el procés. */
void afegir_proces(const Proces& p);

/** @brief Imprimir la prioritat. 
    \pre <em>Cert</em>
    \post Imprimeix tots els elements de la prioritat. */
void imprimir_prioritat() const;

/** @brief Serveix per retornar el primer procés i eliminar-lo de la llista. 
    \pre <em>Cert</em>
    \post Retorna el primer procés i l'elimina de la llista. */
Proces retornar_eliminar_proces();

/** @brief Modifiquem els enviats i rebutjats de cada prioritat. 
    \pre <em>Li passem els nous enviats i rebutjats.</em>
    \post Incrementem els enviats i rebutjats amb els dos nombres rebuts. */
void modificar_enviats_rebutjats (const int&e, const int&r);

private:
    /** @brief Llista de processos pendents.*/
    list<Proces> cua_pendents;

    /** @brief Variable que indica els processos enviats amb èxit al cluster.*/
    int processos_enviats;

    /** @brief Variable que indica els processos rebutjats pel cluster.*/
    int processos_rebutjats;
};
#endif // _PRIORITAT_HH_

/** @file Processador.hh
    @brief Especificació de la classe Processador.
*/
#ifndef _PROCESSADOR_HH_ 
#define _PROCESSADOR_HH_

#include "Proces.hh"

#ifndef NO_DIAGRAM 
#include <iostream>
#include <string> 
#include <set>
#include <map> 
#endif

using namespace std;

/** @class Processador
    @brief Representa les especificacions de cadascun dels processadors. 
*/

class Processador {
public:
//Constructores:

/** @brief Constructor per defecte.
    \pre <em>Cert</em>
    \post El resultat és la creació d'un processador. */
Processador();


//Consultores:

/** @brief Consulta si existeix un procés amb el mateix identificador dins del processador.
    \pre <em>Entra l'identificador del processador i l'identificador del procés.</em>
    \post Retorna true en cas que existeixi, false en cas contrari. */
bool existeix_proces_mateix_id(int idproces) const;

/** @brief Consulta si té processos en execució.
    \pre <em>Cert</em>
    \post Retorna true en cas que en tingui, false en cas contrari. */
bool te_processos_executant() const;

/** @brief Consultador de la quantitat de memòria lliure. 
    \pre <em>Cert</em>
    \post Retorna la quantitat de memòria lliure. */
int consultar_lliure() const;

/** @brief Consultador de la mida del forat més ajustat. 
    \pre <em>Entrem la mida procés</em>
    \post Retorna la mida del forat més ajustat. */
int mida_forat_ajustat(const int & mida);

//Modificadores:

/** @brief Afegir el procés al processador. 
    \pre <em>Entrem un procés.</em>
    \post S'afegeix el procés. */
bool afegir_proces(Proces p);

/** @brief Avançar temps
    \pre <em>t, enter no negatiu</em>
    \post Avança el temps corresponent i s'eliminen els processos actius que hagin esgotat el temps.*/
void avancar_temps(int t);

/** @brief Compracta els processos del processador.
    \pre <em>Cert</em>
    \post S'han compactat els valors del processador.*/
void compactar();

/** @brief Llegeix un processador.
    \pre <em>Cert</em>
    \post El processador correspon al que s'ha llegit. */
void llegir_processador();

/** @brief Elimina un procés.
    \pre <em>Identificador del procés</em>
    \post El procés és eliminat. */
void eliminar_proces(int id);

/** @brief Imprimeix el processador.
    \pre <em>Cert</em>
    \post S'han imprès el processador.*/
void imprimir_processador() const;



private:

    /** @brief Mapa amb l'identificador del procés i la posició de memòria en la que es troba dins del processador.*/
    map<int,int> id_posicio;
    /** @brief Mapa amb la posició de memòria i el procés.*/
    map<int,Proces> posicio_proces;
    /** @brief Mapa amb la mida del forat i un set amb les posicions dels forats amb aquesta mida.*/
    map<int,set<int>> forats;

    /** @brief La variable capacitat indica la capacitat total del processador.*/
    int capacitat;
    
    /** @brief Lliure és la capacitat lliure del processador.*/
    int lliure;

    int modificar_posicio_proces(map<int,Proces>::iterator& it, int pos_final);
    /** @brief Mira si té forat superior i de ser així l'ajunta.
        \pre <em>Entra l'iterador, la mida final i la posició final.</em>
        \post Surt el forat ajuntat.*/
    void forat_superior(map<int, Proces>::iterator it, int& tamfinal, int& posfinal);    

    /** @brief Mira si té forat inferior i de ser així l'ajunta.
        \pre <em>Entra l'iterador i la mida final.</em>
        \post Surt el forat ajuntat.*/
    void forat_inferior(map<int, Proces>::iterator it, int& tamfinal);

    /** @brief Serveix per afegir un forat.
        \pre <em>Entra la posició i la mida.</em>
        \post S'afegeix el forat.*/
    void afegir_forat(int pos, int mida);

};
#endif // _PROCESSADOR_HH_
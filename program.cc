/** @file program.cc
 *  @brief Simulació del rendiment de processadors interconectats.
*/
/** @mainpage Pàgina principal
 *  @brief Aquesta programa detalla el funcionament al fer una simulació del rendiment de processadors connectats entre ells. Per fer-ho tenim un Cluster (una estructura en forma d'arbre binari que conté processadors) i una AreaEspera amb les seves prioritats i processos. Aquests processos són enviats posteriorment al Cluster. El programa principal es troba al mòdul program.cc. Atenent els tipus de dades suggerides a l'enunciat, necessitarem un mòdul per representar el Cluster, un altre per a l'AreaEspera, i uns altres tres per a Processador, Prioritat i Proces. Pràctica de Jaume Mora i Ladària.
*/

#ifndef NO_DIAGRAM 
#include <iostream>
#endif
#include "Cluster.hh"
#include "AreaEspera.hh"
#include "Proces.hh"
using namespace std;

int main(){
    Cluster c;
    AreaEspera a;
    c.configurar_cluster(); //llegeix tots els processadors
    a.llegir_area_espera(); //llegeix les prioritats
    string com;
    cin >> com;
    while(com != "fin"){
        if (com == "configurar_cluster" or com == "cc"){
            cout << '#' << com << endl;
            c.resetejar_cluster();
            c.configurar_cluster();
        }
        else if (com == "modificar_cluster" or com == "mc"){
            string idp;
            cin >> idp;
            Cluster c2;
            c2.configurar_cluster();
            cout << '#' << com << ' ' << idp << endl;
            char lletra = c.modificar_cluster(idp,c2);
            if (lletra == '1') cout << "error: no existe procesador" << endl;
            else if (lletra == '2') cout << "error: procesador con procesos" << endl;
            else if (lletra == '3') cout << "error: procesador con auxiliares" << endl;
        }

        else if (com == "alta_prioridad" or com == "ap"){
            string idp;
            cin >> idp;
            cout << '#' << com << ' ' << idp << endl;
            char lletra = a.alta_prioritat(idp);
            if (lletra == '1') cout << "error: ya existe prioridad" << endl;
        }

        else if (com == "baja_prioridad" or com == "bp"){
            string idp;
            cin >> idp;
            cout << '#' << com << ' ' << idp << endl;
            char lletra = a.baixa_prioritat(idp);
            if (lletra == '1') cout << "error: no existe prioridad" << endl;
            else if (lletra == '2') cout << "error: prioridad con procesos" << endl;
        }

         else if (com == "alta_proceso_espera" or com == "ape"){
            string idp;
            cin >> idp;
            Proces p;
            p.crear_proces();
            cout << '#' << com << ' ' << idp << ' ' << p.consultar_id() << endl;
            char lletra = a.alta_proces_espera(idp,p);
            if (lletra == '1') cout << "error: no existe prioridad" << endl;
            else if (lletra == '2') cout << "error: ya existe proceso" << endl;
        }

         else if (com == "alta_proceso_procesador" or com == "app"){
            string idp;
            cin >> idp;
            Proces p;
            p.crear_proces();
            cout << '#' << com << ' ' << idp << ' ' << p.consultar_id() << endl;
            char lletra = c.alta_proces_processador(idp, p);
            if (lletra == '1') cout << "error: no existe procesador" << endl;
            else if (lletra == '2') cout << "error: ya existe proceso" << endl;
            else if (lletra == '3') cout << "error: no cabe proceso" << endl;
        }

        else if (com == "baja_proceso_procesador" or com == "bpp"){
            string idprocessador;
            int idproces;
            cin >> idprocessador >> idproces;
            cout << '#' << com << ' ' << idprocessador << ' ' << idproces << endl;
            char lletra = c.baixa_proces_processador(idprocessador, idproces);
            if (lletra == '1') cout << "error: no existe procesador" << endl;
            else if (lletra == '2') cout << "error: no existe proceso" << endl;
        }

        else if (com == "enviar_procesos_cluster" or com == "epc"){
            int n;
            cin >> n;
            cout << '#' << com << ' ' << n << endl;
            a.enviar_processos_cluster(n,c);
        }

        else if (com == "avanzar_tiempo" or com == "at"){
            int t;
            cin >> t;
            cout << '#' << com << ' ' << t << endl;
            c.avancar_temps(t);
        }

        else if (com == "imprimir_prioridad" or com == "ipri"){
            string idprior;
            cin >> idprior;
            cout << '#' << com << ' ' << idprior << endl;
            char lletra = a.imprimir_prioritat(idprior);
            if (lletra == '1') cout << "error: no existe prioridad" << endl;
        }

        else if (com == "imprimir_area_espera" or com == "iae"){
            cout << '#' << com << endl;
            a.imprimir_area_espera();
        }

        else if (com == "imprimir_procesador" or com == "ipro"){
            string idproc;
            cin >> idproc;
            cout << '#' << com << ' ' << idproc << endl;
            char lletra = c.imprimir_processador(idproc);
            if (lletra == '1') cout << "error: no existe procesador" << endl;
        }

        else if (com == "imprimir_procesadores_cluster" or com == "ipc"){
            cout << '#' << com << endl;
            c.imprimir_processadors_cluster();
        }

        else if (com == "imprimir_estructura_cluster" or com == "iec"){
            cout << '#' << com << endl;
            c.imprimir_estructura_cluster(c.get_acl()); 
            cout << endl;
        }

        else if (com == "compactar_memoria_procesador" or com == "cmp"){
            string idp;
            cin >> idp;
            cout << '#' << com << ' ' << idp << endl;
            char lletra = c.compactar_memoria_processador(idp);
            if (lletra == '1') cout << "error: no existe procesador" << endl;
        }

        else if (com == "compactar_memoria_cluster" or com == "cmc"){
            cout << '#' << com << endl;
            c.compactar_memoria_cluster();
        }

        cin >> com;
    }
}
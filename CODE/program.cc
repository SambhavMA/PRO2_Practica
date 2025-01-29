/** @mainpage Simulación del rendimiento de procesadores interconectados (Sambhav Mayani)


   Programa que simula el funcionamiento de una arquitectura multiprocesador, donde
cada procesador trabaja exclusivamente con su propia memoria y puede ejecutar más
de un proceso simultáneamente.

*/

/** @file program.cc
 		@brief Programa principal.
*/

#include "Cluster.hh"
#include "Area_espera.hh"



#ifndef NO_DIAGRAM
#include <iostream>
#include "Proceso.hh"
#include "Procesador.hh"
#include "Prioridad.hh"
#endif

using namespace std;

/** @brief main del programa principal
*/
int main() {

    Cluster clust;
    clust.configurar_cluster();
    Area_espera area;
    area.leer_area();

    string com;
    cin >> com;
    while (com != "fin") {

        if (com == "configurar_cluster" or com == "cc") {
            cout << '#' << com << endl;
            clust.configurar_cluster();
        }

        else if (com == "modificar_cluster" or com == "mc") {
            string id_proc;
            cin >> id_proc;

            cout << '#' << com << ' ' << id_proc << endl;

            int res = clust.modificar_cluster(id_proc);
            if (res == 1) cout << "error: no existe procesador" << endl;
            else if (res == 2) cout << "error: procesador con procesos" << endl;
            else if (res == 3) cout << "error: procesador con auxiliares" << endl;
        }

        else if (com == "alta_prioridad" or com == "ap") {

            string id_pri;
            cin >> id_pri;

            cout << '#' << com << ' ' << id_pri << endl;

            if (not area.alta_prioridad(id_pri)) cout << "error: ya existe prioridad" << endl;
        }

        else if (com == "baja_prioridad" or com == "bp") {

            string id_pri;
            cin >> id_pri;

            cout << '#' << com << ' ' << id_pri <<endl;

            int res = area.baja_prioridad(id_pri);

            if (res == 1) cout << "error: no existe prioridad" << endl;
            else if (res == 2) cout << "error: prioridad con procesos" << endl;
        }

        else if (com == "alta_proceso_espera" or com == "ape") {

            string id_pri;
            cin >> id_pri;
            Proceso p;
            p.leer_proceso();

            cout << '#' << com << ' ' << id_pri << ' ' << p.consultar_id() << endl;

            int res = area.alta_proceso_espera(id_pri, p);

            if (res == 1)  cout << "error: no existe prioridad" << endl;
            else if (res == 2) cout << "error: ya existe proceso" << endl;
        }

        else if (com == "alta_proceso_procesador" or com == "app") {

            string id_procesador;
            cin >> id_procesador;
            Proceso p;
            p.leer_proceso();

            cout << '#' << com << ' ' << id_procesador << ' ' << p.consultar_id() << endl;;

            int res = clust.alta_proceso_procesador(id_procesador, p);

            if (res == 1) {
                cout << "error: ya existe proceso" << endl;
            }
            else if (res == 2) {
                cout << "error: no cabe proceso" << endl;

            }
            else if (res == 3) cout << "error: no existe procesador" << endl;
        }

        else if (com == "baja_proceso_procesador" or com == "bpp") {
            string id_procesador;
            int id_proceso;
            cin >> id_procesador >> id_proceso;

            cout << '#' << com << ' ' << id_procesador << ' ' << id_proceso << endl;

            int res = clust.baja_proceso_procesador(id_procesador, id_proceso);

            if (res == 1) cout << "error: no existe procesador" << endl;
            else if (res == 2) cout << "error: no existe proceso" << endl;
        }

        else if (com == "enviar_procesos_cluster" or com == "epc") {
            int n;
            cin >> n;
            cout << '#' << com << ' ' << n << endl;

            clust.enviar_procesos_cluster(area, n);
        }

        else if (com == "avanzar_tiempo" or com == "at") {

            int t;
            cin >> t;

            cout << '#' << com << ' ' << t << endl;

            clust.avanzar_tiempo(t);
        }

        else if (com == "imprimir_prioridad" or com == "ipri") {

            string id_pri;
            cin >> id_pri;

            cout << '#' << com << ' ' << id_pri << endl;

            if (not area.escribir_pri(id_pri)) cout << "error: no existe prioridad" << endl;
        }

        else if (com == "imprimir_area_espera" or com == "iae") {
            cout << '#' << com << endl;
            area.escribir_area();
        }

        else if (com == "imprimir_procesador" or com == "ipro") {

            string id_procesador;
            cin >> id_procesador;

            cout << '#' << com << ' ' << id_procesador << endl;

            if (not clust.imprimir_procesador(id_procesador)) cout << "error: no existe procesador" << endl;
        }

        else if (com == "imprimir_procesadores_cluster" or com == "ipc") {
            cout << '#' << com << endl;
            clust.imprimir_procesadores_cluster();

        }

        else if (com == "imprimir_estructura_cluster" or com == "iec") {
            cout << '#' << com << endl;
            clust.imprimir_estructura_cluster();
        }

        else if (com == "compactar_memoria_procesador" or com == "cmp") {
            string id_procesador;
            cin >> id_procesador;
            cout << '#' << com << ' ' << id_procesador << endl;
            if (not clust.compactar_memoria_procesador(id_procesador)) cout << "error: no existe procesador" << endl;
        }

        else if (com == "compactar_memoria_cluster" or com == "cmc") {
            cout << '#' << com << endl;
            clust.compactar_memoria_cluster();
        }

       cin >> com;
    }
}


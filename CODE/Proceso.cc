/** @file Cluster.cc
 		@brief Implementación de la clase Proceso.
*/


#include "Proceso.hh"
using namespace std;

    Proceso::Proceso() {
        id = 0;
        mem = 0;
        t_ej = 0;
    }


    int Proceso::consultar_id() const {
        return id;
    }


    int Proceso::consultar_mem() const {
        return mem;
    }


    int Proceso::consultar_tiempo() const {
        return t_ej;
    }

    //Modificadoras


    void Proceso::avanzar_tiempo(int t) {
        t_ej = t_ej - t;
    }

    //Lectura y Escritura


    void Proceso::leer_proceso() {
        int n1, n2, n3;
        cin >> n1 >> n2 >> n3;
        id = n1;
        mem = n2;
        t_ej = n3;
    }


    void Proceso::escribir_proceso() {
        cout << id << ' ' << mem << ' ' << t_ej << endl;
    }





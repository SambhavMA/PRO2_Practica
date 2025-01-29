/** @file Cluster.cc
 		@brief Implementación de la clase Prioridad.
*/


#include "Prioridad.hh"
using namespace std;

/*
PRIVADOS:
Numero de procesos de la prioridad colocados en el cluster por la operación enviar_procesos_cluster.
    int env;

Numero de rechazos de procesos que se han intentado colocar en el cluster (un mismo proceso cuenta tantas veces como rechazos ha sufrido) por la operación enviar_procesos_cluster.
    int rech;

Lista de procesos que se usa como una cola.
    list <Proceso> l;

Set con los identificadores de todos los procesos de la prioridad.
    set <int> procesos;
*/


    Prioridad::Prioridad() {
        env = 0;
        rech = 0;
        procesos.clear();
        l.clear();
    }

    bool Prioridad::vacia() const {
        return l.empty();
    }

    int Prioridad::size() const {
        return l.size();
    }


    int Prioridad::consultar_rech() const {
        return rech;
    }



    int Prioridad::consultar_env() const {
        return env;
    }



    bool Prioridad::alta_proceso(const Proceso& p) {
        int id = p.consultar_id();
        if (procesos.find(id) != procesos.end()) return false;

        procesos.insert(id);
        list<Proceso>::iterator it = l.end();
        l.insert(it, p);
        return true;
    }

    void Prioridad::devolver_proceso(const Proceso& p) {
        int id = p.consultar_id();
        procesos.insert(id);
        list<Proceso>::iterator it = l.end();
        l.insert(it, p);
    }


    Proceso Prioridad::baja_proceso() {
        //suponemos que no se intentará hacer baja_proceso en lista vacía debido a la implementación de enviar procesos cluster en la clase Cluster
        list<Proceso>::iterator it = l.begin();
        Proceso p = *it;
        procesos.erase(p.consultar_id());
        l.erase(it);
        return p;
    }

    void Prioridad::inc_rech() {
        ++rech;
    }

    void Prioridad::inc_env() {
        ++env;
    }


    void Prioridad::escribir_pri() {
        list<Proceso>::iterator it = l.begin();
        while (it != l.end()) {
            it->escribir_proceso();
            ++it;
        }
        cout << env << ' ' << rech << endl;
    }








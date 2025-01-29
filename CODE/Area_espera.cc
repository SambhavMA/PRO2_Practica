/** @file Area_espera.cc
 		@brief Implementación area de espera.
*/
/** @file Cluster.cc
 		@brief Implementación de la clase Area_espera.
*/


#include "Area_espera.hh"
using namespace std;

/*
PRIVADOS:

Mapa de prioridades que tiene como clave al id de la prioridad.

    map <string, Prioridad> a_espera;

*/


    Area_espera::Area_espera() {
        a_espera.clear();
    }

    //Consultoras

    int Area_espera::size() const {
        return a_espera.size();
    }

    int Area_espera::size_pri(int n) const {
        map<string, Prioridad>::const_iterator it = a_espera.begin();
        for (int i = 0; i < n; ++i) ++it;
        return it->second.size();
    }

    //Modificadoras

    bool Area_espera::alta_prioridad(const string& id) {

        map<string,Prioridad>::iterator it = a_espera.find(id);

        if (it != a_espera.end()) return false;
        else {
            Prioridad p;
            a_espera[id] = p;
            return true;
        }
    }



    int Area_espera::baja_prioridad(const string& id) {
        map<string,Prioridad>::iterator it = a_espera.find(id);
        if (it == a_espera.end()) return 1;

        if (not it->second.vacia()) return 2;

        a_espera.erase(it);
        return 0;
    }



    int Area_espera::alta_proceso_espera(const string& id, const Proceso& p) {

        map<string,Prioridad>::iterator it = a_espera.find(id);

        if (it == a_espera.end()) return 1;
        if (it->second.alta_proceso(p)) return 0;
        return 2;
    }

    void Area_espera::devolver_proceso_espera(const string& id, const Proceso& p) {
        a_espera[id].devolver_proceso(p);
    }


    Proceso Area_espera::baja_proceso_espera(int n, string& pri) {
        map<string, Prioridad>::iterator it = a_espera.begin();
        for (int i = 0; i < n; ++i) ++it;
        pri = it->first;
        return it->second.baja_proceso();
    }

    void Area_espera::incrementar_rech(const string& id) {
        a_espera[id].inc_rech();
    }

    void Area_espera::incrementar_env(const string& id) {
        a_espera[id].inc_env();
    }

    //Escritura

    void Area_espera::leer_area() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            string id;
            cin >> id;
            alta_prioridad(id);
        }
    }

    void Area_espera::escribir_area() {
        map<string, Prioridad>::iterator it = a_espera.begin();
        while (it != a_espera.end()){
            cout << it->first << endl;
            it->second.escribir_pri();
            ++it;
        }
    }



    bool Area_espera::escribir_pri(const string& id) {
        map<string, Prioridad>::iterator it = a_espera.find(id);
        if (it == a_espera.end()) return false;
        else {
            it->second.escribir_pri();
            return true;
        }
    }








/** @file Cluster.cc
 		@brief Implementación de la clase Cluster.
*/

#include "Cluster.hh"
using namespace std;

/*
PRIVADOS:

Árbol binario con los identificadores de los procesadores, representa la estructura del cluster.

	BinTree <string> cluster;

Mapa de Procesadores con el identificador de los procesadores como clave.

    map<string,Procesador> procesadores;

*/


    BinTree<string> Cluster::leer_cluster() {
        string s;
        cin >> s;
        if (s == "*") {
            BinTree<string> c;
            return c;
        }
        else {
            int n;
            cin >> n;
            Procesador p(s,n);
            procesadores[s] = p;
            BinTree<string> izq = leer_cluster();
            BinTree<string> der = leer_cluster();
            BinTree<string> res(s, izq, der);
            return res;

        }
    }

    BinTree<string> Cluster::leer_cluster_aux(map<string, Procesador>& mapa_aux) {
        string s;
        cin >> s;
        if (s == "*") {
            BinTree<string> c;
            return c;
        }
        else {
            int n;
            cin >> n;
            Procesador p(s,n);
            mapa_aux[s] = p;
            BinTree<string> izq = leer_cluster_aux(mapa_aux);
            BinTree<string> der = leer_cluster_aux(mapa_aux);
            BinTree<string> res(s, izq, der);
            return res;
        }
    }

    void Cluster::imprimir_estructura_arbol(const BinTree<string>& arbol) {
        if (not arbol.empty()) {
            cout << "(";
            cout << arbol.value();
            imprimir_estructura_arbol(arbol.left());
            imprimir_estructura_arbol(arbol.right());
            cout << ")";
        }
        else cout << " ";

    }

    void Cluster::modificar(const string id_procesador, BinTree<string>& a, const BinTree<string>& aux, bool& found) {

        if (not a.empty() and found) {
            if (a.value() == id_procesador) {
                found = a.left().empty() and a.right().empty();
                if (found) {
                    a = aux;
                }
            }

            else {
                BinTree<string> left = a.left();
                modificar(id_procesador, left, aux, found);
                BinTree<string> right = a.right();
                if (found) modificar(id_procesador, right, aux, found);
                a = BinTree<string> (a.value(), left, right);

            }

        }
    }

    void Cluster::mejor_procesador(const BinTree<string>& a, int tam_proceso, int id_proceso, int& hueco_min, int& max_espacio, string& procesador, int nivel, int& nivel_procesador) {
    //string& procesador es el mejor procesador para colocar el proceso

        if (not a.empty()) {
            map<string, Procesador>::iterator it = procesadores.find(a.value());
            int hueco;
            if (it->second.existe_proceso(id_proceso)) hueco = -1;
            else hueco = it->second.hueco_mas_ajustado(tam_proceso);

            //la función hueco mas ajustado retorna -1 en caso de que no haya un hueco ningun hueco lo suficientemente grande para que quepa el proceso
            if (hueco != -1) {

                int espacio = it->second.mem_disponible();

                if (hueco_min == -1) {//el valor inicial que daremos a hueco_min al llamar la función será -1, para detectar si su valor ha sido modificado o no, y así saber si el proceso que se intenta enviar al cluster ha sido rechazado o no
                    hueco_min = hueco;
                    procesador = it->second.consultar_id();
                    max_espacio = espacio;
                    nivel_procesador = nivel;
                }

                else if (hueco < hueco_min) {
                    hueco_min = hueco;
                    max_espacio = espacio;
                    procesador = it->second.consultar_id();
                    nivel_procesador = nivel;
                }

                else if (hueco == hueco_min) {
                    if (espacio > max_espacio) {
                        max_espacio = espacio;
                        procesador = it->second.consultar_id();
                        nivel_procesador = nivel;
                    }

                    else if (espacio == max_espacio) {
                        if (nivel < nivel_procesador) {
                            nivel_procesador = nivel;
                            procesador = it->second.consultar_id();
                        }
                    }
                }

            }
            mejor_procesador(a.left(), tam_proceso, id_proceso, hueco_min, max_espacio, procesador, nivel + 1, nivel_procesador); //hacemos el recorrido en preorden para buscar el procesador más arriba y más a la izquierda
            mejor_procesador(a.right(), tam_proceso, id_proceso, hueco_min, max_espacio, procesador, nivel + 1, nivel_procesador);
        }
    }


    bool Cluster::enviar_proceso(const Proceso& p) {
        string procesador;
        int hueco_min = -1;
        int max_espacio = -1;
        int nivel_procesador = -1;
        int nivel = 0;

        mejor_procesador(cluster,p.consultar_mem(),p.consultar_id(),hueco_min,max_espacio,procesador,nivel,nivel_procesador);

        if (hueco_min == -1) return false;
        else {
            procesadores[procesador].alta_proceso(p);
            return true;
        }

    }

    Cluster::Cluster() {
        procesadores.clear();
    }



    Cluster::Cluster(const Procesador& p) {
        BinTree<string> arbol(p.consultar_id());
        cluster = arbol;
        procesadores[p.consultar_id()] = p;
    }


    //Modificadoras

    int Cluster::modificar_cluster(const string& id_procesador) {

        map <string,Procesador>::iterator it = procesadores.find(id_procesador);
        if (it == procesadores.end()) return 1;
        else if (not it->second.vacio()) return 2;
        else {

            map<string, Procesador> mapa_aux;
            BinTree<string> aux = leer_cluster_aux(mapa_aux);
            bool found = true;
            modificar(id_procesador, cluster, aux, found);

            if (found) {
                procesadores.erase(it);
                procesadores.insert(mapa_aux.begin(), mapa_aux.end());
                return 0;
            }
            else return 3;
        }
    }

    int Cluster::alta_proceso_procesador(const string& id_procesador, const Proceso& p) {
        map <string,Procesador>::iterator it = procesadores.find(id_procesador);
        if (it == procesadores.end()) return 3;

        return it->second.alta_proceso(p);
    }

    int Cluster::baja_proceso_procesador(const string& id_procesador, int id_proceso) {
        map <string,Procesador>::iterator it = procesadores.find(id_procesador);
        if (it == procesadores.end()) return 1;
        if (it->second.baja_proceso(id_proceso)) return 0;
        return 2;
    }

    bool Cluster::compactar_memoria_procesador(const string& id_procesador) {
        map <string,Procesador>::iterator it = procesadores.find(id_procesador);
        if (it == procesadores.end()) return false;

        it->second.compactar_memoria();
        return true;
    }


    void Cluster::compactar_memoria_cluster() {
        map <string,Procesador>::iterator it = procesadores.begin();

        while (it != procesadores.end()) {
            it->second.compactar_memoria();
            ++it;
        }
    }


    void Cluster::enviar_procesos_cluster(Area_espera& area, int n) {
        int tam_area = area.size();
        int i = 0;
        int proc_env = 0; //procesos enviados
        while (proc_env < n and i < tam_area) {
            int tam_pri = area.size_pri(i);
            int j = 0;
            while (proc_env < n and j < tam_pri) {
                string pri;
                Proceso p = area.baja_proceso_espera(i, pri);
                if (enviar_proceso(p)) {
                    area.incrementar_env(pri);
                    ++proc_env;
                }
                else {
                    area.devolver_proceso_espera(pri, p);
                    area.incrementar_rech(pri);
                }
                ++j;
            }
            ++i;
        }
    }

    void Cluster::avanzar_tiempo(int t) {

        if (not procesadores.empty()) {
            map <string,Procesador>::iterator it = procesadores.begin();

            while (it != procesadores.end()) {

                it->second.avanzar_tiempo(t);
                ++it;

            }
        }

    }
    //Lectura y Escritura

    void Cluster::configurar_cluster() {
        procesadores.clear();
        cluster = leer_cluster();
    }

    bool Cluster::imprimir_procesador(const string& id_procesador) {
        map<string,Procesador>::iterator it = procesadores.find(id_procesador);
        if (it == procesadores.end()) return false;

        it->second.escribir_procesador();
        return true;

    }


    void Cluster::imprimir_procesadores_cluster() {
       map<string,Procesador>::iterator it = procesadores.begin();
            while (it != procesadores.end()) {
                cout << it->first << endl;
                it->second.escribir_procesador();
                ++it;
            }

    }

    void Cluster::imprimir_estructura_cluster() {
        imprimir_estructura_arbol(cluster);
        cout << endl;
    }





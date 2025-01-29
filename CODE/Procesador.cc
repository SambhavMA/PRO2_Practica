/** @file Cluster.cc
 		@brief Implementación de la clase Procesador.
*/


#include "Procesador.hh"
using namespace std;

/*
PRIVADOS:

Identificador del procesador.

string id;

Mapa con los huecos en la memoria del procesador, la clave es el tamaño del hueco y el set son las posiciones iniciales de los procesos con ese tamaño.

    map <int, set <int>> huecos; //tam y set de pos_i

Mapa que representa a la memoria, la clave es la posición inicial de los procesos en ejecución.

    map <int, Proceso> mem; //pos_i y el proceso

Mapa que tiene como clave el identificador de los procesos en memoria y como contenido la posición inicial del proceso con ese id.

    map <int, int> procesos; //id y pos_i

Entero que representa la capacidad del procesador.

    int capacidad;

*/

    Procesador::Procesador() {
        mem.clear();
        huecos.clear();
        procesos.clear();
        id = "res";
        capacidad = 0;
    }

    Procesador::Procesador(string s, int n) {
        mem.clear();
        huecos.clear();
        procesos.clear();
        id = s;
        capacidad = n;
        huecos[n].insert(0);
    }

    //Consultoras


    string Procesador::consultar_id() const {
        return id;
    }

    bool Procesador::vacio() const {
        return procesos.empty();
    }

    bool Procesador::existe_proceso(int id_proceso) const {
        map<int,int>::const_iterator it = procesos.find(id_proceso);
        if (it == procesos.end()) return false;
        else return true;
    }

    int Procesador::hueco_mas_ajustado(int n) const {
        map<int,set<int>>::const_iterator it = huecos.lower_bound(n);
        if (it == huecos.end()) return -1;
        return it->first;
    }

    int Procesador::mem_disponible() const {
        map<int,set<int>>::const_iterator it = huecos.begin();
        int suma = 0;
        while (it != huecos.end()) {
            suma += it->first;
            ++it;
        }
        return suma;
    }

    //Modificadoras

    int Procesador::alta_proceso(const Proceso& p) {
        int id_proceso = p.consultar_id(); //un tanto innecesaria esta declaración, solamente sirve para hacer más clara la siguiente línea, lo hago o no??
        if (procesos.find(id_proceso) != procesos.end()) return 1;

        else {
            map<int,set<int>>::iterator it = huecos.lower_bound(p.consultar_mem());

            if (it == huecos.end()) return 2;

            set<int>::iterator it_set = it->second.begin();

            int pos_i_hueco = *it_set;

            int size_new_hueco = it->first - p.consultar_mem();

            mem[pos_i_hueco] = p;
            if (size_new_hueco != 0) huecos[size_new_hueco].insert(pos_i_hueco + p.consultar_mem()); //en [] esta el tamaño del nuevo heuco y en el insert se inserta en el set de posiciones iniciales segun el tamaño del hueco la nueva pos inicial del hueco encontrado
            procesos[id_proceso] = pos_i_hueco;
            it->second.erase(it_set);
            if (it->second.empty()) huecos.erase(it);
            return 0;
        }
    }



    bool Procesador::baja_proceso(int id_proceso) {
        map<int,int>::iterator it = procesos.find(id_proceso);

        if (it == procesos.end()) return false;

        map <int,Proceso>::iterator it_p = mem.find(it->second);

        pair<int,int> sig_hueco; // first int = pos_inicial y el segundo = tamaño
        pair<int,int> prev_hueco;

        map <int,Proceso>::iterator it_sig = it_p;

        ++it_sig;

        //miramos el siguiente hueco
        if (it_sig == mem.end()) {
            sig_hueco.first = it_p->first + it_p->second.consultar_mem();
            sig_hueco.second = capacidad - sig_hueco.first;
        }

        else {
            sig_hueco.first = it_p->first + it_p->second.consultar_mem();
            sig_hueco.second = it_sig->first - sig_hueco.first;
        }

        //miramos el hueco anterior
        if (it_p == mem.begin()) {
                prev_hueco.first = 0;
                prev_hueco.second = it_p->first;
        }

        else {
            map <int,Proceso>::iterator it_prev = it_p;
            --it_prev;

            prev_hueco.first = it_prev->first + it_prev->second.consultar_mem();
            prev_hueco.second = it_p->first - prev_hueco.first;
        }


        bool hay_prev_hueco = true;
        bool hay_sig_hueco = true;

        if (prev_hueco.second == 0) hay_prev_hueco = false;
        if (sig_hueco.second == 0) hay_sig_hueco = false;

        //juntar huecos

        pair<int,int> hueco; //first = primera posicion, second = tamaño, hueco que queda al eliminar el proceso que apunta it_p

        if (not hay_prev_hueco) hueco.first = it_p->first;
        else {
            hueco.first = prev_hueco.first;

            map<int,set<int>>::iterator it_h1 = huecos.find(prev_hueco.second);
            it_h1->second.erase(prev_hueco.first);
            if (it_h1->second.empty()) huecos.erase(it_h1);

        }

        if (not hay_sig_hueco) {
            hueco.second = (it_p->first + it_p->second.consultar_mem()) - hueco.first;
        }//(posición final del proceso a eliminar) - posicion inicial del nuevo hueco = tamaño del nuevo hueco
        else {
            hueco.second = (sig_hueco.first + sig_hueco.second) - hueco.first; //posicion final del siguiente hueco al proceso a ser eliminado - primera posción del nuevo hueco = tamaño del nuevo hueco

            map<int,set<int>>::iterator it_h2 = huecos.find(sig_hueco.second); //borrar siguiente hueco si existe
            it_h2->second.erase(sig_hueco.first);
            if (it_h2->second.empty()) huecos.erase(it_h2);
        }

        mem.erase(it_p);
        huecos[hueco.second].insert(hueco.first);
        procesos.erase(it);
        return true;
    }

    void Procesador::compactar_memoria() {

        bool memoria_compactada = false;
        map<int,set<int>>::iterator it_hueco = huecos.begin();
        if (it_hueco == huecos.end() or procesos.empty()) memoria_compactada = true; //si no hay huecos la memoria ya esta compactada
        else {
            memoria_compactada = huecos.size() == 1 and it_hueco->second.size() == 1 and (*(it_hueco->second.begin()) + it_hueco->first == capacidad); //si solo hay un hueco al final, entonces la memoria ya esta compactada
        }

        if (not memoria_compactada) {

            map<int,Proceso>::iterator it_mem = mem.begin(); //con el bool memoria_compactada, ya sabes que almenos hay un proceso en memoria
            int pos_final_proceso = 0;

            while (it_mem != mem.end()) {

                if (it_mem->first != pos_final_proceso) { //comprobamos si el proceso actual (el apuntado por it_mem) y el anterior ya estan juntos o no
                    mem[pos_final_proceso] = it_mem->second;//usamos la posicion final del proceso anterior al apuntado por it_mem
                    procesos[it_mem->second.consultar_id()] = pos_final_proceso;
                    pos_final_proceso += it_mem->second.consultar_mem(); //guardamos la posicion final del proceso para usarla en la siguiente iteracion
                    it_mem = mem.erase(it_mem);
                }

                else {
                    pos_final_proceso += it_mem->second.consultar_mem();
                    ++it_mem;
                }
            }


            map<int,set<int>>:: iterator it_h = huecos.begin();

            while (it_h != huecos.end()) {
                it_h = huecos.erase(it_h); //borramos todos los huecos
            }

            int tam_hueco = capacidad - pos_final_proceso;
            huecos[tam_hueco].insert(pos_final_proceso); //añadimos el hueco después de compactar memoria
        }
    }


    void Procesador::avanzar_tiempo(int t) {

        if (not mem.empty()) {

            map<int,Proceso>::iterator it = mem.begin();

            while (it != mem.end()) {
                it->second.avanzar_tiempo(t);
                map<int,Proceso>::iterator aux = it;
                ++it;
                if (aux->second.consultar_tiempo() <= 0) {
                    baja_proceso(aux->second.consultar_id());
                }
            }
        }
    }

    //Escritura


    void Procesador::escribir_procesador() {
        map<int,Proceso>::iterator it = mem.begin();
        while (it != mem.end()) {
            cout << it->first << ' ';
            it->second.escribir_proceso();
            ++it;
        }
    }

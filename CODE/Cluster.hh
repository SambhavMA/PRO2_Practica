/** @file Cluster.hh
    @brief Especificación de la clase Cluster
*/

#ifndef _CLUSTER_HH_
#define _CLUSTER_HH_

#include "Proceso.hh"
#include "Procesador.hh"
#include "Area_espera.hh"
using namespace std;

#ifndef NO_DIAGRAM
#include <iostream>
#include "BinTree.hh"
#include <map>
#endif

/** @class Cluster
    @brief Árbol binario de procesadores.

    Clase cluster que almacena varios procesadores en estructura de arbol binario, permite añadir más procesadores al conjunto, además pasar los procesos del area de espera a los procesadores disponibles cuando se precise y compactar la memoria del conjunto de procesadores.
*/

class Cluster {

private:
    /**  @brief Árbol binario con los identificadores de los procesadores, representa la estructura del cluster.
     */
	BinTree <string> cluster;

    /**  @brief Mapa de Procesadores con el identificador de los procesadores como clave.
     */

    map<string,Procesador> procesadores;

    /**  @brief Función para leer el cluster.
         @pre En la entrada tiene que estar escrita la estructura del cluster en formato adecuado.
         @post Devuelve un BinTree con los identificadores de los procesadores y también almacena los procesadores en el mapa de procesadores.
         \coste lineal respecto al tamaño del cluster.
     */
        
    BinTree<string> leer_cluster();

    /**  @brief Función para leer un cluster auxiliar.
         @pre En la entrada tiene que estar escrita la estructura del cluster en formato adecuado.
         @post Devuelve un BinTree con los identificadores de los procesadores y también almacena los procesadores en el mapa_aux de procesadores.
         \coste lineal respecto al tamaño del cluster auxiliar.
     */

    BinTree<string> leer_cluster_aux(map<string, Procesador>& mapa_aux);

    /**  @brief Imprime la estructura del "arbol".
         @pre cierto.
         @post Imprime la estructura del "arbol" ordenado en preorden y usando los paréntesis para diferenciar los distintos niveles del árbol.
         \coste lineal respecto al tamaño del cluster.
     */

    void imprimir_estructura_arbol(const BinTree<string>& arbol);

    /**  @brief Función para modificar el arbol "a".
         @pre found = true y el id_procesador es un procesador que pertenece a "a".
         @post En caso de que el procesador "id_procesador" no tenga procesos en ejecución ni procesadores auxiliares, se inserta el arbol "aux" a "a" por el procesador id_procesador, se sustituye el id_procesador por la raíz de aux.
         \coste lineal respecto al tamaño del cluster.
     */

    void modificar(const string id_procesador, BinTree<string>& a, const BinTree<string>& aux, bool& found);

    /**  @brief Función para encontrar el mejor "procesador" para insertar el proceco con id = "id_proceso".
         @pre hueco_min = -1, max_espacio = -1, nivel_procesador = -1, nivel = 0, tam_proceso y id_proceso son datos válidos de un proceso existente, a = cluster.
         @post Devuelve en "procesador" el mejor procesador para insertar un proceso en la función epc en caso de que el proceso quepa en un procesador del cluster, en caso contrario hueco_min = -1.
         \coste lineal respecto al tamaño del cluster.
         
         Sigue los siguientes criterios para buscar al mejor procesador: El que tenga el hueco mas ajustado, en caso de empate, el que tenga mas espacio libre en total, en caso de empate, el que esta más cerca de la raíz de "a", en caso de empate, el que está más a la izquierda.
     */

    void mejor_procesador(const BinTree<string>& a, int tam_proceso, int id_proceso, int& hueco_min, int& max_espacio, string& procesador, int nivel, int& nivel_procesador);
    
    /**  @brief Función para enviar un proceso al cluster.
         @pre El proceso p es un proceso válido que pertenece a la area de espera.
         @post En caso de que en el cluster haya un procesador donde quepa el proceso p, devuelve true y coloca a p en el mejor procesacor (escogido con la función privada mejor_procesador), en caso contrario devuelve false.
         \coste lineal respecto al tamaño del cluster.
     */

    bool enviar_proceso(const Proceso& p);

public:

    //Constructoras
    
    /** @brief Creadora por defecto.
        @pre cierto.
        @post Construye un Cluster vacío.
        \coste constante.
    */

    Cluster();

    /** @brief Creadora con raíz.
        @pre cierto.
        @post Construye un Cluster con un procesador.
        \coste constante.
    */

    Cluster(const Procesador& p);

    //Modificadoras

    /** @brief Modificadora que lee y añade un Cluster auxiliar en la posición del procesador, expandiendo el Cluster original.
        @pre cierto.
        @post En caso de que el procesador tenga procesos en ejecución se devuelve 2, si tiene procesadores auxiliares se devuelve 3, y si no existe se devuelve 1, en caso contrario se devuelve 0 y el Cluster auxiliar es añadido a la posición del procesador, éste último es sustituido por la raíz de c.
        \coste lineal respecto al tamaño del cluster.
    */

    int modificar_cluster(const string& id_procesador);

    /** @brief Operación que intenta añadir proceso a un procesador.
        @pre cierto.
        @post En caso de que en el procesador haya ya un proceso con el mismo identificador se devuelve 1, si no hay espacio, se devuelve 2, si no existe el procesador se retorna 3. En caso contrario se envia el proceso con id_proceso al procesador y se retorna 0.
        \coste logaritmico.
    */

    int alta_proceso_procesador(const string& id_procesador, const Proceso& p);
    
    /** @brief Operación que finaliza proceso de un procesador.
        @pre cierto.
        @post En caso de que el procesador no tenga un proceso con esa id devuelve 2, si no hay un procesador con id = id_procesador, se devuelve 1, si ninguno de los dos primeros casos se cumple, se envia el proceso con id_proceso al procesador y se retorna 0.
        \coste logaritmico.
    */

    int baja_proceso_procesador(const string& id_procesador, int id_proceso);
    
    /** @brief Compacta la memoria del id_procesador.
        @pre cierto.
        @post Devuelve false si id_procesador no existe en el cluster, en caso contrario, devuelve true y compacta la memoria del mismo. 
        \coste lineal respecto al numero de procesos.
    */

    bool compactar_memoria_procesador(const string& id_procesador);

    /** @brief Compacta la memoria de los procesadores del Clúster.
        @pre cierto.
        @post Los procesadores del Clúster tienen la memoria compactada.
        \coste lineal.
    */

    void compactar_memoria_cluster();

    /** @brief Operación que intenta enviar n procesos de la Area de espera al Cluster.
        @pre n < numero total de procesos en la area de espera.
        @post Se ha intentado colocar n procesos en el Clúster por orden de prioridad (dentro de la misma prioridad el más antiguo primero), se intenta hasta haber colocado n procesos o hasta que no queden procesos pendientes o hasta que todos los pendientes se han intentado colocar sin éxito.
        \coste lineal.
    */

    void enviar_procesos_cluster(Area_espera& a, int n);
    
    /** @brief Operación que avanza t unidades de tiempo a todos los procesos de los procesadores.
        @pre cierto.
        @post Se ha avanzado el tiempo en todos los procesos del cluster, los que ya han acabado el tiempo de ejecución se eliminan de los procesadores.
        \coste lineal respecto al numero total de procesos del cluster.
    */
    
    void avanzar_tiempo(int t);

    //Lectura y Escritura

    /** @brief Operación de Lectura del Cluster. Lee los procesadores, las conexiones entre ellos y la memoria de cada uno.
        @pre cierto..
        @post El cluster contiende los procesadores escritos en la entrada.
        \coste lineal respecto al tamaño del cluster.
    */

    void configurar_cluster();

    /** @brief Operación de escritura del cluster.
        @pre cierto.
        @post Se han escrito los procesadores del Clúster en orden creciente de identificador.
        \coste lineal respecto al tamaño del cluster y el numero de procesos.
    */

    void imprimir_procesadores_cluster();

    /** @brief Operación de escritura de la estructura del cluster.
        @pre cierto.
        @post Se ha escrito la estructura del cluster.
        \coste lineal respecto al tamaño del cluster.
    */

    void imprimir_estructura_cluster();
    
    /** @brief Operación de escritura de un procesador.
        @pre cierto.
        @post En caso de que id_procesador exista, se devuelve true y se imprime el procesador, en caso contrario se devuelve falso.
        \coste lineal respecto al tamaño del procesador "id_procesador".
    */
    
    bool imprimir_procesador(const string& id_procesador);
    
};

#endif

/** @file Procesador.hh
    @brief Especificación de la clase Procesador
*/

#ifndef _PROCESADOR_HH_
#define _PROCESADOR_HH_

#include "Proceso.hh"
using namespace std;


#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <set>
#endif

/** @class Procesador
    @brief Clase capaz de ejecutar y almacenar procesos.

    Clase capaz de almacenar o eliminar procesos en sus unidades de memoria. También permite compactar estos procesos en la posiciones de almacenamiento-
*/

class Procesador {

private:
    /**  @brief Identificador del procesador.
     */
    string id;
    /**  @brief Mapa con los huecos en la memoria del procesador, la clave es el tamaño del hueco y el set son las posiciones iniciales de los procesos con ese tamaño.
     */
    map <int, set <int>> huecos; //tam y set de pos_i
    /**  @brief Mapa que representa a la memoria, la clave es la posición inicial de los procesos en ejecución.
     */
    map <int, Proceso> mem; //pos_i y el proceso
    /**  @brief Mapa que tiene como clave el identificador de los procesos en memoria y como contenido la posición inicial del proceso con ese id.
     */
    map <int, int> procesos; //id y pos_i
    /**  @brief Entero que representa la capacidad del procesador.
     */
    int capacidad;

public:

    //Constructora
    
    /** @brief Constructora por defecto.
        @pre cierto.
        @post El resultado es un procesador con identidad = "res" y 0 posiciones de memoria.
        \coste constante.
    */

    Procesador();

    /** @brief Constructora con parametros.
        @pre id es un string de letras y números y n > 0.
        @post El resultado es un procesador con identidad = id y n posiciones de memoria, todos libres.
        \coste constante.
    */

    Procesador(string id, int n);

    //Consultoras

    /** @brief Consultora de la identidad del procesador.
        @pre cierto.
        @post Devuelve la identidad del procesador.
        \coste constante.
    */

    string consultar_id() const;
    
    /** @brief Consultora que sirve para saber si el procesador esta vacío o no.
        @pre cierto.
        @post Devuelve true si el procesador esta vacío y falso en el caso contrario.
        \coste constante.
    */
    
    bool vacio() const;
    
    /** @brief Consultora que sirve para saber si el procesador contiene un proceso con id_proceso o no.
        @pre cierto.
        @post Devuelve true si el procesador contiene un procesador con id = id_proceso y falso en el caso contrario.
        \coste logaritmico;
    */
    
    bool existe_proceso(int id_proceso) const;
    
    /** @brief Consultora del hueco más ajustado respecto a n.
        @pre cierto.
        @post Devuelve el tamaño del proceso más ajustado respecto a n.
        \coste logaritmico.
    */
    
    int hueco_mas_ajustado(int n) const;
    
    /** @brief Consultora del total de memoria libre.
        @pre cierto.
        @post Devuelve el numero total de posiciones libres en memoria.
        \coste lineal respecto al numero de huecos.
    */
    
    int mem_disponible() const;

    //Modificadoras

    /** @brief Se intenta dar de alta un proceso en el procesador.
        @pre cierto.
        @post Si hay un hueco de x posiciones de memoria donde x >= n (donde n son la memoria que ocupa el proceso p), el hueco es ocupado con esas n posiciones de memoria desde la poscion mas alta y se retorna 0. Si hay varios huecos que cumplen estas condiciones, se escoge el más ajustado con posición inicial de memoria más pequeña. Si en el procesador ya hay un proceso con el mismo identificador de p, se retorna 1. Si no hay hueco lo suficientemente grande se retorna 2
        \coste logaritmico.
    */

    int alta_proceso(const Proceso& p);

    /** @brief Finaliza proceso.
        @pre cierto.
        @post Si no existe proceso con ese identificador, la función devuelve falso, en caos contrario devuelve true y el procesador vuelve a tener libre las posiciones de memoria que ocupaba el proceso p finalizado.
        \coste logaritmico.
    */

    bool baja_proceso(int id_proceso);

    /** @brief Se compacta la memoria de un procesador.
        @pre cierto.
        @post Si hay procesos ejecutandose, se mueven las posiciones de memoria ocupadas por los mismos hacia el principio, de manera que no queden espacios vacíos entre cada proceso, éstos no se solapen y se respete el orden inicial. Devuelve cierto si existe procesador con id = id_proceso, en caso contrario vuelve falso.
        \coste lineal respecto al numero de procesos.
    */

    void compactar_memoria();
    
    /** @brief Operación que avanza t unidades de tiempo a todos los procesos del procesador.
        @pre cierto.
        @post Se avanza el tiempo a todos los procesos ejecutándose, los procesos que se han acabado se dan de baja.
        \coste constante.
    */
    
    void avanzar_tiempo(int t);

    //Escritura

    /** @brief Operación de escritura de un procesador.
        @pre cierto.
        @post Se escriben los procesos en ejecución del procesador en orden creciente de primera posición de memoria, incluye la posición y datos de cada proceso.
        \coste lineal respecto al numeor de procesos.
    */

    void escribir_procesador();

};

#endif

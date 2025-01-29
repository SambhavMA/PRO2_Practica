/** @file Prioridad.hh
    @brief Especificación de la clase Prioridad
*/

#ifndef _PRIORIDAD_HH_
#define _PRIORIDAD_HH_

#include "Proceso.hh"
using namespace std;

#ifndef NO_DIAGRAM
#include <iostream>
#include <set>
#include <list>
#endif

/** @class Prioridad
    @brief Se otorga una prioridad a un proceso para ordenarlo en la area de espera.

    La clase almacena los procesos pendientes por orden de antiguedad, las operaciones permiten otorgar prioridad a los procesos para ser guardados en orden a la Area de espera, además, cada prioridad guarda el numero de rechazos de procesos que se han intentado colocar en el cluster, así como el número de procesos enviados correctamente al cluster.
*/

class Prioridad {

private:

    /**  @brief Numero de procesos de la prioridad colocados en el cluster por la operación enviar_procesos_cluster.
     */
    int env;
    /**  @brief Numero de rechazos de procesos que se han intentado colocar en el cluster (un mismo proceso cuenta tantas veces como rechazos ha sufrido) por la operación enviar_procesos_cluster.
     */
    int rech;
    /**  @brief Lista de procesos que se usa como una cola.
     */
    list <Proceso> l;
    /**  @brief Set con los identificadores de todos los procesos de la prioridad.
     */
    set <int> procesos;

public:

    //Constructora

    /** @brief Constructora por defecto de una prioridad.
        @pre id está compuesta de sólo letras y números.
        @post Se crea prioridad vacía con identificador = id.
        \coste constante.
    */

    Prioridad();

    //Consultoras
    
    /** @brief Consultora de si la prioridad es vacio.
        @pre cierto.
        @post Devuelve true si la prioridad está vacía y false en caso contrario.
        \coste constante.
    */
    
    bool vacia() const;
    
    /** @brief Consultora del numero de procesos de la prioridad.
        @pre cierto.
        @post Devuelve el numero de procesos en la prioridad.
        \coste constante.
    */
    
    int size() const;

    /** @brief Consultora del número total de procesos rechazados de la prioridad.
        @pre cierto.
        @post Devueleve el número de rechazos totales de la prioridad.
        \coste constante.
    */

    int consultar_rech() const;

    /** @brief Consultora del número total de procesos enviados al Cluster.
        @pre cierto.
        @post Devuelve el número de envios totales de la prioridad.
        \coste constante.
    */

    int consultar_env() const;


    //Modificadoras

    /** @brief Operación que añade un nuevo proceso a la prioridad.
        @pre cierto.
        @post Se ha añadido el proceso p a la prioridad.
        \coste logaritmico.
    */

    bool alta_proceso(const Proceso& p);
    
     /** @brief La operación devuelve el nuevo proceso "p" a la prioridad.
        @pre no existe otro proceso en la prioridad con identificador igual al de "p".
        @post Se ha añadido el proceso p a la prioridad.
        \coste logaritmico.
        
        Función idéntica a alta_proceso pero no retorna nada, se usa en enviar_procesos_cluster, método de la clase Cluster.
    */
    
    void devolver_proceso(const Proceso& p);

    /** @brief Para enviar y eliminar proceso de la prioridad.
        @pre cierto.
        @post Si hay procesos pendientes, se envia y elimina el proceso que lleva más tiempo en la prioridad. Además se incrementa en uno el número de envios.
        \coste logaritmico.
    */

    Proceso baja_proceso();

    /** @brief Para incrementar en uno el número total de rechazos.
        @pre cierto.
        @post el numero de rechazos se ha incrementado en 1.
        \coste constante.
    */

    void inc_rech();
    
    /** @brief Para incrementar en uno el número total de envios.
        @pre cierto.
        @post el numero de envios se ha incrementado en 1.
        \coste constante.
    */

    
    void inc_env();

    //Escritura

    /** @brief Operación de escritura de una prioridad.
        @pre cierto.
        @post Escribe los procesos de esa prioridad por orden decreciente de antiguedad, junto con el numero de envios y el numero de rechazos.
        \coste lineal respecto al tamaño de la prioridad.
    */

    void escribir_pri();








};

#endif

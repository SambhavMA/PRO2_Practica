/** @file Area_espera.hh
    @brief Especificación de la clase Area_Espera
*/

#ifndef _AREA_ESPERA_HH_
#define _AREA_ESPERA_HH_

#include "Proceso.hh"
#include "Prioridad.hh"
using namespace std;

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#endif

/** @class Area_espera
    @brief Área en el que residen los procesos pendientes de ser ejecutados.

    La clase guarda los procesos, hasta que son enviados al Cluster a ser ejecutados en orden de prioridad.
*/

class Area_espera {

private:

    /**  @brief Mapa de prioridades que tiene como clave al id de la prioridad.
     */
    map <string, Prioridad> a_espera;

public:

    //Constructora

    /** @brief Constructora por defecto del Area de espera.
        @pre cierto.
        @post Se crea Area de espera vacía.
        \coste constante.
    */

    Area_espera();
    
    //Consultoras

    /** @brief Consultora del tamaño de la area de espera.
        @pre cierto.
        @post Se retorna el numero de prioridades del area de espera.
        \coste constante.

    */
    
    int size() const;  
    
    /** @brief Consultora del tamaño de la primera prioridad de la area.
        @pre cierto.
        @post Se retorna el numero de procesos dentro de la prioridad n de la area de espera (siguiendo el orden de menor identificador de prioridad a mayor).
        \coste lineal respecto al tamaño del area.
    */
    
    int size_pri(int n) const;  
    
    //Modificadoras

    /** @brief Operación que añade una nueva prioridad a la area de espera.
        @pre No existe prioridad p con un identificador igual a id_pri.
        @post Si ya existe una prioridad con ese identificador, devuelve falso, en caso contrario la función devuelve cierto y la area de espera se le añade una nueva prioridad vacía.
        \coste logaritmico.

    */

    bool alta_prioridad(const string& id);

    /** @brief Operación que elimina una prioridad de la area de espera.
        @pre cierto.
        @post Si no existe una prioridad con ese identificador se devuelve 1, si dicha prioridad tiene procesos pendientes, devuelve 2, en caso contrario la función devuelve 0 y a la area de espera se le elimina la prioridad.
        \coste logaritmico .
    */

    int baja_prioridad(const string& id);
    
    /** @brief Operación que añade un proceso en el area de espera con la prioridad id_pri.
        @pre cierto.
        @post Si no existe una prioridad con ese identificador devuelve 1, si ya hay un proceso con el mismo identificador que p con prioridad id_pri, se devuelve 2, en caso contrario se devuelve 0 y el programa añade un proceso pendiente con la prioridad marcada a la area de espera.
        \coste logaritmico .
    */
    
    int alta_proceso_espera(const string& id, const Proceso& p);
    
    /** @brief Operación que devuelve un proceso al area de espera.
        @pre n el area de espera existe una prioridad con el identificador =
        @post Se da de alta el proceso "p" al area de espera con prioridad "id".
        
        Básicamente hace lo mismo que alta proceso espera sin devolver ni comprobar nada, ya que se da por su puesto que la prioridad "id" existe y que no hay un proceso con la misma identidad que "p". La usamos en el método enviar_procesos_cluster en la clase Cluster.
        \coste logaritmico .
    */
    
    
    void devolver_proceso_espera(const string& id, const Proceso& p);
    
    /** @brief Operación que devuelve y elimina proceso pendiente de la area de espera.
        @pre cierto.
        @post La operación retorna y elimina el proceso más antiguo de la prioridad numero n de la area de espera (siguiendo el orden de menor identificador de prioridad a mayor), además, el parámetro string de entrada/salida pri quedará modificado con el nombre de la prioridad en la que se baja el proceso.
        \coste logaritmico .
    */
        
    Proceso baja_proceso_espera(int n, string& pri);
    
    
    
    /** @brief Operación que incrementa el numero de la prioridad con identificador "id".
        @pre cierto.
        @post Se incrementa el numero de rechazos de la prioridad con identificador "id".
        \coste constante.
    */
    
    void incrementar_rech(const string& id);
    
    /** @brief Operación que incrementa el numero de envios de la prioridad con identificador "id".
        @pre cierto.
        @post Se incrementa el numero de envios de la prioridad con identificador "id".
        \coste constante.
    */

    void incrementar_env(const string& id);

    //Escritura

    /** @brief Operación lectura del area de espera.
        @pre cierto.
        @post Se leen todas las prioridades iniciales (vacías) del area.
        \coste lineal respecto al tamaño del area.
    */
    
    void leer_area();
    
    
    /** @brief Operación escribe la prioridad en el parametro de entrada en caso de que exista.
        @pre cierto.
        @post En caso de que exista id_pri en el area se escriben los procesos pendientes de la prioridad y se devuelve true, en caso contrario devuelve falso.
        \coste lineal respecto al tamaño de la prioridad.
    */
    
    bool escribir_pri(const string& id_pri);


    /** @brief Operación escribe el area.
        @pre cierto.
        @post  Escribe todas las prioridades en orden creciente de id.
        \coste lineal respecto al tamaño del area.
    */

    void escribir_area();





};

#endif

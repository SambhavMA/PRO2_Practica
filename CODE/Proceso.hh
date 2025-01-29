/** @file Proceso.hh
    @brief Especificación de la clase Proceso
*/

#ifndef _PROCESO_HH_
#define _PROCESO_HH_

using namespace std;

#ifndef NO_DIAGRAM
#include <iostream>
#endif

/** @class Proceso
    @brief Representa el conjunto de atributos y operaciones de un Proceso.

    Todos los atributos son enteros positivos, las operaciones permiten consultar los atributos, escribirlos y avanzar el tiempo hasta que el proceso finalize.
*/

class Proceso {

private:
    /** @brief Identificador del proceso */
    int id;
    /** @brief Numero de posiciones de memoria que ocupa el proceso durante su ejecución */
    int mem;
    /** @brief Tiempo restante para que termine de ejecutarse el proceso */
    int t_ej;

public:
    //Constructoras

    /** @brief Creadora por defecto.
        @pre cierto
        @post Como resultado tenemos un Proceso con id = 0, mem = 0 y t_ej = 0.
        \coste constante.
    */

    Proceso();

    //Consultoras

    /** @brief Consultora del identificador del proceso.
        @pre cierto.
        @post Nos retorna el identificador del proceso.
        \coste constante.
    */

    int consultar_id() const;

    /** @brief Consultora de las posiciones de memoria que ocupa un proceso.
        @pre cierto.
        @post Nos retorna el numero de posiciones de memoria que ocupa un proceso.
        \coste constante.
    */

    int consultar_mem() const;

    /** @brief Consultora del tiempo restante de ejecución de un proceso.
        @pre cierto.
        @post Nos retorna el tiempo de ejecución restante de un proceso.
        \coste constante.
    */

    int consultar_tiempo() const;

    //Modificadoras

    /** @brief Avanza el tiempo del proceso.
        @pre t > 0.
        @post El t_ej del proceso disminuye t unidades de tiempo, si el t_ej llega a cero quiere decir que el proceso ha terminado.
        \coste constante.
    */

    void avanzar_tiempo(int t);

    //Lectura y Escritura
    
    /** @brief Operación de lectura.
        @pre cierto.
        @post La función devuelve el proceso escrito por el usuario.
        \coste constante.
    */

    void leer_proceso();

    /** @brief Operación de escritura.
        @pre cierto.
        @post Se han escrito los datos del proceso.
        \coste constante.
    */

    void escribir_proceso();
};

#endif








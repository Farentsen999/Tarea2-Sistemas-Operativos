#ifndef REUSABLE_BARRIER_H
#define REUSABLE_BARRIER_H

#include <pthread.h>

/**
 * @brief Estructura de la Barrera Reutilizable (Monitor)
 * * Contiene el estado compartido mínimo y las primitivas de sincronización.
 */
typedef struct {
    int count;                  // Número de hebras que han llegado en la etapa actual. [cite: 25]
    int N;                      // Número total de hebras que deben esperar. [cite: 26]
    int etapa;                  // Identificador de la etapa actual. [cite: 27]
    pthread_mutex_t mutex;      // Mutex para exclusión mutua del estado interno. [cite: 29]
    pthread_cond_t cond;        // Variable de condición para la espera condicional. [cite: 30]
} reusable_barrier_t;

/**
 * @brief Inicializa una barrera reutilizable.
 * * @param barrier Puntero a la estructura de la barrera a inicializar.
 * @param N_threads Número total de hebras que sincronizará la barrera.
 * @return 0 en caso de éxito, -1 si falla la inicialización.
 */
int reusable_barrier_init(reusable_barrier_t* barrier, int N_threads);

/**
 * @brief Bloquea a la hebra hasta que todas las N hebras hayan llegado.
 * * Es la operación fundamental (wait()).
 * * @param barrier Puntero a la estructura de la barrera.
 */
void reusable_barrier_wait(reusable_barrier_t* barrier);

/**
 * @brief Destruye la barrera reutilizable, liberando recursos.
 * * @param barrier Puntero a la estructura de la barrera.
 * @return 0 en caso de éxito, -1 si falla la destrucción.
 */
int reusable_barrier_destroy(reusable_barrier_t* barrier);

#endif // REUSABLE_BARRIER_H
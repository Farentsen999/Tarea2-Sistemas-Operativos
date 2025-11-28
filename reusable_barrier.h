#ifndef REUSABLE_BARRIER_H
#define REUSABLE_BARRIER_H

#include <pthread.h>

// struct de la Barrera Reutilizable (Monitor)
typedef struct {
    int count;                  // Numero de hebras que han llegado en la etapa actual
    int N;                      // Numero total de hebras que deben esperar
    int etapa;                  // Identificador de la etapa actual
    pthread_mutex_t mutex;      // Mutex para exclusion mutua del estado interno
    pthread_cond_t cond;        // Variable de condición para la espera condicional (evita busy-waiting)
} reusable_barrier_t;

// Inicializa una barrera reutilizable
int reusable_barrier_init(reusable_barrier_t* barrier, int N_threads);

// Funcion que bloquea hasta que todas las hebras hayan llegado a la barrera
void reusable_barrier_wait(reusable_barrier_t* barrier);

// Destruye la barrera reutilizable
int reusable_barrier_destroy(reusable_barrier_t* barrier);

#endif
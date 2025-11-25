#include "reusable_barrier.h"
#include <stdio.h>

/**
 * @brief Inicializa una barrera reutilizable.
 */
int reusable_barrier_init(reusable_barrier_t* barrier, int N_threads) {
    if (N_threads <= 0) {
        fprintf(stderr, "Error: N_threads debe ser positivo.\n");
        return -1;
    }

    // 1. Inicialización del Estado Compartido
    barrier->N = N_threads; [cite: 26]
    barrier->count = 0;     // Inicialmente nadie ha llegado. [cite: 25]
    barrier->etapa = 0;     // Inicialmente en la etapa 0. [cite: 27]

    // 2. Inicialización de Primitivas de Sincronización
    if (pthread_mutex_init(&barrier->mutex, NULL) != 0) {
        perror("Error al inicializar mutex");
        return -1;
    }
    if (pthread_cond_init(&barrier->cond, NULL) != 0) {
        perror("Error al inicializar variable de condición");
        // Si falla la condición, se destruye el mutex para evitar leaks.
        pthread_mutex_destroy(&barrier->mutex); 
        return -1;
    }
    
    return 0;
}

/**
 * @brief Operación fundamental wait() de la barrera.
 * * Implementa la lógica de exclusión mutua, espera condicional y reseteo
 * automático (reutilizabilidad).
 */
void reusable_barrier_wait(reusable_barrier_t* barrier) {
    // 1. Bloqueo para exclusión mutua del estado interno (Patrón: lock) [cite: 29, 40]
    pthread_mutex_lock(&barrier->mutex);

    // Capturar la etapa actual antes de cualquier modificación. 
    int current_etapa = barrier->etapa;

    // Modificar estado / decidir wait/broadcast [cite: 41]
    barrier->count++; // Hebra actual ha llegado. [cite: 25]

    if (barrier->count < barrier->N) {
        // La hebra no es la última. Esperar a que cambie de etapa.
        // Esperar mientras la etapa no cambie. 
        do {
            pthread_cond_wait(&barrier->cond, &barrier->mutex); [cite: 30]
        } while (current_etapa == barrier->etapa);
        
    } else {
        // La hebra es la última en llegar.
        
        // 1. Incrementar etapa (Esto permite que las hebras en wait despierten y pasen). 
        barrier->etapa++; 
        
        // 2. Resetear count para la siguiente etapa. 
        barrier->count = 0; 

        // 3. Broadcast para despertar a todas las hebras en espera. [cite: 39, 30]
        pthread_cond_broadcast(&barrier->cond);
    }
    
    // 4. Desbloqueo. (Patrón: unlock) [cite: 41]
    pthread_mutex_unlock(&barrier->mutex);
}

/**
 * @brief Destruye la barrera.
 */
int reusable_barrier_destroy(reusable_barrier_t* barrier) {
    int result = 0;
    
    // Destrucción de primitivas.
    if (pthread_mutex_destroy(&barrier->mutex) != 0) {
        perror("Error al destruir mutex");
        result = -1;
    }
    if (pthread_cond_destroy(&barrier->cond) != 0) {
        perror("Error al destruir variable de condición");
        result = -1;
    }
    
    return result;
}
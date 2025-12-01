#include "reusable_barrier.h"
#include <stdio.h>

// Inicializa un Monitor.
int reusable_barrier_init(reusable_barrier_t* barrier, int num_threads) {
    if (num_threads <= 0) {
        fprintf(stderr, "Error: num_threads debe ser positivo.\n");
        return -1;
    }

    // Inicializacion del Estado Compartido
    barrier->N = num_threads;
    barrier->count = 0;     // Inicialmente no ha llegado ninguna hebra
    barrier->etapa = 0;     // Etapa inicial

    // Inicializacion de Primitivas de Sincronizacion (mutex y variable de condicion)
    if (pthread_mutex_init(&barrier->mutex, NULL) != 0) {
        perror("Error al inicializar mutex");
        return -1;
    }
    if (pthread_cond_init(&barrier->cond, NULL) != 0) {
        perror("Error al inicializar variable de condicion");
        // Si falla la condición, se destruye el mutex para evitar fugas de memoria (memory leaks)
        pthread_mutex_destroy(&barrier->mutex); 
        return -1;
    }
    return 0;
}

// Operacion wait() de la barrera
void reusable_barrier_wait(reusable_barrier_t* barrier) {
    // Bloqueo para exclusion mutua del estado interno (lock)
    pthread_mutex_lock(&barrier->mutex);

    // Capturar la etapa actual antes de cualquier cambio del estado 
    int current_etapa = barrier->etapa;


    barrier->count++; // LLego una nueva hebra

    // Bloque que maneja la logica de la barrera reutilizable (si aun no llega la ultima hebra espera o si ya llego hace el broadcast)
    if (barrier->count < barrier->N) {
        // La hebra no es la ultima. Esperar a que cambie de etapa
        // Esperar mientras la etapa no cambie. 
        while (current_etapa == barrier->etapa) {
        pthread_cond_wait(&barrier->cond, &barrier->mutex);
    }
        
    } else {
        // LLego la ultima hebra
        
        // 1. Se incrementa etapa para indicar cambio a una nueva etapa
        barrier->etapa++; 
        
        // 2. Resetear count para la siguiente etapa
        barrier->count = 0; 

        // 3. Broadcast para despertar a todas las hebras en espera
        pthread_cond_broadcast(&barrier->cond);
    }
    
    // Desbloqueo. (unlock)
    pthread_mutex_unlock(&barrier->mutex);
}

// Destruye la barrera
int reusable_barrier_destroy(reusable_barrier_t* barrier) {
    int result = 0;
    
    // Destruccion de las primitivas (mutex y variable de condicion)
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
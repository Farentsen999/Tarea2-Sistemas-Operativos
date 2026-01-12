#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "reusable_barrier.h"

// Estructura para pasar argumentos a cada hebra

typedef struct {
    int id;
    int etapas;
    reusable_barrier_t* barrera;
} thread_arg_t;

void* worker(void* args) {
    thread_arg_t* arg = (thread_arg_t*) args;
    int id = arg->id;
    int etapas = arg->etapas;
    reusable_barrier_t* barrera = arg->barrera;


    for (int e = 0; e < etapas; e++) {
        // a) Realiza trabajo simulado (usleep con aleatorio)
        int tiempo = rand() % 500000; // Entre 0 y 0.5 segundos
        usleep(tiempo);
        // b) Imprime antes de esperar
        printf("[%d] esperando en etapa %d\n", id, e);
        // c) Llama a wait()
        reusable_barrier_wait(barrera);
        // d) Imprime después de pasar
        printf("[%d] paso barrera en etapa %d\n", id, e);

    }
    return NULL;
}

int main(int argc, char* argv[]) {
    // Valores por defecto 
    int N = 5;
    int E = 4;
    //Lectura de parámetros de línea de comandos 
    if (argc > 1) N = atoi(argv[1]);
    if (argc > 2) E = atoi(argv[2]);

    if (N <= 0 || E <= 0) {
        fprintf(stderr, "Error: N y E deben ser positivos.\n");
        return 1;
    }

    printf("Iniciando prueba con %d hebras y %d etapas.\n", N, E);
    // Inicializar semilla aleatoria
    srand(time(NULL));
    // Inicializar la barrera
    reusable_barrier_t barrera;
    if (reusable_barrier_init(&barrera, N) != 0) {
        return 1;
    }
    pthread_t hebras[N];

    thread_arg_t args[N];
    // Crear las hebras

    for (int i = 0; i < N; i++) {
        args[i].id = i;
        args[i].etapas = E;
        args[i].barrera = &barrera;

        if (pthread_create(&hebras[i], NULL, worker, &args[i]) != 0) {
            perror("Error creando hebra");
            return 1;
        }

    }
    // Esperar a las hebras
    for (int i = 0; i < N; i++) {

        pthread_join(hebras[i], NULL);

    }

    // Destruir la barrera
    reusable_barrier_destroy(&barrera);
    printf("Todas las etapas finalizadas correctamente.\n");
    return 0;

} 

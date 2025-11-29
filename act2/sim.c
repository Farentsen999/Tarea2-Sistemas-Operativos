#include "sim.h"
#include <stdio.h>
#include <descomponer.h>
#include <obtener_direccion_fisica.h>


void simulador(){
    int puntero_reloj = 0;





}

int buscar_marco_libre(Marco *memoria_fisica, int n_marcos){
    for (int i = 0; i < n_marcos; i++)
    {
        if (memoria_fisica[i].pagina_virtual == -1)
        {
            return i;
        }        
    }
    return -1; // NO HAY MARCOS LIBRES
}


int algoritmo_reloj(Marco *memoria_fisica, int n_marcos, int *puntero_reloj){
    while (1) {
        if (memoria_fisica[*puntero_reloj].bit_referencia == 0){
            int victima = *puntero_reloj;
            *puntero_reloj = (*puntero_reloj + 1) % n_marcos;
            return victima;
        }
        // SEGUNDA OPORTUNIDAD SI ES 1
        memoria_fisica[*puntero_reloj].bit_referencia = 0;
        *puntero_reloj = (*puntero_reloj + 1) % n_marcos;
    }
}

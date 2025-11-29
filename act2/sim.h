#ifndef SIM_H
#define SIM_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int marco_fisico; 
    int valid;       // 1 válido, 0 inválido
    int dirty;       // 1 modificado
    int referencia;   // 1 referenciado recientemente
} PageTableEntry;

typedef struct {
    int pagina_virtual; 
    int bit_referencia;
} Marco;

void inicializar_estructuras(PageTableEntry **tabla_paginas, Marco **memoria_fisica, int n_marcos, int num_paginas_virtuales);


#endif

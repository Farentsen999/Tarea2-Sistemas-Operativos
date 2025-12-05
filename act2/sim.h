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
void simulador(const char *archivo_traza, int n_marcos, int tam_marco, int verbose);
int calcular_page_bits(int tam_marco);
unsigned int parsear_direccion(const char *str);
unsigned int traducir_direccion(unsigned int dv, PageTableEntry *tabla_paginas, Marco *memoria_fisica, int n_marcos, int page_bits, int *puntero_reloj, int *fallo, int verbose, int num_paginas_virtuales);
int buscar_marco_libre(Marco *memoria_fisica, int n_marcos);
int algoritmo_reloj(Marco *memoria_fisica, int n_marcos, int *puntero_reloj);

#endif

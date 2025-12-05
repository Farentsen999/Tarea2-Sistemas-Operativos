#include "sim.h"
#include <stdlib.h>
#include <stdio.h>

void inicializar_estructuras(PageTableEntry **tabla_paginas, Marco **memoria_fisica, int n_marcos, int num_paginas_virtuales) {

    *tabla_paginas = (PageTableEntry *)malloc(sizeof(PageTableEntry) * num_paginas_virtuales);


    for (int i = 0; i < num_paginas_virtuales; i++) {
        (*tabla_paginas)[i].marco_fisico = -1; // No asignado
        (*tabla_paginas)[i].valid = 0;         // No válido
        (*tabla_paginas)[i].dirty = 0;
        (*tabla_paginas)[i].referencia = 0;
    }

    *memoria_fisica = (Marco *)malloc(sizeof(Marco) * n_marcos);

    for (int i = 0; i < n_marcos; i++) {
        (*memoria_fisica)[i].pagina_virtual = -1; 
    }
}

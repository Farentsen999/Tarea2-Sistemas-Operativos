#include <stdio.h>

unsigned int obtener_direccion_fisica(unsigned int marco, unsigned int offset, unsigned int page_bits){
    return (marco << page_bits) | offset;
}
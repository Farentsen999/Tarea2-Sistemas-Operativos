all: sim barrera

# Parte I: Barrera
# Se debe compilar el main (barrera.c) junto con la implementación del monitor (reusable_barrier.c)
barrera: barrera.c reusable_barrier.c
	gcc -o barrera barrera.c reusable_barrier.c -pthread

clean:
	rm -f sim barrera
all: sim barrera

# Parte II: Simulador
sim: sim.c descomponer.c inicializar_estructuras.c obtener_direccion_fisica.c
	gcc sim.c descomponer.c inicializar_estructuras.c obtener_direccion_fisica.c -o sim

clean:
	rm -f sim barrera
# Trabajo práctico 2 : PDyTR

## Como ejecutar los experimentos

### Ejercicio 4) a)

Para correr el experimento:

```bash
cd ./pdytr/punto4-a	# Estando ubicados en la carpeta donde se encuentra el proyecto
vagrant up

```

Si bien se muestran los resultados por salida en la terminal, se puede entrar a la máquina cliente para buscar los .txt con las mediciones
Estando en el mismo directorio que antes, ejecutamos:

```bash
vagrant ssh vm2
```

Dentro de la máquina virtual, los resultados se guardan en la carpeta correspondiente al experimento ejecutado, que se encuentran en /home/pdytr
Para ver los resultados del ejercicio 2 hacemos:

```bash
# Dentro de la máquina virtual...
cd /home/pdytr/punto2
cat write_time.txt	# Para ver los tiempos de write()
cat read_time.txt	# Para ver los tiempos de read()
cat prom_w.txt		# Para ver el promedio de tiempos de write()
cat prom_r.txt		# Para ver el promedio de tiempos de read()
```

Para ver los resultados del punto 3 hacemos lo siguiente:
```bash
# Dentro de la misma máquina virtual...
cd /home/pdytr/punto3
cat pingpong.txt	# Para ver los tiempos del RTT
cat time_pp.txt		$ Para ver los tiempos promedio del RTT
```

### Ejercicio 4) b)

Para correr el experimento:

```bash
cd ./pdytr/punto4-b	# Estando ubicados en la carpeta donde se encuentra el proyecto
./script.sh

```

Si bien se muestran los resultados por salida en la terminal, se puede entrar a la máquina cliente para buscar los .txt con las mediciones
Estando en el mismo directorio que antes, ejecutamos:

```bash
vagrant ssh vm3
```

Dentro de la máquina virtual, los resultados se guardan en la carpeta correspondiente al experimento ejecutado, que se encuentran en /home/pdytr
Para ver los resultados del ejercicio 2 hacemos:

```bash
# Dentro de la máquina virtual...
cd /home/pdytr/punto2
cat write_time.txt	# Para ver los tiempos de write()
cat read_time.txt	# Para ver los tiempos de read()
cat prom_w.txt		# Para ver el promedio de tiempos de write()
cat prom_r.txt		# Para ver el promedio de tiempos de read()
```

Para ver los resultados del punto 3 hacemos lo siguiente:
```bash
# Dentro de la misma máquina virtual...
cd /home/pdytr/punto3
cat pingpong.txt	# Para ver los tiempos del RTT
cat time_pp.txt		$ Para ver los tiempos promedio del RTT
```

## Posibles errores y posibles soluciones

### Error porque la máquina está usando kvm en modo root
Ejecutar en la terminal:
```bash
sudo rmmod kvm_intel
sudo rmmod kvm
```

### El puerto ya tiene bindeado un proceso
Si los puertos en uso son los 6901 y 6902, entonces ejecutar:
```bash
sudo fuser -k 6901/tcp
sudo fuser -k 6902/tcp

# Para este punto, ya tendrían que haberse matado a los procesos que estaban ocupando los puertos

sudo lsof -iTCP:6901 -sTCP:LISTEN
sudo lsof -iTCP:6902 -sTCP:LISTEN	# Si no retornan nada, felicidades, problema solucionado :D
```

### Cualquier otro tipo de error relacionado con Vagrant
Lo mejor es volver a levantar las máquinas de nuevo:
```bash
# Estando en el directorio donde se encuentra el vagrant file
vagrant destroy
vagrant up # Para el ejercicio 4) a)
./script.sh # Para el ejercicio 4) b)
```
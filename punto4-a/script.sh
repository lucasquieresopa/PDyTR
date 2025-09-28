#!/bin/bash

# vagrant up --provision

# Ejecucion del punto 4-a

vagrant ssh vm1 -c "/opt/pdytr/punto2/servidor 6901" &

# Esperar en VM1 hasta que el puerto esté en LISTEN (no consume conexiones)
echo "Esperando a que el servidor escuche en 6901..."
until vagrant ssh vm1 -c "ss -lnt 'sport = :6901' | grep -q LISTEN" >/dev/null 2>&1; do
  sleep 0.5
done

# Recién ahora lanzar el cliente en VM2
echo "Servidor listo, arrancando cliente"

vagrant ssh vm2 -c "/opt/pdytr/punto2/cliente 192.168.56.11 6901"

# Ejecucion del punto 4-b

vagrant ssh vm1 -c "/opt/pdytr/punto3/servidor 6902" &

# Esperar en VM1 hasta que el puerto esté en LISTEN
echo "Esperando a que el servidor escuche en 6902..."
until vagrant ssh vm1 -c "ss -lnt 'sport = :6902' | grep -q LISTEN" >/dev/null 2>&1; do
  sleep 0.5
done

# Recién ahora lanzar el cliente en VM2
echo "Servidor listo, arrancando cliente"

vagrant ssh vm2 -c "/opt/pdytr/punto3/cliente 192.168.56.11 6902"
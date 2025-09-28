#!/bin/bash

# Inicializo la maquina cliente (vm3)

vagrant up --provision

# Ejecución del punto 2

cd ..
cd punto2
gcc -o servidor server-full.c
./servidor 6911 &

# Esperar al host hasta que el puerto esté en LISTEN (no consume conexiones)
echo "Esperando a que el servidor escuche en 6911..."
until ss -lnt 'sport = :6911' | grep -q LISTEN >/dev/null 2>&1; do
  sleep 0.5
done

cd ..
cd punto4-b
vagrant ssh vm3 -c "/home/pdytr/punto2/cliente 10.0.2.2 6911"

# Ejecución del punto 3

cd ..
cd punto3
gcc -o servidor server3.c
./servidor 6912 &

# Esperar al host hasta que el puerto esté en LISTEN (no consume conexiones)
echo "Esperando a que el servidor escuche en 6912..."
until ss -lnt 'sport = :6912' | grep -q LISTEN >/dev/null 2>&1; do
  sleep 0.5
done

cd ..
cd punto4-b
vagrant ssh vm3 -c "/home/pdytr/punto3/cliente 10.0.2.2 6912"

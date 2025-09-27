#!/bin/bash

# Dejo ejecutando el punto 2

cd ..
cd punto2
gcc -o servidor server-full.c
./servidor 6901 &

# Dejo ejecutando el punto 3

cd ..
cd punto3
gcc -o servidor server3.c
./servidor 6902 &

# Levanto la máquina que va a ejecutar el cliente

cd punto4-b
vagrant up

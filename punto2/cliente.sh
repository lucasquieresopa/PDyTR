#!/bin/bash

while true; do
		if nc -zv 192.168.56.11 6901; then
			echo "Cliente : Punto 2, el servidor está en escucha por el puerto 6901"
			break;
		fi
		sleep 1
	done

# Ejecucion punto 2 por parte del cliente
cd /opt/pdytr/punto2
gcc -o cliente client-full.c
./cliente 192.168.56.11 6901

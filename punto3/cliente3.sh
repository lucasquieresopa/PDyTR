#!/bin/bash

while true; do
				if nc -zv 192.168.56.11 6902; then
					echo "PUNTO 3: CLIENTE" 
					break;
				fi
				sleep 1
			done
# Ejecucion punto 3
cd /home/pdytr/punto3
gcc -o cliente client3.c
./cliente 192.168.56.11 6902

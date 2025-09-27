#!/bin/bash

while true; do
				if netstat -tuln | grep :6901; then
					echo "PUNTO 2: CLIENTE" 
					break;
				fi
			done
			
			# Ejecucion punto 2
			cd /opt/pdytr/punto2
			gcc -o cliente client-full.c
			./cliente 192.168.56.11 6901


#!/bin/bash

# Ejecucion punto 2
cd /opt/pdytr/punto2/
gcc -o cliente client-full.c
./cliente 192.168.56.11 6901 > /opt/pdytr/punto2/resultados-punto2.txt
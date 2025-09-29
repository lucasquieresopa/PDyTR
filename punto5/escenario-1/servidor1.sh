#!/bin/bash


echo "#### Servidor : Ejecutando servidor1.sh ####"
cd /home/pdytr/punto5/escenario-1
gcc -o servidor server-full.c
nohup ./servidor 6901 &

#!/bin/bash


echo "#### Servidor : Ejecutando servidor3.sh ####"
cd /home/pdytr/punto5/escenario-3
gcc -o servidor server-full.c
nohup ./servidor 6903 &

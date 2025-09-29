#!/bin/bash


echo "#### Servidor : Ejecutando servidor4.sh ####"
cd /home/pdytr/punto5/escenario-4
gcc -o servidor server-full.c
nohup ./servidor 6904 &

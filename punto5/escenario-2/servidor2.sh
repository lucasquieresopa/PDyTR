#!/bin/bash


echo "#### Servidor : Ejecutando servidor2.sh ####"
cd /home/pdytr/punto5/escenario-2
gcc -o servidor server-full.c
nohup ./servidor 6902 &

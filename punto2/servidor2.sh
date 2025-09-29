#!/bin/bash


echo "#### Servidor : Ejecutando servidor2.sh ####"
cd /home/pdytr/punto2
gcc -o servidor server-full.c
nohup ./servidor 6901 &

#!/bin/bash

echo "#### Servidor : Ejecutando servidor3.sh ####"
cd /home/pdytr/punto3
sudo gcc -o servidor server3.c
nohup ./servidor 6902 &

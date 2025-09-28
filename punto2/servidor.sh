#!/bin/bash

# Ejecucion punto 2
echo "PUNTO 2: SERVIDOR" 
cd /opt/pdytr/punto2
gcc -o servidor server-full.c
nohup ./servidor 6901 > /home/vagrant/servidor_6901.log 2>&1 &

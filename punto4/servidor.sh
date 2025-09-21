#!/bin/bash

# Ejecucion punto 2
cd /opt/pdytr/punto2/
gcc -o servidor server-full.c
sudo bash servidor 6901

# Ejecucion punto 3
cd /opt/pdytr/punto3/
gcc -o servidor server3.c
sudo bash servidor 192.168.56.11 6901
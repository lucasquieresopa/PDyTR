#!/bin/bash

# Ejecucion punto 2
cd /opt/pdytr/punto2/
gcc -o cliente client-full.c
sudo bash cliente 192.168.56.11 6901

# Ejecucion punto 3
cd /opt/pdytr/punto3/
gcc -o cliente clien3.c
sudo bash cliente 192.168.56.11 6901
#!/bin/bash

cd /home/pdytr/punto2
gcc -o cliente client-full.c

while true; do
    ./cliente 192.168.56.11 6902
    rc=$?
    if [ $rc -eq 0 ]; then
        echo "PUNTO 2: CLIENTE" 
        break
    fi
    echo "CLIENTE: fallo al conectar. PERO NO ME RENDIRE! ESA CONEXION SE HARA DEMONIOS"
    sleep 1
done

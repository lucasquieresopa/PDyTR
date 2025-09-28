#!/bin/bash

cd /home/pdytr/punto3
gcc -o cliente client3.c

while true; do
    ./cliente 192.168.56.11 6902
    rc=$?
    if [ $rc -eq 0 ]; then
        echo "PUNTO 3: CLIENTE" 
        break
    fi
    echo "CLIENTE: fallo al conectar. PERO NO ME RENDIRE! ESA CONEXION SE HARA DEMONIOS"
    sleep 1
done

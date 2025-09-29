#!/bin/bash

cd /home/pdytr/punto2
gcc -o cliente client-full.c

while true; do
    ./cliente 10.0.2.2 6901
    rc=$?
    if [ $rc -eq 0 ]; then
        echo "#### Cliente : Punto 2, conexión exitosa ####"
        break
    fi
    echo "CLIENTE: fallo al conectar. PERO NO ME RENDIRE! ESA CONEXION SE HARA DEMONIOS"
    sleep 1
done

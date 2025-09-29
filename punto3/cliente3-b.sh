#!/bin/bash

cd /home/pdytr/punto3
gcc -o cliente client3.c

while true; do
    ./cliente 10.0.2.2 6902
    rc=$?
    if [ $rc -eq 0 ]; then
        echo "#### Cliente : Punto 3, conexión exitosa ####"
        break
    fi
    echo "CLIENTE: fallo al conectar. PERO NO ME RENDIRE! ESA CONEXION SE HARA DEMONIOS"
    sleep 1
done
